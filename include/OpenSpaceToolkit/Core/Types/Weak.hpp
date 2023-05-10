/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Types_Weak__
#define __OpenSpaceToolkit_Core_Types_Weak__

#include <functional>
#include <memory>

namespace ostk
{
namespace core
{
namespace types
{

/// @brief                      Holds a non-owning reference to an object that is managed by Shared

template <class T>
using Weak = std::weak_ptr<T>;

}  // namespace types
}  // namespace core
}  // namespace ostk

#endif
