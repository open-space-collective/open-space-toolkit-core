/// Apache License 2.0

#include <pybind11/pybind11.h>
// #include <pybind11/cast.h>
#include <pybind11/stl.h>

// #include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>

namespace pybind11
{
namespace detail
{

// using ostk::core::types::Real;
using ostk::core::ctnr::Array;

template <typename T>
struct type_caster<Array<T>> : list_caster<Array<T>, T>
{
};

// template <>
// struct type_caster<Real> {
// public:
//     PYBIND11_TYPE_CASTER(Real, _("Real"));

//     // Convert Python object back to C++ Real
//     bool load(handle src, bool convert) {
//         if (!convert) return false;
//         if (!pybind11::isinstance<pybind11::float_>(src)) return false;
//         value = Real::ValueType(pybind11::cast<double>(src));
//         return true;
//     }

//     // Convert Real to Python float
//     static handle cast(const Real &src, return_value_policy /* policy */, handle /* parent */) {
//         return pybind11::float_(Real::ValueType(src));
//     }
// };

// using list_caster::load ;
// using list_caster::cast ;

}  // namespace detail
}  // namespace pybind11
