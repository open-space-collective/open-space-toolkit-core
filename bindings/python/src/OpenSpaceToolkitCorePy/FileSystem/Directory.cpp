/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

using ostk::core::filesystem::Directory;

inline void OpenSpaceToolkitCorePy_FileSystem_Directory(pybind11::class_<Directory>& directoryClass)
{
    using namespace pybind11;

    directoryClass

        // Define init method using pybind11 "init" convenience method
        // No init here - Directories are created via static methods

        // Define methods
        .def(self == self, R"doc(Check if two Directories are equal.)doc")
        .def(self != self, R"doc(Check if two Directories are not equal.)doc")

        .def("__str__", &(shiftToString<Directory>), R"doc(Return string representation of the Directory.)doc")
        .def("__repr__", &(shiftToString<Directory>), R"doc(Return string representation of the Directory for debugging.)doc")

        .def(
            "is_defined",
            &Directory::isDefined,
            R"doc(
                Check if the Directory is defined.

                Returns:
                    bool: True if the Directory is defined, False otherwise.

                Example:
                    >>> directory = Directory.path("/home/user")
                    >>> directory.is_defined()  # True
            )doc"
        )
        .def(
            "exists",
            &Directory::exists,
            R"doc(
                Check if the Directory exists on the filesystem.

                Returns:
                    bool: True if the directory exists, False otherwise.

                Example:
                    >>> directory = Directory.path("/home")
                    >>> directory.exists()  # True (usually)
            )doc"
        )
        .def(
            "is_empty",
            &Directory::isEmpty,
            R"doc(
                Check if the Directory is empty.

                Returns:
                    bool: True if the directory contains no files or subdirectories, False otherwise.

                Example:
                    >>> directory = Directory.path("/tmp")
                    >>> directory.is_empty()  # Depends on contents
            )doc"
        )
        .def(
            "contains_file_with_name",
            &Directory::containsFileWithName,
            R"doc(
                Check if the Directory contains a file with the specified name.

                Args:
                    name (str): The name of the file to search for.

                Returns:
                    bool: True if a file with the given name exists in the directory.

                Example:
                    >>> directory = Directory.path("/home/user")
                    >>> directory.contains_file_with_name("document.txt")  # True/False
            )doc",
            arg("name")
        )
        .def(
            "get_name",
            &Directory::getName,
            R"doc(
                Get the name of the Directory.

                Returns:
                    str: The directory name (last component of the path).

                Example:
                    >>> directory = Directory.path("/home/user/Documents")
                    >>> directory.get_name()  # "Documents"
            )doc"
        )
        .def(
            "get_path",
            &Directory::getPath,
            R"doc(
                Get the full path of the Directory.

                Returns:
                    Path: The complete path to the directory.

                Example:
                    >>> directory = Directory.path("/home/user")
                    >>> path = directory.get_path()
                    >>> str(path)  # "/home/user"
            )doc"
        )
        .def(
            "get_parent_directory",
            &Directory::getParentDirectory,
            R"doc(
                Get the parent directory of this Directory.

                Returns:
                    Directory: The parent directory.

                Example:
                    >>> directory = Directory.path("/home/user/Documents")
                    >>> parent = directory.get_parent_directory()
                    >>> parent.get_name()  # "user"
            )doc"
        )
        .def(
            "get_directories",
            &Directory::getDirectories,
            R"doc(
                Get all subdirectories in this Directory.

                Returns:
                    list[Directory]: A list of subdirectories.

                Example:
                    >>> directory = Directory.path("/home/user")
                    >>> subdirs = directory.get_directories()
            )doc"
        )
        .def(
            "to_string",
            &Directory::toString,
            R"doc(
                Convert the Directory to a string representation.

                Returns:
                    str: String representation of the directory path.

                Example:
                    >>> directory = Directory.path("/home/user")
                    >>> directory.to_string()  # "/home/user"
            )doc"
        )
        .def(
            "create",
            &Directory::create,
            R"doc(
                Create the Directory on the filesystem.

                Creates the directory and any necessary parent directories.

                Raises:
                    RuntimeError: If the directory cannot be created.

                Example:
                    >>> directory = Directory.path("/tmp/new_directory")
                    >>> directory.create()
            )doc"
        )
        .def(
            "remove",
            &Directory::remove,
            R"doc(
                Remove the Directory from the filesystem.

                Removes the directory and all its contents recursively.

                Raises:
                    RuntimeError: If the directory cannot be removed.

                Example:
                    >>> directory = Directory.path("/tmp/temp_directory")
                    >>> directory.remove()
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &Directory::Undefined,
            R"doc(
                Create an undefined Directory.

                Returns:
                    Directory: An undefined Directory object.

                Example:
                    >>> undefined_dir = Directory.undefined()
                    >>> undefined_dir.is_defined()  # False
            )doc"
        )
        .def_static(
            "root",
            &Directory::Root,
            R"doc(
                Get the root directory of the filesystem.

                Returns:
                    Directory: The root directory ("/" on Unix systems).

                Example:
                    >>> root = Directory.root()
                    >>> root.get_name()  # "/"
            )doc"
        )
        .def_static(
            "path",
            &Directory::Path,
            R"doc(
                Create a Directory from a path.

                Args:
                    path (Path): The path to the directory.

                Returns:
                    Directory: A Directory object representing the specified path.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> path = Path.parse("/home/user")
                    >>> directory = Directory.path(path)
            )doc",
            arg("path")
        )

        ;
}
