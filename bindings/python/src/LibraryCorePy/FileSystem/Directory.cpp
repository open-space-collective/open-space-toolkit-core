////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           LibraryCorePy/FileSystem/Directory.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/Directory.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_FileSystem_Directory          ( )
{

    using namespace boost::python ;

    using library::core::fs::Directory ;

    scope in_Directory = class_<Directory>("Directory", no_init)

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Directory::isDefined)
        .def("exists", &Directory::exists)
        .def("isEmpty", &Directory::isEmpty)
        .def("containsFileWithName", &Directory::containsFileWithName)
        // .def("containsDirectoryWithName", &Directory::containsDirectoryWithName)
        .def("getName", &Directory::getName)
        .def("getPath", &Directory::getPath)
        // .def("getPermissions", &Directory::getPermissions)
        .def("getParentDirectory", &Directory::getParentDirectory)
        // .def("getFiles", &Directory::getFiles)
        .def("getDirectories", &Directory::getDirectories)
        .def("toString", &Directory::toString)
        // .def("renameTo", &Directory::renameTo)
        // .def("copyToDirectory", &Directory::copyToDirectory)
        // .def("moveToDirectory", &Directory::moveToDirectory)
        .def("create", &Directory::create)
        .def("remove", &Directory::remove)

        .def("Undefined", &Directory::Undefined).staticmethod("Undefined")
        .def("Root", &Directory::Root).staticmethod("Root")
        .def("Path", &Directory::Path).staticmethod("Path")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
