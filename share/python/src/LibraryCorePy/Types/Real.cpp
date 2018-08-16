////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           LibraryCorePy/Types/Real.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

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

    .def("isDefined", &Real::isDefined)
    .def("isZero", &Real::isZero)
    .def("isPositive", &Real::isPositive)
    .def("isNegative", &Real::isNegative)
    .def("isStrictlyPositive", &Real::isStrictlyPositive)
    .def("isStrictlyNegative", &Real::isStrictlyNegative)
    .def("isInfinity", &Real::isInfinity)
    .def("isPositiveInfinity", &Real::isPositiveInfinity)
    .def("isNegativeInfinity", &Real::isNegativeInfinity)
    .def("isInteger", &Real::isInteger)
    .def("isFinite", &Real::isFinite)

    .def("getSign", &Real::getSign)
    // .def("toString", Real_toString_overloads(args("aPrecision"), "Convert Real to String."))
    // .def("toString", Real_toString_overloads())
    .def("toInteger", &Real::toInteger)
    .def("abs", &Real::abs)
    .def("floor", &Real::floor)
    .def("sqrt", &Real::sqrt)
    
    .def("Undefined", &Real::Undefined).staticmethod("Undefined")
    .def("Zero", &Real::Zero).staticmethod("Zero")
    .def("Pi", &Real::Pi).staticmethod("Pi")
    .def("HalfPi", &Real::HalfPi).staticmethod("HalfPi")
    .def("TwoPi", &Real::TwoPi).staticmethod("TwoPi")
    .def("Epsilon", &Real::Epsilon).staticmethod("Epsilon")
    .def("PositiveInfinity", &Real::PositiveInfinity).staticmethod("PositiveInfinity")
    .def("NegativeInfinity", &Real::NegativeInfinity).staticmethod("NegativeInfinity")
    .def("Integer", &Real::Integer).staticmethod("Integer")
    .def("CanParse", &Real::CanParse).staticmethod("CanParse")
    .def("Parse", &Real::Parse).staticmethod("Parse")

    ;

    implicitly_convertible<Real, double>() ;
    implicitly_convertible<double, Real>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////