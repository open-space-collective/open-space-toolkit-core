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

inline void                     OpenSpaceToolkitCorePy_FileSystem                    ( )
{

    boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("library.core.filesystem")))) ;

    boost::python::scope().attr("filesystem") = module ;

    boost::python::scope scope = module ;

    OpenSpaceToolkitCorePy_FileSystem_PermissionSet() ;
    OpenSpaceToolkitCorePy_FileSystem_Path() ;
    OpenSpaceToolkitCorePy_FileSystem_File() ;
    OpenSpaceToolkitCorePy_FileSystem_Directory() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
