//! Paths at the binding boundary: Rust APIs take `impl AsRef<Path>`; shims get
//! UTF-8 strings.

use std::path::Path;

use crate::{Error, ErrorKind};

/// `path` as UTF-8 for a shim; otherwise [`ErrorKind::Wrong`].
pub fn to_utf8(path: &Path) -> Result<&str, Error> {
    path.to_str()
        .ok_or_else(|| Error::new(ErrorKind::Wrong, format!("{} is not valid UTF-8", path.display())))
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn utf8_paths_pass_through() {
        assert_eq!(to_utf8(Path::new("/tmp/données/file.txt")).unwrap(), "/tmp/données/file.txt");
    }

    #[test]
    fn non_utf8_paths_are_wrong() {
        use std::os::unix::ffi::OsStrExt;
        let path = Path::new(std::ffi::OsStr::from_bytes(b"/tmp/\xff"));
        assert_eq!(to_utf8(path).unwrap_err().kind(), ErrorKind::Wrong);
    }
}
