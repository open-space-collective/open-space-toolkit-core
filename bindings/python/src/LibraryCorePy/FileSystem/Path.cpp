////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/LibraryCorePy/FileSystem/Path.cpp
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

        .def("is_defined", &Path::isDefined)
        .def("is_absolute", &Path::isAbsolute)
        .def("is_relative", &Path::isRelative)
        .def("get_parent_path", &Path::getParentPath)
        .def("get_last_element", &Path::getLastElement)
        .def("get_normalized_path", &Path::getNormalizedPath)
        .def("get_absolute_path", &Path::getAbsolutePath)
        // .def("get_relative_path_to", &Path::getRelativePathTo)
        .def("to_string", &Path::toString)

        .def("undefined", &Path::Undefined).staticmethod("undefined")
        .def("root", &Path::Root).staticmethod("root")
        .def("current", &Path::Current).staticmethod("current")
        .def("parse", &Path::Parse).staticmethod("parse")
        // .def("strings", &Path::Strings).staticmethod("strings")

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
