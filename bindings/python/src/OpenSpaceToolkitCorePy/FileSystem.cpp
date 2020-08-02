////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <OpenSpaceToolkitCorePy/FileSystem/SymbolicLink.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/Directory.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/File.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/Path.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/PermissionSet.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem                    (py::module&                       aModule)
{

    auto filesystem = aModule.def_submodule("filesystem") ;

    OpenSpaceToolkitCorePy_FileSystem_PermissionSet(filesystem) ;
    OpenSpaceToolkitCorePy_FileSystem_Path(filesystem) ;
    OpenSpaceToolkitCorePy_FileSystem_File(filesystem) ;
    OpenSpaceToolkitCorePy_FileSystem_Directory(filesystem) ;


    // boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.core.filesystem")))) ;

    // boost::python::scope().attr("filesystem") = module ;

    // boost::python::scope scope = module ;

    // OpenSpaceToolkitCorePy_FileSystem_PermissionSet() ;
    // OpenSpaceToolkitCorePy_FileSystem_Path() ;
    // OpenSpaceToolkitCorePy_FileSystem_File() ;
    // OpenSpaceToolkitCorePy_FileSystem_Directory() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
