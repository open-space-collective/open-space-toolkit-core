/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Unique__
#define __OpenSpaceToolkit_Core_Type_Unique__

#include <functional>
#include <memory>

namespace ostk
{
namespace core
{
namespace type
{

/// @brief                      Owns and manages another object through a pointer

template <class T>
using Unique = std::unique_ptr<T>;

}  // namespace type
}  // namespace core
}  // namespace ostk

#endif
