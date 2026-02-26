/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Real__
#define __OpenSpaceToolkit_Core_Type_Real__

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Sign.hpp>
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

/// @brief Real type
///
/// Represents a real number with support for undefined and infinite values.
///
/// @code
///     Real real(1.23) ;
///     real.isDefined() ; // True
///     real.toString() ; // "1.23"
/// @endcode
class Real
{
   public:
    typedef double ValueType;

    /// @brief Default constructor (disabled)
    Real() = delete;

    /// @brief Constructor
    ///
    /// @code
    ///     Real real(1.23) ;
    /// @endcode
    ///
    /// @param [in] aReal A real value
    Real(Real::ValueType aReal);

    /// @brief Copy assignment operator
    ///
    /// @param [in] aReal A real value
    /// @return Reference to real
    Real& operator=(Real::ValueType aReal);

    /// @brief Equal to operator
    ///
    /// @code
    ///     Real(1.23) == Real(1.23) ; // True
    /// @endcode
    ///
    /// @param [in] aReal A real
    /// @return True if reals are equal
    bool operator==(const Real& aReal) const;

    /// @brief Not equal to operator
    ///
    /// @code
    ///     Real(1.23) != Real(4.56) ; // True
    /// @endcode
    ///
    /// @param [in] aReal A real
    /// @return True if reals are not equal
    bool operator!=(const Real& aReal) const;

    /// @brief Less than operator
    ///
    /// @param [in] aReal A real
    /// @return True if lhs real is less than rhs real
    bool operator<(const Real& aReal) const;

    /// @brief Less than or equal to operator
    ///
    /// @param [in] aReal A real
    /// @return True if lhs real is less than or equal to rhs real
    bool operator<=(const Real& aReal) const;

    /// @brief Greater than operator
    ///
    /// @param [in] aReal A real
    /// @return True if lhs real is greater than rhs real
    bool operator>(const Real& aReal) const;

    /// @brief Greater than or equal to operator
    ///
    /// @param [in] aReal A real
    /// @return True if lhs real is greater than or equal to rhs real
    bool operator>=(const Real& aReal) const;

    /// @brief Equal to ValueType operator
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return True if real is equal to ValueType
    bool operator==(const Real::ValueType& aReal) const;

    /// @brief Not equal to ValueType operator
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return True if real is not equal to ValueType
    bool operator!=(const Real::ValueType& aReal) const;

    /// @brief Less than ValueType operator
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return True if real is less than ValueType
    bool operator<(const Real::ValueType& aReal) const;

    /// @brief Less than or equal to ValueType operator
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return True if real is less than or equal to ValueType
    bool operator<=(const Real::ValueType& aReal) const;

    /// @brief Greater than ValueType operator
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return True if real is greater than ValueType
    bool operator>(const Real::ValueType& aReal) const;

    /// @brief Greater than or equal to ValueType operator
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return True if real is greater than or equal to ValueType
    bool operator>=(const Real::ValueType& aReal) const;

    /// @brief Addition operator
    ///
    /// @param [in] aReal A real
    /// @return Sum of reals
    Real operator+(const Real& aReal) const;

    /// @brief Subtraction operator
    ///
    /// @param [in] aReal A real
    /// @return Difference of reals
    Real operator-(const Real& aReal) const;

    /// @brief Multiplication operator
    ///
    /// @param [in] aReal A real
    /// @return Product of reals
    Real operator*(const Real& aReal) const;

    /// @brief Division operator
    ///
    /// @param [in] aReal A real
    /// @return Quotient of reals
    Real operator/(const Real& aReal) const;

    /// @brief Addition operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Sum
    Real operator+(const Real::ValueType& aReal) const;

    /// @brief Subtraction operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Difference
    Real operator-(const Real::ValueType& aReal) const;

    /// @brief Multiplication operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Product
    Real operator*(const Real::ValueType& aReal) const;

    /// @brief Division operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Quotient
    Real operator/(const Real::ValueType& aReal) const;

    /// @brief Addition operator with Integer
    ///
    /// @param [in] anInteger An integer
    /// @return Sum
    Real operator+(const Integer& anInteger) const;

    /// @brief Subtraction operator with Integer
    ///
    /// @param [in] anInteger An integer
    /// @return Difference
    Real operator-(const Integer& anInteger) const;

    /// @brief Multiplication operator with Integer
    ///
    /// @param [in] anInteger An integer
    /// @return Product
    Real operator*(const Integer& anInteger) const;

    /// @brief Division operator with Integer
    ///
    /// @param [in] anInteger An integer
    /// @return Quotient
    Real operator/(const Integer& anInteger) const;

    /// @brief Addition assignment operator
    ///
    /// @param [in] aReal A real
    /// @return Reference to real
    Real& operator+=(const Real& aReal);

    /// @brief Subtraction assignment operator
    ///
    /// @param [in] aReal A real
    /// @return Reference to real
    Real& operator-=(const Real& aReal);

