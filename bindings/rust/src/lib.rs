//! Open Space Toolkit ▸ Core, built statically for the `ostk-*` crates, and the
//! [`Error`] type they all return.

mod error;

pub use error::{Error, ErrorKind, StackTrace};
