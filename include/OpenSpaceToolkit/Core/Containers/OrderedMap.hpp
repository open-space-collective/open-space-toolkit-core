/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_OrderedMap__
#define __OpenSpaceToolkit_Core_Containers_OrderedMap__

#include <cstddef>
#include <deque>
#include <functional>
#include <initializer_list>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>

#include <tsl/ordered_map.h>

namespace ostk
{
namespace core
{
namespace containers
{

/// @brief                      Ordered map container
///
///                             The ordered-map library provides a hash map and a hash set which preserve the order of
///                             insertion in a way similar to Python's OrderedDict. When iterating over the map, the
///                             values will be returned in the same order as they were inserted.
///
/// @ref                        https://github.com/Tessil/ordered-map
/// @note                       This has to be eventually fully wrapped (to remove user dependency on tsl/ordered_map)

template <
    class Key,
    class T,
    class Hash = std::hash<Key>,
    class KeyEqual = std::equal_to<Key>,
    class Allocator = std::allocator<std::pair<Key, T>>,
    class ValueTypeContainer = std::deque<std::pair<Key, T>, Allocator>>
using OrderedMap = tsl::ordered_map<Key, T, Hash, KeyEqual, Allocator, ValueTypeContainer>;

// template
// <
//     class Key,
//     class T,
//     class Hash = std::hash<Key>,
//     class KeyEqual = std::equal_to<Key>,
//     class Allocator = std::allocator<std::pair<Key, T>>,
//     class ValueTypeContainer = std::deque<std::pair<Key, T>, Allocator>
// >
// class OrderedMap
// {

//     public:

//     private:

// } ;

}  // namespace containers
}  // namespace core
}  // namespace ostk

#endif
