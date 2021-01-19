////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/Path.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_Path                     (            pybind11::module&                     aModule          )
{

    using namespace pybind11 ;

    using ostk::core::fs::Path ;

    class_<Path>(aModule, "Path")

        // Define init method using pybind11 "init" convenience method
        // No init here

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        // .def("__str__", +[] (const ostk::core::fs::Path& aPath) -> str { return aPath.toString() ; })
        // .def("__repr__", +[] (const ostk::core::fs::Path& aPath) -> str { return aPath.toString() ; })
        .def("__str__", &(shift_to_string<Path>))
        .def("__repr__", &(shift_to_string<Path>))

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
        // .def_static("strings", &Path::Strings)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
