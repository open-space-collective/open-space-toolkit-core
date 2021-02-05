////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy.cxx
/// @author         Remy Derollez <remy@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>

#include <OpenSpaceToolkitCorePy/Utilities/ShiftToString.hpp>

#include <OpenSpaceToolkitCorePy/Types.cpp>
#include <OpenSpaceToolkitCorePy/Containers.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PYBIND11_MODULE (OpenSpaceToolkitCorePy, m)
{

    // Add optional docstring for package OpenSpaceToolkitCorePy
    m.doc() = "Fundamental types, containers and utilities for OpenSpaceToolkit." ;

    // Add __path__ attribute to python package
    m.attr("__path__") = "ostk.core" ;

    // Change attribute __name__ to make OpenSpaceToolkitCorePy invisible in import path
    m.attr("__name__") = "ostk.core" ;

    // Package version information
    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO ;
    #else
        m.attr("__version__") = "dev" ;
    #endif

    // Add python submodules to OpenSpaceToolkitCorePy
    OpenSpaceToolkitCorePy_Types(m) ;
    OpenSpaceToolkitCorePy_Containers(m) ;
    OpenSpaceToolkitCorePy_FileSystem(m) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