    /// @brief Multiplication assignment operator
    ///
    /// @param [in] aReal A real
    /// @return Reference to real
    Real& operator*=(const Real& aReal);

    /// @brief Division assignment operator
    ///
    /// @param [in] aReal A real
    /// @return Reference to real
    Real& operator/=(const Real& aReal);

    /// @brief Addition assignment operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Reference to real
    Real& operator+=(const Real::ValueType& aReal);

    /// @brief Subtraction assignment operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Reference to real
    Real& operator-=(const Real::ValueType& aReal);

    /// @brief Multiplication assignment operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Reference to real
    Real& operator*=(const Real::ValueType& aReal);

    /// @brief Division assignment operator with ValueType
    ///
    /// @param [in] aReal A real (ValueType)
    /// @return Reference to real
    Real& operator/=(const Real::ValueType& aReal);

    /// @brief Addition operator (ValueType + Real)
    ///
    /// @param [in] aDouble A double
    /// @param [in] aReal A real
    /// @return Sum
    friend Real operator+(const Real::ValueType& aDouble, const Real& aReal);

    /// @brief Subtraction operator (ValueType - Real)
    ///
    /// @param [in] aDouble A double
    /// @param [in] aReal A real
    /// @return Difference
    friend Real operator-(const Real::ValueType& aDouble, const Real& aReal);

    /// @brief Multiplication operator (ValueType * Real)
    ///
    /// @param [in] aDouble A double
    /// @param [in] aReal A real
    /// @return Product
    friend Real operator*(const Real::ValueType& aDouble, const Real& aReal);

    /// @brief Division operator (ValueType / Real)
    ///
    /// @param [in] aDouble A double
    /// @param [in] aReal A real
    /// @return Quotient
    friend Real operator/(const Real::ValueType& aDouble, const Real& aReal);

    /// @brief Unary plus operator
    ///
    /// @return Real value
    Real operator+() const;

    /// @brief Unary minus operator
    ///
    /// @return Negated real value
    Real operator-() const;

