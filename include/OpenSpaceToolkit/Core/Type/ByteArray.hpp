/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_ByteArray__
#define __OpenSpaceToolkit_Core_Type_ByteArray__

#include <OpenSpaceToolkit/Core/Type/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Byte.hpp>

namespace ostk
{
namespace core
{
namespace type
{

/// @brief                      An array of bytes [TBI]

class ByteArray
{
   public:
    ByteArray() = default;

   private:
    Array<Byte> bytes_;
};

}  // namespace type
}  // namespace core
}  // namespace ostk

#endif
