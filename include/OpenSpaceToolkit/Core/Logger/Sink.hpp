/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Sink__
#define __OpenSpaceToolkit_Core_Logger_Sink__

#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sinks/Sink.hpp>
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
using ostk::core::logger::Severity;

/// @brief                      Log sink

class Sink
{
   public:
    Sink(const sinks::Sink& aSink);

    Sink(const Sink& aSink);

    void enable();
    void disable();

    void addChannel(const String& aChannel);
    void removeChannel(const String& aChannel);

    static Sink Console(const Severity& aSeverity);

   private:
    Unique<sinks::Sink> sinkUPtr_;
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
