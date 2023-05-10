/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Types_Unique__
#define __OpenSpaceToolkit_Core_Types_Unique__

#include <functional>
#include <memory>

namespace ostk
{
namespace core
{
namespace types
{

/// @brief                      Owns and manages another object through a pointer

template <class T>
using Unique = std::unique_ptr<T>;

}  // namespace types
}  // namespace core
}  // namespace ostk

#endif
