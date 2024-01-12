/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Tuple__
#define __OpenSpaceToolkit_Core_Containers_Tuple__

#include <ostream>
#include <tuple>

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

/// @brief                      Tuple container

template <typename... Args>
using Tuple = std::tuple<Args...>;

template <typename... Args>
auto Unpack(Args&... args)
{
    return std::tuple<Args&...>(args...);
}

}  // namespace containers
}  // namespace core
}  // namespace ostk

#endif
