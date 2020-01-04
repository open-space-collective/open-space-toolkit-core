////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           bindings/python/src/LibraryCorePy/Types/Real.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Types/Real.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS (Real_toString_overloads, library::core::types::Real::toString, 0, 1)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_Types_Real                    ( )
{

    using namespace boost::python ;

    using library::core::types::Integer ;
    using library::core::types::Real ;
    using library::core::types::String ;

    class_<Real>("Real", init<double>())

        .def(float_(self))

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

        .def("__str__", +[] (const library::core::types::Real& aReal) -> std::string { return aReal.toString() ; })
        .def("__repr__", +[] (const library::core::types::Real& aReal) -> std::string { return aReal.toString() ; })

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
        // .def("to_string", Real_toString_overloads(args("aPrecision"), "Convert Real to String."))
        // .def("to_string", Real_toString_overloads())
        .def("to_integer", &Real::toInteger)
        .def("abs", &Real::abs)
        .def("floor", &Real::floor)
        .def("sqrt", &Real::sqrt)

        .def("undefined", &Real::Undefined).staticmethod("undefined")
        .def("zero", &Real::Zero).staticmethod("zero")
        .def("pi", &Real::Pi).staticmethod("pi")
        .def("half_pi", &Real::HalfPi).staticmethod("half_pi")
        .def("two_pi", &Real::TwoPi).staticmethod("two_pi")
        .def("epsilon", &Real::Epsilon).staticmethod("epsilon")
        .def("positive_infinity", &Real::PositiveInfinity).staticmethod("positive_infinity")
        .def("negative_infinity", &Real::NegativeInfinity).staticmethod("negative_infinity")
        .def("integer", &Real::Integer).staticmethod("integer")
        .def("can_parse", &Real::CanParse).staticmethod("can_parse")
        .def("parse", &Real::Parse).staticmethod("parse")

    ;

    implicitly_convertible<Real, double>() ;
    implicitly_convertible<double, Real>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
