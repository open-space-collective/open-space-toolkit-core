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

/// @brief                      Tuple container

template <typename... Args>
using Tuple = std::tuple<Args...>;

template <typename... Args>
auto Unpack(Args&... args)
{
    return std::tuple<Args&...>(args...);
}

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
