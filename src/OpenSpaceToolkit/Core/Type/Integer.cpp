/// Apache License 2.0

#include <iostream>
#include <limits>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>

namespace ostk
{
namespace core
{
namespace type
{

Integer::Integer(Integer::ValueType anInteger)
    : type_(Integer::Type::Defined),
      value_(anInteger)
{
}

Integer& Integer::operator=(Integer::ValueType anInteger)
{
    type_ = Integer::Type::Defined;
    value_ = anInteger;

    return *this;
}

bool Integer::operator==(const Integer& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (anInteger.type_ == Integer::Type::Defined) &&
           (value_ == anInteger.value_);
}

bool Integer::operator!=(const Integer& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (anInteger.type_ == Integer::Type::Defined) &&
           (value_ != anInteger.value_);
}

bool Integer::operator<(const Integer& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (anInteger.type_ == Integer::Type::Defined) &&
           (value_ < anInteger.value_);
}

bool Integer::operator<=(const Integer& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (anInteger.type_ == Integer::Type::Defined) &&
           (value_ <= anInteger.value_);
}

bool Integer::operator>(const Integer& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (anInteger.type_ == Integer::Type::Defined) &&
           (value_ > anInteger.value_);
}

bool Integer::operator>=(const Integer& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (anInteger.type_ == Integer::Type::Defined) &&
           (value_ >= anInteger.value_);
}

bool Integer::operator==(const Integer::ValueType& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (value_ == anInteger);
}

bool Integer::operator!=(const Integer::ValueType& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (value_ != anInteger);
}

bool Integer::operator<(const Integer::ValueType& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (value_ < anInteger);
}

bool Integer::operator<=(const Integer::ValueType& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (value_ <= anInteger);
}

bool Integer::operator>(const Integer::ValueType& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (value_ > anInteger);
}

bool Integer::operator>=(const Integer::ValueType& anInteger) const
{
    return (type_ == Integer::Type::Defined) && (value_ >= anInteger);
}

Integer Integer::operator+(const Integer& anInteger) const
{
    if ((type_ == Integer::Type::PositiveInfinity) && (anInteger.type_ == Integer::Type::PositiveInfinity))
    {
        return Integer::PositiveInfinity();
    }
    else if ((type_ == Integer::Type::NegativeInfinity) && (anInteger.type_ == Integer::Type::NegativeInfinity))
    {
        return Integer::NegativeInfinity();
    }
    else if ((type_ == Integer::Type::PositiveInfinity) && (anInteger.type_ == Integer::Type::NegativeInfinity))
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: +Inf + (-Inf).");
    }
    else if ((type_ == Integer::Type::NegativeInfinity) && (anInteger.type_ == Integer::Type::PositiveInfinity))
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: -Inf + (+Inf).");
    }
    else if ((type_ == Integer::Type::Defined) || (anInteger.type_ == Integer::Type::Defined))
    {
        if (type_ != Integer::Type::Defined)
        {
            return *this;
        }
        else if (anInteger.type_ != Integer::Type::Defined)
        {
            return anInteger;
        }

        if ((anInteger.value_ > 0) &&
            (value_ > (std::numeric_limits<Integer::ValueType>::max() - anInteger.value_)))
        {
            return Integer::PositiveInfinity();
        }

        if ((anInteger.value_ < 0) &&
            (value_ < (std::numeric_limits<Integer::ValueType>::min() - anInteger.value_)))
        {
            return Integer::NegativeInfinity();
        }

        return Integer(value_ + anInteger.value_);
    }

