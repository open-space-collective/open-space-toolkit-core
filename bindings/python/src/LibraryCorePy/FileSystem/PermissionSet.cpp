////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/PermissionSet.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_PermissionSet      ( )
{

    using namespace boost::python ;

    using ostk::core::fs::PermissionSet ;

    scope in_PermissionSet = class_<PermissionSet>("PermissionSet", init<const bool, const bool, const bool>())

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("is_none", &PermissionSet::isNone)
        .def("is_all", &PermissionSet::isAll)
        .def("can_read", &PermissionSet::canRead)
        .def("can_write", &PermissionSet::canWrite)
        .def("can_execute", &PermissionSet::canExecute)

        .def("none", &PermissionSet::None).staticmethod("none")
        .def("r", &PermissionSet::R).staticmethod("r")
        .def("w", &PermissionSet::W).staticmethod("w")
        .def("x", &PermissionSet::X).staticmethod("x")
        .def("rw", &PermissionSet::RW).staticmethod("rw")
        .def("rx", &PermissionSet::RX).staticmethod("rx")
        .def("rwx", &PermissionSet::RWX).staticmethod("rwx")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
