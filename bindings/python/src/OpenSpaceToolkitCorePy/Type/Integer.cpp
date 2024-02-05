/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>

inline void OpenSpaceToolkitCorePy_Type_Integer(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::String;

    class_<Integer>(aModule, "Integer")

        // Define init method using pybind11 "init" convenience method
        .def(init<Integer::ValueType>())

        // Define __int__ method for direct conversion (previously .def(int_(self)))
        .def(
            "__int__",
            +[](const ostk::core::type::Integer& anInteger) -> int
            {
                return static_cast<int>(anInteger);
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

        .def(self + int())
        .def(self += int())
        .def(self - int())
        .def(self -= int())
        .def(self * int())
        .def(self *= int())
        .def(self / int())
        .def(self /= int())

        .def(int() + self)
        .def(int() - self)
        .def(int() * self)
        .def(int() / self)

        .def(
            "__str__",
            +[](const ostk::core::type::Integer& anInteger) -> std::string
            {
                return anInteger.toString();
            }
        )
        .def(
            "__repr__",
            +[](const ostk::core::type::Integer& anInteger) -> std::string
            {
                return anInteger.toString();
            }
        )
        .def(
            "__hash__",
            +[](const ostk::core::type::Integer& anInteger) -> std::size_t
            {
                return std::hash<Integer::ValueType>()(anInteger);
            }
        )

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

        // Define static methods
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
        .def_static("can_parse", static_cast<bool (*)(const String&)>(&Integer::CanParse))
        .def_static("parse", static_cast<Integer (*)(const String&)>(&Integer::Parse))

        ;

    // Implicit conversion (allowed in the direction of the binded custom type only in pybind11)
    implicitly_convertible<Integer::ValueType, Integer>();
}
