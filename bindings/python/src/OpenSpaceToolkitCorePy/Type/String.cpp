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
        .def(
            init<std::string>(),
            R"doc(
                Construct a String from a standard string.

                Args:
                    value (str): A string value to initialize the String.

                Example:
                    >>> string = String("Hello, World!")
                    >>> string = String("")
            )doc",
            arg("value")
        )

        // Define methods
        .def(self == self, R"doc(Check if two Strings are equal.)doc")
        .def(self != self, R"doc(Check if two Strings are not equal.)doc")

        .def(self + self, R"doc(Concatenate two Strings.)doc")
        .def(self += self, R"doc(Append another String to this one in-place.)doc")

        .def(self + String(), R"doc(Concatenate a String with another String.)doc")
        .def(self += std::string(), R"doc(Append a standard string to this String in-place.)doc")

        .def(std::string() + self, R"doc(Concatenate a standard string with a String.)doc")

        .def(
            "__str__",
            +[](const ostk::core::type::String& aString) -> str
            {
                return aString;
            },
            R"doc(
                Return the string value.

                Returns:
                    str: The string content.
            )doc"
        )
        .def(
            "__repr__",
            +[](const ostk::core::type::String& aString) -> std::string
            {
                return aString;
            },
            R"doc(
                Return a string representation for debugging.

                Returns:
                    str: The string content.
            )doc"
        )
        .def(
            "__hash__",
            +[](const ostk::core::type::String& aString) -> std::size_t
            {
                return std::hash<std::string>()(aString);
            },
            R"doc(
                Return a hash value for the String.

                Returns:
                    int: Hash value of the String.
            )doc"
        )

        .def(
            "is_empty",
            &String::isEmpty,
            R"doc(
                Check if the String is empty.

                Returns:
                    bool: True if the String has zero length, False otherwise.

                Example:
                    >>> String("").is_empty()  # True
                    >>> String("hello").is_empty()  # False
            )doc"
        )
        .def(
            "is_uppercase",
            &String::isUppercase,
            R"doc(
                Check if all alphabetic characters in the String are uppercase.

                Returns:
                    bool: True if all letters are uppercase, False otherwise.

                Example:
                    >>> String("HELLO").is_uppercase()  # True
                    >>> String("Hello").is_uppercase()  # False
                    >>> String("123").is_uppercase()  # True (no letters)
            )doc"
        )
        .def(
            "is_lowercase",
            &String::isLowercase,
            R"doc(
                Check if all alphabetic characters in the String are lowercase.

                Returns:
                    bool: True if all letters are lowercase, False otherwise.

                Example:
                    >>> String("hello").is_lowercase()  # True
                    >>> String("Hello").is_lowercase()  # False
                    >>> String("123").is_lowercase()  # True (no letters)
            )doc"
        )
        .def(
            "match",
            &String::match,
            R"doc(
                Check if the String matches a regular expression pattern.

                Args:
                    pattern (str): The regular expression pattern to match against.

                Returns:
                    bool: True if the String matches the pattern, False otherwise.

                Example:
                    >>> String("hello123").match(r"[a-z]+\d+")  # True
                    >>> String("HELLO").match(r"[a-z]+")  # False
            )doc",
            arg("pattern")
        )

        .def(
            "get_length",
            &String::getLength,
            R"doc(
                Get the length of the String.

                Returns:
                    int: The number of characters in the String.

                Example:
                    >>> String("hello").get_length()  # 5
                    >>> String("").get_length()  # 0
            )doc"
        )
        .def(
            "get_first",
            &String::getFirst,
            R"doc(
                Get the first character of the String.

                Returns:
                    str: The first character.

                Raises:
                    RuntimeError: If the String is empty.

                Example:
                    >>> String("hello").get_first()  # "h"
            )doc"
        )
        .def(
            "get_last",
            &String::getLast,
            R"doc(
                Get the last character of the String.

                Returns:
                    str: The last character.

                Raises:
                    RuntimeError: If the String is empty.

                Example:
                    >>> String("hello").get_last()  # "o"
            )doc"
        )
        .def(
            "get_head",
            &String::getHead,
            R"doc(
                Get the first n characters of the String.

                Args:
                    count (int): The number of characters to get from the beginning.

                Returns:
                    String: A new String containing the first n characters.

                Example:
                    >>> String("hello").get_head(3)  # String("hel")
            )doc",
            arg("count")
        )
        .def(
            "get_tail",
            &String::getTail,
            R"doc(
                Get the last n characters of the String.

                Args:
                    count (int): The number of characters to get from the end.

                Returns:
                    String: A new String containing the last n characters.

                Example:
                    >>> String("hello").get_tail(3)  # String("llo")
            )doc",
            arg("count")
        )
        .def(
            "get_substring",
            &String::getSubstring,
            R"doc(
                Get a substring from the String.

                Args:
                    start_index (int): The starting position (0-based).
                    length (int): The number of characters to extract.

                Returns:
                    String: A new String containing the substring.

                Example:
                    >>> String("hello").get_substring(1, 3)  # String("ell")
            )doc",
            arg("start_index"),
            arg("length")
        )
        // .def("trim", &String::trim)

        // Define static methods
        .def_static(
            "empty",
            &String::Empty,
            R"doc(
                Create an empty String.

                Returns:
                    String: An empty String.

                Example:
                    >>> empty_str = String.empty()
                    >>> empty_str.is_empty()  # True
            )doc"
        )
        .def_static(
            "boolean",
            &String::Boolean,
            R"doc(
                Create a String from a boolean value.

                Args:
                    value (bool): The boolean value to convert.

                Returns:
                    String: A String containing "True" or "False".

                Example:
                    >>> String.boolean(True)  # String("True")
                    >>> String.boolean(False)  # String("False")
            )doc",
            arg("value")
        )
        .def_static(
            "char",
            &String::Char,
            R"doc(
                Create a String from a single character.

                Args:
                    character (str): A single character.

                Returns:
                    String: A String containing the single character.

                Example:
                    >>> String.char('A')  # String("A")
            )doc",
            arg("character")
        )
        .def_static(
            "replicate",
            static_cast<String (*)(const String&, Size)>(&String::Replicate),
            R"doc(
                Create a String by replicating another String multiple times.

                Args:
                    string (String): The String to replicate.
                    count (int): The number of times to replicate.

                Returns:
                    String: A new String containing the repeated content.

                Example:
                    >>> String.replicate(String("ab"), 3)  # String("ababab")
                    >>> String.replicate(String("x"), 5)  # String("xxxxx")
            )doc",
            arg("string"),
            arg("count")
        )
        // .def_static("format", &String::Format)

        ;

    implicitly_convertible<std::string, String>();
}
