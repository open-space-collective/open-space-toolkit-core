/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Integer__
#define __OpenSpaceToolkit_Core_Type_Integer__

#include <ostream>

#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Sign.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#if __cplusplus >= 202002L
#define CPP20
#endif

namespace ostk
{
namespace core
{
namespace type
{

typedef int8_t Int8;
typedef int16_t Int16;
typedef int32_t Int32;
typedef int64_t Int64;

typedef uint8_t Uint8;
typedef uint16_t Uint16;
typedef uint32_t Uint32;
typedef uint64_t Uint64;

class Real;

/// @brief Integer type
///
/// Represents an integer number with support for undefined and infinite values.
///
/// @code
///     Integer integer(123) ;
///     integer.isDefined() ; // True
///     integer.toString() ; // "123"
/// @endcode
class Integer
{
   public:
    typedef int32_t ValueType;

    /// @brief Default constructor (disabled)
    Integer() = delete;

    /// @brief Constructor
    ///
    /// @code
    ///     Integer integer(123) ;
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    Integer(Integer::ValueType anInteger);

    /// @brief Float constructor (disabled)
    Integer(float) = delete;

    /// @brief Double constructor (disabled)
    Integer(double) = delete;

    /// @brief Copy assignment operator
    ///
    /// @param [in] anInteger An integer
    /// @return Reference to integer
    Integer& operator=(Integer::ValueType anInteger);

    /// @brief Equal to operator
    ///
    /// @code
    ///     Integer(123) == Integer(123) ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return True if integers are equal
    bool operator==(const Integer& anInteger) const;

    /// @brief Not equal to operator
    ///
    /// @code
    ///     Integer(123) != Integer(456) ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return True if integers are not equal
    bool operator!=(const Integer& anInteger) const;

    /// @brief Less than operator
    ///
    /// @code
    ///     Integer(123) < Integer(456) ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return True if lhs integer is less than rhs integer
    bool operator<(const Integer& anInteger) const;

    /// @brief Less than or equal to operator
    ///
    /// @code
    ///     Integer(123) <= Integer(456) ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return True if lhs integer is less than or equal to rhs integer
    bool operator<=(const Integer& anInteger) const;

    /// @brief Greater than operator
    ///
    /// @code
    ///     Integer(456) > Integer(123) ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return True if lhs integer is greater than rhs integer
    bool operator>(const Integer& anInteger) const;

    /// @brief Greater than or equal to operator
    ///
    /// @code
    ///     Integer(456) >= Integer(123) ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return True if lhs integer is greater than or equal to rhs integer
    bool operator>=(const Integer& anInteger) const;

    /// @brief Equal to ValueType operator
    ///
    /// @code
    ///     Integer(123) == 123 ; // True
    /// @endcode
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return True if integer is equal to ValueType
    bool operator==(const Integer::ValueType& anInteger) const;

    /// @brief Not equal to ValueType operator
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return True if integer is not equal to ValueType
    bool operator!=(const Integer::ValueType& anInteger) const;

    /// @brief Less than ValueType operator
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return True if integer is less than ValueType
    bool operator<(const Integer::ValueType& anInteger) const;

    /// @brief Less than or equal to ValueType operator
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return True if integer is less than or equal to ValueType
    bool operator<=(const Integer::ValueType& anInteger) const;

    /// @brief Greater than ValueType operator
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return True if integer is greater than ValueType
    bool operator>(const Integer::ValueType& anInteger) const;

    /// @brief Greater than or equal to ValueType operator
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return True if integer is greater than or equal to ValueType
    bool operator>=(const Integer::ValueType& anInteger) const;

    /// @brief Addition operator
    ///
    /// @param [in] anInteger An integer
    /// @return Sum of integers
    Integer operator+(const Integer& anInteger) const;

    /// @brief Subtraction operator
    ///
    /// @param [in] anInteger An integer
    /// @return Difference of integers
    Integer operator-(const Integer& anInteger) const;

    /// @brief Multiplication operator
    ///
    /// @param [in] anInteger An integer
    /// @return Product of integers
    Integer operator*(const Integer& anInteger) const;

    /// @brief Division operator
    ///
    /// @param [in] anInteger An integer
    /// @return Quotient of integers
    Integer operator/(const Integer& anInteger) const;

