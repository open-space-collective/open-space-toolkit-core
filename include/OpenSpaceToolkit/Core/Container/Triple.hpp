/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Triple__
#define __OpenSpaceToolkit_Core_Container_Triple__

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

}  // namespace container
}  // namespace core
}  // namespace ostk

#include <OpenSpaceToolkit/Core/Container/Triple.tpp>

#endif
