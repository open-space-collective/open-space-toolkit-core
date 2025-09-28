/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>

using ostk::core::type::Integer;

inline void OpenSpaceToolkitCorePy_Type_Integer(pybind11::class_<Integer>& integerClass)
{
    using namespace pybind11;

    using ostk::core::type::Real;
    using ostk::core::type::String;

    integerClass

        // Define init method using pybind11 "init" convenience method
        .def(
            init<Integer::ValueType>(),
            R"doc(
                Construct an Integer from a numeric value.

                Args:
                    value: An integer value to initialize the Integer.

                Example:
                    >>> integer = Integer(42)
                    >>> integer = Integer(-123)
            )doc",
            arg("value")
        )

        // Define __int__ method for direct conversion (previously .def(int_(self)))
        .def(
            "__int__",
            +[](const ostk::core::type::Integer& anInteger) -> int
            {
                return static_cast<int>(anInteger);
            },
            R"doc(
                Convert the Integer to a Python int.

                Returns:
                    int: The numeric value as a Python int.

                Example:
                    >>> integer = Integer(42)
                    >>> int(integer)  # 42
            )doc"
        )

        // Define methods
        .def(self == self, R"doc(Check if two Integers are equal.)doc")
        .def(self != self, R"doc(Check if two Integers are not equal.)doc")
        .def(self < self, R"doc(Check if this Integer is less than another.)doc")
        .def(self <= self, R"doc(Check if this Integer is less than or equal to another.)doc")
        .def(self > self, R"doc(Check if this Integer is greater than another.)doc")
        .def(self >= self, R"doc(Check if this Integer is greater than or equal to another.)doc")

        .def(self + self, R"doc(Add two Integers.)doc")
        .def(self += self, R"doc(Add another Integer to this one in-place.)doc")
        .def(self - self, R"doc(Subtract two Integers.)doc")
        .def(self -= self, R"doc(Subtract another Integer from this one in-place.)doc")
        .def(self * self, R"doc(Multiply two Integers.)doc")
        .def(self *= self, R"doc(Multiply this Integer by another in-place.)doc")
        .def(self / self, R"doc(Divide two Integers.)doc")
        .def(self /= self, R"doc(Divide this Integer by another in-place.)doc")

        .def(self + int(), R"doc(Add an Integer and a Python int.)doc")
        .def(self += int(), R"doc(Add a Python int to this Integer in-place.)doc")
        .def(self - int(), R"doc(Subtract a Python int from an Integer.)doc")
        .def(self -= int(), R"doc(Subtract a Python int from this Integer in-place.)doc")
        .def(self * int(), R"doc(Multiply an Integer by a Python int.)doc")
        .def(self *= int(), R"doc(Multiply this Integer by a Python int in-place.)doc")
        .def(self / int(), R"doc(Divide an Integer by a Python int.)doc")
        .def(self /= int(), R"doc(Divide this Integer by a Python int in-place.)doc")

        .def(int() + self, R"doc(Add a Python int and an Integer.)doc")
        .def(int() - self, R"doc(Subtract an Integer from a Python int.)doc")
        .def(int() * self, R"doc(Multiply a Python int by an Integer.)doc")
        .def(int() / self, R"doc(Divide a Python int by an Integer.)doc")

        .def(
            "__str__",
            +[](const ostk::core::type::Integer& anInteger) -> std::string
            {
                return anInteger.toString();
            },
            R"doc(
                Return a string representation of the Integer.

                Returns:
                    str: String representation of the Integer.
            )doc"
        )
        .def(
            "__repr__",
            +[](const ostk::core::type::Integer& anInteger) -> std::string
            {
                return anInteger.toString();
            },
            R"doc(
                Return a string representation of the Integer for debugging.

                Returns:
                    str: String representation of the Integer.
            )doc"
        )
        .def(
            "__hash__",
            +[](const ostk::core::type::Integer& anInteger) -> std::size_t
            {
                return std::hash<Integer::ValueType>()(anInteger);
            },
            R"doc(
                Return a hash value for the Integer.

                Returns:
                    int: Hash value of the Integer.
            )doc"
        )

        .def(
            "is_defined",
            &Integer::isDefined,
            R"doc(
                Check if the Integer is defined (not uninitialized).

                Returns:
                    bool: True if the Integer is defined, False otherwise.

                Example:
                    >>> integer = Integer(42)
                    >>> integer.is_defined()  # True
                    >>> undefined_int = Integer.undefined()
                    >>> undefined_int.is_defined()  # False
            )doc"
        )
        .def(
            "is_zero",
            &Integer::isZero,
            R"doc(
                Check if the Integer is exactly zero.

                Returns:
                    bool: True if the Integer equals zero, False otherwise.

                Example:
                    >>> Integer(0).is_zero()  # True
                    >>> Integer(5).is_zero()  # False
            )doc"
        )
        .def(
            "is_positive",
            &Integer::isPositive,
            R"doc(
                Check if the Integer is positive (>= 0).

                Returns:
                    bool: True if the Integer is positive or zero, False otherwise.

                Example:
                    >>> Integer(5).is_positive()  # True
                    >>> Integer(0).is_positive()  # True
                    >>> Integer(-1).is_positive()  # False
            )doc"
        )
        .def(
            "is_negative",
            &Integer::isNegative,
            R"doc(
                Check if the Integer is negative (<= 0).

                Returns:
                    bool: True if the Integer is negative or zero, False otherwise.

                Example:
                    >>> Integer(-5).is_negative()  # True
                    >>> Integer(0).is_negative()  # True
                    >>> Integer(1).is_negative()  # False
            )doc"
        )
        .def(
            "is_strictly_positive",
            &Integer::isStrictlyPositive,
            R"doc(
                Check if the Integer is strictly positive (> 0).

                Returns:
                    bool: True if the Integer is greater than zero, False otherwise.

                Example:
                    >>> Integer(5).is_strictly_positive()  # True
                    >>> Integer(0).is_strictly_positive()  # False
                    >>> Integer(-1).is_strictly_positive()  # False
            )doc"
        )
        .def(
            "is_strictly_negative",
            &Integer::isStrictlyNegative,
            R"doc(
                Check if the Integer is strictly negative (< 0).

                Returns:
                    bool: True if the Integer is less than zero, False otherwise.

                Example:
                    >>> Integer(-5).is_strictly_negative()  # True
                    >>> Integer(0).is_strictly_negative()  # False
                    >>> Integer(1).is_strictly_negative()  # False
            )doc"
        )
        .def(
            "is_infinity",
            &Integer::isInfinity,
            R"doc(
                Check if the Integer represents infinity (positive or negative).

                Returns:
                    bool: True if the Integer is infinity, False otherwise.

                Example:
                    >>> Integer.positive_infinity().is_infinity()  # True
                    >>> Integer.negative_infinity().is_infinity()  # True
                    >>> Integer(42).is_infinity()  # False
            )doc"
        )
        .def(
            "is_positive_infinity",
            &Integer::isPositiveInfinity,
            R"doc(
                Check if the Integer represents positive infinity.

                Returns:
                    bool: True if the Integer is positive infinity, False otherwise.

                Example:
                    >>> Integer.positive_infinity().is_positive_infinity()  # True
                    >>> Integer.negative_infinity().is_positive_infinity()  # False
            )doc"
        )
        .def(
            "is_negative_infinity",
            &Integer::isNegativeInfinity,
            R"doc(
                Check if the Integer represents negative infinity.

                Returns:
                    bool: True if the Integer is negative infinity, False otherwise.

                Example:
                    >>> Integer.negative_infinity().is_negative_infinity()  # True
                    >>> Integer.positive_infinity().is_negative_infinity()  # False
            )doc"
        )
        .def(
            "is_finite",
            &Integer::isFinite,
            R"doc(
                Check if the Integer is finite (not infinity).

                Returns:
                    bool: True if the Integer is finite, False otherwise.

                Example:
                    >>> Integer(42).is_finite()  # True
                    >>> Integer.positive_infinity().is_finite()  # False
            )doc"
        )
        .def(
            "is_even",
            &Integer::isEven,
            R"doc(
                Check if the Integer is even.

                Returns:
                    bool: True if the Integer is divisible by 2, False otherwise.

                Example:
                    >>> Integer(4).is_even()  # True
                    >>> Integer(3).is_even()  # False
            )doc"
        )
        .def(
            "is_odd",
            &Integer::isOdd,
            R"doc(
                Check if the Integer is odd.

                Returns:
                    bool: True if the Integer is not divisible by 2, False otherwise.

                Example:
                    >>> Integer(3).is_odd()  # True
                    >>> Integer(4).is_odd()  # False
            )doc"
        )

        .def(
            "get_sign",
            &Integer::getSign,
            R"doc(
                Get the sign of the Integer.

                Returns:
                    Sign: The sign (positive, negative, or zero) of the Integer.

                Example:
                    >>> Integer(5).get_sign()  # Sign.Positive
                    >>> Integer(-5).get_sign()  # Sign.Negative
                    >>> Integer(0).get_sign()  # Sign.Zero
            )doc"
        )
        .def(
            "to_string",
            &Integer::toString,
            R"doc(
                Convert the Integer to a string representation.

                Returns:
                    str: String representation of the Integer.

                Example:
                    >>> Integer(42).to_string()  # "42"
                    >>> Integer(-123).to_string()  # "-123"
            )doc"
        )

        // Define static methods
        .def_static(
            "undefined",
            &Integer::Undefined,
            R"doc(
                Create an undefined Integer.

                Returns:
                    Integer: An undefined Integer.

                Example:
                    >>> undefined_int = Integer.undefined()
                    >>> undefined_int.is_defined()  # False
            )doc"
        )
        .def_static(
            "zero",
            &Integer::Zero,
            R"doc(
                Create an Integer representing zero.

                Returns:
                    Integer: An Integer with value 0.

                Example:
                    >>> zero = Integer.zero()
                    >>> zero.is_zero()  # True
            )doc"
        )
        .def_static(
            "positive_infinity",
            &Integer::PositiveInfinity,
            R"doc(
                Create an Integer representing positive infinity.

                Returns:
                    Integer: An Integer with value +∞.

                Example:
                    >>> pos_inf = Integer.positive_infinity()
                    >>> pos_inf.is_positive_infinity()  # True
            )doc"
        )
        .def_static(
            "negative_infinity",
            &Integer::NegativeInfinity,
            R"doc(
                Create an Integer representing negative infinity.

                Returns:
                    Integer: An Integer with value -∞.

                Example:
                    >>> neg_inf = Integer.negative_infinity()
                    >>> neg_inf.is_negative_infinity()  # True
            )doc"
        )
        .def_static(
            "int8",
            &Integer::Int8,
            R"doc(
                Create an Integer from an 8-bit signed integer value.

                Args:
                    value (int): The 8-bit signed integer value (-128 to 127).

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> int8_val = Integer.int8(127)
            )doc",
            arg("value")
        )
        .def_static(
            "int16",
            &Integer::Int16,
            R"doc(
                Create an Integer from a 16-bit signed integer value.

                Args:
                    value (int): The 16-bit signed integer value.

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> int16_val = Integer.int16(32767)
            )doc",
            arg("value")
        )
        .def_static(
            "int32",
            &Integer::Int32,
            R"doc(
                Create an Integer from a 32-bit signed integer value.

                Args:
                    value (int): The 32-bit signed integer value.

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> int32_val = Integer.int32(2147483647)
            )doc",
            arg("value")
        )
        .def_static(
            "int64",
            &Integer::Int64,
            R"doc(
                Create an Integer from a 64-bit signed integer value.

                Args:
                    value (int): The 64-bit signed integer value.

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> int64_val = Integer.int64(9223372036854775807)
            )doc",
            arg("value")
        )
        .def_static(
            "uint8",
            &Integer::Uint8,
            R"doc(
                Create an Integer from an 8-bit unsigned integer value.

                Args:
                    value (int): The 8-bit unsigned integer value (0 to 255).

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> uint8_val = Integer.uint8(255)
            )doc",
            arg("value")
        )
        .def_static(
            "uint16",
            &Integer::Uint16,
            R"doc(
                Create an Integer from a 16-bit unsigned integer value.

                Args:
                    value (int): The 16-bit unsigned integer value.

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> uint16_val = Integer.uint16(65535)
            )doc",
            arg("value")
        )
        .def_static(
            "uint32",
            &Integer::Uint32,
            R"doc(
                Create an Integer from a 32-bit unsigned integer value.

                Args:
                    value (int): The 32-bit unsigned integer value.

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> uint32_val = Integer.uint32(4294967295)
            )doc",
            arg("value")
        )
        .def_static(
            "uint64",
            &Integer::Uint64,
            R"doc(
                Create an Integer from a 64-bit unsigned integer value.

                Args:
                    value (int): The 64-bit unsigned integer value.

                Returns:
                    Integer: An Integer with the specified value.

                Example:
                    >>> uint64_val = Integer.uint64(18446744073709551615)
            )doc",
            arg("value")
        )
        .def_static(
            "index",
            &Integer::Index,
            R"doc(
                Create an Integer from an index value.

                Args:
                    index: The index value to convert.

                Returns:
                    Integer: An Integer representing the index.

                Example:
                    >>> index_val = Integer.index(42)
            )doc",
            arg("index")
        )
        .def_static(
            "size",
            &Integer::Size,
            R"doc(
                Create an Integer from a size value.

                Args:
                    size: The size value to convert.

                Returns:
                    Integer: An Integer representing the size.

                Example:
                    >>> size_val = Integer.size(100)
            )doc",
            arg("size")
        )
        .def_static(
            "can_parse",
            static_cast<bool (*)(const String&)>(&Integer::CanParse),
            R"doc(
                Check if a string can be parsed as an Integer.

                Args:
                    string (str): The string to check.

                Returns:
                    bool: True if the string can be parsed as an Integer, False otherwise.

                Example:
                    >>> Integer.can_parse("42")  # True
                    >>> Integer.can_parse("not_a_number")  # False
            )doc",
            arg("string")
        )
        .def_static(
            "parse",
            static_cast<Integer (*)(const String&)>(&Integer::Parse),
            R"doc(
                Parse a string as an Integer.

                Args:
                    string (str): The string to parse.

                Returns:
                    Integer: The parsed Integer.

                Raises:
                    RuntimeError: If the string cannot be parsed as an Integer.

                Example:
                    >>> integer = Integer.parse("42")
                    >>> integer = Integer.parse("-123")
            )doc",
            arg("string")
        )

        ;

    // Implicit conversion (allowed in the direction of the binded custom type only in pybind11)
    implicitly_convertible<Integer::ValueType, Integer>();
}
