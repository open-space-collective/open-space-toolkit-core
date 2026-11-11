//! OSTK's JSON / YAML object model: [`Object`] and [`Dictionary`].
//!
//! ```ignore
//! let song = Object::parse(yaml, Some(Format::Yaml))?;
//! let count = song["partridges"]["count"].as_integer()?;
//! for (key, value) in song.as_dictionary()? { /* (&str, &Object) */ }
//! ```

mod dictionary;
mod object;

pub use dictionary::Iter;
pub use ffi::{Dictionary, Object};
pub use object::{ArrayItems, Format, ObjectType};

#[cxx::bridge(namespace = "ostk_rs::core::container")]
mod ffi {
    #[repr(u8)]
    enum ObjectType {
        Undefined,
        Boolean,
        Integer,
        Real,
        String,
        Dictionary,
        Array,
    }

    #[repr(u8)]
    enum FormatChoice {
        Detect,
        Json,
        Yaml,
    }

    unsafe extern "C++" {
        include!("ostk-core/src/container/shim.h");

        /// Undefined, a boolean, integer, real, string, [`Dictionary`] or array.
        #[namespace = "ostk::core::container"]
        type Object;

        /// Insertion-ordered map from string keys to [`Object`]s.
        #[namespace = "ostk::core::container"]
        type Dictionary;

        fn object_undefined() -> UniquePtr<Object>;
        fn object_boolean(value: bool) -> UniquePtr<Object>;
        fn object_integer(value: i32) -> UniquePtr<Object>;
        fn object_real(value: f64) -> UniquePtr<Object>;
        fn object_string(value: &str) -> UniquePtr<Object>;
        fn object_dictionary(value: &Dictionary) -> UniquePtr<Object>;
        fn object_empty_array() -> UniquePtr<Object>;
        fn object_array_push(array: Pin<&mut Object>, value: &Object) -> Result<()>;
        fn object_parse(text: &str, format: FormatChoice) -> Result<UniquePtr<Object>>;
        fn object_load(path: &str, format: FormatChoice) -> Result<UniquePtr<Object>>;

        fn object_type(object: &Object) -> ObjectType;
        fn object_equals(lhs: &Object, rhs: &Object) -> bool;
        fn object_as_boolean(object: &Object) -> Result<bool>;
        fn object_as_integer(object: &Object) -> Result<i32>;
        fn object_as_real(object: &Object) -> Result<f64>;
        fn object_as_string(object: &Object) -> Result<&CxxString>;
        fn object_as_dictionary(object: &Object) -> Result<&Dictionary>;
        fn object_array_len(object: &Object) -> Result<usize>;
        fn object_array_at(object: &Object, index: usize) -> Result<&Object>;
        fn object_at_key<'a>(object: &'a Object, key: &str) -> Result<&'a Object>;
        fn object_to_string(object: &Object, format: FormatChoice) -> Result<String>;
        fn object_type_to_string(object_type: ObjectType) -> Result<String>;
        fn object_type_from_string(name: &str) -> Result<ObjectType>;

        fn dictionary_empty() -> UniquePtr<Dictionary>;
        fn dictionary_parse(text: &str, format: FormatChoice) -> Result<UniquePtr<Dictionary>>;
        fn dictionary_len(dictionary: &Dictionary) -> usize;
        fn dictionary_contains(dictionary: &Dictionary, key: &str) -> bool;
        fn dictionary_get<'a>(dictionary: &'a Dictionary, key: &str) -> Result<&'a Object>;
        fn dictionary_insert(dictionary: Pin<&mut Dictionary>, key: &str, value: &Object) -> Result<()>;
        fn dictionary_key_at(dictionary: &Dictionary, index: usize) -> &CxxString;
        fn dictionary_value_at(dictionary: &Dictionary, index: usize) -> &Object;
        fn dictionary_equals(lhs: &Dictionary, rhs: &Dictionary) -> bool;
        fn dictionary_to_string(dictionary: &Dictionary) -> String;
    }
}
