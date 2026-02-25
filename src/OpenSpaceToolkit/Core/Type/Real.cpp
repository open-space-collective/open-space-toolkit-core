/// Apache License 2.0

#include <iomanip>
#include <iostream>
#include <limits>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

namespace ostk
{
namespace core
{
namespace type
{

Real::Real(Real::ValueType aReal)
    : type_(Real::Type::Defined),
      value_(aReal)
{
}

Real& Real::operator=(Real::ValueType aReal)
{
    type_ = Real::Type::Defined;
    value_ = aReal;

    return *this;
}

bool Real::operator==(const Real& aReal) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ == aReal.value_);
}

bool Real::operator!=(const Real& aReal) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ != aReal.value_);
}

bool Real::operator<(const Real& aReal) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ < aReal.value_);
}

bool Real::operator<=(const Real& aReal) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ <= aReal.value_);
}

bool Real::operator>(const Real& aReal) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ > aReal.value_);
}

bool Real::operator>=(const Real& aReal) const
{
    return (type_ == Real::Type::Defined) && (aReal.type_ == Real::Type::Defined) && (value_ >= aReal.value_);
}

bool Real::operator==(const Real::ValueType& aReal) const
{
    return (type_ == Real::Type::Defined) && (value_ == aReal);
}

bool Real::operator!=(const Real::ValueType& aReal) const
{
    return (type_ == Real::Type::Defined) && (value_ != aReal);
}

bool Real::operator<(const Real::ValueType& aReal) const
{
    return (type_ == Real::Type::Defined) && (value_ < aReal);
}

bool Real::operator<=(const Real::ValueType& aReal) const
{
    return (type_ == Real::Type::Defined) && (value_ <= aReal);
}

bool Real::operator>(const Real::ValueType& aReal) const
{
    return (type_ == Real::Type::Defined) && (value_ > aReal);
}

bool Real::operator>=(const Real::ValueType& aReal) const
{
    return (type_ == Real::Type::Defined) && (value_ >= aReal);
}

Real Real::operator+(const Real& aReal) const
{
    if ((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::PositiveInfinity))
    {
        return Real::PositiveInfinity();
    }
    else if ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::NegativeInfinity))
    {
        return Real::NegativeInfinity();
    }
    else if (((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::NegativeInfinity)) ||
             ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::PositiveInfinity)))
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: +Inf + (-Inf).");
    }
    else if ((type_ == Real::Type::Defined) || (aReal.type_ == Real::Type::Defined))
    {
        if (type_ != Real::Type::Defined)
        {
            return *this;
        }
        else if (aReal.type_ != Real::Type::Defined)
        {
            return aReal;
        }

        // [TBC] Use __builtin_add_overflow instead?

        if ((aReal.value_ > 0.0) &&
            (value_ >= (std::numeric_limits<Real::ValueType>::max() - aReal.value_)))  // Addition would overflow
        {
            return (value_ != 0.0) ? Real::PositiveInfinity() : aReal;
        }

        if ((aReal.value_ < 0.0) && (value_ <= (std::numeric_limits<Real::ValueType>::lowest() - aReal.value_)
                                    ))  // Addition would underflow
        {
            return (value_ != 0.0) ? Real::NegativeInfinity() : aReal;
        }

        return Real(value_ + aReal.value_);
    }

    throw ostk::core::error::RuntimeError("Indeterminate form: +Inf + (-Inf).");
}

