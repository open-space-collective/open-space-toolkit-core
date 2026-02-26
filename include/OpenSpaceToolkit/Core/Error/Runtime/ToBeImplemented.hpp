/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Runtime_ToBeImplemented__
#define __OpenSpaceToolkit_Core_Error_Runtime_ToBeImplemented__

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

/// @brief To be implemented error class
///
/// Thrown when a function or feature is not yet implemented.
class ToBeImplemented : public RuntimeError
{
   public:
    /// @brief Default constructor
    ToBeImplemented();

    /// @brief Constructor with function name
    ///
    /// @param [in] aFunctionName The name of the unimplemented function
    ToBeImplemented(const String& aFunctionName);

    // ToBeImplemented                             (   const   String&                     aScope,
    //                                                 const   String&                     aFunctionName ) ;

    /// @brief Destructor
    ~ToBeImplemented();
};

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
