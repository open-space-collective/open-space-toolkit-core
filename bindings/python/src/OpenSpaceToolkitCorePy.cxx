/// Apache License 2.0

#include <OpenSpaceToolkitCorePy/Utility/ShiftToString.hpp>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>

#include <OpenSpaceToolkitCorePy/Container.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem.cpp>
#include <OpenSpaceToolkitCorePy/Logger.cpp>
#include <OpenSpaceToolkitCorePy/Type.cpp>

PYBIND11_MODULE(OpenSpaceToolkitCorePy, m)
{
    // Add optional docstring for package OpenSpaceToolkitCorePy
    m.doc() = "Fundamental types, container and utility for OpenSpaceToolkit.";

    // Change attribute __name__ to make OpenSpaceToolkitCorePy invisible in import path
    m.attr("__name__") = "ostk.core";

// Package version information
#ifdef VERSION_INFO
    m.attr("__version__") = VERSION_INFO;
#else
    m.attr("__version__") = "dev";
#endif

    // Add python submodules to OpenSpaceToolkitCorePy
    OpenSpaceToolkitCorePy_Type(m);
    OpenSpaceToolkitCorePy_FileSystem(m);
    OpenSpaceToolkitCorePy_Container(m);
    OpenSpaceToolkitCorePy_Logger(m);
}