Real Real::operator-(const Real& aReal) const
{
    if ((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::NegativeInfinity))
    {
        return Real::PositiveInfinity();
    }
    else if ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::PositiveInfinity))
    {
        return Real::NegativeInfinity();
    }
    else if (((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::PositiveInfinity)) ||
             ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::NegativeInfinity)))
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: Inf - Inf.");
    }
    else if ((type_ == Real::Type::Defined) || (aReal.type_ == Real::Type::Defined))
    {
        if (type_ != Real::Type::Defined)
        {
            return *this;
        }
        else if (aReal.type_ != Real::Type::Defined)
        {
            if (aReal.type_ == Real::Type::PositiveInfinity)
            {
                return Real::NegativeInfinity();
            }

            return Real::PositiveInfinity();
        }

        if ((aReal.value_ < 0.0) &&
            (value_ >= (std::numeric_limits<Real::ValueType>::max() + aReal.value_)))  // Subtraction would overflow
        {
            return (value_ != 0.0) ? Real::PositiveInfinity() : -aReal;
        }

        if ((aReal.value_ > 0.0) && (value_ <= (std::numeric_limits<Real::ValueType>::lowest() + aReal.value_)
                                    ))  // Subtraction would underflow
        {
            return (value_ != 0.0) ? Real::NegativeInfinity() : -aReal;
        }

        return Real(value_ - aReal.value_);
    }

    throw ostk::core::error::RuntimeError("Indeterminate form: Inf - Inf.");
}

