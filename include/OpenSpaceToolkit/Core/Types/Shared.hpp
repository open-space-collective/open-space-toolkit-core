/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Types_Shared__
#define __OpenSpaceToolkit_Core_Types_Shared__

#include <functional>
#include <memory>

namespace ostk
{
namespace core
{
namespace types
{

/// @brief                      Retains shared ownership of an object through a pointer

template <class T>
using Shared = std::shared_ptr<T>;

}  // namespace types
}  // namespace core
}  // namespace ostk

#endif
