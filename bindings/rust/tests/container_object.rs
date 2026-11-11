//! Port of python/test/containers/test_object.py, plus Rust-specific checks.

use ostk_core::container::{Dictionary, Format, Object, ObjectType};
use ostk_core::{ErrorKind, Unique};

const SONG: &str = r#"
doe: "a deer, a female deer"
ray: "a drop of golden sun"
pi: 3.14159
xmas: true
french-hens: 3
calling-birds:
  - huey
  - dewey
  - louie
  - fred
xmas-fifth-day:
  calling-birds: four
  french-hens: 3
  golden-rings: 5
  partridges:
    count: 1
    location: "a pear tree"
  turtle-doves: two
"#;

fn mixed_array() -> Unique<Object> {
    Object::array([Object::integer(123), Object::real(123.456), Object::string("abc")])
}

#[test]
fn operators() {
    assert!(Object::boolean(true) == Object::boolean(true));
    assert!(!(Object::boolean(true) != Object::boolean(true)));
    let array = mixed_array();
    assert_eq!(array[0], *Object::integer(123));
    assert_eq!(array[1], *Object::real(123.456));
    assert_eq!(array[2], *Object::string("abc"));
}

#[test]
fn display_is_json() {
    assert_eq!(Object::boolean(true).to_string(), "true");
    assert_eq!(format!("{:?}", Object::integer(1)), "Object(Integer: 1)");
}

#[test]
fn predicates() {
    assert!(Object::boolean(true).is_defined());
    assert!(Object::boolean(true).is_boolean());
    assert!(Object::integer(123).is_integer());
    assert!(Object::real(123.456).is_real());
    assert!(Object::string("abc").is_string());
    assert!(Object::dictionary(&Dictionary::empty()).is_dictionary());
    assert!(mixed_array().is_array());
}

#[test]
fn kind() {
    assert_eq!(Object::boolean(true).kind(), ObjectType::Boolean);
}

#[test]
fn typed_getters() {
    assert!(Object::boolean(true).as_boolean().unwrap());
    assert_eq!(Object::integer(123).as_integer().unwrap(), 123);
    assert_eq!(Object::real(123.456).as_real().unwrap(), 123.456);
    assert_eq!(Object::string("abc").as_str().unwrap(), "abc");
    assert_eq!(*Object::dictionary(&Dictionary::empty()).as_dictionary().unwrap(), *Dictionary::empty());
    let array = mixed_array();
    let items: Vec<_> = array.as_array().unwrap().collect();
    assert_eq!(items.len(), 3);
    assert_eq!(*items[0], *Object::integer(123));
    assert_eq!(*items[1], *Object::real(123.456));
    assert_eq!(*items[2], *Object::string("abc"));
}

#[test]
fn typed_getters_error_on_another_type() {
    assert!(Object::integer(1).as_boolean().is_err());
    assert!(Object::boolean(true).as_str().is_err());
    assert!(Object::string("abc").as_array().is_err());
}

#[test]
fn to_string_as() {
    assert_eq!(Object::real(123.456).to_string_as(Format::Json).unwrap(), "123.456");
}

#[test]
fn factories() {
    assert!(!Object::undefined().is_defined());
    assert!(Object::boolean(true).is_defined());
    assert!(Object::integer(123).is_defined());
    assert!(Object::real(123.456).is_defined());
    assert!(Object::string("abc").is_defined());
    assert!(Object::dictionary(&Dictionary::empty()).is_defined());
    assert!(mixed_array().is_defined());
}

#[test]
fn parse_without_format() {
    let json = Object::parse(r#"{"key": 123}"#, Some(Format::Json)).unwrap();
    assert_eq!(Object::parse(r#"{"key": 123}"#, None).unwrap(), json);
    assert!(Object::parse("abc", None).is_err());
}

#[test]
fn parse_yaml() {
    let yaml = |text| Object::parse(text, Some(Format::Yaml)).unwrap();
    assert_eq!(yaml(""), Object::undefined());
    assert_eq!(yaml("null"), Object::undefined());
    assert_eq!(yaml("true"), Object::boolean(true));
    assert_eq!(yaml("false"), Object::boolean(false));
    assert_eq!(yaml("0"), Object::integer(0));
    assert_eq!(yaml("123"), Object::integer(123));
    assert_eq!(yaml("0.0"), Object::real(0.0));
    assert_eq!(yaml("123.456"), Object::real(123.456));

    let song = yaml(SONG);
    assert!(song.is_dictionary());
    assert_eq!(song["xmas-fifth-day"]["partridges"]["count"], *Object::integer(1));
}

#[test]
fn load() {
    let reference = Object::parse(SONG, Some(Format::Yaml)).unwrap();
    let path = std::env::temp_dir().join(format!("ostk-core-object-load-{}.yaml", std::process::id()));
    std::fs::write(&path, SONG).unwrap();
    let loaded = Object::load(&path, Some(Format::Yaml));
    std::fs::remove_file(&path).unwrap();
    assert_eq!(loaded.unwrap(), reference);
}

#[test]
fn load_missing_file_is_an_error() {
    assert!(Object::load("/nonexistent/ostk.yaml", None).is_err());
}

#[test]
fn type_names() {
    assert_eq!(ObjectType::Boolean.to_string(), "Boolean");
    assert_eq!("Boolean".parse::<ObjectType>().unwrap(), ObjectType::Boolean);
    assert!("Bool".parse::<ObjectType>().is_err());
}

#[test]
fn accessors_borrow_instead_of_copying() {
    let song = Object::parse(SONG, Some(Format::Yaml)).unwrap();
    let a = song.get("xmas-fifth-day").unwrap();
    let b = song.get("xmas-fifth-day").unwrap();
    assert!(std::ptr::eq(a, b), "both lookups return the object stored in `song`");
}

#[test]
fn out_of_range_index_is_an_error_not_undefined_behaviour() {
    let array = mixed_array();
    let err = array.at(3).unwrap_err();
    assert_eq!(err.kind(), ErrorKind::Runtime, "{err:?}");
    assert!(err.message().contains("out of range"), "{err}");
}

#[test]
#[should_panic(expected = "object[3]")]
fn index_out_of_range_panics() {
    let _ = &mixed_array()[3];
}

#[test]
fn key_lookup_errors() {
    assert!(Object::integer(1).get("key").is_err(), "not a dictionary");
    let object = Object::parse(r#"{"key": 1}"#, None).unwrap();
    assert!(object.get("other").is_err(), "missing key");
}

#[test]
fn plain_references_work_everywhere() {
    fn kind_of(object: &Object) -> ObjectType {
        object.kind()
    }
    let owned = Object::integer(1);
    assert_eq!(kind_of(&owned), ObjectType::Integer, "&Unique<Object> coerces to &Object");
    let array = Object::array([&*owned, &*Object::string("x")]);
    assert_eq!(kind_of(&array[1]), ObjectType::String, "accessors return &Object");
}

#[test]
fn conversions() {
    assert_eq!(Unique::<Object>::from(true), Object::boolean(true));
    assert_eq!(Unique::<Object>::from(7), Object::integer(7));
    assert_eq!(Unique::<Object>::from(1.5), Object::real(1.5));
    assert_eq!(Unique::<Object>::from("x"), Object::string("x"));
    assert_eq!(Unique::<Object>::from(&*Dictionary::empty()), Object::dictionary(&Dictionary::empty()));
}
