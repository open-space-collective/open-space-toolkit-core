/// Apache License 2.0

#include <iomanip>
#include <iostream>
#include <limits>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

namespace ostk
{
namespace core
{
namespace types
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
    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {
        if ((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::PositiveInfinity))
        {
            return Real::PositiveInfinity();
        }
        else if ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::NegativeInfinity))
        {
            return Real::NegativeInfinity();
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
    }

    return Real::Undefined();
}

Real Real::operator-(const Real& aReal) const
{
    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {
        if ((type_ == Real::Type::PositiveInfinity) && (aReal.type_ == Real::Type::NegativeInfinity))
        {
            return Real::PositiveInfinity();
        }
        else if ((type_ == Real::Type::NegativeInfinity) && (aReal.type_ == Real::Type::PositiveInfinity))
        {
            return Real::NegativeInfinity();
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
    }

    return Real::Undefined();
}

Real Real::operator*(const Real& aReal) const
{
    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
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

            return Real::Undefined();
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

            return Real::Undefined();
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

            return Real::Undefined();
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

            return Real::Undefined();
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

    return Real::Undefined();
}

Real Real::operator/(const Real& aReal) const
{
    if (aReal.isZero())
    {
        return Real::Undefined();
    }

    if ((type_ != Real::Type::Undefined) && (aReal.type_ != Real::Type::Undefined))
    {
        if (type_ == Real::Type::PositiveInfinity)
        {
            if (aReal.isInfinity())
            {
                return Real::Undefined();
            }
            else if (aReal.isStrictlyPositive())
            {
                return Real::PositiveInfinity();
            }
            else if (aReal.isStrictlyNegative())
            {
                return Real::NegativeInfinity();
            }

            return Real::Undefined();
        }
        else if (type_ == Real::Type::NegativeInfinity)
        {
            if (aReal.isInfinity())
            {
                return Real::Undefined();
            }
            else if (aReal.isStrictlyPositive())
            {
                return Real::NegativeInfinity();
            }
            else if (aReal.isStrictlyNegative())
            {
                return Real::PositiveInfinity();
            }

            return Real::Undefined();
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

    return Real::Undefined();
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

        case Real::Type::Undefined:
            return Real::Undefined();

        case Real::Type::PositiveInfinity:
            return Real::NegativeInfinity();

        case Real::Type::NegativeInfinity:
            return Real::PositiveInfinity();

        default:
            break;
    }

    return Real::Undefined();
}

Real::operator Real::ValueType() const
{
    if (type_ != Real::Type::Defined)
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    return value_;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Real& aReal)
{
    (void)aReal;

    switch (aReal.type_)
    {
        case Real::Type::Undefined:
            anOutputStream << "Undefined";
            break;

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

    // ostk::core::utilities::Output::Header(anOutputStream, "Real") ;

    // ostk::core::utilities::Output::Line(anOutputStream) << "Type:" << aReal.type_ ;
    // ostk::core::utilities::Output::Line(anOutputStream) << "Value:" << aReal.value_ ;

    // ostk::core::utilities::Output::Footer(anOutputStream) ;

    return anOutputStream;
}

bool Real::isDefined() const
{
    return type_ != Real::Type::Undefined;
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
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (!aValue.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (!aTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
    }

    if ((!this->isFinite()) || (!aValue.isFinite()))
    {
        return false;
    }

    return ((*this) - aValue).abs() <= aTolerance;
}

types::Sign Real::getSign() const
{
    switch (type_)
    {
        case Real::Type::Undefined:
            return types::Sign::Undefined;

        case Real::Type::Defined:
        {
            if (value_ > 0.0)
            {
                return types::Sign::Positive;
            }
            else if (value_ < 0.0)
            {
                return types::Sign::Negative;
            }

            return types::Sign::None;
        }

        case Real::Type::PositiveInfinity:
            return types::Sign::Positive;

        case Real::Type::NegativeInfinity:
            return types::Sign::Negative;

        default:
            return types::Sign::Undefined;
    }

    return types::Sign::Undefined;
}

types::String Real::toString(const types::Integer& aPrecision) const
{
    switch (type_)
    {
        case Real::Type::Undefined:
            return "Undefined";

        case Real::Type::Defined:
        {
            if (!aPrecision.isDefined())
            {
                if (this->isInteger())
                {
                    types::String realString = boost::lexical_cast<std::string>(value_);

                    if (realString.find('e') == std::string::npos)
                    {
                        realString += ".0";
                    }

                    return realString;
                }

                // types::String realString = std::to_string(value_) ;
                types::String realString = boost::lexical_cast<std::string>(value_);

                // std::ostringstream stringStream ;

                // stringStream.precision(14) ;

                // stringStream << std::fixed << value_ ;

                // types::String realString = stringStream.str() ;

                if (realString.find('e') == std::string::npos)
                {
                    realString.erase(
                        realString.find_last_not_of('0') + 1, std::string::npos
                    );  // Remove trailing zeros if any
                }

                return realString;

                // return boost::lexical_cast<std::string>(value_) ;
                // return std::to_string(value_) ;
            }

            std::ostringstream stringStream;

            stringStream.precision(aPrecision);

            stringStream << std::fixed << value_;

            return stringStream.str();
        }

        case Real::Type::PositiveInfinity:
            return "+Inf";

        case Real::Type::NegativeInfinity:
            return "-Inf";
    }

    return types::String::Empty();
}

types::Integer Real::toInteger() const
{
    if (this->isInteger())
    {
        return types::Integer(static_cast<types::Integer::ValueType>(value_));
    }

    throw ostk::core::error::RuntimeError("Real is not integer.");

    return types::Integer::Undefined();
}

Real Real::abs() const
{
    switch (type_)
    {
        case Real::Type::Undefined:
            return Real::Undefined();

        case Real::Type::Defined:
            return Real(Real::Type::Defined, std::abs(value_));

        case Real::Type::PositiveInfinity:
        case Real::Type::NegativeInfinity:
            return Real::PositiveInfinity();

        default:
            throw ostk::core::error::runtime::Undefined("Type");
            break;
    }

    return Real::Undefined();
}

types::Integer Real::floor() const
{
    switch (type_)
    {
        case Real::Type::Undefined:
            return types::Integer::Undefined();

        case Real::Type::Defined:
            return types::Integer(static_cast<types::Integer::ValueType>(std::floor(value_)));

        case Real::Type::PositiveInfinity:
        case Real::Type::NegativeInfinity:
            return types::Integer::Undefined();

        default:
            throw ostk::core::error::runtime::Undefined("Type");
            break;
    }

    return types::Integer::Undefined();
}

Real Real::sqrt() const
{
    switch (type_)
    {
        case Real::Type::Undefined:
            return Real::Undefined();

        case Real::Type::Defined:
        {
            if (this->isStrictlyNegative())
            {
                return Real::Undefined();
            }

            return Real(Real::Type::Defined, std::sqrt(value_));
        }

        case Real::Type::PositiveInfinity:
            return Real::PositiveInfinity();

        case Real::Type::NegativeInfinity:
            return Real::Undefined();

        default:
            throw ostk::core::error::runtime::Undefined("Type");
            break;
    }

    return Real::Undefined();
}

Real Real::Undefined()
{
    return Real(Real::Type::Undefined, 0.0);
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

Real Real::Integer(const types::Integer& anInteger)
{
    if (anInteger.isDefined())
    {
        return Real(Real::Type::Defined, anInteger);
    }

    return Real::Undefined();
}

Real Real::CanParse(const types::String& aString)
{
    if (aString.isEmpty())
    {
        return false;
    }

    if ((aString == "Undefined") || (aString == "NaN") || (aString == "Inf") || (aString == "+Inf") ||
        (aString == "-Inf"))
    {
        return true;
    }

    Real::ValueType real;

    return boost::conversion::try_lexical_convert<Real::ValueType>(aString, real);
}

Real Real::Parse(const types::String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    if ((aString == "Undefined") || (aString == "NaN"))
    {
        return Real::Undefined();
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

    return Real::Undefined();
}

// Real                             Real::Object                             (   const   containers::Object& anObject )
// {

// }

Real::Real(const Real::Type& aType, const Real::ValueType& aReal)
    : type_(aType),
      value_(aReal)
{
}

}  // namespace types
}  // namespace core
}  // namespace ostk
