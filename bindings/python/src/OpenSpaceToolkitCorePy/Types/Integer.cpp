////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Types/Integer.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>  // exposes py::self

#include <OpenSpaceToolkit/Core/Types/Integer.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace py = pybind11 ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_Types_Integer                                    (           py::module&                       aModule               )
{

    // auto integer = aModule.def_submodule("integer") ; Not needed Integer in sublibraries types rn

    using ostk::core::types::Integer ;
    using ostk::core::types::Real ;
    using ostk::core::types::String ;

    // py::class_<Pet>(aModule, "Pet")
    //     .def(py::init<const std::string &>())
    //     .def("setName", &Pet::setName)
    //     .def("getName", &Pet::getName) ;

    py::class_<Integer>(aModule, "Integer")

        .def(py::init<Integer::ValueType>())

        // .def(py::init<py::int_>())

        .def(py::self == py::self)
        .def(py::self != py::self)
        .def(py::self < py::self)
        .def(py::self <= py::self)
        .def(py::self > py::self)
        .def(py::self >= py::self)

        .def(py::self + py::self)
        .def(py::self += py::self)
        .def(py::self - py::self)
        .def(py::self -= py::self)
        .def(py::self * py::self)
        .def(py::self *= py::self)
        .def(py::self / py::self)
        .def(py::self /= py::self)

        .def(py::self + int())
        .def(py::self += int())
        .def(py::self - int())
        .def(py::self -= int())
        .def(py::self * int())
        .def(py::self *= int())
        .def(py::self / int())
        .def(py::self /= int())

        .def(int() + py::self)
        .def(int() - py::self)
        .def(int() * py::self)
        .def(int() / py::self)

        .def("__str__", +[] (const ostk::core::types::Integer& anInteger) -> std::string { return anInteger.toString() ; })
        .def("__repr__", +[] (const ostk::core::types::Integer& anInteger) -> std::string { return anInteger.toString() ; })

        .def("is_defined", &Integer::isDefined)
        .def("is_zero", &Integer::isZero)
        .def("is_positive", &Integer::isPositive)
        .def("is_negative", &Integer::isNegative)
        .def("is_strictly_positive", &Integer::isStrictlyPositive)
        .def("is_strictly_negative", &Integer::isStrictlyNegative)
        .def("is_infinity", &Integer::isInfinity)
        .def("is_positive_infinity", &Integer::isPositiveInfinity)
        .def("is_negative_infinity", &Integer::isNegativeInfinity)
        .def("is_finite", &Integer::isFinite)
        .def("is_even", &Integer::isEven)
        .def("is_odd", &Integer::isOdd)

        .def("get_sign", &Integer::getSign)
        .def("to_string", &Integer::toString)

        // Substitution for implicitly_convertible not working in that direction
        .def("to_int", &Integer::toInt)

        .def_static("undefined", &Integer::Undefined)
        .def_static("zero", &Integer::Zero)
        .def_static("positive_infinity", &Integer::PositiveInfinity)
        .def_static("negative_infinity", &Integer::NegativeInfinity)
        .def_static("int8", &Integer::Int8)
        .def_static("int16", &Integer::Int16)
        .def_static("int32", &Integer::Int32)
        .def_static("int64", &Integer::Int64)
        .def_static("uint8", &Integer::Uint8)
        .def_static("uint16", &Integer::Uint16)
        .def_static("uint32", &Integer::Uint32)
        .def_static("uint64", &Integer::Uint64)
        .def_static("index", &Integer::Index)
        .def_static("size", &Integer::Size)
        .def_static("can_parse", static_cast<bool(*)(const String&)>(&Integer::CanParse))
        .def_static("parse", static_cast<Integer(*)(const String&)>(&Integer::Parse))

    ;

    // py::implicitly_convertible<Integer::ValueType, Integer>() ;




}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
