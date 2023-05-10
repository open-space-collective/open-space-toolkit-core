/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Pair__
#define __OpenSpaceToolkit_Core_Containers_Pair__

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
namespace ctnr
{

using ostk::core::types::Index;
using ostk::core::types::Size;
using ostk::core::types::String;

/// @brief                      Pair container

template <class T, class U>
using Pair = std::pair<T, U>;

}  // namespace ctnr
}  // namespace core
}  // namespace ostk

#endif