    /// @brief Conversion operator to ValueType
    ///
    /// @return Underlying value
    operator Real::ValueType() const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aReal A real
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Real& aReal);

    /// @brief Check if real is defined
    ///
    /// @code
    ///     Real(1.23).isDefined() ; // True
    ///     Real::Undefined().isDefined() ; // False
    /// @endcode
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Check if real is zero
    ///
    /// @code
    ///     Real(0.0).isZero() ; // True
    /// @endcode
    ///
    /// @return True if zero
    bool isZero() const;

    /// @brief Check if real is positive (including zero)
    ///
    /// @code
    ///     Real(1.23).isPositive() ; // True
    ///     Real(0.0).isPositive() ; // True
    /// @endcode
    ///
    /// @return True if positive
    bool isPositive() const;

    /// @brief Check if real is negative (including zero)
    ///
    /// @code
    ///     Real(-1.23).isNegative() ; // True
    ///     Real(0.0).isNegative() ; // True
    /// @endcode
    ///
    /// @return True if negative
    bool isNegative() const;

    /// @brief Check if real is strictly positive (excluding zero)
    ///
    /// @code
    ///     Real(1.23).isStrictlyPositive() ; // True
    ///     Real(0.0).isStrictlyPositive() ; // False
    /// @endcode
    ///
    /// @return True if strictly positive
    bool isStrictlyPositive() const;

    /// @brief Check if real is strictly negative (excluding zero)
    ///
    /// @code
    ///     Real(-1.23).isStrictlyNegative() ; // True
    ///     Real(0.0).isStrictlyNegative() ; // False
    /// @endcode
    ///
    /// @return True if strictly negative
    bool isStrictlyNegative() const;

    /// @brief Check if real is infinity (positive or negative)
    ///
    /// @code
    ///     Real::PositiveInfinity().isInfinity() ; // True
    /// @endcode
    ///
    /// @return True if infinity
    bool isInfinity() const;

    /// @brief Check if real is positive infinity
    ///
    /// @code
    ///     Real::PositiveInfinity().isPositiveInfinity() ; // True
    /// @endcode
    ///
    /// @return True if positive infinity
    bool isPositiveInfinity() const;

    /// @brief Check if real is negative infinity
    ///
    /// @code
    ///     Real::NegativeInfinity().isNegativeInfinity() ; // True
    /// @endcode
    ///
    /// @return True if negative infinity
    bool isNegativeInfinity() const;

    /// @brief Check if real is an integer value
    ///
    /// @code
    ///     Real(1.0).isInteger() ; // True
    ///     Real(1.5).isInteger() ; // False
    /// @endcode
    ///
    /// @return True if integer
    bool isInteger() const;

    /// @brief Check if real is finite
    ///
    /// @code
    ///     Real(1.23).isFinite() ; // True
    ///     Real::PositiveInfinity().isFinite() ; // False
    /// @endcode
    ///
    /// @return True if finite
    bool isFinite() const;

    /// @brief Check if real is near another real within a tolerance
    ///
    /// @code
    ///     Real(1.0).isNear(Real(1.0 + 1e-16), Real::Epsilon()) ; // True
    /// @endcode
    ///
    /// @param [in] aValue A real value to compare against
    /// @param [in] aTolerance A tolerance (default: Epsilon)
    /// @return True if near
    bool isNear(const Real& aValue, const Real& aTolerance = Real::Epsilon()) const;

    /// @brief Get sign of real
    ///
    /// @code
    ///     Real(1.23).getSign() ; // Sign::Positive
    /// @endcode
    ///
    /// @return Sign of real
    type::Sign getSign() const;

    /// @brief Convert real to string representation
    ///
    /// @code
    ///     Real(1.23).toString() ; // "1.23"
    ///     Real(1.23).toString(Integer(2)) ; // "1.23"
    /// @endcode
    ///
    /// @param [in] aPrecision A precision (default: Undefined)
    /// @return String representation
    type::String toString(const type::Integer& aPrecision = type::Integer::Undefined()) const;

    /// @brief Convert real to integer
    ///
    /// @code
    ///     Real(123.0).toInteger() ; // Integer(123)
    /// @endcode
    ///
    /// @return Integer value
    type::Integer toInteger() const;

    /// @brief Get absolute value
    ///
    /// @code
    ///     Real(-1.23).abs() ; // Real(1.23)
    /// @endcode
    ///
    /// @return Absolute value
    Real abs() const;

    /// @brief Get floor value
    ///
    /// @code
    ///     Real(1.7).floor() ; // Integer(1)
    /// @endcode
    ///
    /// @return Floor value as integer
    type::Integer floor() const;

    /// @brief Get square root
    ///
    /// @code
    ///     Real(4.0).sqrt() ; // Real(2.0)
    /// @endcode
    ///
    /// @return Square root
    Real sqrt() const;

    /// @brief Construct an undefined real
    ///
    /// @code
    ///     Real real = Real::Undefined() ;
    /// @endcode
    ///
    /// @return Undefined real
    static Real Undefined();

    /// @brief Construct a zero real
    ///
    /// @code
    ///     Real real = Real::Zero() ;
    /// @endcode
    ///
    /// @return Zero real
    static Real Zero();

    /// @brief Construct a real with value Pi
    ///
    /// @code
    ///     Real real = Real::Pi() ; // 3.14159...
    /// @endcode
    ///
    /// @return Pi
    static Real Pi();

    /// @brief Construct a real with value Pi/2
    ///
    /// @code
    ///     Real real = Real::HalfPi() ; // 1.5708...
    /// @endcode
    ///
    /// @return Half Pi
    static Real HalfPi();

    /// @brief Construct a real with value 2*Pi
    ///
    /// @code
    ///     Real real = Real::TwoPi() ; // 6.28318...
    /// @endcode
    ///
    /// @return Two Pi
    static Real TwoPi();

    /// @brief Construct a real with machine epsilon value
    ///
    /// @code
    ///     Real real = Real::Epsilon() ;
    /// @endcode
    ///
    /// @return Machine epsilon
    static Real Epsilon();

    /// @brief Construct a positive infinity real
    ///
    /// @code
    ///     Real real = Real::PositiveInfinity() ;
    /// @endcode
    ///
    /// @return Positive infinity
    static Real PositiveInfinity();

    /// @brief Construct a negative infinity real
    ///
    /// @code
    ///     Real real = Real::NegativeInfinity() ;
    /// @endcode
    ///
    /// @return Negative infinity
    static Real NegativeInfinity();

    /// @brief Construct a real from an integer
    ///
    /// @code
    ///     Real real = Real::Integer(Integer(123)) ; // 123.0
    /// @endcode
    ///
    /// @param [in] anInteger An integer
    /// @return Real value
    static Real Integer(const type::Integer& anInteger);

    /// @brief Check if a string can be parsed as a real
    ///
    /// @code
    ///     Real::CanParse("1.23") ; // True
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @return True if can be parsed
    static Real CanParse(const type::String& aString);

    /// @brief Construct a real from a string
    ///
    /// @code
    ///     Real real = Real::Parse("1.23") ;
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @return Real value
    static Real Parse(const type::String& aString);

   private:
    enum class Type
    {

        Undefined,
        Defined,
        PositiveInfinity,
        NegativeInfinity

    };

    Real::Type type_;
    Real::ValueType value_;

    Real(const Real::Type& aType, const Real::ValueType& aReal);
};

}  // namespace type
}  // namespace core
}  // namespace ostk

#ifdef CPP20
template <>
struct std::formatter<ostk::core::type::Real> : std::formatter<double>
{
    template <typename FormatContext>
    auto format(const ostk::core::type::Real& aReal, FormatContext& ctx) const
    {
        return std::formatter<double>::format(static_cast<double>(aReal), ctx);
    }
};
#endif

#endif
