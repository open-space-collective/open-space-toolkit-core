////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Types/String.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>  // exposes py::py::self

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://www.boost.org/doc/libs/1_66_0/libs/python/doc/html/faq/how_can_i_automatically_convert_.html

inline void                     OpenSpaceToolkitCorePy_Types_String                     (          py::module&                     aModule                     )
{

    using ostk::core::types::Size ;
    using ostk::core::types::String ;

    py::class_<String>(aModule, "String")

        // Define init method using pybind11 "init" convenience method
        .def(py::init<std::string>())
        // .def(py::str(py::self))

        // Define methods
        .def(py::self == py::self)
        .def(py::self != py::self)

        .def(py::self + py::self)
        .def(py::self += py::self)

        // .def(py::self + str())
        // .def(py::self += string())

        // .def(string() + py::self)

        .def("__str__", +[] (const ostk::core::types::String& aString) -> std::string { return aString ; })
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

        // .def("empty", &String::Empty).staticmethod("empty")
        // .def("boolean", &String::Empty).staticmethod("boolean")
        // .def("char", &String::Empty).staticmethod("char")
        // .def("replicate", static_cast<String(*)(const String&, Size)>(&String::Replicate)).staticmethod("replicate")
        // .def("format", &String::Empty).staticmethod("format")

    ;

    // Implicit conversion to be further investigated
    // py::implicitly_convertible<std::string, String>() ;
    // py::implicitly_convertible<String, std::string>() ;

    // py::implicitly_convertible<str_, String>() ;
    // py::implicitly_convertible<String, str_>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
