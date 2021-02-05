////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/Directory.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_Directory (           pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::fs::Directory ;

    class_<Directory>(aModule, "Directory")

        // Define init method using pybind11 "init" convenience method
        // No init here

        // Define methods
        .def(self == self)
        .def(self != self)

        // .def("__str__", +[] (const ostk::core::fs::Directory& aDirectory) -> str { return aDirectory.toString() ; })
        // .def("__repr__", +[] (const ostk::core::fs::Directory& aDirectory) -> str { return aDirectory.toString() ; })
        .def("__str__", &(shiftToString<Directory>))
        .def("__repr__", &(shiftToString<Directory>))

        .def("is_defined", &Directory::isDefined)
        .def("exists", &Directory::exists)
        .def("is_empty", &Directory::isEmpty)
        .def("contains_file_with_name", &Directory::containsFileWithName)
        // .def("contains_directory_with_name", &Directory::containsDirectoryWithName)
        .def("get_name", &Directory::getName)
        .def("get_path", &Directory::getPath)
        // .def("get_permissions", &Directory::getPermissions)
        .def("get_parent_directory", &Directory::getParentDirectory)
        // .def("get_files", &Directory::getFiles)
        .def("get_directories", &Directory::getDirectories)
        .def("to_string", &Directory::toString)
        // .def("rename_to", &Directory::renameTo)
        // .def("copy_to_directory", &Directory::copyToDirectory)
        // .def("move_to_directory", &Directory::moveToDirectory)
        .def("create", &Directory::create)
        .def("remove", &Directory::remove)

        // Define static methods
        .def_static("undefined", &Directory::Undefined)
        .def_static("root", &Directory::Root)
        .def_static("path", &Directory::Path)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