    /// @brief Modulo operator
    ///
    /// @param [in] anInteger An integer
    /// @return Remainder of division
    Integer operator%(const Integer& anInteger) const;

    /// @brief Addition operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Sum
    Integer operator+(const Integer::ValueType& anInteger) const;

    /// @brief Subtraction operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Difference
    Integer operator-(const Integer::ValueType& anInteger) const;

    /// @brief Multiplication operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Product
    Integer operator*(const Integer::ValueType& anInteger) const;

    /// @brief Division operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Quotient
    Integer operator/(const Integer::ValueType& anInteger) const;

    /// @brief Modulo operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Remainder
    Integer operator%(const Integer::ValueType& anInteger) const;

    /// @brief Addition operator with Real
    ///
    /// @param [in] aReal A real
    /// @return Sum as real
    Real operator+(const Real& aReal) const;

    /// @brief Subtraction operator with Real
    ///
    /// @param [in] aReal A real
    /// @return Difference as real
    Real operator-(const Real& aReal) const;

    /// @brief Multiplication operator with Real
    ///
    /// @param [in] aReal A real
    /// @return Product as real
    Real operator*(const Real& aReal) const;

    /// @brief Division operator with Real
    ///
    /// @param [in] aReal A real
    /// @return Quotient as real
    Real operator/(const Real& aReal) const;

    /// @brief Addition assignment operator
    ///
    /// @param [in] anInteger An integer
    /// @return Reference to integer
    Integer& operator+=(const Integer& anInteger);

    /// @brief Subtraction assignment operator
    ///
    /// @param [in] anInteger An integer
    /// @return Reference to integer
    Integer& operator-=(const Integer& anInteger);

    /// @brief Multiplication assignment operator
    ///
    /// @param [in] anInteger An integer
    /// @return Reference to integer
    Integer& operator*=(const Integer& anInteger);

    /// @brief Division assignment operator
    ///
    /// @param [in] anInteger An integer
    /// @return Reference to integer
    Integer& operator/=(const Integer& anInteger);

    /// @brief Modulo assignment operator
    ///
    /// @param [in] anInteger An integer
    /// @return Reference to integer
    Integer& operator%=(const Integer& anInteger);

    /// @brief Addition assignment operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Reference to integer
    Integer& operator+=(const Integer::ValueType& anInteger);

    /// @brief Subtraction assignment operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Reference to integer
    Integer& operator-=(const Integer::ValueType& anInteger);

    /// @brief Multiplication assignment operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Reference to integer
    Integer& operator*=(const Integer::ValueType& anInteger);

    /// @brief Division assignment operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Reference to integer
    Integer& operator/=(const Integer::ValueType& anInteger);

    /// @brief Modulo assignment operator with ValueType
    ///
    /// @param [in] anInteger An integer (ValueType)
    /// @return Reference to integer
    Integer& operator%=(const Integer::ValueType& anInteger);

    /// @brief Addition operator (ValueType + Integer)
    ///
    /// @param [in] anInt A ValueType integer
    /// @param [in] anInteger An integer
    /// @return Sum
    friend Integer operator+(const Integer::ValueType& anInt, const Integer& anInteger);

    /// @brief Subtraction operator (ValueType - Integer)
    ///
    /// @param [in] anInt A ValueType integer
    /// @param [in] anInteger An integer
    /// @return Difference
    friend Integer operator-(const Integer::ValueType& anInt, const Integer& anInteger);

    /// @brief Multiplication operator (ValueType * Integer)
    ///
    /// @param [in] anInt A ValueType integer
    /// @param [in] anInteger An integer
    /// @return Product
    friend Integer operator*(const Integer::ValueType& anInt, const Integer& anInteger);

    /// @brief Division operator (ValueType / Integer)
    ///
    /// @param [in] anInt A ValueType integer
    /// @param [in] anInteger An integer
    /// @return Quotient
    friend Integer operator/(const Integer::ValueType& anInt, const Integer& anInteger);

    /// @brief Modulo operator (ValueType % Integer)
    ///
    /// @param [in] anInt A ValueType integer
    /// @param [in] anInteger An integer
    /// @return Remainder
    friend Integer operator%(const Integer::ValueType& anInt, const Integer& anInteger);

