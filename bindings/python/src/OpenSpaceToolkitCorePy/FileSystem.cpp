////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/FileSystem.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <OpenSpaceToolkitCorePy/FileSystem/SymbolicLink.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/Directory.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/File.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/Path.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/PermissionSet.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_FileSystem           (           pybind11::module&           aModule                                     )
{

    // Create "filesystem" python submodule
    auto filesystem = aModule.def_submodule("filesystem") ;

    // Add __path__ attribute for "filesystem" submodule
    filesystem.attr("__path__") = "ostk.core.filesystem" ;

    // Add custom objects to python "filesystem" submodule
    OpenSpaceToolkitCorePy_FileSystem_PermissionSet(filesystem) ;
    OpenSpaceToolkitCorePy_FileSystem_Path(filesystem) ;
    OpenSpaceToolkitCorePy_FileSystem_File(filesystem) ;
    OpenSpaceToolkitCorePy_FileSystem_Directory(filesystem) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