Real Real::operator*(const Real& aReal) const
{
    if (type_ == Real::Type::PositiveInfinity)
    {
        if (aReal.isStrictlyPositive())
        {
            return Real::PositiveInfinity();
        }
        else if (aReal.isStrictlyNegative())
        {
            return Real::NegativeInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: Inf * 0.");
    }
    else if (type_ == Real::Type::NegativeInfinity)
    {
        if (aReal.isStrictlyPositive())
        {
            return Real::NegativeInfinity();
        }
        else if (aReal.isStrictlyNegative())
        {
            return Real::PositiveInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: Inf * 0.");
    }
    else if (aReal.type_ == Real::Type::PositiveInfinity)
    {
        if (this->isStrictlyPositive())
        {
            return Real::PositiveInfinity();
        }
        else if (this->isStrictlyNegative())
        {
            return Real::NegativeInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: 0 * Inf.");
    }
    else if (aReal.type_ == Real::Type::NegativeInfinity)
    {
        if (this->isStrictlyPositive())
        {
            return Real::NegativeInfinity();
        }
        else if (this->isStrictlyNegative())
        {
            return Real::PositiveInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: 0 * Inf.");
    }
    else
    {
        if (this->isZero() || aReal.isZero())
        {
            return Real::Zero();
        }

        // Check for -1 for two's complement machines

        if ((value_ < 0.0) &&
            (aReal.value_ == std::numeric_limits<Real::ValueType>::lowest()))  // Multiplication can overflow
        {
            return Real::PositiveInfinity();
        }

        if ((aReal.value_ < 0.0) &&
            (value_ == std::numeric_limits<Real::ValueType>::lowest()))  // Multiplication can overflow
        {
            return Real::PositiveInfinity();
        }

        if ((this->getSign() == aReal.getSign()) &&
            (std::abs(value_) > (std::numeric_limits<Real::ValueType>::max() / std::abs(aReal.value_))
            ))  // Multiplication would overflow
        {
            return Real::PositiveInfinity();
        }

        if ((value_ == +1) && (aReal.value_ == std::numeric_limits<Real::ValueType>::lowest()))
        {
            return Real(std::numeric_limits<Real::ValueType>::lowest());
        }

        if ((value_ == -1) && (aReal.value_ == std::numeric_limits<Real::ValueType>::lowest()))
        {
            return Real::PositiveInfinity();
        }

        if ((aReal.value_ != -1) && (this->getSign() != aReal.getSign()) &&
            ((-std::abs(value_)) < (std::numeric_limits<Real::ValueType>::lowest() / std::abs(aReal.value_))
            ))  // Multiplication would underflow
        {
            return Real::NegativeInfinity();
        }

        return Real(value_ * aReal.value_);
    }
}

Real Real::operator/(const Real& aReal) const
{
    if (aReal.isZero())
    {
        throw ostk::core::error::RuntimeError("Division by zero.");
    }

    if (type_ == Real::Type::PositiveInfinity)
    {
        if (aReal.isInfinity())
        {
            throw ostk::core::error::RuntimeError("Indeterminate form: Inf / Inf.");
        }
        else if (aReal.isStrictlyPositive())
        {
            return Real::PositiveInfinity();
        }
        else if (aReal.isStrictlyNegative())
        {
            return Real::NegativeInfinity();
        }

        throw ostk::core::error::RuntimeError("Division by zero.");
    }
    else if (type_ == Real::Type::NegativeInfinity)
    {
        if (aReal.isInfinity())
        {
            throw ostk::core::error::RuntimeError("Indeterminate form: Inf / Inf.");
        }
        else if (aReal.isStrictlyPositive())
        {
            return Real::NegativeInfinity();
        }
        else if (aReal.isStrictlyNegative())
        {
            return Real::PositiveInfinity();
        }

        throw ostk::core::error::RuntimeError("Division by zero.");
    }
    else
    {
        if (this->isZero() || aReal.isInfinity())
        {
            return Real::Zero();
        }
        else
        {
            if ((value_ == std::numeric_limits<Real::ValueType>::lowest()) && (aReal.value_ == -1))
            {
                return Real::PositiveInfinity();
            }

            return Real(value_ / aReal.value_);
        }
    }
}

Real Real::operator+(const Real::ValueType& aReal) const
{
    return (*this) + Real(aReal);
}

Real Real::operator-(const Real::ValueType& aReal) const
{
    return (*this) - Real(aReal);
}

Real Real::operator*(const Real::ValueType& aReal) const
{
    return (*this) * Real(aReal);
}

Real Real::operator/(const Real::ValueType& aReal) const
{
    return (*this) / Real(aReal);
}

Real& Real::operator+=(const Real& aReal)
{
    (*this) = (*this) + aReal;

    return *this;
}

Real& Real::operator-=(const Real& aReal)
{
    (*this) = (*this) - aReal;

    return *this;
}

Real& Real::operator*=(const Real& aReal)
{
    (*this) = (*this) * aReal;

    return *this;
}

Real& Real::operator/=(const Real& aReal)
{
    (*this) = (*this) / aReal;

    return *this;
}

Real& Real::operator+=(const Real::ValueType& aReal)
{
    (*this) = (*this) + Real(aReal);

    return *this;
}

Real& Real::operator-=(const Real::ValueType& aReal)
{
    (*this) = (*this) - Real(aReal);

    return *this;
}

Real& Real::operator*=(const Real::ValueType& aReal)
{
    (*this) = (*this) * Real(aReal);

    return *this;
}

Real& Real::operator/=(const Real::ValueType& aReal)
{
    (*this) = (*this) / Real(aReal);

    return *this;
}

Real operator+(const Real::ValueType& anInt, const Real& aReal)
{
    return Real(anInt) + aReal;
}

Real operator-(const Real::ValueType& anInt, const Real& aReal)
{
    return Real(anInt) - aReal;
}

Real operator*(const Real::ValueType& anInt, const Real& aReal)
{
    return Real(anInt) * aReal;
}

Real operator/(const Real::ValueType& anInt, const Real& aReal)
{
    return Real(anInt) / aReal;
}

Real Real::operator+() const
{
    return *this;
}

Real Real::operator-() const
{
    switch (type_)
    {
        case Real::Type::Defined:
        {
            if (value_ == std::numeric_limits<Real::ValueType>::lowest())
            {
                return Real::PositiveInfinity();
            }

            return Real(-value_);
        }

        case Real::Type::PositiveInfinity:
            return Real::NegativeInfinity();

        case Real::Type::NegativeInfinity:
            return Real::PositiveInfinity();

        default:
            break;
    }

    throw ostk::core::error::RuntimeError("Cannot negate Real.");
}

Real::operator Real::ValueType() const
{
    if (type_ != Real::Type::Defined)
    {
        throw ostk::core::error::RuntimeError("Cannot convert non-finite Real to value.");
    }

    return value_;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Real& aReal)
{
    switch (aReal.type_)
    {
        case Real::Type::Defined:
            anOutputStream << aReal.value_;
            break;

        case Real::Type::PositiveInfinity:
            anOutputStream << "+Inf";
            break;

        case Real::Type::NegativeInfinity:
            anOutputStream << "-Inf";
            break;
    }

    return anOutputStream;
}

bool Real::isZero() const
{
    return (type_ == Real::Type::Defined) && (value_ == 0.0);
}

bool Real::isPositive() const
{
    return ((type_ == Real::Type::Defined) && (value_ >= 0.0)) || this->isPositiveInfinity();
}

bool Real::isNegative() const
{
    return ((type_ == Real::Type::Defined) && (value_ <= 0.0)) || this->isNegativeInfinity();
}

bool Real::isStrictlyPositive() const
{
    return ((type_ == Real::Type::Defined) && (value_ > 0.0)) || this->isPositiveInfinity();
}

bool Real::isStrictlyNegative() const
{
    return ((type_ == Real::Type::Defined) && (value_ < 0.0)) || this->isNegativeInfinity();
}

bool Real::isInfinity() const
{
    return this->isPositiveInfinity() || this->isNegativeInfinity();
}

bool Real::isPositiveInfinity() const
{
    return type_ == Real::Type::PositiveInfinity;
}

bool Real::isNegativeInfinity() const
{
    return type_ == Real::Type::NegativeInfinity;
}

bool Real::isInteger() const
{
    if (this->isFinite())
    {
        double intpart;

        return std::modf(value_, &intpart) == 0.0;
    }

    return false;
}

bool Real::isFinite() const
{
    return type_ == Real::Type::Defined;
}

bool Real::isNear(const Real& aValue, const Real& aTolerance) const
{
    if ((!this->isFinite()) || (!aValue.isFinite()))
    {
        return false;
    }

    return ((*this) - aValue).abs() <= aTolerance;
}

type::Sign Real::getSign() const
{
    switch (type_)
    {
        case Real::Type::Defined:
        {
            if (value_ > 0.0)
            {
                return type::Sign::Positive;
            }
            else if (value_ < 0.0)
            {
                return type::Sign::Negative;
            }

            return type::Sign::None;
        }

        case Real::Type::PositiveInfinity:
            return type::Sign::Positive;

        case Real::Type::NegativeInfinity:
            return type::Sign::Negative;

        default:
            return type::Sign::Undefined;
    }

    return type::Sign::Undefined;
}

type::String Real::toString(const std::optional<type::Integer>& aPrecision) const
{
    switch (type_)
    {
        case Real::Type::Defined:
        {
            if (!aPrecision.has_value())
            {
                if (this->isInteger())
                {
                    type::String realString = boost::lexical_cast<std::string>(value_);

                    if (realString.find('e') == std::string::npos)
                    {
                        realString += ".0";
                    }

                    return realString;
                }

                type::String realString = boost::lexical_cast<std::string>(value_);

                if (realString.find('e') == std::string::npos)
                {
                    realString.erase(
                        realString.find_last_not_of('0') + 1, std::string::npos
                    );  // Remove trailing zeros if any
                }

                return realString;
            }

            std::ostringstream stringStream;

            stringStream.precision(aPrecision.value());

            stringStream << std::fixed << value_;

            return stringStream.str();
        }

        case Real::Type::PositiveInfinity:
            return "+Inf";

        case Real::Type::NegativeInfinity:
            return "-Inf";
    }

    return type::String::Empty();
}

type::Integer Real::toInteger() const
{
    if (this->isInteger())
    {
        return type::Integer(static_cast<type::Integer::ValueType>(value_));
    }

    throw ostk::core::error::RuntimeError("Real is not integer.");
}

Real Real::abs() const
{
    switch (type_)
    {
        case Real::Type::Defined:
            return Real(Real::Type::Defined, std::abs(value_));

        case Real::Type::PositiveInfinity:
        case Real::Type::NegativeInfinity:
            return Real::PositiveInfinity();

        default:
            throw ostk::core::error::RuntimeError("Cannot compute abs of Real.");
            break;
    }

    throw ostk::core::error::RuntimeError("Cannot compute abs of Real.");
}

type::Integer Real::floor() const
{
    switch (type_)
    {
        case Real::Type::Defined:
            return type::Integer(static_cast<type::Integer::ValueType>(std::floor(value_)));

        case Real::Type::PositiveInfinity:
        case Real::Type::NegativeInfinity:
            throw ostk::core::error::RuntimeError("Cannot compute floor of infinite Real.");

        default:
            throw ostk::core::error::RuntimeError("Cannot compute floor of Real.");
            break;
    }

    throw ostk::core::error::RuntimeError("Cannot compute floor of Real.");
}

Real Real::sqrt() const
{
    switch (type_)
    {
        case Real::Type::Defined:
        {
            if (this->isStrictlyNegative())
            {
                throw ostk::core::error::RuntimeError("Cannot compute sqrt of negative Real.");
            }

            return Real(Real::Type::Defined, std::sqrt(value_));
        }

        case Real::Type::PositiveInfinity:
            return Real::PositiveInfinity();

        case Real::Type::NegativeInfinity:
            throw ostk::core::error::RuntimeError("Cannot compute sqrt of negative infinity.");

        default:
            throw ostk::core::error::RuntimeError("Cannot compute sqrt of Real.");
            break;
    }

    throw ostk::core::error::RuntimeError("Cannot compute sqrt of Real.");
}

Real Real::Zero()
{
    return Real(Real::Type::Defined, 0.0);
}

Real Real::Pi()
{
    return Real(Real::Type::Defined, M_PI);
}

Real Real::HalfPi()
{
    return Real(Real::Type::Defined, M_PI / 2.0);
}

Real Real::TwoPi()
{
    return Real(Real::Type::Defined, 2.0 * M_PI);
}

Real Real::Epsilon()
{
    return Real(Real::Type::Defined, 1e-15);
}

Real Real::PositiveInfinity()
{
    return Real(Real::Type::PositiveInfinity, std::numeric_limits<Real::ValueType>::max());
}

Real Real::NegativeInfinity()
{
    return Real(Real::Type::NegativeInfinity, std::numeric_limits<Real::ValueType>::lowest());
}

Real Real::Integer(const type::Integer& anInteger)
{
    return Real(Real::Type::Defined, anInteger);
}

Real Real::CanParse(const type::String& aString)
{
    if (aString.isEmpty())
    {
        return false;
    }

    if ((aString == "NaN") || (aString == "Inf") || (aString == "+Inf") || (aString == "-Inf"))
    {
        return true;
    }

    Real::ValueType real;

    return boost::conversion::try_lexical_convert<Real::ValueType>(aString, real);
}

Real Real::Parse(const type::String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    if (aString == "NaN")
    {
        throw ostk::core::error::RuntimeError("Cannot parse 'NaN' as Real.");
    }

    if ((aString == "Undefined"))
    {
        throw ostk::core::error::RuntimeError("Cannot parse 'Undefined' as Real.");
    }

    if ((aString == "Inf") || (aString == "+Inf"))
    {
        return Real::PositiveInfinity();
    }

    if (aString == "-Inf")
    {
        return Real::NegativeInfinity();
    }

    try
    {
        const Real::ValueType value = boost::lexical_cast<Real::ValueType>(aString);

        if (value != value)
        {
            throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.");
        }

        return Real(value);
    }
    catch (const boost::bad_lexical_cast&)
    {
        throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.");
    }

    throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.");
}

Real::Real(const Real::Type& aType, const Real::ValueType& aReal)
    : type_(aType),
      value_(aReal)
{
}

}  // namespace type
}  // namespace core
}  // namespace ostk
