/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Pair__
#define __OpenSpaceToolkit_Core_Container_Pair__

#include <ostream>
#include <utility>

#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace container
{

using ostk::core::type::Index;
using ostk::core::type::Size;
using ostk::core::type::String;

/// @brief Pair container
///
/// @code
///     Pair<String, Integer> pair = std::make_pair(String("key"), Integer(123)) ;
///     pair.first ; // "key"
///     pair.second ; // 123
/// @endcode
template <class T, class U>
using Pair = std::pair<T, U>;

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
