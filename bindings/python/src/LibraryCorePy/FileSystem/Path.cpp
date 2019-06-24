////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           LibraryCorePy/FileSystem/Path.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/Path.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_FileSystem_Path               ( )
{

    using namespace boost::python ;

    using library::core::fs::Path ;

    scope in_Path = class_<Path>("Path", no_init)

        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        .def(self_ns::str(self_ns::self))
        .def(self_ns::repr(self_ns::self))

        .def("isDefined", &Path::isDefined)
        .def("isAbsolute", &Path::isAbsolute)
        .def("isRelative", &Path::isRelative)
        .def("getParentPath", &Path::getParentPath)
        .def("getLastElement", &Path::getLastElement)
        .def("getNormalizedPath", &Path::getNormalizedPath)
        .def("getAbsolutePath", &Path::getAbsolutePath)
        // .def("getRelativePathTo", &Path::getRelativePathTo)
        .def("toString", &Path::toString)

        .def("Undefined", &Path::Undefined).staticmethod("Undefined")
        .def("Root", &Path::Root).staticmethod("Root")
        .def("Current", &Path::Current).staticmethod("Current")
        .def("Parse", &Path::Parse).staticmethod("Parse")
        // .def("Strings", &Path::Strings).staticmethod("Strings")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
