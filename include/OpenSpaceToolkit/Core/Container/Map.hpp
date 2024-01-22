/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Map__
#define __OpenSpaceToolkit_Core_Container_Map__

#include <map>

namespace ostk
{
namespace core
{
namespace container
{

/// @brief                      Map container

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
using Map = std::map<Key, T, Compare, Allocator>;

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
