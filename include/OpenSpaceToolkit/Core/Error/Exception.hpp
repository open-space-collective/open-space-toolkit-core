/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Exception__
#define __OpenSpaceToolkit_Core_Error_Exception__

#include <exception>

#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace error
{

using ostk::core::types::String;

/// @brief                      Exception class

class Exception : public std::exception
{
   public:
    Exception(const String& aScope);

    ~Exception();

    String getScope() const;

    virtual const char* what() const noexcept;

   private:
    String scope_;
};

}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
