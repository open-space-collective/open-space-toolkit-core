////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy.cxx
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <pybind11/pybind11.h>

int add(int i, int j) {
    return i + j;
}

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

    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function which adds two numbers");

    // auto ostk = m.def_submodule("ostk") ;

    // py::module m("ostk", "pybind11 example plugin") ;

    // pybind11::object package = pybind11::scope() ;

    // package.attr("__path__") = "ostk" ;

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
    //     Some other explanation about the subtract function.
    // )pbdoc");

    #ifdef VERSION_INFO
        m.attr("__version__") = VERSION_INFO ;
    #else
        m.attr("__version__") = "dev" ;
    #endif

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
