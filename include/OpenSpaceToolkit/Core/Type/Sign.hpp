/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Sign__
#define __OpenSpaceToolkit_Core_Type_Sign__

#include <stdint.h>

#include <OpenSpaceToolkit/Core/Type/String.hpp>  // Required by EnumHelper for String type
#include <OpenSpaceToolkit/Core/Type/EnumHelper.hpp> // For OSTK_CORE_DEFINE_ENUM_STRING_CONVERSION

namespace ostk
{
namespace core
{
namespace type
{

/// @brief                      Sign enum

enum class Sign : uint8_t
{

    Undefined,
    Positive,
    Negative,
    None

};

OSTK_CORE_DEFINE_ENUM_STRING_CONVERSION(Sign)

}  // namespace type
}  // namespace core
}  // namespace ostk

#endif
