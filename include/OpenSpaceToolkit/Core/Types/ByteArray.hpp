/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Types_ByteArray__
#define __OpenSpaceToolkit_Core_Types_ByteArray__

#include <OpenSpaceToolkit/Core/Types/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Byte.hpp>

namespace ostk
{
namespace core
{
namespace types
{

/// @brief                      An array of bytes [TBI]

class ByteArray
{
   public:
    ByteArray() = default;

   private:
    Array<Byte> bytes_;
};

}  // namespace types
}  // namespace core
}  // namespace ostk

#endif
