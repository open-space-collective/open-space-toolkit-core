////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/PermissionSet.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_PermissionSet (        pybind11::module&          aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::fs::PermissionSet ;

    class_<PermissionSet>(aModule, "PermissionSet")

        // Define init method using pybind11 "init" convenience method
        .def(init<const bool, const bool, const bool>())

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self - self)

        // .def("__str__", +[] (const ostk::core::fs::PermissionSet& aPermissionSet) -> str { return aPermissionSet.toString() ; })
        // .def("__repr__", +[] (const ostk::core::fs::PermissionSet& aPermissionSet) -> str { return aPermissionSet.toString() ; })
        .def("__str__", &(shiftToString<PermissionSet>))
        .def("__repr__", &(shiftToString<PermissionSet>))

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

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
