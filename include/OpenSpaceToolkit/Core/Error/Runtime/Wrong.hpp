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

/// @brief Wrong variable error class
///
/// Thrown when a variable has an unexpected or invalid value.
class Wrong : public RuntimeError
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aVariableName The name of the wrong variable
    Wrong(const String& aVariableName);

    /// @brief Formatted constructor with variable name and value
    ///
    /// @param [in] aVariableName The name of the wrong variable
    /// @param [in] anArgumentList The value(s) of the wrong variable
    template <typename... Args>
    Wrong(const String& aVariableName, Args... anArgumentList)
        : RuntimeError("{} = {} is wrong.", aVariableName, anArgumentList...)
    {
    }

    // Wrong                                       (   const   String&                     aScope,
    //                                                 const   String&                     aVariableName ) ;

    /// @brief Destructor
    ~Wrong();
};

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
