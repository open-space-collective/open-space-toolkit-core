/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Runtime_ToBeImplemented__
#define __OpenSpaceToolkit_Core_Error_Runtime_ToBeImplemented__

#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

using ostk::core::types::String;

/// @brief                      To be implemented error class

class ToBeImplemented : public RuntimeError
{
   public:
    ToBeImplemented();

    ToBeImplemented(const String& aFunctionName);

    // ToBeImplemented                             (   const   String&                     aScope,
    //                                                 const   String&                     aFunctionName ) ;

    ~ToBeImplemented();
};

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
