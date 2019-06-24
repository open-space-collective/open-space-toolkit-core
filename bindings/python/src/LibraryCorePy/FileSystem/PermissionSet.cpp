////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           LibraryCorePy/FileSystem/PermissionSet.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/PermissionSet.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_FileSystem_PermissionSet      ( )
{

    using namespace boost::python ;

    using library::core::fs::PermissionSet ;

    scope in_PermissionSet = class_<PermissionSet>("PermissionSet", init<const bool, const bool, const bool>())

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isNone", &PermissionSet::isNone)
        .def("isAll", &PermissionSet::isAll)
        .def("canRead", &PermissionSet::canRead)
        .def("canWrite", &PermissionSet::canWrite)
        .def("canExecute", &PermissionSet::canExecute)

        .def("None", &PermissionSet::None).staticmethod("None")
        .def("R", &PermissionSet::R).staticmethod("R")
        .def("W", &PermissionSet::W).staticmethod("W")
        .def("X", &PermissionSet::X).staticmethod("X")
        .def("RW", &PermissionSet::RW).staticmethod("RW")
        .def("RX", &PermissionSet::RX).staticmethod("RX")
        .def("RWX", &PermissionSet::RWX).staticmethod("RWX")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
