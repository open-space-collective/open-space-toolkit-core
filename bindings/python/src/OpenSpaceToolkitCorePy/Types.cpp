////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Types.cpp
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkitCorePy/Types/String.cpp>
#include <OpenSpaceToolkitCorePy/Types/Real.cpp>
#include <OpenSpaceToolkitCorePy/Types/Integer.cpp>
#include <OpenSpaceToolkitCorePy/Types/Sign.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_Types                (           pybind11::module&           aModule                                     )
{

    // Create "types" python submodule
    auto types = aModule.def_submodule("types") ;

    // Add __path__ attribute for "types" submodule
    types.attr("__path__") = "ostk.core.types" ;

    // Add custom types to python "types" submodule
    OpenSpaceToolkitCorePy_Types_Sign(types) ;
    OpenSpaceToolkitCorePy_Types_Integer(types) ;
    OpenSpaceToolkitCorePy_Types_Real(types) ;
    OpenSpaceToolkitCorePy_Types_String(types) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
