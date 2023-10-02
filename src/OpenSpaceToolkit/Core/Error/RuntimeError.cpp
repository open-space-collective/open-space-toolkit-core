/// Apache License 2.0
#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>

namespace ostk
{
namespace core
{
namespace error
{

RuntimeError::RuntimeError(const String& aMessage)
    : Exception(String::Empty()),
      message_(aMessage),
      stackTrace_(String::SanitizeUTF8(boost::stacktrace::to_string(boost::stacktrace::stacktrace()))),
      what_(aMessage + "\n" + stackTrace_)
{
}

String RuntimeError::getMessage() const
{
    return message_;
}

String RuntimeError::getStackTrace() const
{
    return stackTrace_;
}

RuntimeError::~RuntimeError() {}

const char* RuntimeError::what() const noexcept
{
    return what_.data();
}

}  // namespace error
}  // namespace core
}  // namespace ostk
