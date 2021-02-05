////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem/File.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem_File      (           pybind11::module&           aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::fs::File ;

    class_<File>(aModule, "File")

        // Define init method using pybind11 "init" convenience method
        // No init here

        // Define methods
        .def(self == self)
        .def(self != self)

        // .def("__str__", +[] (const ostk::core::fs::File& aFile) -> str { return aFile.toString() ; })
        // .def("__repr__", +[] (const ostk::core::fs::File& aFile) -> str { return aFile.toString() ; })
        .def("__str__", &(shiftToString<File>))
        .def("__repr__", &(shiftToString<File>))

        .def("is_defined", &File::isDefined)
        .def("exists", &File::exists)
        .def("get_name", &File::getName, "withExtension"_a=true)
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

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
