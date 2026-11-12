// Container bridge (mod.rs). OSTK headers are included here: cxx needs complete
// types for UniquePtr.
#pragma once

#include <memory>

#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>

#include "ostk_rs/cxx_exceptions.hpp"
#include "rust/cxx.h"

namespace ostk_rs
{
namespace core
{
namespace container
{

using Object = ostk::core::container::Object;
using Dictionary = ostk::core::container::Dictionary;

enum class ObjectType : uint8_t;
enum class FormatChoice : uint8_t;

std::unique_ptr<Object> object_undefined();
std::unique_ptr<Object> object_boolean(bool value);
std::unique_ptr<Object> object_integer(int32_t value);
std::unique_ptr<Object> object_real(double value);
std::unique_ptr<Object> object_string(rust::Str value);
std::unique_ptr<Object> object_dictionary(const Dictionary& value);
std::unique_ptr<Object> object_empty_array();
void object_array_push(Object& array, const Object& value);
std::unique_ptr<Object> object_parse(rust::Str text, FormatChoice format);
std::unique_ptr<Object> object_load(rust::Str path, FormatChoice format);

ObjectType object_type(const Object& object);
bool object_equals(const Object& lhs, const Object& rhs);
bool object_as_boolean(const Object& object);
int32_t object_as_integer(const Object& object);
double object_as_real(const Object& object);
const std::string& object_as_string(const Object& object);
const Dictionary& object_as_dictionary(const Object& object);
size_t object_array_len(const Object& object);
const Object& object_array_at(const Object& object, size_t index);
const Object& object_at_key(const Object& object, rust::Str key);
rust::String object_to_string(const Object& object, FormatChoice format);
rust::String object_type_to_string(ObjectType objectType);
ObjectType object_type_from_string(rust::Str name);

std::unique_ptr<Dictionary> dictionary_empty();
std::unique_ptr<Dictionary> dictionary_parse(rust::Str text, FormatChoice format);
size_t dictionary_len(const Dictionary& dictionary);
bool dictionary_contains(const Dictionary& dictionary, rust::Str key);
const Object& dictionary_get(const Dictionary& dictionary, rust::Str key);
void dictionary_insert(Dictionary& dictionary, rust::Str key, const Object& value);
const std::string& dictionary_key_at(const Dictionary& dictionary, size_t index);
const Object& dictionary_value_at(const Dictionary& dictionary, size_t index);
bool dictionary_equals(const Dictionary& lhs, const Dictionary& rhs);
rust::String dictionary_to_string(const Dictionary& dictionary);

}  // namespace container
}  // namespace core
}  // namespace ostk_rs
