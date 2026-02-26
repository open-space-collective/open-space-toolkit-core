/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Runtime_Undefined__
#define __OpenSpaceToolkit_Core_Error_Runtime_Undefined__

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

/// @brief Undefined variable error class
///
/// Thrown when an undefined variable is accessed.
class Undefined : public RuntimeError
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aVariableName The name of the undefined variable
    Undefined(const String& aVariableName);

    // Undefined                                   (   const   String&                     aScope,
    //                                                 const   String&                     aVariableName ) ;

    /// @brief Destructor
    ~Undefined();
};

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