    /// @brief Unary plus operator
    ///
    /// @return Integer value
    Integer operator+() const;

    /// @brief Unary minus operator
    ///
    /// @return Negated integer value
    Integer operator-() const;

    /// @brief Pre-increment operator
    ///
    /// @return Reference to incremented integer
    Integer& operator++();

    /// @brief Pre-decrement operator
    ///
    /// @return Reference to decremented integer
    Integer& operator--();

    /// @brief Post-increment operator
    ///
    /// @param [in] anInteger Dummy parameter
    /// @return Integer value before increment
    Integer operator++(int anInteger);

    /// @brief Post-decrement operator
    ///
    /// @param [in] anInteger Dummy parameter
    /// @return Integer value before decrement
    Integer operator--(int anInteger);

    /// @brief Conversion operator to ValueType
    ///
    /// @return Underlying value
    operator Integer::ValueType() const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anInteger An integer
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Integer& anInteger);

    /// @brief Check if integer is defined
    ///
    /// @code
    ///     Integer(123).isDefined() ; // True
    ///     Integer::Undefined().isDefined() ; // False
    /// @endcode
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Check if integer is zero
    ///
    /// @code
    ///     Integer(0).isZero() ; // True
    /// @endcode
    ///
    /// @return True if zero
    bool isZero() const;

    /// @brief Check if integer is positive (including zero)
    ///
    /// @code
    ///     Integer(123).isPositive() ; // True
    ///     Integer(0).isPositive() ; // True
    /// @endcode
    ///
    /// @return True if positive
    bool isPositive() const;

    /// @brief Check if integer is negative (including zero)
    ///
    /// @code
    ///     Integer(-123).isNegative() ; // True
    ///     Integer(0).isNegative() ; // True
    /// @endcode
    ///
    /// @return True if negative
    bool isNegative() const;

    /// @brief Check if integer is strictly positive (excluding zero)
    ///
    /// @code
    ///     Integer(123).isStrictlyPositive() ; // True
    ///     Integer(0).isStrictlyPositive() ; // False
    /// @endcode
    ///
    /// @return True if strictly positive
    bool isStrictlyPositive() const;

    /// @brief Check if integer is strictly negative (excluding zero)
    ///
    /// @code
    ///     Integer(-123).isStrictlyNegative() ; // True
    ///     Integer(0).isStrictlyNegative() ; // False
    /// @endcode
    ///
    /// @return True if strictly negative
    bool isStrictlyNegative() const;

    /// @brief Check if integer is infinity (positive or negative)
    ///
    /// @code
    ///     Integer::PositiveInfinity().isInfinity() ; // True
    /// @endcode
    ///
    /// @return True if infinity
    bool isInfinity() const;

    /// @brief Check if integer is positive infinity
    ///
    /// @code
    ///     Integer::PositiveInfinity().isPositiveInfinity() ; // True
    /// @endcode
    ///
    /// @return True if positive infinity
    bool isPositiveInfinity() const;

    /// @brief Check if integer is negative infinity
    ///
    /// @code
    ///     Integer::NegativeInfinity().isNegativeInfinity() ; // True
    /// @endcode
    ///
    /// @return True if negative infinity
    bool isNegativeInfinity() const;

    /// @brief Check if integer is finite
    ///
    /// @code
    ///     Integer(123).isFinite() ; // True
    ///     Integer::PositiveInfinity().isFinite() ; // False
    /// @endcode
    ///
    /// @return True if finite
    bool isFinite() const;

    /// @brief Check if integer is even
    ///
    /// @code
    ///     Integer(2).isEven() ; // True
    ///     Integer(3).isEven() ; // False
    /// @endcode
    ///
    /// @return True if even
    bool isEven() const;

    /// @brief Check if integer is odd
    ///
    /// @code
    ///     Integer(3).isOdd() ; // True
    ///     Integer(2).isOdd() ; // False
    /// @endcode
    ///
    /// @return True if odd
    bool isOdd() const;

    /// @brief Get sign of integer
    ///
    /// @code
    ///     Integer(123).getSign() ; // Sign::Positive
    /// @endcode
    ///
    /// @return Sign of integer
    type::Sign getSign() const;

