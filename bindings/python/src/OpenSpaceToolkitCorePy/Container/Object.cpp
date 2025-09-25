/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

using ostk::core::container::Object;

inline void OpenSpaceToolkitCorePy_Container_Object(pybind11::class_<Object>& objectClass)
{
    using namespace pybind11;

    using ostk::core::type::Index;
    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    enum_<Object::Type>(objectClass, "Type", R"doc(
        Enumeration of Object types.

        Defines the different types that an Object can represent.
    )doc")

        .value("Undefined", Object::Type::Undefined, "Undefined object type")
        .value("Boolean", Object::Type::Boolean, "Boolean object type")
        .value("Integer", Object::Type::Integer, "Integer object type")
        .value("Real", Object::Type::Real, "Real number object type")
        .value("String", Object::Type::String, "String object type")
        .value("Dictionary", Object::Type::Dictionary, "Dictionary object type")
        .value("Array", Object::Type::Array, "Array object type")

        ;

    enum_<Object::Format>(objectClass, "Format", R"doc(
        Enumeration of Object serialization formats.

        Defines the supported formats for serializing/deserializing Objects.
    )doc")

        .value("Undefined", Object::Format::Undefined, "Undefined format")
        .value("JSON", Object::Format::JSON, "JSON format")
        .value("YAML", Object::Format::YAML, "YAML format")

        ;

    objectClass

        .def(self == self, R"doc(Check if two Objects are equal.)doc")
        .def(self != self, R"doc(Check if two Objects are not equal.)doc")

        .def(
            "__getitem__",
            overload_cast<const String&>(&Object::operator[]),
            R"doc(
                Access object element by string key (for dictionaries).

                Args:
                    key (str): The key to access.

                Returns:
                    Object: The object at the specified key.
            )doc",
            arg("key")
        )
        .def(
            "__getitem__",
            overload_cast<const Index&>(&Object::operator[]),
            R"doc(
                Access object element by index (for arrays).

                Args:
                    index (int): The index to access.

                Returns:
                    Object: The object at the specified index.
            )doc",
            arg("index")
        )

        .def(
            "__str__",
            [](const Object& anObject) -> std::string
            {
                return anObject.toString(Object::Format::JSON);
            },
            R"doc(
                Return JSON string representation of the Object.

                Returns:
                    str: JSON representation of the object.
            )doc"
        )
        .def(
            "__repr__",
            [](const Object& anObject) -> std::string
            {
                return anObject.toString(Object::Format::JSON);
            },
            R"doc(
                Return JSON string representation of the Object for debugging.

                Returns:
                    str: JSON representation of the object.
            )doc"
        )

        .def(
            "is_defined",
            &Object::isDefined,
            R"doc(
                Check if the Object is defined.

                Returns:
                    bool: True if the object is defined, False otherwise.
            )doc"
        )
        .def(
            "is_boolean",
            &Object::isBoolean,
            R"doc(
                Check if the Object contains a boolean value.

                Returns:
                    bool: True if the object is a boolean, False otherwise.
            )doc"
        )
        .def(
            "is_integer",
            &Object::isInteger,
            R"doc(
                Check if the Object contains an integer value.

                Returns:
                    bool: True if the object is an integer, False otherwise.
            )doc"
        )
        .def(
            "is_real",
            &Object::isReal,
            R"doc(
                Check if the Object contains a real number value.

                Returns:
                    bool: True if the object is a real number, False otherwise.
            )doc"
        )
        .def(
            "is_string",
            &Object::isString,
            R"doc(
                Check if the Object contains a string value.

                Returns:
                    bool: True if the object is a string, False otherwise.
            )doc"
        )
        .def(
            "is_dictionary",
            &Object::isDictionary,
            R"doc(
                Check if the Object contains a dictionary.

                Returns:
                    bool: True if the object is a dictionary, False otherwise.
            )doc"
        )
        .def(
            "is_array",
            &Object::isArray,
            R"doc(
                Check if the Object contains an array.

                Returns:
                    bool: True if the object is an array, False otherwise.
            )doc"
        )

        .def(
            "get_type",
            &Object::getType,
            R"doc(
                Get the type of the Object.

                Returns:
                    Object.Type: The type of the object.
            )doc"
        )
        .def(
            "get_boolean",
            &Object::getBoolean,
            R"doc(
                Get the boolean value from the Object.

                Returns:
                    bool: The boolean value.

                Raises:
                    RuntimeError: If the object is not a boolean.
            )doc"
        )
        .def(
            "get_integer",
            &Object::getInteger,
            R"doc(
                Get the integer value from the Object.

                Returns:
                    Integer: The integer value.

                Raises:
                    RuntimeError: If the object is not an integer.
            )doc"
        )
        .def(
            "get_real",
            &Object::getReal,
            R"doc(
                Get the real number value from the Object.

                Returns:
                    Real: The real number value.

                Raises:
                    RuntimeError: If the object is not a real number.
            )doc"
        )
        .def(
            "get_string",
            &Object::getString,
            R"doc(
                Get the string value from the Object.

                Returns:
                    String: The string value.

                Raises:
                    RuntimeError: If the object is not a string.
            )doc"
        )
        .def(
            "get_dictionary",
            &Object::getDictionary,
            R"doc(
                Get the dictionary from the Object.

                Returns:
                    Dictionary: The dictionary value.

                Raises:
                    RuntimeError: If the object is not a dictionary.
            )doc"
        )
        .def(
            "get_array",
            &Object::getArray,
            R"doc(
                Get the array from the Object.

                Returns:
                    Array: The array value.

                Raises:
                    RuntimeError: If the object is not an array.
            )doc"
        )
        .def(
            "to_string",
            &Object::toString,
            R"doc(
                Convert the Object to a string representation.

                Args:
                    format (Object.Format): The output format (JSON or YAML).

                Returns:
                    str: String representation of the object.
            )doc",
            arg("format")
        )

        .def_static(
            "undefined",
            &Object::Undefined,
            R"doc(
                Create an undefined Object.

                Returns:
                    Object: An undefined object.
            )doc"
        )
        .def_static(
            "boolean",
            &Object::Boolean,
            R"doc(
                Create an Object containing a boolean value.

                Args:
                    boolean (bool): The boolean value.

                Returns:
                    Object: An object containing the boolean.
            )doc",
            arg("boolean")
        )
        .def_static(
            "integer",
            &Object::Integer,
            R"doc(
                Create an Object containing an integer value.

                Args:
                    integer (Integer): The integer value.

                Returns:
                    Object: An object containing the integer.
            )doc",
            arg("integer")
        )
        .def_static(
            "real",
            &Object::Real,
            R"doc(
                Create an Object containing a real number value.

                Args:
                    real (Real): The real number value.

                Returns:
                    Object: An object containing the real number.
            )doc",
            arg("real")
        )
        .def_static(
            "string",
            &Object::String,
            R"doc(
                Create an Object containing a string value.

                Args:
                    string (String): The string value.

                Returns:
                    Object: An object containing the string.
            )doc",
            arg("string")
        )
        .def_static(
            "dictionary",
            &Object::Dictionary,
            R"doc(
                Create an Object containing a dictionary.

                Args:
                    dictionary (Dictionary): The dictionary.

                Returns:
                    Object: An object containing the dictionary.
            )doc",
            arg("dictionary")
        )
        .def_static(
            "array",
            &Object::Array,
            R"doc(
                Create an Object containing an array.

                Args:
                    array (Array): The array.

                Returns:
                    Object: An object containing the array.
            )doc",
            arg("array")
        )
        .def_static(
            "parse",
            &Object::Parse,
            R"doc(
                Parse a string as an Object.

                Args:
                    string (str): The string to parse.
                    format (Object.Format): The format of the string (JSON or YAML).

                Returns:
                    Object: The parsed object.

                Raises:
                    RuntimeError: If the string cannot be parsed.
            )doc",
            arg("string"),
            arg("format")
        )
        .def_static(
            "load",
            &Object::Load,
            R"doc(
                Load an Object from a file.

                Args:
                    file (File): The file to load from.
                    format (Object.Format): The format of the file content.

                Returns:
                    Object: The loaded object.

                Raises:
                    RuntimeError: If the file cannot be loaded or parsed.
            )doc",
            arg("file"),
            arg("format")
        )
        .def_static(
            "string_from_type",
            &Object::StringFromType,
            R"doc(
                Get string representation of an Object type.

                Args:
                    type (Object.Type): The object type.

                Returns:
                    str: String representation of the type.
            )doc",
            arg("type")
        )
        .def_static(
            "type_from_string",
            &Object::TypeFromString,
            R"doc(
                Get Object type from string representation.

                Args:
                    string (str): String representation of the type.

                Returns:
                    Object.Type: The object type.
            )doc",
            arg("string")
        )

        ;
}
