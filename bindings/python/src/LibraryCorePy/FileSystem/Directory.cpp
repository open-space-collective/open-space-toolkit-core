////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/LibraryCorePy/FileSystem/Directory.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/Directory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_FileSystem_Directory          ( )
{

    using namespace boost::python ;

    using ostk::core::fs::Directory ;

    scope in_Directory = class_<Directory>("Directory", no_init)

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

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

        .def("undefined", &Directory::Undefined).staticmethod("undefined")
        .def("root", &Directory::Root).staticmethod("root")
        .def("path", &Directory::Path).staticmethod("path")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
