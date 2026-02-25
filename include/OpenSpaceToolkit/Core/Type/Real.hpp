/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Real__
#define __OpenSpaceToolkit_Core_Type_Real__

#include <optional>

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

/// @brief                      Real type

class Real
{
   public:
    typedef double ValueType;

    Real() = delete;

    Real(Real::ValueType aReal);

    Real& operator=(Real::ValueType aReal);

    bool operator==(const Real& aReal) const;
    bool operator!=(const Real& aReal) const;
    bool operator<(const Real& aReal) const;
    bool operator<=(const Real& aReal) const;
    bool operator>(const Real& aReal) const;
    bool operator>=(const Real& aReal) const;

    bool operator==(const Real::ValueType& aReal) const;
    bool operator!=(const Real::ValueType& aReal) const;
    bool operator<(const Real::ValueType& aReal) const;
    bool operator<=(const Real::ValueType& aReal) const;
    bool operator>(const Real::ValueType& aReal) const;
    bool operator>=(const Real::ValueType& aReal) const;

    Real operator+(const Real& aReal) const;
    Real operator-(const Real& aReal) const;
    Real operator*(const Real& aReal) const;
    Real operator/(const Real& aReal) const;

    Real operator+(const Real::ValueType& aReal) const;
    Real operator-(const Real::ValueType& aReal) const;
    Real operator*(const Real::ValueType& aReal) const;
    Real operator/(const Real::ValueType& aReal) const;

    Real operator+(const Integer& anInteger) const;
    Real operator-(const Integer& anInteger) const;
    Real operator*(const Integer& anInteger) const;
    Real operator/(const Integer& anInteger) const;

    Real& operator+=(const Real& aReal);
    Real& operator-=(const Real& aReal);
    Real& operator*=(const Real& aReal);
    Real& operator/=(const Real& aReal);

    Real& operator+=(const Real::ValueType& aReal);
    Real& operator-=(const Real::ValueType& aReal);
    Real& operator*=(const Real::ValueType& aReal);
    Real& operator/=(const Real::ValueType& aReal);

    friend Real operator+(const Real::ValueType& aDouble, const Real& aReal);
    friend Real operator-(const Real::ValueType& aDouble, const Real& aReal);
    friend Real operator*(const Real::ValueType& aDouble, const Real& aReal);
    friend Real operator/(const Real::ValueType& aDouble, const Real& aReal);

    Real operator+() const;
    Real operator-() const;

    operator Real::ValueType() const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Real& aReal);

    bool isZero() const;
    bool isPositive() const;
    bool isNegative() const;
    bool isStrictlyPositive() const;
    bool isStrictlyNegative() const;
    bool isInfinity() const;
    bool isPositiveInfinity() const;
    bool isNegativeInfinity() const;

    bool isInteger() const;
    bool isFinite() const;

    bool isNear(const Real& aValue, const Real& aTolerance = Real::Epsilon()) const;

    type::Sign getSign() const;

    type::String toString(const std::optional<type::Integer>& aPrecision = std::nullopt) const;

    type::Integer toInteger() const;

    Real abs() const;

    type::Integer floor() const;

    Real sqrt() const;

    static Real Zero();

    static Real Pi();

    static Real HalfPi();

    static Real TwoPi();

    static Real Epsilon();

    static Real PositiveInfinity();

    static Real NegativeInfinity();

    static Real Integer(const type::Integer& anInteger);

    static Real CanParse(const type::String& aString);

    static Real Parse(const type::String& aString);

   private:
    enum class Type
    {

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
