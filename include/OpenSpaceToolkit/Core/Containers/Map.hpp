/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Map__
#define __OpenSpaceToolkit_Core_Containers_Map__

#include <map>

namespace ostk
{
namespace core
{
namespace containers
{

/// @brief                      Map container

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
using Map = std::map<Key, T, Compare, Allocator>;

}  // namespace containers
}  // namespace core
}  // namespace ostk

#endif
