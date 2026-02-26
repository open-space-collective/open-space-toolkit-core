/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Table_Cell__
#define __OpenSpaceToolkit_Core_Container_Table_Cell__

#include <OpenSpaceToolkit/Core/Container/Object.hpp>

namespace ostk
{
namespace core
{
namespace container
{
namespace table
{

/// @brief Cell of table
///
/// A cell is a universal type container (alias for Object).
///
/// @code
///     Cell cell = Object::Integer(123) ;
/// @endcode
using Cell = container::Object;

}  // namespace table
}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
