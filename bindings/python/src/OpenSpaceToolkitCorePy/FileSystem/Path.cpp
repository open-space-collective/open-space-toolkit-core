/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

using ostk::core::filesystem::Path;

inline void OpenSpaceToolkitCorePy_FileSystem_Path(pybind11::class_<Path>& pathClass)
{
    using namespace pybind11;

    pathClass

        // Define init method using pybind11 "init" convenience method
        // No init here - Paths are created via static methods

        // Define methods
        .def(self == self, R"doc(Check if two Paths are equal.)doc")
        .def(self != self, R"doc(Check if two Paths are not equal.)doc")

        .def(self + self, R"doc(Concatenate two Paths.)doc")
        .def(self += self, R"doc(Append another Path to this one in-place.)doc")

        .def("__str__", &(shiftToString<Path>), R"doc(Return string representation of the Path.)doc")
        .def("__repr__", &(shiftToString<Path>), R"doc(Return string representation of the Path for debugging.)doc")

        .def(
            "is_absolute",
            &Path::isAbsolute,
            R"doc(
                Check if the Path is absolute.

                Returns:
                    bool: True if the path is absolute (starts from root), False otherwise.

                Example:
                    >>> Path.parse("/home/user").is_absolute()  # True
                    >>> Path.parse("user/documents").is_absolute()  # False
            )doc"
        )
        .def(
            "is_relative",
            &Path::isRelative,
            R"doc(
                Check if the Path is relative.

                Returns:
                    bool: True if the path is relative, False otherwise.

                Example:
                    >>> Path.parse("user/documents").is_relative()  # True
                    >>> Path.parse("/home/user").is_relative()  # False
            )doc"
        )
        .def(
            "get_parent_path",
            &Path::getParentPath,
            R"doc(
                Get the parent path.

                Returns:
                    Path: The parent path.

                Example:
                    >>> path = Path.parse("/home/user/documents")
                    >>> parent = path.get_parent_path()
                    >>> str(parent)  # "/home/user"
            )doc"
        )
        .def(
            "get_last_element",
            &Path::getLastElement,
            R"doc(
                Get the last element (filename or directory name) of the path.

                Returns:
                    str: The last component of the path.

                Example:
                    >>> path = Path.parse("/home/user/document.txt")
                    >>> path.get_last_element()  # "document.txt"
            )doc"
        )
        .def(
            "get_normalized_path",
            &Path::getNormalizedPath,
            R"doc(
                Get a normalized version of the Path.

                Resolves "." and ".." components and removes redundant separators.

                Returns:
                    Path: The normalized path.

                Example:
                    >>> path = Path.parse("/home/user/../user/./documents")
                    >>> normalized = path.get_normalized_path()
                    >>> str(normalized)  # "/home/user/documents"
            )doc"
        )
        .def(
            "get_absolute_path",
            &Path::getAbsolutePath,
            R"doc(
                Get an absolute version of the Path.

                Args:
                    base_path (Path, optional): The base path to resolve against. Defaults to current directory.

                Returns:
                    Path: The absolute path.

                Example:
                    >>> relative_path = Path.parse("documents/file.txt")
                    >>> absolute = relative_path.get_absolute_path()
            )doc",
            arg_v("base_path", Path::Current(), "Path.current()")
        )
        .def(
            "to_string",
            &Path::toString,
            R"doc(
                Convert the Path to a string representation.

                Returns:
                    str: String representation of the path.

                Example:
                    >>> path = Path.parse("/home/user")
                    >>> path.to_string()  # "/home/user"
            )doc"
        )

        // Define static methods
        .def_static(
            "root",
            &Path::Root,
            R"doc(
                Get the root path of the filesystem.

                Returns:
                    Path: The root path ("/" on Unix systems).

                Example:
                    >>> root = Path.root()
                    >>> str(root)  # "/"
            )doc"
        )
        .def_static(
            "current",
            &Path::Current,
            R"doc(
                Get the current working directory path.

                Returns:
                    Path: The current working directory.

                Example:
                    >>> current = Path.current()
                    >>> print(current)  # Current working directory
            )doc"
        )
        .def_static(
            "parse",
            &Path::Parse,
            R"doc(
                Parse a string as a Path.

                Args:
                    path_string (str): The path string to parse.

                Returns:
                    Path: The parsed Path object.

                Example:
                    >>> path = Path.parse("/home/user/documents")
                    >>> path = Path.parse("relative/path")
            )doc",
            arg("path_string")
        )

        ;
}
