/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Source__
#define __OpenSpaceToolkit_Core_Logger_Source__

#include <OpenSpaceToolkit/Core/Logger/Sources/Source.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

using ostk::core::types::Unique;
using ostk::core::types::String;

/// @brief                      Log source

class Source
{
   public:
    Source(const String& aChannel);

    Source(const Source& aSource);

    Source& operator=(const Source& aSource);

    bool isDefined() const;

    static Source Undefined();

    // private:

    Unique<sources::Source> sourceUPtr_;
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
