/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Exception__
#define __OpenSpaceToolkit_Core_Error_Exception__

#include <exception>

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace error
{

using ostk::core::type::String;

/// @brief Exception class
///
/// Base exception class for all OpenSpaceToolkit exceptions.
class Exception : public std::exception
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aScope A scope identifier
    Exception(const String& aScope);

    /// @brief Destructor
    ~Exception();

    /// @brief Get the scope of the exception
    ///
    /// @return Scope string
    String getScope() const;

    /// @brief Get the exception message
    ///
    /// @return Exception message as C-string
    virtual const char* what() const noexcept;

   private:
    String scope_;
};

}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
