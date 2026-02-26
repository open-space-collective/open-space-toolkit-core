/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_Weak__
#define __OpenSpaceToolkit_Core_Type_Weak__

#include <functional>
#include <memory>

namespace ostk
{
namespace core
{
namespace type
{

/// @brief Holds a non-owning reference to an object that is managed by Shared
///
/// @code
///     Shared<MyClass> shared = std::make_shared<MyClass>() ;
///     Weak<MyClass> weak = shared ;
/// @endcode
template <class T>
using Weak = std::weak_ptr<T>;

}  // namespace type
}  // namespace core
}  // namespace ostk

#endif
