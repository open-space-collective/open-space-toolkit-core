/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Source__
#define __OpenSpaceToolkit_Core_Logger_Source__

#include <OpenSpaceToolkit/Core/Logger/Source/Source.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

using ostk::core::type::String;
using ostk::core::type::Unique;

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

    Unique<source::Source> sourceUPtr_;
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