    /// @brief Convert integer to string representation
    ///
    /// @code
    ///     Integer(123).toString() ; // "123"
    /// @endcode
    ///
    /// @return String representation
    type::String toString() const;

    /// @brief Construct an undefined integer
    ///
    /// @code
    ///     Integer integer = Integer::Undefined() ;
    /// @endcode
    ///
    /// @return Undefined integer
    static Integer Undefined();

    /// @brief Construct a zero integer
    ///
    /// @code
    ///     Integer integer = Integer::Zero() ;
    /// @endcode
    ///
    /// @return Zero integer
    static Integer Zero();

    /// @brief Construct a positive infinity integer
    ///
    /// @code
    ///     Integer integer = Integer::PositiveInfinity() ;
    /// @endcode
    ///
    /// @return Positive infinity integer
    static Integer PositiveInfinity();

    /// @brief Construct a negative infinity integer
    ///
    /// @code
    ///     Integer integer = Integer::NegativeInfinity() ;
    /// @endcode
    ///
    /// @return Negative infinity integer
    static Integer NegativeInfinity();

    /// @brief Construct an integer from an Int8 value
    ///
    /// @param [in] anInteger An Int8 value
    /// @return Integer
    static Integer Int8(type::Int8 anInteger);

    /// @brief Construct an integer from an Int16 value
    ///
    /// @param [in] anInteger An Int16 value
    /// @return Integer
    static Integer Int16(type::Int16 anInteger);

    /// @brief Construct an integer from an Int32 value
    ///
    /// @param [in] anInteger An Int32 value
    /// @return Integer
    static Integer Int32(type::Int32 anInteger);

    /// @brief Construct an integer from an Int64 value
    ///
    /// @param [in] anInteger An Int64 value
    /// @return Integer
    static Integer Int64(type::Int64 anInteger);

    /// @brief Construct an integer from a Uint8 value
    ///
    /// @param [in] anInteger A Uint8 value
    /// @return Integer
    static Integer Uint8(type::Uint8 anInteger);

    /// @brief Construct an integer from a Uint16 value
    ///
    /// @param [in] anInteger A Uint16 value
    /// @return Integer
    static Integer Uint16(type::Uint16 anInteger);

    /// @brief Construct an integer from a Uint32 value
    ///
    /// @param [in] anInteger A Uint32 value
    /// @return Integer
    static Integer Uint32(type::Uint32 anInteger);

    /// @brief Construct an integer from a Uint64 value
    ///
    /// @param [in] anInteger A Uint64 value
    /// @return Integer
    static Integer Uint64(type::Uint64 anInteger);

    /// @brief Construct an integer from an Index value
    ///
    /// @param [in] anIndex An index
    /// @return Integer
    static Integer Index(const type::Index& anIndex);

    /// @brief Construct an integer from a Size value
    ///
    /// @param [in] aSize A size
    /// @return Integer
    static Integer Size(const type::Size& aSize);

    /// @brief Check if a character can be parsed as an integer
    ///
    /// @param [in] aCharacter A character
    /// @return True if can be parsed
    static bool CanParse(char aCharacter);

    /// @brief Check if a string can be parsed as an integer
    ///
    /// @param [in] aString A string
    /// @return True if can be parsed
    static bool CanParse(const type::String& aString);

    /// @brief Construct an integer by parsing a character
    ///
    /// @param [in] aCharacter A character
    /// @return Integer
    static Integer Parse(char aCharacter);

    /// @brief Construct an integer by parsing a string
    ///
    /// @code
    ///     Integer integer = Integer::Parse("123") ;
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @return Integer
    static Integer Parse(const type::String& aString);

   private:
    enum class Type
    {

        Undefined,
        Defined,
        PositiveInfinity,
        NegativeInfinity

    };

    Integer::Type type_;
    Integer::ValueType value_;

    Integer(const Integer::Type& aType, const Integer::ValueType& anInteger);
};

}  // namespace type
}  // namespace core
}  // namespace ostk

#ifdef CPP20
template <>
struct std::formatter<ostk::core::type::Integer> : std::formatter<int>
{
    template <typename FormatContext>
    auto format(const ostk::core::type::Integer& anInteger, FormatContext& ctx) const
    {
        return std::formatter<int>::format(static_cast<int>(anInteger), ctx);
    }
};
#endif

#endif
