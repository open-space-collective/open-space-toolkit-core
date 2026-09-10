/// Apache License 2.0

#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>

namespace ostk
{
namespace core
{
namespace type
{

// Everything that is a single hardware instruction on the native IEEE-754
// representation is inlined in Real.hpp. What remains here is the formatting,
// parsing and integer-conversion code, which is neither small nor hot.

void Real::ThrowUndefined()
{
    throw ostk::core::error::runtime::Undefined("Real");
}

std::ostream& operator<<(std::ostream& anOutputStream, const Real& aReal)
{
    if (std::isnan(aReal.value_))
    {
        anOutputStream << "Undefined";
    }
    else if (std::isinf(aReal.value_))
    {
        anOutputStream << ((aReal.value_ > 0.0) ? "+Inf" : "-Inf");
    }
    else
    {
        anOutputStream << aReal.value_;
    }

    return anOutputStream;
}

bool Real::isNear(const Real& aReal, const Real& aTolerance) const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (!aReal.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Real");
    }

    if (!aTolerance.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Tolerance");
    }

    if ((!this->isFinite()) || (!aReal.isFinite()))
    {
        return false;
    }

    return ((*this) - aReal).abs() <= aTolerance;
}

type::String Real::toString(const type::Integer& aPrecision) const
{
    if (std::isnan(value_))
    {
        return "Undefined";
    }

    if (std::isinf(value_))
    {
        return (value_ > 0.0) ? "+Inf" : "-Inf";
    }

    if (!aPrecision.isDefined())
    {
        type::String realString = boost::lexical_cast<std::string>(value_);

        if (this->isInteger())
        {
            if (realString.find('e') == std::string::npos)
            {
                realString += ".0";
            }

            return realString;
        }

        if (realString.find('e') == std::string::npos)
        {
            realString.erase(realString.find_last_not_of('0') + 1, std::string::npos);  // Remove trailing zeros if any
        }

        return realString;
    }

    std::ostringstream stringStream;

    stringStream.precision(aPrecision);

    stringStream << std::fixed << value_;

    return stringStream.str();
}

type::Integer Real::toInteger() const
{
    if (this->isInteger())
    {
        return type::Integer(static_cast<type::Integer::ValueType>(value_));
    }

    throw ostk::core::error::RuntimeError("Real is not integer.");
}

type::Integer Real::floor() const
{
    if (!std::isfinite(value_))
    {
        return type::Integer::Undefined();
    }

    return type::Integer(static_cast<type::Integer::ValueType>(std::floor(value_)));
}

Real Real::CanParse(const type::String& aString)
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

Real Real::Parse(const type::String& aString)
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

        if (std::isnan(value))
        {
            throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.");
        }

        return Real(value);
    }
    catch (const boost::bad_lexical_cast&)
    {
        throw ostk::core::error::RuntimeError("Cannot cast string [" + aString + "] to Real.");
    }
}

}  // namespace type
}  // namespace core
}  // namespace ostk
