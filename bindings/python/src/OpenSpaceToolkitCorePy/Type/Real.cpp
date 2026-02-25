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
        .def(
            init<Real::ValueType>(),
            R"doc(
                Construct a Real number from a numeric value.

                Args:
                    value: A numeric value (int, float, or double) to initialize the Real number.

                Example:
                    >>> real = Real(3.14159)
                    >>> real = Real(42)
            )doc",
            arg("value")
        )

        // Define __float__ method for direct conversion
        .def(
            "__float__",
            +[](const ostk::core::type::Real& aReal) -> double
            {
                return static_cast<double>(aReal);
            },
            R"doc(
                Convert the Real number to a Python float.

                Returns:
                    float: The numeric value as a Python float.

                Example:
                    >>> real = Real(3.14159)
                    >>> float(real)  # 3.14159
            )doc"
        )

        // Define methods
        .def(self == self, R"doc(Check if two Real numbers are equal.)doc")
        .def(self != self, R"doc(Check if two Real numbers are not equal.)doc")
        .def(self < self, R"doc(Check if this Real number is less than another.)doc")
        .def(self <= self, R"doc(Check if this Real number is less than or equal to another.)doc")
        .def(self > self, R"doc(Check if this Real number is greater than another.)doc")
        .def(self >= self, R"doc(Check if this Real number is greater than or equal to another.)doc")

        .def(self + self, R"doc(Add two Real numbers.)doc")
        .def(self += self, R"doc(Add another Real number to this one in-place.)doc")
        .def(self - self, R"doc(Subtract two Real numbers.)doc")
        .def(self -= self, R"doc(Subtract another Real number from this one in-place.)doc")
        .def(self * self, R"doc(Multiply two Real numbers.)doc")
        .def(self *= self, R"doc(Multiply this Real number by another in-place.)doc")
        .def(self / self, R"doc(Divide two Real numbers.)doc")
        .def(self /= self, R"doc(Divide this Real number by another in-place.)doc")

        .def(self + double(), R"doc(Add a Real number and a double.)doc")
        .def(self += double(), R"doc(Add a double to this Real number in-place.)doc")
        .def(self - double(), R"doc(Subtract a double from a Real number.)doc")
        .def(self -= double(), R"doc(Subtract a double from this Real number in-place.)doc")
        .def(self * double(), R"doc(Multiply a Real number by a double.)doc")
        .def(self *= double(), R"doc(Multiply this Real number by a double in-place.)doc")
        .def(self / double(), R"doc(Divide a Real number by a double.)doc")
        .def(self /= double(), R"doc(Divide this Real number by a double in-place.)doc")

        .def(double() + self, R"doc(Add a double and a Real number.)doc")
        .def(double() - self, R"doc(Subtract a Real number from a double.)doc")
        .def(double() * self, R"doc(Multiply a double by a Real number.)doc")
        .def(double() / self, R"doc(Divide a double by a Real number.)doc")

        .def(
            "__str__",
            +[](const ostk::core::type::Real& aReal) -> std::string
            {
                return aReal.toString();
            },
            R"doc(
                Return a string representation of the Real number.

                Returns:
                    str: String representation of the Real number.
            )doc"
        )
        .def(
            "__repr__",
            +[](const ostk::core::type::Real& aReal) -> std::string
            {
                return aReal.toString();
            },
            R"doc(
                Return a string representation of the Real number for debugging.

                Returns:
                    str: String representation of the Real number.
            )doc"
        )
        .def(
            "__hash__",
            +[](const ostk::core::type::Real& aReal) -> std::size_t
            {
                return std::hash<Real::ValueType>()(aReal);
            },
            R"doc(
                Return a hash value for the Real number.

                Returns:
                    int: Hash value of the Real number.
            )doc"
        )

        .def(
            "is_zero",
            &Real::isZero,
            R"doc(
                Check if the Real number is exactly zero.

                Returns:
                    bool: True if the Real number equals zero, False otherwise.

                Example:
                    >>> Real(0.0).is_zero()  # True
                    >>> Real(1e-15).is_zero()  # False
            )doc"
        )
        .def(
            "is_positive",
            &Real::isPositive,
            R"doc(
                Check if the Real number is positive (>= 0).

                Returns:
                    bool: True if the Real number is positive or zero, False otherwise.

                Example:
                    >>> Real(5.0).is_positive()  # True
                    >>> Real(0.0).is_positive()  # True
                    >>> Real(-1.0).is_positive()  # False
            )doc"
        )
        .def(
            "is_negative",
            &Real::isNegative,
            R"doc(
                Check if the Real number is negative (<= 0).

                Returns:
                    bool: True if the Real number is negative or zero, False otherwise.

                Example:
                    >>> Real(-5.0).is_negative()  # True
                    >>> Real(0.0).is_negative()  # True
                    >>> Real(1.0).is_negative()  # False
            )doc"
        )
        .def(
            "is_strictly_positive",
            &Real::isStrictlyPositive,
            R"doc(
                Check if the Real number is strictly positive (> 0).

                Returns:
                    bool: True if the Real number is greater than zero, False otherwise.

                Example:
                    >>> Real(5.0).is_strictly_positive()  # True
                    >>> Real(0.0).is_strictly_positive()  # False
                    >>> Real(-1.0).is_strictly_positive()  # False
            )doc"
        )
        .def(
            "is_strictly_negative",
            &Real::isStrictlyNegative,
            R"doc(
                Check if the Real number is strictly negative (< 0).

                Returns:
                    bool: True if the Real number is less than zero, False otherwise.

                Example:
                    >>> Real(-5.0).is_strictly_negative()  # True
                    >>> Real(0.0).is_strictly_negative()  # False
                    >>> Real(1.0).is_strictly_negative()  # False
            )doc"
        )
        .def(
            "is_infinity",
            &Real::isInfinity,
            R"doc(
                Check if the Real number represents infinity (positive or negative).

                Returns:
                    bool: True if the Real number is infinity, False otherwise.

                Example:
                    >>> Real.positive_infinity().is_infinity()  # True
                    >>> Real.negative_infinity().is_infinity()  # True
                    >>> Real(42.0).is_infinity()  # False
            )doc"
        )
        .def(
            "is_positive_infinity",
            &Real::isPositiveInfinity,
            R"doc(
                Check if the Real number represents positive infinity.

                Returns:
                    bool: True if the Real number is positive infinity, False otherwise.

                Example:
                    >>> Real.positive_infinity().is_positive_infinity()  # True
                    >>> Real.negative_infinity().is_positive_infinity()  # False
            )doc"
        )
        .def(
            "is_negative_infinity",
            &Real::isNegativeInfinity,
            R"doc(
                Check if the Real number represents negative infinity.

                Returns:
                    bool: True if the Real number is negative infinity, False otherwise.

                Example:
                    >>> Real.negative_infinity().is_negative_infinity()  # True
                    >>> Real.positive_infinity().is_negative_infinity()  # False
            )doc"
        )
        .def(
            "is_integer",
            &Real::isInteger,
            R"doc(
                Check if the Real number represents an integer value.

                Returns:
                    bool: True if the Real number has no fractional part, False otherwise.

                Example:
                    >>> Real(42.0).is_integer()  # True
                    >>> Real(42.5).is_integer()  # False
            )doc"
        )
        .def(
            "is_finite",
            &Real::isFinite,
            R"doc(
                Check if the Real number is finite (not infinity or NaN).

                Returns:
                    bool: True if the Real number is finite, False otherwise.

                Example:
                    >>> Real(42.0).is_finite()  # True
                    >>> Real.positive_infinity().is_finite()  # False
            )doc"
        )
        .def(
            "is_near",
            &Real::isNear,
            R"doc(
                Check if the Real number is near another value within a tolerance.

                Args:
                    other (Real): The value to compare against.
                    tolerance (Real): The tolerance for comparison.

                Returns:
                    bool: True if the values are within tolerance, False otherwise.

                Example:
                    >>> real1 = Real(3.14159)
                    >>> real2 = Real(3.14160)
                    >>> real1.is_near(real2, Real(1e-4))  # True
            )doc",
            arg("other"),
            arg("tolerance")
        )

        .def(
            "get_sign",
            &Real::getSign,
            R"doc(
                Get the sign of the Real number.

                Returns:
                    Sign: The sign (positive, negative, or zero) of the Real number.

                Example:
                    >>> Real(5.0).get_sign()  # Sign.Positive
                    >>> Real(-5.0).get_sign()  # Sign.Negative
                    >>> Real(0.0).get_sign()  # Sign.Zero
            )doc"
        )
        .def(
            "to_integer",
            &Real::toInteger,
            R"doc(
                Convert the Real number to an Integer.

                Returns:
                    Integer: The Real number converted to an Integer (truncated).

                Raises:
                    RuntimeError: If the Real number is undefined or infinity.

                Example:
                    >>> Real(3.7).to_integer()  # Integer(3)
                    >>> Real(-2.9).to_integer()  # Integer(-2)
            )doc"
        )
        .def(
            "abs",
            &Real::abs,
            R"doc(
                Get the absolute value of the Real number.

                Returns:
                    Real: The absolute value of the Real number.

                Example:
                    >>> Real(-5.5).abs()  # Real(5.5)
                    >>> Real(3.2).abs()  # Real(3.2)
            )doc"
        )
        .def(
            "floor",
            &Real::floor,
            R"doc(
                Get the floor (largest integer <= value) of the Real number.

                Returns:
                    Real: The floor of the Real number.

                Example:
                    >>> Real(3.7).floor()  # Real(3.0)
                    >>> Real(-2.3).floor()  # Real(-3.0)
            )doc"
        )
        .def(
            "sqrt",
            &Real::sqrt,
            R"doc(
                Get the square root of the Real number.

                Returns:
                    Real: The square root of the Real number.

                Raises:
                    RuntimeError: If the Real number is negative.

                Example:
                    >>> Real(25.0).sqrt()  # Real(5.0)
                    >>> Real(2.0).sqrt()  # Real(1.41421...)
            )doc"
        )

        // Define static methods
        .def_static(
            "zero",
            &Real::Zero,
            R"doc(
                Create a Real number representing zero.

                Returns:
                    Real: A Real number with value 0.0.

                Example:
                    >>> zero = Real.zero()
                    >>> zero.is_zero()  # True
            )doc"
        )
        .def_static(
            "pi",
            &Real::Pi,
            R"doc(
                Create a Real number representing π (pi).

                Returns:
                    Real: A Real number with value π ≈ 3.14159265358979324.

                Example:
                    >>> pi = Real.pi()
                    >>> print(pi)  # 3.14159265358979324
            )doc"
        )
        .def_static(
            "half_pi",
            &Real::HalfPi,
            R"doc(
                Create a Real number representing π/2 (half pi).

                Returns:
                    Real: A Real number with value π/2 ≈ 1.57079632679489662.

                Example:
                    >>> half_pi = Real.half_pi()
                    >>> print(half_pi)  # 1.57079632679489662
            )doc"
        )
        .def_static(
            "two_pi",
            &Real::TwoPi,
            R"doc(
                Create a Real number representing 2π (two pi).

                Returns:
                    Real: A Real number with value 2π ≈ 6.28318530717958648.

                Example:
                    >>> two_pi = Real.two_pi()
                    >>> print(two_pi)  # 6.28318530717958648
            )doc"
        )
        .def_static(
            "epsilon",
            &Real::Epsilon,
            R"doc(
                Create a Real number representing machine epsilon.

                Returns:
                    Real: A Real number with the smallest representable positive value.

                Example:
                    >>> eps = Real.epsilon()
                    >>> print(eps)  # Very small positive number
            )doc"
        )
        .def_static(
            "positive_infinity",
            &Real::PositiveInfinity,
            R"doc(
                Create a Real number representing positive infinity.

                Returns:
                    Real: A Real number with value +∞.

                Example:
                    >>> pos_inf = Real.positive_infinity()
                    >>> pos_inf.is_positive_infinity()  # True
            )doc"
        )
        .def_static(
            "negative_infinity",
            &Real::NegativeInfinity,
            R"doc(
                Create a Real number representing negative infinity.

                Returns:
                    Real: A Real number with value -∞.

                Example:
                    >>> neg_inf = Real.negative_infinity()
                    >>> neg_inf.is_negative_infinity()  # True
            )doc"
        )
        .def_static(
            "integer",
            &Real::Integer,
            R"doc(
                Create a Real number from an Integer.

                Args:
                    integer (Integer): The Integer value to convert.

                Returns:
                    Real: A Real number with the integer's value.

                Example:
                    >>> integer_val = Integer(42)
                    >>> real_val = Real.integer(integer_val)
                    >>> real_val.is_integer()  # True
            )doc",
            arg("integer")
        )
        .def_static(
            "can_parse",
            &Real::CanParse,
            R"doc(
                Check if a string can be parsed as a Real number.

                Args:
                    string (str): The string to check.

                Returns:
                    bool: True if the string can be parsed as a Real, False otherwise.

                Example:
                    >>> Real.can_parse("3.14159")  # True
                    >>> Real.can_parse("not_a_number")  # False
                    >>> Real.can_parse("inf")  # True
            )doc",
            arg("string")
        )
        .def_static(
            "parse",
            &Real::Parse,
            R"doc(
                Parse a string as a Real number.

                Args:
                    string (str): The string to parse.

                Returns:
                    Real: The parsed Real number.

                Raises:
                    RuntimeError: If the string cannot be parsed as a Real number.

                Example:
                    >>> real = Real.parse("3.14159")
                    >>> real = Real.parse("-42.5")
                    >>> real = Real.parse("inf")  # positive infinity
            )doc",
            arg("string")
        )

        ;

    implicitly_convertible<Real::ValueType, Real>();
}
