////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           LibraryCorePy/Types/String.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Size.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// http://www.boost.org/doc/libs/1_66_0/libs/python/doc/html/faq/how_can_i_automatically_convert_.html

inline void                     LibraryCorePy_Types_String                  ( )
{

    using namespace boost::python ;

    using library::core::types::Size ;
    using library::core::types::String ;

    class_<String>("String", init<std::string>())

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        // .def(self + str())
        // .def(self += string())

        // .def(string() + self)

        .def("__str__", +[] (const library::core::types::String& aString) -> std::string { return aString ; })
        .def("__repr__", +[] (const library::core::types::String& aString) -> std::string { return aString ; })

        .def("isEmpty", &String::isEmpty)
        .def("isUppercase", &String::isUppercase)
        .def("isLowercase", &String::isLowercase)
        .def("match", &String::match)

        .def("getLength", &String::getLength)
        .def("getFirst", &String::getFirst)
        .def("getLast", &String::getLast)
        .def("getHead", &String::getHead)
        .def("getTail", &String::getTail)
        .def("getSubstring", &String::getSubstring)
        // .def("trim", &String::trim)

        // .def("Empty", &String::Empty).staticmethod("Empty")
        // .def("Boolean", &String::Empty).staticmethod("Boolean")
        // .def("Char", &String::Empty).staticmethod("Char")
        // .def("Replicate", static_cast<String(*)(const String&, Size)>(&String::Replicate)).staticmethod("Replicate")
        // .def("Format", &String::Empty).staticmethod("Format")

    ;

    implicitly_convertible<std::string, String>() ;
    implicitly_convertible<String, std::string>() ;

    // implicitly_convertible<str, String>() ;
    // implicitly_convertible<String, str>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////