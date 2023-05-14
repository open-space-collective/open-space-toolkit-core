/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Types_Sign__
#define __OpenSpaceToolkit_Core_Types_Sign__

#include <stdint.h>

namespace ostk
{
namespace core
{
namespace types
{

/// @brief                      Sign enum

enum class Sign : uint8_t
{

    Undefined,
    Positive,
    Negative,
    None

};

}  // namespace types
}  // namespace core
}  // namespace ostk

#endif
