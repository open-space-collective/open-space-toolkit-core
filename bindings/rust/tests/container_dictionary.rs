//! Port of python/test/containers/test_dictionary.py, plus Rust-specific checks.

use ostk_core::container::{Dictionary, Format, Object};
use ostk_core::Unique;

fn inner() -> Unique<Dictionary> {
    [("key", Object::string("value"))].into_iter().collect()
}

fn sample() -> Unique<Dictionary> {
    [
        ("boolean", Object::boolean(true)),
        ("integer", Object::integer(123)),
        ("real", Object::real(123.456)),
        ("string", Object::string("abc")),
        ("array", Object::array([Object::integer(123), Object::real(123.456), Object::string("abc")])),
        ("dictionary", Object::dictionary(&inner())),
    ]
    .into_iter()
    .collect()
}

#[test]
fn constructor_and_index() {
    let dictionary = sample();
    assert_eq!(dictionary["boolean"], *Object::boolean(true));
    assert_eq!(dictionary["integer"], *Object::integer(123));
    assert_eq!(dictionary["real"], *Object::real(123.456));
    assert_eq!(dictionary["string"], *Object::string("abc"));
    assert_eq!(
        dictionary["array"],
        *Object::array([Object::integer(123), Object::real(123.456), Object::string("abc")])
    );
    assert_eq!(dictionary["dictionary"], *Object::dictionary(&inner()));
}

#[test]
fn equality() {
    assert!(sample() == sample());
    assert!(!(sample() != sample()));
    assert!(sample() != Dictionary::empty());
}

#[test]
fn len_and_emptiness() {
    assert_eq!(sample().len(), 6);
    assert!(!sample().is_empty());
    assert!(Dictionary::empty().is_empty());
}

#[test]
fn iteration_is_in_insertion_order() {
    let dictionary = sample();
    let keys: Vec<&str> = dictionary.keys().collect();
    assert_eq!(keys, ["boolean", "integer", "real", "string", "array", "dictionary"]);
    for (key, value) in &dictionary {
        assert!(std::ptr::eq(value, dictionary.get(key).unwrap()), "{key}: borrowed, not copied");
    }
    assert_eq!(dictionary.iter().len(), 6);
}

#[test]
fn contains_key() {
    let dictionary = sample();
    assert!(dictionary.contains_key("boolean"));
    assert!(!dictionary.contains_key("abc"));
}

#[test]
fn display_and_debug() {
    let one: Unique<Dictionary> = [("count", Object::integer(1))].into_iter().collect();
    assert_eq!(one.to_string().replace([' ', '\n'], ""), r#"{"count":1}"#);
    assert_eq!(format!("{one:?}"), r#"{"count": Object(Integer: 1)}"#);
}

#[test]
fn insert() {
    let mut dictionary = sample();
    assert!(!dictionary.contains_key("abc"));
    dictionary.pin_mut().insert("abc", &Object::integer(123)).unwrap();
    assert!(dictionary.contains_key("abc"));
    assert_eq!(dictionary["abc"], *Object::integer(123));
}

#[test]
fn insert_does_not_overwrite() {
    let mut dictionary = sample();
    assert!(dictionary.pin_mut().insert("integer", &Object::integer(1)).is_err());
    assert_eq!(dictionary["integer"], *Object::integer(123));
    assert!(dictionary.pin_mut().insert("", &Object::integer(1)).is_err(), "empty key");
}

#[test]
fn parse() {
    let data = r#"
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
    let dictionary = Dictionary::parse(data, Some(Format::Yaml)).unwrap();
    assert_eq!(dictionary["count"], *Object::integer(1));
}

#[test]
fn parse_without_format() {
    let dictionary = Dictionary::parse(r#"{"count": 1}"#, None).unwrap();
    assert_eq!(dictionary["count"], *Object::integer(1));
    assert!(dictionary == Dictionary::parse(r#"{"count": 1}"#, Some(Format::Json)).unwrap());
    assert!(Dictionary::parse("abc", None).is_err());
}

#[test]
fn missing_key_is_an_error() {
    assert!(sample().get("missing").is_err());
}

#[test]
fn errors_carry_ostks_stack_trace() {
    let error = sample().get("missing").unwrap_err();
    assert_eq!(error.message(), "No value for key [missing].");
    let trace = error.stack_trace().expect("OSTK errors have a stack trace").to_string();
    assert!(trace.contains("dictionary_get"), "frames are named:\n{trace}");
    assert!(format!("{error:?}").contains("OSTK stack trace"), "Debug shows the trace");
}

#[test]
#[should_panic(expected = "dictionary[\"missing\"]")]
fn index_missing_key_panics() {
    let _ = &sample()["missing"];
}

#[test]
#[should_panic(expected = "dictionary key \"a\"")]
fn from_iter_with_a_repeated_key_panics() {
    let _: Unique<Dictionary> = [("a", Object::integer(1)), ("a", Object::integer(2))].into_iter().collect();
}
