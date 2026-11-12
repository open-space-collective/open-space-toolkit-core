use std::fmt;
use std::borrow::Borrow;
use std::ops::Index;
use std::path::Path;
use std::str::FromStr;

use super::ffi::{self, Dictionary, Object};
use crate::{Error, Unique};

/// The type of an [`Object`].
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum ObjectType {
    Undefined,
    Boolean,
    Integer,
    Real,
    String,
    Dictionary,
    Array,
}

impl ObjectType {
    fn to_ffi(self) -> ffi::ObjectType {
        match self {
            ObjectType::Undefined => ffi::ObjectType::Undefined,
            ObjectType::Boolean => ffi::ObjectType::Boolean,
            ObjectType::Integer => ffi::ObjectType::Integer,
            ObjectType::Real => ffi::ObjectType::Real,
            ObjectType::String => ffi::ObjectType::String,
            ObjectType::Dictionary => ffi::ObjectType::Dictionary,
            ObjectType::Array => ffi::ObjectType::Array,
        }
    }

    fn from_ffi(object_type: ffi::ObjectType) -> Self {
        match object_type {
            ffi::ObjectType::Undefined => ObjectType::Undefined,
            ffi::ObjectType::Boolean => ObjectType::Boolean,
            ffi::ObjectType::Integer => ObjectType::Integer,
            ffi::ObjectType::Real => ObjectType::Real,
            ffi::ObjectType::String => ObjectType::String,
            ffi::ObjectType::Dictionary => ObjectType::Dictionary,
            ffi::ObjectType::Array => ObjectType::Array,
            _ => unreachable!("unknown Object type from OSTK"),
        }
    }
}

/// OSTK's name, e.g. `"Dictionary"`.
impl fmt::Display for ObjectType {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        let name = ffi::object_type_to_string(self.to_ffi()).map_err(|_| fmt::Error)?;
        f.write_str(&name)
    }
}

/// Parses OSTK's name.
impl FromStr for ObjectType {
    type Err = Error;

    fn from_str(name: &str) -> Result<Self, Error> {
        Ok(ObjectType::from_ffi(ffi::object_type_from_string(name)?))
    }
}

/// Serialization format.
#[derive(Debug, Clone, Copy, PartialEq, Eq, Hash)]
pub enum Format {
    Json,
    Yaml,
}

pub(super) fn format_choice(format: Option<Format>) -> ffi::FormatChoice {
    match format {
        None => ffi::FormatChoice::Detect,
        Some(Format::Json) => ffi::FormatChoice::Json,
        Some(Format::Yaml) => ffi::FormatChoice::Yaml,
    }
}

impl Object {
    pub fn undefined() -> Unique<Object> {
        Unique::from_ffi(ffi::object_undefined())
    }

    pub fn boolean(value: bool) -> Unique<Object> {
        Unique::from_ffi(ffi::object_boolean(value))
    }

    pub fn integer(value: i32) -> Unique<Object> {
        Unique::from_ffi(ffi::object_integer(value))
    }

    pub fn real(value: f64) -> Unique<Object> {
        Unique::from_ffi(ffi::object_real(value))
    }

    pub fn string(value: &str) -> Unique<Object> {
        Unique::from_ffi(ffi::object_string(value))
    }

    /// OSTK copies `dictionary`.
    pub fn dictionary(dictionary: &Dictionary) -> Unique<Object> {
        Unique::from_ffi(ffi::object_dictionary(dictionary))
    }

    /// OSTK copies `items`.
    pub fn array<I>(items: I) -> Unique<Object>
    where
        I: IntoIterator,
        I::Item: Borrow<Object>,
    {
        let mut array = Unique::from_ffi(ffi::object_empty_array());
        for item in items {
            ffi::object_array_push(array.pin_mut(), item.borrow()).expect("an array object accepts items");
        }
        array
    }

    /// JSON or YAML; `None` detects the format.
    pub fn parse(text: &str, format: Option<Format>) -> Result<Unique<Object>, Error> {
        Ok(Unique::from_ffi(ffi::object_parse(text, format_choice(format))?))
    }

    /// Reads a JSON or YAML file; `None` detects the format.
    pub fn load(path: impl AsRef<Path>, format: Option<Format>) -> Result<Unique<Object>, Error> {
        let path = crate::filesystem::to_utf8(path.as_ref())?;
        Ok(Unique::from_ffi(ffi::object_load(path, format_choice(format))?))
    }

    pub fn kind(&self) -> ObjectType {
        ObjectType::from_ffi(ffi::object_type(self))
    }

