/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Triple__
#define __OpenSpaceToolkit_Core_Containers_Triple__

#include <ostream>
#include <utility>

#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace containers
{

using ostk::core::types::Index;
using ostk::core::types::Size;
using ostk::core::types::String;

/// @brief                      Triple container

template <typename T, typename U, typename V>
struct Triple
{
    T first;
    U second;
    V third;
};

template <typename T, typename U, typename V>
Triple<T, U, V> make_triple(const T& aFirstElement, const U& aSecondElement, const V& aThirdElement);

}  // namespace containers
}  // namespace core
}  // namespace ostk

#include <OpenSpaceToolkit/Core/Containers/Triple.tpp>

#endif
