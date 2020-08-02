////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Types.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>

#include <OpenSpaceToolkitCorePy/Types/String.cpp>
#include <OpenSpaceToolkitCorePy/Types/Real.cpp>
#include <OpenSpaceToolkitCorePy/Types/Integer.cpp>

#include <pybind11/embed.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_Types                (           py::module&                       aModule                                     )
{

    // types.attr("__path__") = "ostk.core.types" ;

    auto types = aModule.def_submodule("types") ;

    types.attr("__path__") = "ostk.core.types" ;

    // Using the `PyImport_AddModule` from Python/C API
    // py::object module(py::handle(PyImport_AddModule("ostk.core.types"))) ;

    // auto mod = aModule.import("ostk.core.types") ;

    // thing.attr("types") = mod ;

    // auto module = py::handle::import("ostk.core.types") ;
    // py::scope::scope().attr("types") = module ;

    // py::module m("example", "pybind11 example plugin") ;

    // boost::python::object module(boost::python::handle<>(boost::python::borrowed(PyImport_AddModule("ostk.core.types")))) ;

    // boost::python::scope().attr("types") = module ;

    // boost::python::scope scope = module ;

    OpenSpaceToolkitCorePy_Types_Integer(types) ;
    OpenSpaceToolkitCorePy_Types_Real(types) ;
    OpenSpaceToolkitCorePy_Types_String(types) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
