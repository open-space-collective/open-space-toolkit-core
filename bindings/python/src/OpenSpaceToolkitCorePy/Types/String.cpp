////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Types/String.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_Types_String         (          pybind11::module&            aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::Size ;
    using ostk::core::types::String ;

    class_<String>(aModule, "String")

        // Define init method using pybind11 "init" convenience method
        .def(init<std::string>())

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def(self + String())
        .def(self += std::string())

        .def(std::string() + self)

        .def("__str__", +[] (const ostk::core::types::String& aString) -> str { return aString ; })
        .def("__repr__", +[] (const ostk::core::types::String& aString) -> std::string { return aString ; })

        .def("is_empty", &String::isEmpty)
        .def("is_uppercase", &String::isUppercase)
        .def("is_lowercase", &String::isLowercase)
        .def("match", &String::match)

        .def("get_length", &String::getLength)
        .def("get_first", &String::getFirst)
        .def("get_last", &String::getLast)
        .def("get_head", &String::getHead)
        .def("get_tail", &String::getTail)
        .def("get_substring", &String::getSubstring)
        // .def("trim", &String::trim)

        // Define static methods
        .def_static("empty", &String::Empty)
        .def_static("boolean", &String::Boolean)
        .def_static("char", &String::Char)
        .def_static("replicate", static_cast<String(*)(const String&, Size)>(&String::Replicate))
        // .def_static("format", &String::Format)

    ;

    implicitly_convertible<std::string, String>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
