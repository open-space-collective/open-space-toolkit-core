////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/PermissionSet.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>  // exposes py::self

#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_PermissionSet                     (           py::module&                     aModule        )
{

    using ostk::core::fs::PermissionSet ;

    py::class_<PermissionSet>(aModule, "PermissionSet")

        // Define init method using pybind11 "init" convenience method
        .def(py::init<const bool, const bool, const bool>())

        // Define methods
        .def(py::self == py::self)
        .def(py::self != py::self)

        .def(py::self + py::self)
        .def(py::self - py::self)

        // .def(py::self_ns::str(py::self_ns::py::self))
        // .def(py::self_ns::repr(py::self_ns::py::self))

        .def("is_none", &PermissionSet::isNone)
        .def("is_all", &PermissionSet::isAll)
        .def("can_read", &PermissionSet::canRead)
        .def("can_write", &PermissionSet::canWrite)
        .def("can_execute", &PermissionSet::canExecute)

        // Define static methods
        .def_static("none", &PermissionSet::None)
        .def_static("r", &PermissionSet::R)
        .def_static("w", &PermissionSet::W)
        .def_static("x", &PermissionSet::X)
        .def_static("rw", &PermissionSet::RW)
        .def_static("rx", &PermissionSet::RX)
        .def_static("rwx", &PermissionSet::RWX)

    ;

    // scope in_PermissionSet = class_<PermissionSet>("PermissionSet", init<const bool, const bool, const bool>())

    //     .def(self == self)
    //     .def(self != self)

    //     .def(self + self)
    //     .def(self - self)

    //     .def(self_ns::str(self_ns::self))
    //     .def(self_ns::repr(self_ns::self))

    //     .def("is_none", &PermissionSet::isNone)
    //     .def("is_all", &PermissionSet::isAll)
    //     .def("can_read", &PermissionSet::canRead)
    //     .def("can_write", &PermissionSet::canWrite)
    //     .def("can_execute", &PermissionSet::canExecute)

    //     .def("none", &PermissionSet::None).staticmethod("none")
    //     .def("r", &PermissionSet::R).staticmethod("r")
    //     .def("w", &PermissionSet::W).staticmethod("w")
    //     .def("x", &PermissionSet::X).staticmethod("x")
    //     .def("rw", &PermissionSet::RW).staticmethod("rw")
    //     .def("rx", &PermissionSet::RX).staticmethod("rx")
    //     .def("rwx", &PermissionSet::RWX).staticmethod("rwx")

    // ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
