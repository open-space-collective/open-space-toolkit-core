////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Types/Integer.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

struct Pet {
    Pet(const std::string &name) : name(name) { }
    void setName(const std::string &name_) { name = name_; }
    const std::string &getName() const { return name; }

    std::string name;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     Integer                                     (           auto&                       aModule                                     )
{

    py::class_<Pet>(aModule, "Pet")
        .def(py::init<const std::string &>())
        .def("setName", &Pet::setName)
        .def("getName", &Pet::getName) ;

    // using namespace boost::python ;

    // using ostk::core::types::Integer ;
    // using ostk::core::types::Real ;
    // using ostk::core::types::String ;

    // class_<Integer>("Integer", init<int>())

    //     .def(int_(self))

    //     .def(self == self)
    //     .def(self != self)
    //     .def(self < self)
    //     .def(self <= self)
    //     .def(self > self)
    //     .def(self >= self)

    //     .def(self + self)
    //     .def(self += self)
    //     .def(self - self)
    //     .def(self -= self)
    //     .def(self * self)
    //     .def(self *= self)
    //     .def(self / self)
    //     .def(self /= self)

    //     .def(self + int())
    //     .def(self += int())
    //     .def(self - int())
    //     .def(self -= int())
    //     .def(self * int())
    //     .def(self *= int())
    //     .def(self / int())
    //     .def(self /= int())

    //     .def(int() + self)
    //     .def(int() - self)
    //     .def(int() * self)
    //     .def(int() / self)

    //     .def("__str__", +[] (const ostk::core::types::Integer& anInteger) -> std::string { return anInteger.toString() ; })
    //     .def("__repr__", +[] (const ostk::core::types::Integer& anInteger) -> std::string { return anInteger.toString() ; })

    //     .def("is_defined", &Integer::isDefined)
    //     .def("is_zero", &Integer::isZero)
    //     .def("is_positive", &Integer::isPositive)
    //     .def("is_negative", &Integer::isNegative)
    //     .def("is_strictly_positive", &Integer::isStrictlyPositive)
    //     .def("is_strictly_negative", &Integer::isStrictlyNegative)
    //     .def("is_infinity", &Integer::isInfinity)
    //     .def("is_positive_infinity", &Integer::isPositiveInfinity)
    //     .def("is_negative_infinity", &Integer::isNegativeInfinity)
    //     .def("is_finite", &Integer::isFinite)
    //     .def("is_even", &Integer::isEven)
    //     .def("is_odd", &Integer::isOdd)

    //     .def("get_sign", &Integer::getSign)
    //     .def("to_string", &Integer::toString)

    //     .def("undefined", &Integer::Undefined).staticmethod("undefined")
    //     .def("zero", &Integer::Zero).staticmethod("zero")
    //     .def("positive_infinity", &Integer::PositiveInfinity).staticmethod("positive_infinity")
    //     .def("negative_infinity", &Integer::NegativeInfinity).staticmethod("negative_infinity")
    //     .def("int8", &Integer::Int8).staticmethod("int8")
    //     .def("int16", &Integer::Int16).staticmethod("int16")
    //     .def("int32", &Integer::Int32).staticmethod("int32")
    //     .def("int64", &Integer::Int64).staticmethod("int64")
    //     .def("uint8", &Integer::Uint8).staticmethod("uint8")
    //     .def("uint16", &Integer::Uint16).staticmethod("uint16")
    //     .def("uint32", &Integer::Uint32).staticmethod("uint32")
    //     .def("uint64", &Integer::Uint64).staticmethod("uint64")
    //     .def("index", &Integer::Index).staticmethod("index")
    //     .def("size", &Integer::Size).staticmethod("size")
    //     .def("can_parse", static_cast<bool(*)(const String&)>(&Integer::CanParse)).staticmethod("can_parse")
    //     .def("parse", static_cast<Integer(*)(const String&)>(&Integer::Parse)).staticmethod("parse")

    // ;

    // implicitly_convertible<Integer, int>() ;
    // implicitly_convertible<int, Integer>() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
