////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           bindings/python/src/LibraryCorePy/FileSystem/File.cpp
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

        .def("is_defined", &File::isDefined)
        .def("exists", &File::exists)
        .def("get_name", &File::getName)
        .def("get_extension", &File::getExtension)
        .def("get_path", &File::getPath)
        .def("get_permissions", &File::getPermissions)
        .def("get_parent_directory", &File::getParentDirectory)
        .def("get_contents", &File::getContents)
        .def("to_string", &File::toString)
        // .def("rename_to", &File::renameTo)
        // .def("copy_to_directory", &File::copyToDirectory)
        .def("move_to_directory", &File::moveToDirectory)
        .def("create", &File::create)
        // .def("clear", &File::clear)
        .def("remove", &File::remove)

        .def("undefined", &File::Undefined).staticmethod("undefined")
        .def("path", &File::Path).staticmethod("path")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
