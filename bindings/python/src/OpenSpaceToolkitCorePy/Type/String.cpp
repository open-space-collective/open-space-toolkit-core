/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

using ostk::core::type::String;

inline void OpenSpaceToolkitCorePy_Type_String(pybind11::class_<String>& stringClass)
{
    using namespace pybind11;

    using ostk::core::type::Size;

    stringClass

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

        .def(
            "__str__",
            +[](const ostk::core::type::String& aString) -> str
            {
                return aString;
            }
        )
        .def(
            "__repr__",
            +[](const ostk::core::type::String& aString) -> std::string
            {
                return aString;
            }
        )
        .def(
            "__hash__",
            +[](const ostk::core::type::String& aString) -> std::size_t
            {
                return std::hash<std::string>()(aString);
            }
        )

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
        .def_static("replicate", static_cast<String (*)(const String&, Size)>(&String::Replicate))
        // .def_static("format", &String::Format)

        ;

    implicitly_convertible<std::string, String>();
}
