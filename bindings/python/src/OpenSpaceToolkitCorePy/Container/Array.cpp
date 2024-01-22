/// Apache License 2.0

#include <OpenSpaceToolkitCorePy/Container/ArrayCasting.hpp>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

using ostk::core::container::Array;
using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

/// @brief                      Set and Get Array functions
///
///                             Simple C++ functions using the templated class
///                             "Array" used to test the casting of Arrays from
///                             C++ to python.

void setIntArray(const Array<int>& anArray)
{
    (void)anArray;
}

void setDoubleArray(const Array<double>& anArray)
{
    (void)anArray;
}

void setIntegerArray(const Array<Integer>& anArray)
{
    (void)anArray;
}

void setRealArray(const Array<Real>& anArray)
{
    (void)anArray;
}

void setStringArray(const Array<String>& anArray)
{
    (void)anArray;
}

Array<int> getIntArray()
{
    Array<int> vector = {1, 2, 3};
    return vector;
}

Array<double> getDoubleArray()
{
    Array<double> vector = {1, 2, 3};
    return vector;
}

Array<Integer> getIntegerArray()
{
    Array<Integer> vector = {1, 2, 3};
    return vector;
}

Array<Real> getRealArray()
{
    Array<Real> vector = {1.0, 2.0, 3.0};
    return vector;
}

Array<String> getStringArray()
{
    Array<String> vector = {"abc", "def", "ghi"};
    return vector;
}

inline void OpenSpaceToolkitCorePy_Container_Array(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    using ostk::core::container::Array;

    aModule.def("set_int_array", overload_cast<const Array<int>&>(&setIntArray));
    aModule.def("set_double_array", overload_cast<const Array<double>&>(&setDoubleArray));
    aModule.def("set_integer_array", overload_cast<const Array<Integer>&>(&setIntegerArray));
    aModule.def("set_real_array", overload_cast<const Array<Real>&>(&setRealArray));
    aModule.def("set_string_array", overload_cast<const Array<String>&>(&setStringArray));

    aModule.def("get_int_array", (&getIntArray));
    aModule.def("get_double_array", (&getDoubleArray));
    aModule.def("get_integer_array", (&getIntegerArray));
    aModule.def("get_real_array", (&getRealArray));
    aModule.def("get_string_array", (&getStringArray));
}
