////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy.cxx
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <pybind11/pybind11.h>

// int add(int i, int j) {
//     return i + j;
// }

// PYBIND11_MODULE(example, m) {
//     m.doc() = "pybind11 example plugin"; // optional module docstring

//     m.def("add", &add, "A function which adds two numbers");
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>

#include <OpenSpaceToolkitCorePy/Types.cpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PYBIND11_MODULE (OpenSpaceToolkitCorePy, m)
{

    m.doc() = "YOYO"; // optional module docstring

    m.attr("__path__") = "ostk.core" ;

    m.attr("__name__") = "ostk.core" ;

    // py::handle package = py::scope(m) ;

    // package.attr("__path__") = "ostk" ;

    // py::scope() ;

    // auto core = m.def_submodule("core") ;

    // // py::module m("ostk", "pybind11 example plugin") ;

    // // pybind11::object package = pybind11::scope() ;

    // py::object package = py::scope(m) ;

    // package.attr("__path__") = "ostk" ;

    // py::module types = m.def_submodule("types", "Types is a submodule of OpenSpaceToolkitCorePy") ;

    OpenSpaceToolkitCorePy_Types(m) ;

    // m.doc() = "Orks live here";

    // py::module peon = m.def_submodule("peon", "A peon is a submodule of 'OpenSpaceToolkitCorePy'");
    // peon.def("work_work", &Peon::work_work, "Do some work");

    // OpenSpaceToolkitCorePy_Types(ostk) ;

    // m.doc() = R"pbdoc(
    //     Pybind11 example plugin
    //     -----------------------
    //     .. currentmodule:: OpenSpaceToolkitCorePy
    //     .. autosummary::
    //        :toctree: _generate
    //        add
    //        subtract
    // )pbdoc";

    // m.def("add", &add, R"pbdoc(
    //     Add two numbers
    //     Some other explanation about the add function.
    // )pbdoc");

    // m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
    //     Subtract two numbers
    //     Some other explanation about the substract function.
    // )pbdoc");

    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO ;
    #else
        m.attr("__version__") = "dev" ;
    #endif


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
