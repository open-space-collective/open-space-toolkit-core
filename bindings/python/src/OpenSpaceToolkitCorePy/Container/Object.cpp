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

    enum_<Object::Type>(objectClass, "Type")

        .value("Undefined", Object::Type::Undefined)
        .value("Boolean", Object::Type::Boolean)
        .value("Integer", Object::Type::Integer)
        .value("Real", Object::Type::Real)
        .value("String", Object::Type::String)
        .value("Dictionary", Object::Type::Dictionary)
        .value("Array", Object::Type::Array)

        ;

    enum_<Object::Format>(objectClass, "Format")

        .value("Undefined", Object::Format::Undefined)
        .value("JSON", Object::Format::JSON)
        .value("YAML", Object::Format::YAML)

        ;

    objectClass

        .def(self == self)
        .def(self != self)

        .def("__getitem__", overload_cast<const String&>(&Object::operator[]))
        .def("__getitem__", overload_cast<const Index&>(&Object::operator[]))

        .def(
            "__str__",
            [](const Object& anObject) -> std::string
            {
                return anObject.toString(Object::Format::JSON);
            }
        )
        .def(
            "__repr__",
            [](const Object& anObject) -> std::string
            {
                return anObject.toString(Object::Format::JSON);
            }
        )

        .def("is_defined", &Object::isDefined)
        .def("is_boolean", &Object::isBoolean)
        .def("is_integer", &Object::isInteger)
        .def("is_real", &Object::isReal)
        .def("is_string", &Object::isString)
        .def("is_dictionary", &Object::isDictionary)
        .def("is_array", &Object::isArray)

        .def("get_type", &Object::getType)
        .def("get_boolean", &Object::getBoolean)
        .def("get_integer", &Object::getInteger)
        .def("get_real", &Object::getReal)
        .def("get_string", &Object::getString)
        .def("get_dictionary", &Object::getDictionary)
        .def("get_array", &Object::getArray)
        .def("to_string", &Object::toString)

        .def_static("undefined", &Object::Undefined)
        .def_static("boolean", &Object::Boolean, arg("boolean"))
        .def_static("integer", &Object::Integer, arg("integer"))
        .def_static("real", &Object::Real, arg("real"))
        .def_static("string", &Object::String, arg("string"))
        .def_static("dictionary", &Object::Dictionary, arg("dictionary"))
        .def_static("array", &Object::Array, arg("array"))
        .def_static("parse", &Object::Parse, arg("string"), arg("format"))
        .def_static("load", &Object::Load, arg("file"), arg("format"))
        .def_static("string_from_type", &Object::StringFromType, arg("type"))
        .def_static("type_from_string", &Object::TypeFromString, arg("string"))

        ;
}
