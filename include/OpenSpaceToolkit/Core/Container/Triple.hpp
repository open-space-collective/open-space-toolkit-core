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

/// @brief Triple container
///
/// A container holding three elements of potentially different types.
///
/// @code
///     Triple<int, double, String> triple = make_triple(1, 2.0, String("abc")) ;
///     triple.first ; // 1
///     triple.second ; // 2.0
///     triple.third ; // "abc"
/// @endcode
template <typename T, typename U, typename V>
struct Triple
{
    T first;   ///< First element
    U second;  ///< Second element
    V third;   ///< Third element
};

/// @brief Construct a Triple from three values
///
/// @param [in] aFirstElement A first element
/// @param [in] aSecondElement A second element
/// @param [in] aThirdElement A third element
/// @return A triple
template <typename T, typename U, typename V>
Triple<T, U, V> make_triple(const T& aFirstElement, const U& aSecondElement, const V& aThirdElement);

}  // namespace container
}  // namespace core
}  // namespace ostk

#include <OpenSpaceToolkit/Core/Container/Triple.tpp>

#endif
