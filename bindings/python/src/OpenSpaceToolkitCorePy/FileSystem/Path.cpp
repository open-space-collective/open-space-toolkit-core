////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/Path.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>  // exposes py::self

#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_Path                     (            py::module&                     aModule                )
{

    using ostk::core::fs::Path ;

    py::class_<Path>(aModule, "Path")

        // Define init method using pybind11 "init" convenience method
        // No init here

        // Define methods
        .def(py::self == py::self)
        .def(py::self != py::self)

        .def(py::self + py::self)
        .def(py::self += py::self)

        // .def(py::self_ns::str(py::self_ns::py::self))
        // .def(py::self_ns::repr(py::self_ns::py::self))

        .def("is_defined", &Path::isDefined)
        .def("is_absolute", &Path::isAbsolute)
        .def("is_relative", &Path::isRelative)
        .def("get_parent_path", &Path::getParentPath)
        .def("get_last_element", &Path::getLastElement)
        .def("get_normalized_path", &Path::getNormalizedPath)
        .def("get_absolute_path", &Path::getAbsolutePath)
        // .def("get_relative_path_to", &Path::getRelativePathTo)
        .def("to_string", &Path::toString)

        // Define static methods
        .def_static("undefined", &Path::Undefined)
        .def_static("root", &Path::Root)
        .def_static("current", &Path::Current)
        .def_static("parse", &Path::Parse)
        // .def("strings", &Path::Strings).staticmethod("strings")

    ;

    // scope in_Path = class_<Path>("Path", no_init)

    //     .def(self == self)
    //     .def(self != self)

    //     .def(self + self)
    //     .def(self += self)

    //     .def(self_ns::str(self_ns::self))
    //     .def(self_ns::repr(self_ns::self))

    //     .def("is_defined", &Path::isDefined)
    //     .def("is_absolute", &Path::isAbsolute)
    //     .def("is_relative", &Path::isRelative)
    //     .def("get_parent_path", &Path::getParentPath)
    //     .def("get_last_element", &Path::getLastElement)
    //     .def("get_normalized_path", &Path::getNormalizedPath)
    //     .def("get_absolute_path", &Path::getAbsolutePath)
    //     // .def("get_relative_path_to", &Path::getRelativePathTo)
    //     .def("to_string", &Path::toString)

    //     .def("undefined", &Path::Undefined).staticmethod("undefined")
    //     .def("root", &Path::Root).staticmethod("root")
    //     .def("current", &Path::Current).staticmethod("current")
    //     .def("parse", &Path::Parse).staticmethod("parse")
    //     // .def("strings", &Path::Strings).staticmethod("strings")

    // ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
