/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_RuntimeError__
#define __OpenSpaceToolkit_Core_Error_RuntimeError__

#include <stdexcept>

#include <boost/stacktrace.hpp>

#include <OpenSpaceToolkit/Core/Error/Exception.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace error
{

using ostk::core::type::String;

/// @brief Runtime error class
///
/// Exception class for runtime errors, with stack trace support.
class RuntimeError : public Exception
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aMessage An error message
    RuntimeError(const String& aMessage);

    /// @brief Formatted constructor
    ///
    /// @param [in] aFormat A format string
    /// @param [in] anArgumentList Format arguments
    template <typename... Args>
    RuntimeError(const char* aFormat, Args... anArgumentList)
        : Exception(String::Empty()),
          message_(String::Format(aFormat, anArgumentList...)),
          stackTrace_(String::SanitizeUTF8(boost::stacktrace::to_string(boost::stacktrace::stacktrace()))),
          what_(stackTrace_ + message_)
    {
    }

    /// @brief Destructor
    ~RuntimeError();

    /// @brief Get the error message
    ///
    /// @return Error message
    String getMessage() const;

    /// @brief Get the stack trace
    ///
    /// @return Stack trace string
    String getStackTrace() const;

    /// @brief Get the full error description (stack trace + message)
    ///
    /// @return Error description as C-string
    virtual const char* what() const noexcept override;

   private:
    String message_;
    String stackTrace_;
    String what_;
};

}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
