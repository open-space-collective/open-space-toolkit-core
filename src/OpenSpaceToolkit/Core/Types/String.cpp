/// Apache License 2.0

#include <boost/algorithm/string.hpp>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace types
{

using ostk::core::types::Integer;

String::String()
    : std::string()
{
}

String::String(const std::string& aString)
    : std::string(aString)
{
}

String::~String() {}

bool String::isEmpty() const
{
    return this->empty();
}

bool String::isUppercase() const

{
    return (!this->empty()) && !std::any_of(
                                   this->begin(),
                                   this->end(),
                                   [](char ch)
                                   {
                                       return ::islower(ch);
                                   }
                               );
}

bool String::isLowercase() const

{
    return (!this->empty()) && !std::any_of(
                                   this->begin(),
                                   this->end(),
                                   [](char ch)
                                   {
                                       return ::isupper(ch);
                                   }
                               );
}

bool String::match(const std::regex& aRegularExpression) const
{
    return std::regex_match((*this), aRegularExpression);
}

Size String::getLength() const
{
    return this->length();
}

String String::getHead(const Size& aLength) const
{
    if (aLength > this->length())
    {
        throw ostk::core::error::RuntimeError(
            "Head length [{}] greater than string length [{}].", aLength, this->length()
        );
    }

    return this->substr(0, aLength);
}

String String::getTail(const Size& aLength) const
{
    if (aLength > this->length())
    {
        throw ostk::core::error::RuntimeError(
            "Tail length [{}] greater than string length [{}].", aLength, this->length()
        );
    }

    return this->substr(this->length() - aLength, aLength);
}

char String::getFirst() const
{
    if (this->empty())
    {
        throw ostk::core::error::RuntimeError("String is empty.");
    }

    return (*this)[0];
}

char String::getLast() const
{
    if (this->empty())
    {
        throw ostk::core::error::RuntimeError("String is empty.");
    }

    return (*this)[this->length() - 1];
}

String String::getSubstring(const Index& aStartPosition, const Size& aLength) const
{
    if (aLength == 0)
    {
        throw ostk::core::error::runtime::Wrong("Length");
    }

    if (this->empty())
    {
        throw ostk::core::error::RuntimeError("String is empty.");
    }

    if (aStartPosition >= this->length())
    {
        throw ostk::core::error::RuntimeError(
            "Start position [" + Integer::Index(aStartPosition).toString() + "] out of bounds [" +
            Integer::Size(this->length() - 1).toString() + "]."
        );
    }

    if ((aStartPosition + aLength) > this->length())
    {
        throw ostk::core::error::RuntimeError(
            "End position [" + Integer::Index(aStartPosition + aLength - 1).toString() + "] out of bounds [" +
            Integer::Size(this->length() - 1).toString() + "]."
        );
    }

    return this->substr(aStartPosition, aLength);
}

Array<String> String::split(const String& aDelimiter) const
{
    Array<String> result;
    boost::split(result, *this, boost::is_any_of(aDelimiter));
    return result;
}

String& String::trim()
{
    if (!this->empty())
    {
        boost::trim(*this);
    }

    return *this;
}

String& String::replace(const char aCharacter, const char aNewCharacter)
{
    std::replace(this->begin(), this->end(), aCharacter, aNewCharacter);

    return *this;
}

String& String::replace(const String& aString, const String& aNewString)
{
    boost::replace_all(*this, aString, aNewString);

    return *this;
}

String String::Empty()

{
    return String("");
}

String String::Boolean(bool aBoolean)
{
    return aBoolean ? "True" : "False";
}

String String::Char(char aCharacter)
{
    return String(1, aCharacter);
}

String String::Replicate(char aCharacter, Size aCount)
{
    return String(aCount, aCharacter);
}

String String::Replicate(const String& aString, Size aCount)
{
    std::ostringstream stringStream;

    for (Index idx = 0; idx < aCount; ++idx)
    {
        stringStream << aString;
    }

    return stringStream.str();
}

}  // namespace types
}  // namespace core
}  // namespace ostk
