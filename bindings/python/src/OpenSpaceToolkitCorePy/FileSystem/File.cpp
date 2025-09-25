/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

using ostk::core::filesystem::File;

inline void OpenSpaceToolkitCorePy_FileSystem_File(pybind11::class_<File>& fileClass)
{
    using namespace pybind11;

    fileClass

        // Define init method using pybind11 "init" convenience method
        // No init here - Files are created via static methods

        // Define methods
        .def(self == self, R"doc(Check if two Files are equal.)doc")
        .def(self != self, R"doc(Check if two Files are not equal.)doc")

        // .def("__str__", +[] (const ostk::core::filesystem::File& aFile) -> str { return aFile.toString() ; })
        // .def("__repr__", +[] (const ostk::core::filesystem::File& aFile) -> str { return aFile.toString() ; })
        .def("__str__", &(shiftToString<File>), R"doc(Return string representation of the File.)doc")
        .def("__repr__", &(shiftToString<File>), R"doc(Return string representation of the File for debugging.)doc")

        .def(
            "is_defined",
            &File::isDefined,
            R"doc(
                Check if the File is defined.

                Returns:
                    bool: True if the File is defined, False otherwise.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/path/to/file.txt"))
                    >>> file.is_defined()  # True
                    >>> undefined_file = File.undefined()
                    >>> undefined_file.is_defined()  # False
            )doc"
        )
        .def(
            "exists",
            &File::exists,
            R"doc(
                Check if the File exists on the filesystem.

                Returns:
                    bool: True if the file exists, False otherwise.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/etc/passwd"))
                    >>> file.exists()  # True (on Unix systems)
                    >>> nonexistent = File.path(Path.parse("/nonexistent/file.txt"))
                    >>> nonexistent.exists()  # False
            )doc"
        )
        .def(
            "get_name",
            &File::getName,
            R"doc(
                Get the name of the File.

                Args:
                    with_extension (bool, optional): Whether to include the file extension. Defaults to True.

                Returns:
                    str: The file name, with or without extension.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/path/to/document.pdf"))
                    >>> file.get_name()  # "document.pdf"
                    >>> file.get_name(False)  # "document"
            )doc",
            arg("withExtension") = true
        )
        .def(
            "get_extension",
            &File::getExtension,
            R"doc(
                Get the file extension.

                Returns:
                    str: The file extension (without the dot).

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/path/to/document.pdf"))
                    >>> file.get_extension()  # "pdf"
                    >>> file_no_ext = File.path(Path.parse("/path/to/README"))
                    >>> file_no_ext.get_extension()  # ""
            )doc"
        )
        .def(
            "get_path",
            &File::getPath,
            R"doc(
                Get the full path of the File.

                Returns:
                    Path: The complete path to the file.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/home/user/document.txt"))
                    >>> path = file.get_path()
                    >>> str(path)  # "/home/user/document.txt"
            )doc"
        )
        .def(
            "get_permissions",
            &File::getPermissions,
            R"doc(
                Get the file permissions.

                Returns:
                    PermissionSet: The permission set for the file.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/etc/passwd"))
                    >>> permissions = file.get_permissions()
            )doc"
        )
        .def(
            "get_parent_directory",
            &File::getParentDirectory,
            R"doc(
                Get the parent directory of the File.

                Returns:
                    Directory: The parent directory containing this file.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/home/user/document.txt"))
                    >>> parent = file.get_parent_directory()
                    >>> str(parent.get_path())  # "/home/user"
            )doc"
        )
        .def(
            "get_contents",
            &File::getContents,
            R"doc(
                Get the contents of the File as a string.

                Returns:
                    str: The file contents.

                Raises:
                    RuntimeError: If the file cannot be read or doesn't exist.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/path/to/text_file.txt"))
                    >>> content = file.get_contents()
                    >>> print(content)  # File contents as string
            )doc"
        )
        .def(
            "to_string",
            &File::toString,
            R"doc(
                Convert the File to a string representation.

                Returns:
                    str: String representation of the file path.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/home/user/document.txt"))
                    >>> file.to_string()  # "/home/user/document.txt"
            )doc"
        )
        // .def("rename_to", &File::renameTo)
        // .def("copy_to_directory", &File::copyToDirectory)
        .def(
            "move_to_directory",
            &File::moveToDirectory,
            R"doc(
                Move the File to a different directory.

                Args:
                    directory (Directory): The target directory to move the file to.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/tmp/document.txt"))
                    >>> target_dir = Directory.path(Path.parse("/home/user/Documents"))
                    >>> file.move_to_directory(target_dir)
            )doc",
            arg("directory")
        )
        .def(
            "create",
            &File::create,
            R"doc(
                Create the File on the filesystem.

                Creates the file if it doesn't exist, including any necessary parent directories.

                Raises:
                    RuntimeError: If the file cannot be created.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/tmp/new_file.txt"))
                    >>> file.create()
            )doc"
        )
        // .def("clear", &File::clear)
        .def(
            "remove",
            &File::remove,
            R"doc(
                Remove the File from the filesystem.

                Deletes the file if it exists.

                Raises:
                    RuntimeError: If the file cannot be removed.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> file = File.path(Path.parse("/tmp/temp_file.txt"))
                    >>> file.remove()
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &File::Undefined,
            R"doc(
                Create an undefined File.

                Returns:
                    File: An undefined File object.

                Example:
                    >>> undefined_file = File.undefined()
                    >>> undefined_file.is_defined()  # False
            )doc"
        )
        .def_static(
            "path",
            &File::Path,
            R"doc(
                Create a File from a file path.

                Args:
                    path (Path): The path to the file.

                Returns:
                    File: A File object representing the specified path.

                Example:
                    >>> from ostk.core.filesystem import Path
                    >>> path = Path.parse("/home/user/document.txt")
                    >>> file = File.path(path)
                    >>> file.get_name()  # "document.txt"
            )doc",
            arg("path")
        )

        ;
}
