/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_List__
#define __OpenSpaceToolkit_Core_Container_List__

#include <list>

namespace ostk
{
namespace core
{
namespace container
{

/// @brief List container
///
/// @code
///     List<Integer> list ;
///     list.push_back(123) ;
/// @endcode
template <class T>
using List = std::list<T>;

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
