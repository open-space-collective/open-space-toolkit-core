/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Error_Runtime_Undefined__
#define __OpenSpaceToolkit_Core_Error_Runtime_Undefined__

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

/// @brief                      Undefined variable error class

class Undefined : public RuntimeError
{
   public:
    Undefined(const String& aVariableName);

    // Undefined                                   (   const   String&                     aScope,
    //                                                 const   String&                     aVariableName ) ;

    ~Undefined();
};

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk

#endif