    throw ostk::core::error::RuntimeError("Indeterminate form in Integer addition.");
}

Integer Integer::operator-(const Integer& anInteger) const
{
    if ((type_ == Integer::Type::PositiveInfinity) && (anInteger.type_ == Integer::Type::NegativeInfinity))
    {
        return Integer::PositiveInfinity();
    }
    else if ((type_ == Integer::Type::NegativeInfinity) && (anInteger.type_ == Integer::Type::PositiveInfinity))
    {
        return Integer::NegativeInfinity();
    }
    else if ((type_ == Integer::Type::PositiveInfinity) && (anInteger.type_ == Integer::Type::PositiveInfinity))
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: +Inf - (+Inf).");
    }
    else if ((type_ == Integer::Type::NegativeInfinity) && (anInteger.type_ == Integer::Type::NegativeInfinity))
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: -Inf - (-Inf).");
    }
    else if ((type_ == Integer::Type::Defined) || (anInteger.type_ == Integer::Type::Defined))
    {
        if (type_ != Integer::Type::Defined)
        {
            return *this;
        }
        else if (anInteger.type_ != Integer::Type::Defined)
        {
            if (anInteger.type_ == Integer::Type::PositiveInfinity)
            {
                return Integer::NegativeInfinity();
            }

            return Integer::PositiveInfinity();
        }

        if ((anInteger.value_ < 0) &&
            (value_ > (std::numeric_limits<Integer::ValueType>::max() + anInteger.value_)))
        {
            return Integer::PositiveInfinity();
        }

        if ((anInteger.value_ > 0) &&
            (value_ < (std::numeric_limits<Integer::ValueType>::min() + anInteger.value_)))
        {
            return Integer::NegativeInfinity();
        }

        return Integer(value_ - anInteger.value_);
    }

    throw ostk::core::error::RuntimeError("Indeterminate form in Integer subtraction.");
}

