/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Tuple__
#define __OpenSpaceToolkit_Core_Container_Tuple__

#include <ostream>
#include <tuple>

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

/// @brief Tuple container
///
/// @code
///     Tuple<int, double, String> tuple = std::make_tuple(1, 2.0, String("abc")) ;
/// @endcode
template <typename... Args>
using Tuple = std::tuple<Args...>;

/// @brief Unpack values into a tuple of references for structured assignment
///
/// @code
///     int a ;
///     double b ;
///     Unpack(a, b) = std::make_tuple(1, 2.0) ;
/// @endcode
///
/// @param [in] args References to variables to unpack into
/// @return Tuple of references
template <typename... Args>
auto Unpack(Args&... args)
{
    return std::tuple<Args&...>(args...);
}

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
