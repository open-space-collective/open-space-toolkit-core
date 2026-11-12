//! OSTK errors, decoded from `cxx_exceptions.hpp`.

use std::ffi::c_void;
use std::fmt;

/// Separates kind, message and stack trace (see `cxx_exceptions.hpp`).
const SEPARATOR: char = '\u{1f}';

/// The kind of an OSTK error, mirroring `ostk::core::error`.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
#[non_exhaustive]
pub enum ErrorKind {
    /// `runtime::Undefined`
    Undefined,
    /// `runtime::Wrong`
    Wrong,
    /// `runtime::ToBeImplemented`
    ToBeImplemented,
    /// Any other `RuntimeError`
    Runtime,
    /// A non-OSTK `std::exception`
    Std,
    /// Anything else
    Unknown,
}

impl ErrorKind {
    fn from_tag(tag: &str) -> Option<Self> {
        Some(match tag {
            "undefined" => ErrorKind::Undefined,
            "wrong" => ErrorKind::Wrong,
            "to_be_implemented" => ErrorKind::ToBeImplemented,
            "runtime" => ErrorKind::Runtime,
            "std" => ErrorKind::Std,
            "unknown" => ErrorKind::Unknown,
            _ => return None,
        })
    }
}

/// An OSTK error: its kind, message and, for OSTK's own errors, the stack trace
/// where it was thrown. `Display` shows the message; `Debug` adds the trace.
#[derive(Clone)]
pub struct Error {
    kind: ErrorKind,
    message: String,
    stack_trace: Option<StackTrace>,
}

impl Error {
    pub fn new(kind: ErrorKind, message: impl Into<String>) -> Self {
        Self { kind, message: message.into(), stack_trace: None }
    }

    pub fn kind(&self) -> ErrorKind {
        self.kind
    }

    pub fn message(&self) -> &str {
        &self.message
    }

    pub fn stack_trace(&self) -> Option<&StackTrace> {
        self.stack_trace.as_ref()
    }

    fn decode(what: &str) -> Self {
        let mut parts = what.splitn(3, SEPARATOR);
        let (tag, message, trace) = (parts.next(), parts.next(), parts.next());
        match (tag.and_then(ErrorKind::from_tag), message) {
            (Some(kind), Some(message)) => Self {
                kind,
                message: message.to_string(),
                stack_trace: trace.filter(|t| !t.is_empty()).map(|t| StackTrace(t.to_string())),
            },
            // Not from the hook (shouldn't happen): keep the whole text.
            _ => Error::new(ErrorKind::Unknown, what),
        }
    }
}

impl From<cxx::Exception> for Error {
    fn from(exception: cxx::Exception) -> Self {
        Error::decode(exception.what())
    }
}

/// Compares kind and message.
impl PartialEq for Error {
    fn eq(&self, other: &Self) -> bool {
        self.kind == other.kind && self.message == other.message
    }
}

impl Eq for Error {}

impl fmt::Display for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.message)
    }
}

impl fmt::Debug for Error {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "{:?}: {}", self.kind, self.message)?;
        if let Some(trace) = &self.stack_trace {
            write!(f, "\n\nOSTK stack trace:\n{trace}")?;
        }
        Ok(())
    }
}

impl std::error::Error for Error {}

/// OSTK's stack trace, captured where the error was thrown (C++ and Rust
/// frames). `Display` names frames that OSTK could only print as addresses.
#[derive(Clone)]
pub struct StackTrace(String);

impl StackTrace {
    /// The trace as OSTK printed it.
    pub fn raw(&self) -> &str {
        &self.0
    }
}

impl fmt::Display for StackTrace {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        for line in self.0.lines() {
            writeln!(f, "{}", resolve_frame(line).unwrap_or_else(|| line.to_string()))?;
        }
        Ok(())
    }
}

impl fmt::Debug for StackTrace {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt::Display::fmt(self, f)
    }
}

/// `" 3# 0x00006146CCE2FFCD in /path/bin"` → `" 3# crate::function at file.rs:12"`.
fn resolve_frame(line: &str) -> Option<String> {
    let (index, rest) = line.split_once("# ")?;
    let address = rest.strip_prefix("0x")?.split_whitespace().next()?;
    let address = usize::from_str_radix(address, 16).ok()?;
    let mut resolved = None;
    backtrace::resolve(address as *mut c_void, |symbol| {
        if let (None, Some(name)) = (&resolved, symbol.name()) {
            resolved = Some(match (symbol.filename(), symbol.lineno()) {
                (Some(file), Some(line)) => format!("{index}# {name:#} at {}:{line}", file.display()),
                _ => format!("{index}# {name:#}"),
            });
        }
    });
    resolved
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn kinds_parse_from_their_tags() {
        for (tag, kind) in [
            ("undefined", ErrorKind::Undefined),
            ("wrong", ErrorKind::Wrong),
            ("to_be_implemented", ErrorKind::ToBeImplemented),
            ("runtime", ErrorKind::Runtime),
            ("std", ErrorKind::Std),
            ("unknown", ErrorKind::Unknown),
        ] {
            assert_eq!(ErrorKind::from_tag(tag), Some(kind));
        }
        assert_eq!(ErrorKind::from_tag("nope"), None);
    }

    #[test]
    fn decodes_kind_message_and_trace() {
        let error = Error::decode("wrong\u{1f}{x} is wrong.\u{1f} 0# f in lib\n");
        assert_eq!((error.kind(), error.message()), (ErrorKind::Wrong, "{x} is wrong."));
        assert_eq!(error.stack_trace().unwrap().raw(), " 0# f in lib\n");
        assert!(Error::decode("std\u{1f}bad alloc\u{1f}").stack_trace().is_none());
        assert_eq!(Error::decode("garbage").kind(), ErrorKind::Unknown);
    }

    #[test]
    fn stack_trace_names_address_only_frames() {
        // Frames are return addresses, so point inside the function.
        let address = resolve_frame as fn(&str) -> Option<String> as usize + 1;
        let trace = StackTrace(format!(" 0# 0x{address:016X} in bin\n 1# named in bin\n"));
        let shown = trace.to_string();
        assert!(shown.contains("resolve_frame"), "{shown}");
        assert!(shown.contains(" 1# named in bin"), "{shown}");
    }
}
