////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           LibraryCorePy/FileSystem/File.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/File.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_FileSystem_File               ( )
{

    using namespace boost::python ;

    using library::core::fs::File ;

    scope in_File = class_<File>("File", no_init)

        .def(self == self)
        .def(self != self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &File::isDefined)
        .def("exists", &File::exists)
        .def("getName", &File::getName)
        .def("getExtension", &File::getExtension)
        .def("getPath", &File::getPath)
        .def("getPermissions", &File::getPermissions)
        .def("getParentDirectory", &File::getParentDirectory)
        .def("getContents", &File::getContents)
        .def("toString", &File::toString)
        // .def("renameTo", &File::renameTo)
        // .def("copyToDirectory", &File::copyToDirectory)
        .def("moveToDirectory", &File::moveToDirectory)
        .def("create", &File::create)
        // .def("clear", &File::clear)
        .def("remove", &File::remove)
        
        .def("Undefined", &File::Undefined).staticmethod("Undefined")
        .def("Path", &File::Path).staticmethod("Path")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////