/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Runtime_Wrong__
#define __OpenSpaceToolkit_Core_Error_Runtime_Wrong__

#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

using ostk::core::type::String;

/// @brief                      Wrong variable error class

class Wrong : public RuntimeError
{
   public:
    Wrong(const String& aVariableName);

    template <typename... Args>
    Wrong(const String& aVariableName, Args... anArgumentList)
        : RuntimeError("{} = {} is wrong.", aVariableName, anArgumentList...)
    {
    }

    // Wrong                                       (   const   String&                     aScope,
    //                                                 const   String&                     aVariableName ) ;

    ~Wrong();
};

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
