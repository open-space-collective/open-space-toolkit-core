////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/File.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>  // exposes py::self

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_File                     (             py::module&                     aModule               )
{

    using ostk::core::fs::File ;

    py::class_<File>(aModule, "File")

        // Define init method using pybind11 "init" convenience method
        // No init here

        // Define methods
        .def(py::self == py::self)
        .def(py::self != py::self)

        // .def(py::self_ns::str(py::self_ns::py::self))
        // .def(py::self_ns::repr(py::self_ns::py::self))

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

        // Define static methods
        .def_static("undefined", &File::Undefined)
        .def_static("path", &File::Path)

    ;


    // scope in_File = class_<File>("File", no_init)

    //     .def(self == self)
    //     .def(self != self)

    //     .def(self_ns::str(self_ns::self))
    //     .def(self_ns::repr(self_ns::self))

    //     .def("is_defined", &File::isDefined)
    //     .def("exists", &File::exists)
    //     .def("get_name", &File::getName)
    //     .def("get_extension", &File::getExtension)
    //     .def("get_path", &File::getPath)
    //     .def("get_permissions", &File::getPermissions)
    //     .def("get_parent_directory", &File::getParentDirectory)
    //     .def("get_contents", &File::getContents)
    //     .def("to_string", &File::toString)
    //     // .def("rename_to", &File::renameTo)
    //     // .def("copy_to_directory", &File::copyToDirectory)
    //     .def("move_to_directory", &File::moveToDirectory)
    //     .def("create", &File::create)
    //     // .def("clear", &File::clear)
    //     .def("remove", &File::remove)

    //     .def("undefined", &File::Undefined).staticmethod("undefined")
    //     .def("path", &File::Path).staticmethod("path")

    // ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
