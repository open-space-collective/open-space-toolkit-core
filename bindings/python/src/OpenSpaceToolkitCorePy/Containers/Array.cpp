////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Containers/Array.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>

#include <OpenSpaceToolkitCorePy/Containers/ArrayCasting.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::ctnr::Array ;
using ostk::core::types::Integer ;
using ostk::core::types::Real ;
using ostk::core::types::String ;

// Define Cpp Functions
void          set_int_array(const Array<int>& anArray) { (void) anArray ; }
void          set_double_array(const Array<double>& anArray) { (void) anArray ; }
void          set_integer_array(const Array<Integer>& anArray) { (void) anArray ; }
void          set_real_array(const Array<Real>& anArray) { (void) anArray ; }
void          set_string_array(const Array<String>& anArray) { (void) anArray ; }

Array<int>    get_int_array() { Array<int> vector = { 1, 2, 3 } ; return vector ; }
Array<double>    get_double_array() { Array<double> vector = { 1.0, 2.0, 3.0 } ; return vector ; }
Array<Integer>    get_integer_array() { Array<Integer> vector = { 1, 2, 3 } ; return vector ; }
Array<Real>    get_real_array() { Array<Real> vector = { 1.0, 2.0, 3.0 } ; return vector ; }
Array<String>    get_string_array() { Array<String> vector = { "abc", "def", "ghi" } ; return vector ; }

// Define Python Module
inline void                     OpenSpaceToolkitCorePy_Containers_Array                     (           pybind11::module&                     aModule          )
{

    using namespace pybind11 ;

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    using ostk::core::ctnr::Array ;

    aModule.def("set_int_array", overload_cast<const Array<int>&>(&set_int_array));
    aModule.def("set_double_array", overload_cast<const Array<double>&>(&set_double_array));
    aModule.def("set_integer_array", overload_cast<const Array<Integer>&>(&set_integer_array));
    aModule.def("set_real_array", overload_cast<const Array<Real>&>(&set_real_array));
    aModule.def("set_string_array", overload_cast<const Array<String>&>(&set_string_array));

    aModule.def("get_int_array", (&get_int_array));
    aModule.def("get_double_array", (&get_double_array));
    aModule.def("get_integer_array", (&get_integer_array));
    aModule.def("get_real_array", (&get_real_array));
    aModule.def("get_string_array", (&get_string_array));

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
