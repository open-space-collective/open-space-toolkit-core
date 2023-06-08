/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_RuntimeError__
#define __OpenSpaceToolkit_Core_Error_RuntimeError__

#include <stdexcept>

#include <boost/stacktrace.hpp>

#include <OpenSpaceToolkit/Core/Error/Exception.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace error
{

using ostk::core::types::String;

/// @brief                      Runtime error class

class RuntimeError : public Exception
{
   public:
    RuntimeError(const String& aMessage);

    template <typename... Args>
    RuntimeError(const char* aFormat, Args... anArgumentList)
        : Exception(String::Empty()),
          message_(String::Format(aFormat, anArgumentList...)),
          stackTrace_(boost::stacktrace::to_string(boost::stacktrace::stacktrace()))
    {
    }

    ~RuntimeError();

    String getMessage() const;
    String getStackTrace() const;

    virtual const char* what() const noexcept override;

   private:
    String message_;
    String stackTrace_;
};

}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