Integer Integer::operator*(const Integer& anInteger) const
{
    if (type_ == Integer::Type::PositiveInfinity)
    {
        if (anInteger.isStrictlyPositive())
        {
            return Integer::PositiveInfinity();
        }
        else if (anInteger.isStrictlyNegative())
        {
            return Integer::NegativeInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: +Inf * 0.");
    }
    else if (type_ == Integer::Type::NegativeInfinity)
    {
        if (anInteger.isStrictlyPositive())
        {
            return Integer::NegativeInfinity();
        }
        else if (anInteger.isStrictlyNegative())
        {
            return Integer::PositiveInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: -Inf * 0.");
    }
    else if (anInteger.type_ == Integer::Type::PositiveInfinity)
    {
        if (this->isStrictlyPositive())
        {
            return Integer::PositiveInfinity();
        }
        else if (this->isStrictlyNegative())
        {
            return Integer::NegativeInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: 0 * +Inf.");
    }
    else if (anInteger.type_ == Integer::Type::NegativeInfinity)
    {
        if (this->isStrictlyPositive())
        {
            return Integer::NegativeInfinity();
        }
        else if (this->isStrictlyNegative())
        {
            return Integer::PositiveInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form: 0 * -Inf.");
    }
    else
    {
        if (this->isZero() || anInteger.isZero())
        {
            return Integer::Zero();
        }

        // Check for -1 for two's complement machines

        if ((value_ < 0) &&
            (anInteger.value_ == std::numeric_limits<Integer::ValueType>::min()))
        {
            return Integer::PositiveInfinity();
        }

        if ((anInteger.value_ < 0) &&
            (value_ == std::numeric_limits<Integer::ValueType>::min()))
        {
            return Integer::PositiveInfinity();
        }

        if ((this->getSign() == anInteger.getSign()) &&
            (std::abs(value_) > (std::numeric_limits<Integer::ValueType>::max() / std::abs(anInteger.value_))))
        {
            return Integer::PositiveInfinity();
        }

        if ((value_ == +1) && (anInteger.value_ == std::numeric_limits<Integer::ValueType>::min()))
        {
            return Integer(std::numeric_limits<Integer::ValueType>::min());
        }

        if ((value_ == -1) && (anInteger.value_ == std::numeric_limits<Integer::ValueType>::min()))
        {
            return Integer::PositiveInfinity();
        }

        if ((anInteger.value_ != -1) && (this->getSign() != anInteger.getSign()) &&
            ((-std::abs(value_)) < (std::numeric_limits<Integer::ValueType>::min() / std::abs(anInteger.value_))))
        {
            return Integer::NegativeInfinity();
        }

        return Integer(value_ * anInteger.value_);
    }
}

Integer Integer::operator/(const Integer& anInteger) const
{
    if (anInteger.isZero())
    {
        throw ostk::core::error::RuntimeError("Division by zero.");
    }

    if (type_ == Integer::Type::PositiveInfinity)
    {
        if (anInteger.isInfinity())
        {
            throw ostk::core::error::RuntimeError("Indeterminate form: Inf / Inf.");
        }
        else if (anInteger.isStrictlyPositive())
        {
            return Integer::PositiveInfinity();
        }
        else if (anInteger.isStrictlyNegative())
        {
            return Integer::NegativeInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form in Integer division.");
    }
    else if (type_ == Integer::Type::NegativeInfinity)
    {
        if (anInteger.isInfinity())
        {
            throw ostk::core::error::RuntimeError("Indeterminate form: Inf / Inf.");
        }
        else if (anInteger.isStrictlyPositive())
        {
            return Integer::NegativeInfinity();
        }
        else if (anInteger.isStrictlyNegative())
        {
            return Integer::PositiveInfinity();
        }

        throw ostk::core::error::RuntimeError("Indeterminate form in Integer division.");
    }
    else
    {
        if (this->isZero() || anInteger.isInfinity())
        {
            return Integer::Zero();
        }
        else
        {
            if ((value_ == std::numeric_limits<Integer::ValueType>::min()) && (anInteger.value_ == -1))
            {
                return Integer::PositiveInfinity();
            }

            return Integer(value_ / anInteger.value_);
        }
    }
}

Integer Integer::operator%(const Integer& anInteger) const
{
    if (anInteger.isZero())
    {
        throw ostk::core::error::RuntimeError("Modulo by zero.");
    }

    if (this->isZero())
    {
        return Integer::Zero();
    }
    else if (!this->isInfinity() && anInteger.isInfinity())
    {
        return *this;
    }
    else if ((!this->isInfinity()) && this->isStrictlyPositive() && (!anInteger.isInfinity()) &&
             (anInteger.value_ == std::numeric_limits<Integer::ValueType>::min()))
    {
        return *this;
    }
    else if ((!anInteger.isInfinity()) && (std::abs(anInteger.value_) == 1))
    {
        return Integer::Zero();
    }
    else if (this->isInfinity())
    {
        throw ostk::core::error::RuntimeError("Indeterminate form: Inf % n.");
    }
    else
    {
        return Integer(value_ % anInteger.value_);
    }
}

Integer Integer::operator+(const Integer::ValueType& anInteger) const
{
    return (*this) + Integer(anInteger);
}

Integer Integer::operator-(const Integer::ValueType& anInteger) const
{
    return (*this) - Integer(anInteger);
}

Integer Integer::operator*(const Integer::ValueType& anInteger) const
{
    return (*this) * Integer(anInteger);
}

Integer Integer::operator/(const Integer::ValueType& anInteger) const
{
    return (*this) / Integer(anInteger);
}

Integer Integer::operator%(const Integer::ValueType& anInteger) const
{
    return (*this) % Integer(anInteger);
}

Integer& Integer::operator+=(const Integer& anInteger)
{
    (*this) = (*this) + anInteger;

    return *this;
}

Integer& Integer::operator-=(const Integer& anInteger)
{
    (*this) = (*this) - anInteger;

    return *this;
}

Integer& Integer::operator*=(const Integer& anInteger)
{
    (*this) = (*this) * anInteger;

    return *this;
}

Integer& Integer::operator/=(const Integer& anInteger)
{
    (*this) = (*this) / anInteger;

    return *this;
}

Integer& Integer::operator%=(const Integer& anInteger)
{
    (*this) = (*this) % anInteger;

    return *this;
}

Integer& Integer::operator+=(const Integer::ValueType& anInteger)
{
    (*this) = (*this) + Integer(anInteger);

    return *this;
}

Integer& Integer::operator-=(const Integer::ValueType& anInteger)
{
    (*this) = (*this) - Integer(anInteger);

    return *this;
}

Integer& Integer::operator*=(const Integer::ValueType& anInteger)
{
    (*this) = (*this) * Integer(anInteger);

    return *this;
}

Integer& Integer::operator/=(const Integer::ValueType& anInteger)
{
    (*this) = (*this) / Integer(anInteger);

    return *this;
}

Integer& Integer::operator%=(const Integer::ValueType& anInteger)
{
    (*this) = (*this) % Integer(anInteger);

    return *this;
}

Integer operator+(const Integer::ValueType& anInt, const Integer& anInteger)
{
    return Integer(anInt) + anInteger;
}

Integer operator-(const Integer::ValueType& anInt, const Integer& anInteger)
{
    return Integer(anInt) - anInteger;
}

Integer operator*(const Integer::ValueType& anInt, const Integer& anInteger)
{
    return Integer(anInt) * anInteger;
}

Integer operator/(const Integer::ValueType& anInt, const Integer& anInteger)
{
    return Integer(anInt) / anInteger;
}

Integer operator%(const Integer::ValueType& anInt, const Integer& anInteger)
{
    return Integer(anInt) % anInteger;
}

Integer Integer::operator+() const
{
    return *this;
}

Integer Integer::operator-() const
{
    switch (type_)
    {
        case Integer::Type::Defined:
        {
            if (value_ == std::numeric_limits<Integer::ValueType>::min())
            {
                return Integer::PositiveInfinity();
            }

            return Integer(-value_);
        }

        case Integer::Type::PositiveInfinity:
            return Integer::NegativeInfinity();

        case Integer::Type::NegativeInfinity:
            return Integer::PositiveInfinity();

        default:
            break;
    }

    throw ostk::core::error::RuntimeError("Cannot negate Integer.");
}

Integer& Integer::operator++()
{
    switch (type_)
    {
        case Integer::Type::Defined:
        {
            if (value_ == std::numeric_limits<Integer::ValueType>::max())
            {
                type_ = Integer::Type::PositiveInfinity;
            }
            else
            {
                ++value_;
            }

            break;
        }

        case Integer::Type::PositiveInfinity:
        case Integer::Type::NegativeInfinity:
        default:
            break;
    }

    return *this;
}

Integer& Integer::operator--()
{
    switch (type_)
    {
        case Integer::Type::Defined:
        {
            if (value_ == std::numeric_limits<Integer::ValueType>::min())
            {
                type_ = Integer::Type::NegativeInfinity;
            }
            else
            {
                --value_;
            }

            break;
        }

        case Integer::Type::PositiveInfinity:
        case Integer::Type::NegativeInfinity:
        default:
            break;
    }

    return *this;
}

Integer Integer::operator++(int anInteger)
{
    (void)anInteger;

    Integer integerCopy(*this);

    switch (type_)
    {
        case Integer::Type::Defined:
        {
            if (value_ == std::numeric_limits<Integer::ValueType>::max())
            {
                type_ = Integer::Type::PositiveInfinity;
            }
            else
            {
                value_++;
            }

            break;
        }

        case Integer::Type::PositiveInfinity:
        case Integer::Type::NegativeInfinity:
        default:
            break;
    }

    return integerCopy;
}

Integer Integer::operator--(int anInteger)
{
    (void)anInteger;

    Integer integerCopy(*this);

    switch (type_)
    {
        case Integer::Type::Defined:
        {
            if (value_ == std::numeric_limits<Integer::ValueType>::min())
            {
                type_ = Integer::Type::NegativeInfinity;
            }
            else
            {
                value_--;
            }

            break;
        }

        case Integer::Type::PositiveInfinity:
        case Integer::Type::NegativeInfinity:
        default:
            break;
    }

    return integerCopy;
}

Integer::operator Integer::ValueType() const
{
    if (type_ != Integer::Type::Defined)
    {
        throw ostk::core::error::RuntimeError("Cannot convert non-finite Integer to value.");
    }

    return value_;
}

std::ostream& operator<<(std::ostream& anOutputStream, const Integer& anInteger)
{
    (void)anInteger;

    switch (anInteger.type_)
    {
        case Integer::Type::Defined:
            anOutputStream << anInteger.value_;
            break;

        case Integer::Type::PositiveInfinity:
            anOutputStream << "+Inf";
            break;

        case Integer::Type::NegativeInfinity:
            anOutputStream << "-Inf";
            break;
    }

    return anOutputStream;
}

bool Integer::isZero() const
{
    return (type_ == Integer::Type::Defined) && (value_ == 0);
}

bool Integer::isPositive() const
{
    return ((type_ == Integer::Type::Defined) && (value_ >= 0)) || this->isPositiveInfinity();
}

bool Integer::isNegative() const
{
    return ((type_ == Integer::Type::Defined) && (value_ <= 0)) || this->isNegativeInfinity();
}

bool Integer::isStrictlyPositive() const
{
    return ((type_ == Integer::Type::Defined) && (value_ > 0)) || this->isPositiveInfinity();
}

bool Integer::isStrictlyNegative() const
{
    return ((type_ == Integer::Type::Defined) && (value_ < 0)) || this->isNegativeInfinity();
}

bool Integer::isInfinity() const
{
    return this->isPositiveInfinity() || this->isNegativeInfinity();
}

bool Integer::isPositiveInfinity() const
{
    return type_ == Integer::Type::PositiveInfinity;
}

bool Integer::isNegativeInfinity() const
{
    return type_ == Integer::Type::NegativeInfinity;
}

bool Integer::isFinite() const
{
    return type_ == Integer::Type::Defined;
}

bool Integer::isEven() const
{
    return this->isFinite() && (value_ % 2 == 0);
}

bool Integer::isOdd() const
{
    return this->isFinite() && (value_ % 2 != 0);
}

type::Sign Integer::getSign() const
{
    switch (type_)
    {
        case Integer::Type::Defined:
        {
            if (value_ > 0)
            {
                return type::Sign::Positive;
            }
            else if (value_ < 0)
            {
                return type::Sign::Negative;
            }

            return type::Sign::None;
        }

        case Integer::Type::PositiveInfinity:
            return type::Sign::Positive;

        case Integer::Type::NegativeInfinity:
            return type::Sign::Negative;

        default:
            return type::Sign::Undefined;
    }

    return type::Sign::Undefined;
}

type::String Integer::toString() const
{
    switch (type_)
    {
        case Integer::Type::Defined:
            return boost::lexical_cast<std::string>(value_);

        case Integer::Type::PositiveInfinity:
            return "+Inf";

        case Integer::Type::NegativeInfinity:
            return "-Inf";
    }

    return type::String::Empty();
}

Integer Integer::Zero()
{
    return Integer(Integer::Type::Defined, 0);
}

Integer Integer::PositiveInfinity()
{
    return Integer(Integer::Type::PositiveInfinity, std::numeric_limits<Integer::ValueType>::max());
}

Integer Integer::NegativeInfinity()
{
    return Integer(Integer::Type::NegativeInfinity, std::numeric_limits<Integer::ValueType>::min());
}

Integer Integer::Int8(type::Int8 anInteger)
{
    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Int16(type::Int16 anInteger)
{
    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Int32(type::Int32 anInteger)
{
    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Int64(type::Int64 anInteger)
{
    if ((anInteger < static_cast<type::Int64>(std::numeric_limits<Integer::ValueType>::min())) ||
        (anInteger > static_cast<type::Int64>(std::numeric_limits<Integer::ValueType>::max())))
    {
        throw ostk::core::error::RuntimeError(
            "Int64 value [" + boost::lexical_cast<std::string>(anInteger) + "] is out of Integer supported range [" +
            boost::lexical_cast<std::string>(std::numeric_limits<Integer::ValueType>::min()) + ", " +
            boost::lexical_cast<std::string>(std::numeric_limits<Integer::ValueType>::max()) + "]."
        );
    }

    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Uint8(type::Uint8 anInteger)
{
    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Uint16(type::Uint16 anInteger)
{
    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Uint32(type::Uint32 anInteger)
{
    if (anInteger > static_cast<type::Uint32>(std::numeric_limits<Integer::ValueType>::max()))
    {
        throw ostk::core::error::RuntimeError(
            "Uint32 value [" + boost::lexical_cast<std::string>(anInteger) + "] is out of Integer supported range [" +
            boost::lexical_cast<std::string>(std::numeric_limits<Integer::ValueType>::min()) + ", " +
            boost::lexical_cast<std::string>(std::numeric_limits<Integer::ValueType>::max()) + "]."
        );
    }

    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Uint64(type::Uint64 anInteger)
{
    if (anInteger > static_cast<type::Uint64>(std::numeric_limits<Integer::ValueType>::max()))
    {
        throw ostk::core::error::RuntimeError(
            "Uint64 value [" + boost::lexical_cast<std::string>(anInteger) + "] is out of Integer supported range [" +
            boost::lexical_cast<std::string>(std::numeric_limits<Integer::ValueType>::min()) + ", " +
            boost::lexical_cast<std::string>(std::numeric_limits<Integer::ValueType>::max()) + "]."
        );
    }

    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anInteger));
}

Integer Integer::Index(const type::Index& anIndex)
{
    if (!(anIndex < std::numeric_limits<Integer::ValueType>::max()))
    {
        throw ostk::core::error::RuntimeError("Index out of bounds.");
    }

    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(anIndex));
}

Integer Integer::Size(const type::Size& aSize)
{
    if (!(aSize < std::numeric_limits<Integer::ValueType>::max()))
    {
        throw ostk::core::error::RuntimeError("Size out of bounds.");
    }

    return Integer(Integer::Type::Defined, static_cast<Integer::ValueType>(aSize));
}

bool Integer::CanParse(char aCharacter)
{
    return std::isdigit(aCharacter);
}

bool Integer::CanParse(const type::String& aString)
{
    if (aString.isEmpty())
    {
        return false;
    }

    if ((aString == "Inf") || (aString == "+Inf") || (aString == "-Inf"))
    {
        return true;
    }

    Integer::ValueType integer;

    return boost::conversion::try_lexical_convert<Integer::ValueType>(aString, integer);
}

Integer Integer::Parse(char aCharacter)
{
    try
    {
        return Integer(boost::lexical_cast<Integer::ValueType>(aCharacter));
    }
    catch (const boost::bad_lexical_cast&)
    {
        throw ostk::core::error::RuntimeError("Cannot cast character [" + String::Char(aCharacter) + "] to Integer.");
    }
}

Integer Integer::Parse(const type::String& aString)
{
    if (aString.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("String");
    }

    if ((aString == "Inf") || (aString == "+Inf"))
    {
        return Integer::PositiveInfinity();
    }

    if (aString == "-Inf")
    {
        return Integer::NegativeInfinity();
    }

    try
    {
        return Integer(boost::lexical_cast<Integer::ValueType>(aString));
    }
    catch (const boost::bad_lexical_cast&)
    {
        throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Integer.");
    }
}

Integer::Integer(const Integer::Type& aType, const Integer::ValueType& anInteger)
    : type_(aType),
      value_(anInteger)
{
}

}  // namespace type
}  // namespace core
}  // namespace ostk
