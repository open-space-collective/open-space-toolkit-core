//! [`Unique`], the owner of an OSTK object.

use std::fmt;
use std::ops::Deref;
use std::pin::Pin;

use cxx::memory::UniquePtrTarget;
use cxx::UniquePtr;

/// Owner of an OSTK object on the C++ heap (OSTK's `Unique<T>`). Derefs to `T`.
///
/// ```ignore
/// let mut dictionary: Unique<Dictionary> = Dictionary::empty();
/// dictionary.pin_mut().insert("key", &Object::integer(1))?; // mutation
/// let value: &Object = dictionary.get("key")?;               // reads use &T
/// ```
pub struct Unique<T: UniquePtrTarget>(UniquePtr<T>);

impl<T: UniquePtrTarget> Unique<T> {
    /// For binding code. Panics if `ptr` is null.
    #[doc(hidden)]
    pub fn from_ffi(ptr: UniquePtr<T>) -> Self {
        assert!(!ptr.is_null(), "OSTK binding returned a null object");
        Unique(ptr)
    }

    /// For mutating methods (`self: Pin<&mut T>`): Rust may not move C++ objects.
    pub fn pin_mut(&mut self) -> Pin<&mut T> {
        self.0.pin_mut()
    }
}

impl<T: UniquePtrTarget> Deref for Unique<T> {
    type Target = T;

    fn deref(&self) -> &T {
        self.0.as_ref().unwrap()
    }
}

impl<T: UniquePtrTarget> AsRef<T> for Unique<T> {
    fn as_ref(&self) -> &T {
        self
    }
}

impl<T: UniquePtrTarget> std::borrow::Borrow<T> for Unique<T> {
    fn borrow(&self) -> &T {
        self
    }
}

/// `for item in &unique` (`for` loops don't deref).
impl<'a, T: UniquePtrTarget> IntoIterator for &'a Unique<T>
where
    &'a T: IntoIterator,
{
    type Item = <&'a T as IntoIterator>::Item;
    type IntoIter = <&'a T as IntoIterator>::IntoIter;

    fn into_iter(self) -> Self::IntoIter {
        (**self).into_iter()
    }
}

impl<T: UniquePtrTarget + PartialEq> PartialEq for Unique<T> {
    fn eq(&self, other: &Unique<T>) -> bool {
        **self == **other
    }
}

impl<T: UniquePtrTarget + PartialEq> PartialEq<T> for Unique<T> {
    fn eq(&self, other: &T) -> bool {
        **self == *other
    }
}

impl<T: UniquePtrTarget + fmt::Display> fmt::Display for Unique<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt::Display::fmt(&**self, f)
    }
}

impl<T: UniquePtrTarget + fmt::Debug> fmt::Debug for Unique<T> {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        fmt::Debug::fmt(&**self, f)
    }
}