    pub fn is_defined(&self) -> bool {
        self.kind() != ObjectType::Undefined
    }

    pub fn is_boolean(&self) -> bool {
        self.kind() == ObjectType::Boolean
    }

    pub fn is_integer(&self) -> bool {
        self.kind() == ObjectType::Integer
    }

    pub fn is_real(&self) -> bool {
        self.kind() == ObjectType::Real
    }

    pub fn is_string(&self) -> bool {
        self.kind() == ObjectType::String
    }

    pub fn is_dictionary(&self) -> bool {
        self.kind() == ObjectType::Dictionary
    }

    pub fn is_array(&self) -> bool {
        self.kind() == ObjectType::Array
    }

    // The `as_*` views error if the object holds another type.
    pub fn as_boolean(&self) -> Result<bool, Error> {
        Ok(ffi::object_as_boolean(self)?)
    }

    pub fn as_integer(&self) -> Result<i32, Error> {
        Ok(ffi::object_as_integer(self)?)
    }

    pub fn as_real(&self) -> Result<f64, Error> {
        Ok(ffi::object_as_real(self)?)
    }

    /// Also errors on invalid UTF-8.
    pub fn as_str(&self) -> Result<&str, Error> {
        let string = ffi::object_as_string(self)?;
        string.to_str().map_err(|e| Error::new(crate::ErrorKind::Wrong, format!("string is not UTF-8: {e}")))
    }

    pub fn as_dictionary(&self) -> Result<&Dictionary, Error> {
        Ok(ffi::object_as_dictionary(self)?)
    }

    /// Borrowed items.
    pub fn as_array(&self) -> Result<ArrayItems<'_>, Error> {
        let len = ffi::object_array_len(self)?;
        Ok(ArrayItems { array: self, index: 0, len })
    }

    /// Value for `key` in a dictionary object.
    pub fn get(&self, key: &str) -> Result<&Object, Error> {
        Ok(ffi::object_at_key(self, key)?)
    }

    /// Item at `index` in an array object.
    pub fn at(&self, index: usize) -> Result<&Object, Error> {
        Ok(ffi::object_array_at(self, index)?)
    }

    pub fn to_string_as(&self, format: Format) -> Result<String, Error> {
        Ok(ffi::object_to_string(self, format_choice(Some(format)))?)
    }
}

/// Items of an array [`Object`].
pub struct ArrayItems<'a> {
    array: &'a Object,
    index: usize,
    len: usize,
}

impl<'a> Iterator for ArrayItems<'a> {
    type Item = &'a Object;

    fn next(&mut self) -> Option<&'a Object> {
        if self.index == self.len {
            return None;
        }
        let item = ffi::object_array_at(self.array, self.index).expect("index within the array");
        self.index += 1;
        Some(item)
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        (self.len - self.index, Some(self.len - self.index))
    }
}

impl ExactSizeIterator for ArrayItems<'_> {}

/// Panics on another type or a missing key; see [`Object::get`].
impl Index<&str> for Object {
    type Output = Object;

    fn index(&self, key: &str) -> &Object {
        self.get(key).unwrap_or_else(|e| panic!("object[{key:?}]: {e}"))
    }
}

/// Panics on another type or out of range; see [`Object::at`].
impl Index<usize> for Object {
    type Output = Object;

    fn index(&self, index: usize) -> &Object {
        self.at(index).unwrap_or_else(|e| panic!("object[{index}]: {e}"))
    }
}

impl PartialEq for Object {
    fn eq(&self, other: &Object) -> bool {
        ffi::object_equals(self, other)
    }
}

/// JSON.
impl fmt::Display for Object {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        f.write_str(&self.to_string_as(Format::Json).map_err(|_| fmt::Error)?)
    }
}

impl fmt::Debug for Object {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        write!(f, "Object({}: {self})", self.kind())
    }
}

impl From<bool> for Unique<Object> {
    fn from(value: bool) -> Self {
        Object::boolean(value)
    }
}

impl From<i32> for Unique<Object> {
    fn from(value: i32) -> Self {
        Object::integer(value)
    }
}

impl From<f64> for Unique<Object> {
    fn from(value: f64) -> Self {
        Object::real(value)
    }
}

impl From<&str> for Unique<Object> {
    fn from(value: &str) -> Self {
        Object::string(value)
    }
}

impl From<&Dictionary> for Unique<Object> {
    fn from(value: &Dictionary) -> Self {
        Object::dictionary(value)
    }
}
