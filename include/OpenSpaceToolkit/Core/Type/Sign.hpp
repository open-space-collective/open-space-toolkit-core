/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Sign__
#define __OpenSpaceToolkit_Core_Type_Sign__

#include <stdint.h>

namespace ostk
{
namespace core
{
namespace type
{

/// @brief Sign enum
enum class Sign : uint8_t
{

    Undefined,  ///< Undefined sign
    Positive,   ///< Positive sign
    Negative,   ///< Negative sign
    None        ///< No sign (zero)
};

}  // namespace type
}  // namespace core
}  // namespace ostk

#endif
