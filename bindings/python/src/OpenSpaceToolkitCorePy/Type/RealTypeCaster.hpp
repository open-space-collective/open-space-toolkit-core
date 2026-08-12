/// Apache License 2.0

#ifndef __OpenSpaceToolkitCorePy_Type_RealTypeCaster__
#define __OpenSpaceToolkitCorePy_Type_RealTypeCaster__

#include <cmath>
#include <limits>

#include <pybind11/pybind11.h>

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

namespace pybind11
{
namespace detail
{

/// @brief Custom type caster for ostk::core::type::Real.
///
/// Converts between C++ Real and Python float transparently.
/// - Real::Undefined() <-> float('nan')
/// - Real::PositiveInfinity() <-> float('inf')
/// - Real::NegativeInfinity() <-> float('-inf')
/// - Real(value) <-> float(value)

template <>
struct type_caster<ostk::core::type::Real>
{
   protected:
    ostk::core::type::Real value {0.0};

   public:
    static constexpr auto name = const_name("float");

    template <
        typename T_,
        enable_if_t<std::is_same<ostk::core::type::Real, remove_cv_t<T_>>::value, int> = 0>
    static handle cast(T_* src, return_value_policy policy, handle parent)
    {
        if (!src)
        {
            return none().release();
        }

        if (policy == return_value_policy::take_ownership)
        {
            auto h = cast(std::move(*src), policy, parent);
            delete src;
            return h;
        }

        return cast(*src, policy, parent);
    }

    operator ostk::core::type::Real*()
    {
        return &value;
    }

    operator ostk::core::type::Real&()
    {
        return value;
    }

    operator ostk::core::type::Real&&() &&
    {
        return std::move(value);
    }

    template <typename T_>
    using cast_op_type = movable_cast_op_type<T_>;

    bool load(handle src, bool /*convert*/)
    {
        if (src.is_none())
        {
            return false;
        }

        PyObject* tmp = PyNumber_Float(src.ptr());

        if (!tmp)
        {
            PyErr_Clear();
            return false;
        }

        const double val = PyFloat_AsDouble(tmp);
        Py_DECREF(tmp);

        if (PyErr_Occurred())
        {
            PyErr_Clear();
            return false;
        }

        if (std::isnan(val))
        {
            value = ostk::core::type::Real::Undefined();
        }
        else if (std::isinf(val))
        {
            value =
                val > 0 ? ostk::core::type::Real::PositiveInfinity() : ostk::core::type::Real::NegativeInfinity();
        }
        else
        {
            value = ostk::core::type::Real(val);
        }

        return true;
    }

    static handle cast(const ostk::core::type::Real& src, return_value_policy /*policy*/, handle /*parent*/)
    {
        if (!src.isDefined())
        {
            return PyFloat_FromDouble(std::numeric_limits<double>::quiet_NaN());
        }

        if (src.isPositiveInfinity())
        {
            return PyFloat_FromDouble(std::numeric_limits<double>::infinity());
        }

        if (src.isNegativeInfinity())
        {
            return PyFloat_FromDouble(-std::numeric_limits<double>::infinity());
        }

        return PyFloat_FromDouble(static_cast<double>(src));
    }
};

}  // namespace detail
}  // namespace pybind11

#endif
