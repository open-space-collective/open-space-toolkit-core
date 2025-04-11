/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Real.hpp>

using ostk::core::type::Integer;
using ostk::core::type::Real;
using ostk::core::type::String;

inline void OpenSpaceToolkitCorePy_Type_Real(pybind11::class_<Real>& realClass)
{
    using namespace pybind11;

    realClass

        // Define init method using pybind11 "init" convenience method
        .def(init<Real::ValueType>())

        // Define __float__ method for direct conversion
        .def(
            "__float__",
            +[](const ostk::core::type::Real& aReal) -> double
            {
                return static_cast<double>(aReal);
            }
        )

        // Define methods
        .def(self == self)
        .def(self != self)
        .def(self < self)
        .def(self <= self)
        .def(self > self)
        .def(self >= self)

        .def(self + self)
        .def(self += self)
        .def(self - self)
        .def(self -= self)
        .def(self * self)
        .def(self *= self)
        .def(self / self)
        .def(self /= self)

        .def(self + double())
        .def(self += double())
        .def(self - double())
        .def(self -= double())
        .def(self * double())
        .def(self *= double())
        .def(self / double())
        .def(self /= double())

        .def(double() + self)
        .def(double() - self)
        .def(double() * self)
        .def(double() / self)

        .def(
            "__str__",
            +[](const ostk::core::type::Real& aReal) -> std::string
            {
                return aReal.toString();
            }
        )
        .def(
            "__repr__",
            +[](const ostk::core::type::Real& aReal) -> std::string
            {
                return aReal.toString();
            }
        )
        .def(
            "__hash__",
            +[](const ostk::core::type::Real& aReal) -> std::size_t
            {
                return std::hash<Real::ValueType>()(aReal);
            }
        )

        .def("is_defined", &Real::isDefined)
        .def("is_zero", &Real::isZero)
        .def("is_positive", &Real::isPositive)
        .def("is_negative", &Real::isNegative)
        .def("is_strictly_positive", &Real::isStrictlyPositive)
        .def("is_strictly_negative", &Real::isStrictlyNegative)
        .def("is_infinity", &Real::isInfinity)
        .def("is_positive_infinity", &Real::isPositiveInfinity)
        .def("is_negative_infinity", &Real::isNegativeInfinity)
        .def("is_integer", &Real::isInteger)
        .def("is_finite", &Real::isFinite)
        .def("is_near", &Real::isNear)

        .def("get_sign", &Real::getSign)
        .def("to_integer", &Real::toInteger)
        .def("abs", &Real::abs)
        .def("floor", &Real::floor)
        .def("sqrt", &Real::sqrt)

        // Define static methods
        .def_static("undefined", &Real::Undefined)
        .def_static("zero", &Real::Zero)
        .def_static("pi", &Real::Pi)
        .def_static("half_pi", &Real::HalfPi)
        .def_static("two_pi", &Real::TwoPi)
        .def_static("epsilon", &Real::Epsilon)
        .def_static("positive_infinity", &Real::PositiveInfinity)
        .def_static("negative_infinity", &Real::NegativeInfinity)
        .def_static("integer", &Real::Integer)
        .def_static("can_parse", &Real::CanParse)
        .def_static("parse", &Real::Parse)

        ;

    implicitly_convertible<Real::ValueType, Real>();
}
