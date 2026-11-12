#include <optional>

#include <OpenSpaceToolkit/Core/Error.hpp>

#include "ostk-core/src/container/shim.h"
#include "ostk_rs/core/filesystem.hpp"
#include "ostk_rs/core/string.hpp"

#include "ostk-core/src/container/mod.rs.h"

namespace ostk_rs
{
namespace core
{
namespace container
{

// Factories construct in place: without move constructors, make_unique of a
// factory's result would deep-copy it.

namespace
{
std::optional<Object::Format> toFormat(FormatChoice format)
{
    switch (format)
    {
        case FormatChoice::Json:
            return Object::Format::JSON;
        case FormatChoice::Yaml:
            return Object::Format::YAML;
        case FormatChoice::Detect:
            break;
    }
    return std::nullopt;
}

ObjectType toObjectType(Object::Type objectType)
{
    switch (objectType)
    {
        case Object::Type::Undefined:
            return ObjectType::Undefined;
        case Object::Type::Boolean:
            return ObjectType::Boolean;
        case Object::Type::Integer:
            return ObjectType::Integer;
        case Object::Type::Real:
            return ObjectType::Real;
        case Object::Type::String:
            return ObjectType::String;
        case Object::Type::Dictionary:
            return ObjectType::Dictionary;
        case Object::Type::Array:
            return ObjectType::Array;
    }
    throw ostk::core::error::runtime::Wrong("Object type");
}

Object::Type fromObjectType(ObjectType objectType)
{
    switch (objectType)
    {
        case ObjectType::Undefined:
            return Object::Type::Undefined;
        case ObjectType::Boolean:
            return Object::Type::Boolean;
        case ObjectType::Integer:
            return Object::Type::Integer;
        case ObjectType::Real:
            return Object::Type::Real;
        case ObjectType::String:
            return Object::Type::String;
        case ObjectType::Dictionary:
            return Object::Type::Dictionary;
        case ObjectType::Array:
            return Object::Type::Array;
    }
    throw ostk::core::error::runtime::Wrong("Object type");
}

// tsl::ordered_map iterators are random access.
Dictionary::ConstIterator::MapConstIterator mapIteratorAt(const Dictionary& dictionary, size_t index)
{
    Dictionary::ConstIterator iterator = dictionary.begin();
    return iterator.accessMapConstIterator() + static_cast<std::ptrdiff_t>(index);
}
}  // namespace

std::unique_ptr<Object> object_undefined()
{
    return std::unique_ptr<Object>(new Object(Object::Undefined()));
}

std::unique_ptr<Object> object_boolean(bool value)
{
    return std::unique_ptr<Object>(new Object(Object::Boolean(value)));
}

std::unique_ptr<Object> object_integer(int32_t value)
{
    return std::unique_ptr<Object>(new Object(Object::Integer(value)));
}

std::unique_ptr<Object> object_real(double value)
{
    return std::unique_ptr<Object>(new Object(Object::Real(value)));
}

std::unique_ptr<Object> object_string(rust::Str value)
{
    return std::unique_ptr<Object>(new Object(Object::String(toOstkString(value))));
}

std::unique_ptr<Object> object_dictionary(const Dictionary& value)
{
    return std::unique_ptr<Object>(new Object(Object::Dictionary(value)));
}

std::unique_ptr<Object> object_empty_array()
{
    return std::unique_ptr<Object>(new Object(Object::Array()));
}

void object_array_push(Object& array, const Object& value)
{
    array.accessArray().push_back(value);
}

std::unique_ptr<Object> object_parse(rust::Str text, FormatChoice format)
{
    return std::unique_ptr<Object>(new Object(Object::Parse(toOstkString(text), toFormat(format))));
}

std::unique_ptr<Object> object_load(rust::Str path, FormatChoice format)
{
    return std::unique_ptr<Object>(new Object(Object::Load(toFile(path), toFormat(format))));
}

ObjectType object_type(const Object& object)
{
    return toObjectType(object.getType());
}

bool object_equals(const Object& lhs, const Object& rhs)
{
    return lhs == rhs;
}

bool object_as_boolean(const Object& object)
{
    return object.getBoolean();
}

int32_t object_as_integer(const Object& object)
{
    return object.getInteger();
}

double object_as_real(const Object& object)
{
    return object.getReal();
}

const std::string& object_as_string(const Object& object)
{
    return object.getString();
}

const Dictionary& object_as_dictionary(const Object& object)
{
    return object.getDictionary();
}

size_t object_array_len(const Object& object)
{
    return object.getArray().size();
}

const Object& object_array_at(const Object& object, size_t index)
{
    // OSTK doesn't bounds-check.
    const auto& array = object.getArray();
    if (index >= array.size())
    {
        throw ostk::core::error::RuntimeError("Index [{}] out of range [0, {}).", index, array.size());
    }
    return array[index];
}

const Object& object_at_key(const Object& object, rust::Str key)
{
    return object[toOstkString(key)];
}

rust::String object_to_string(const Object& object, FormatChoice format)
{
    return toRustString(object.toString(toFormat(format)));
}

rust::String object_type_to_string(ObjectType objectType)
{
    return toRustString(Object::StringFromType(fromObjectType(objectType)));
}

ObjectType object_type_from_string(rust::Str name)
{
    return toObjectType(Object::TypeFromString(toOstkString(name)));
}

std::unique_ptr<Dictionary> dictionary_empty()
{
    return std::unique_ptr<Dictionary>(new Dictionary(Dictionary::Empty()));
}

std::unique_ptr<Dictionary> dictionary_parse(rust::Str text, FormatChoice format)
{
    return std::unique_ptr<Dictionary>(new Dictionary(Dictionary::Parse(toOstkString(text), toFormat(format))));
}

size_t dictionary_len(const Dictionary& dictionary)
{
    return dictionary.getSize();
}

bool dictionary_contains(const Dictionary& dictionary, rust::Str key)
{
    return dictionary.hasValueForKey(toOstkString(key));
}

const Object& dictionary_get(const Dictionary& dictionary, rust::Str key)
{
    return dictionary[toOstkString(key)];
}

void dictionary_insert(Dictionary& dictionary, rust::Str key, const Object& value)
{
    dictionary.addValueForKey(value, toOstkString(key));
}

const std::string& dictionary_key_at(const Dictionary& dictionary, size_t index)
{
    return mapIteratorAt(dictionary, index)->first;
}

const Object& dictionary_value_at(const Dictionary& dictionary, size_t index)
{
    return mapIteratorAt(dictionary, index)->second;
}

bool dictionary_equals(const Dictionary& lhs, const Dictionary& rhs)
{
    return lhs == rhs;
}

// JSON like Python's str(): OSTK only serializes Object, so this copies.
rust::String dictionary_to_string(const Dictionary& dictionary)
{
    return toRustString(Object::Dictionary(dictionary).toString(Object::Format::JSON));
}

}  // namespace container
}  // namespace core
}  // namespace ostk_rs
