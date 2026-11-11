use std::borrow::Borrow;
use std::fmt;
use std::ops::Index;
use std::pin::Pin;

use super::ffi::{self, Dictionary, Object};
use super::object::{format_choice, Format};
use crate::{Error, Unique};

impl Dictionary {
    pub fn empty() -> Unique<Dictionary> {
        Unique::from_ffi(ffi::dictionary_empty())
    }

    /// JSON or YAML; `None` detects the format.
    pub fn parse(text: &str, format: Option<Format>) -> Result<Unique<Dictionary>, Error> {
        Ok(Unique::from_ffi(ffi::dictionary_parse(text, format_choice(format))?))
    }

    /// OSTK copies `value`. Errors on an empty or existing key (no overwrite).
    pub fn insert(self: Pin<&mut Self>, key: &str, value: &Object) -> Result<(), Error> {
        Ok(ffi::dictionary_insert(self, key, value)?)
    }

    pub fn len(&self) -> usize {
        ffi::dictionary_len(self)
    }

    pub fn is_empty(&self) -> bool {
        self.len() == 0
    }

    pub fn contains_key(&self, key: &str) -> bool {
        ffi::dictionary_contains(self, key)
    }

    /// Errors if there's no value for `key`.
    pub fn get(&self, key: &str) -> Result<&Object, Error> {
        Ok(ffi::dictionary_get(self, key)?)
    }

    /// Borrowed entries, in insertion order.
    pub fn iter(&self) -> Iter<'_> {
        Iter { dictionary: self, index: 0, len: self.len() }
    }

    pub fn keys(&self) -> impl ExactSizeIterator<Item = &str> + '_ {
        self.iter().map(|(key, _)| key)
    }

    pub fn values(&self) -> impl ExactSizeIterator<Item = &Object> + '_ {
        self.iter().map(|(_, value)| value)
    }
}

/// Entries of a [`Dictionary`], in insertion order.
pub struct Iter<'a> {
    dictionary: &'a Dictionary,
    index: usize,
    len: usize,
}

impl<'a> Iterator for Iter<'a> {
    type Item = (&'a str, &'a Object);

    fn next(&mut self) -> Option<Self::Item> {
        if self.index == self.len {
            return None;
        }
        let key = ffi::dictionary_key_at(self.dictionary, self.index);
        let value = ffi::dictionary_value_at(self.dictionary, self.index);
        self.index += 1;
        Some((key.to_str().expect("dictionary keys are UTF-8"), value))
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        (self.len - self.index, Some(self.len - self.index))
    }
}

impl ExactSizeIterator for Iter<'_> {}

impl<'a> IntoIterator for &'a Dictionary {
    type Item = (&'a str, &'a Object);
    type IntoIter = Iter<'a>;

    fn into_iter(self) -> Iter<'a> {
        self.iter()
    }
}

/// `collect()` `(key, value)` pairs. Panics on an empty or repeated key.
impl<K: AsRef<str>, V: Borrow<Object>> FromIterator<(K, V)> for Unique<Dictionary> {
    fn from_iter<I: IntoIterator<Item = (K, V)>>(entries: I) -> Self {
        let mut dictionary = Dictionary::empty();
        for (key, value) in entries {
            let key = key.as_ref();
            dictionary
                .pin_mut()
                .insert(key, value.borrow())
                .unwrap_or_else(|e| panic!("dictionary key {key:?}: {e}"));
        }
        dictionary
    }
}

/// Panics if there's no value for `key`; see [`Dictionary::get`].
impl Index<&str> for Dictionary {
    type Output = Object;

    fn index(&self, key: &str) -> &Object {
        self.get(key).unwrap_or_else(|e| panic!("dictionary[{key:?}]: {e}"))
    }
}

impl PartialEq for Dictionary {
    fn eq(&self, other: &Dictionary) -> bool {
        ffi::dictionary_equals(self, other)
    }
}

/// JSON.
impl fmt::Display for Dictionary {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&ffi::dictionary_to_string(self))
    }
}

impl fmt::Debug for Dictionary {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.debug_map().entries(self.iter()).finish()
    }
}
