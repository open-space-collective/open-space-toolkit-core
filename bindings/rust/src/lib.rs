//! Open Space Toolkit ▸ Core, built statically for the `ostk-*` crates, and what
//! they share: [`Error`], [`filesystem`], and C++ helpers in
//! `include/ostk_rs/core/`.

mod error;
pub mod filesystem;
#[cfg(test)]
mod test_support;

pub use error::{Error, ErrorKind, StackTrace};
