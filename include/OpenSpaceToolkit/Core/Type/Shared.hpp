/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Shared__
#define __OpenSpaceToolkit_Core_Type_Shared__

#include <functional>
#include <memory>

namespace ostk
{
namespace core
{
namespace type
{

/// @brief Retains shared ownership of an object through a pointer
///
/// @code
///     Shared<MyClass> ptr = std::make_shared<MyClass>() ;
///     Shared<MyClass> ptr2 = ptr ; // Shared ownership
/// @endcode
template <class T>
using Shared = std::shared_ptr<T>;

}  // namespace type
}  // namespace core
}  // namespace ostk

#endif
