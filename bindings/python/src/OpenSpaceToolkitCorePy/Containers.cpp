////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Containers.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitCorePy/Containers/Dictionary.cpp>
#include <OpenSpaceToolkitCorePy/Containers/Object.cpp>
#include <OpenSpaceToolkitCorePy/Containers/Array.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_Containers           (           pybind11::module&           aModule                                     )
{

    // Create "containers" python submodule
    auto containers = aModule.def_submodule("containers") ;

    // Add __path__ attribute for "containers" submodule
    containers.attr("__path__") = "ostk.core.containers" ;

    // Add objects to python "containers" submodules
    OpenSpaceToolkitCorePy_Containers_Array(containers) ;
    OpenSpaceToolkitCorePy_Containers_Object(containers) ;
    OpenSpaceToolkitCorePy_Containers_Dictionary(containers) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
