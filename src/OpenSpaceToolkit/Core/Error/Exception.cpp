/// Apache License 2.0
#include <iostream>
#include <OpenSpaceToolkit/Core/Error/Exception.hpp>

namespace ostk
{
namespace core
{
namespace error
{

Exception::Exception(const String& aScope)
    : scope_(aScope)
{
}

Exception::~Exception() {}

String Exception::getScope() const
{
    return scope_;
}

const char* Exception::what() const noexcept
{
    return scope_.data();
}

}  // namespace error
}  // namespace core
}  // namespace ostk
