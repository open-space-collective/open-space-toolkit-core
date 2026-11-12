//! Open Space Toolkit ▸ Core, built statically for the `ostk-*` crates, and what
//! they share: [`Error`], [`Unique`], [`filesystem`], and C++ helpers in
//! `include/ostk_rs/core/`.

pub mod container;
mod error;
pub mod filesystem;
#[cfg(test)]
mod test_support;
mod unique;

pub use error::{Error, ErrorKind, StackTrace};
pub use unique::Unique;
