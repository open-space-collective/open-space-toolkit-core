/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Map__
#define __OpenSpaceToolkit_Core_Containers_Map__

#include <map>

namespace ostk
{
namespace core
{
namespace ctnr
{

/// @brief                      Map container

template <class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<std::pair<const Key, T>>>
using Map = std::map<Key, T, Compare, Allocator>;

}  // namespace ctnr
}  // namespace core
}  // namespace ostk

#endif
