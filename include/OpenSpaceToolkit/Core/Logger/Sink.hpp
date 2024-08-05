/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Sink__
#define __OpenSpaceToolkit_Core_Logger_Sink__

#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sink/Sink.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

using ostk::core::logger::Severity;
using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief                      Log sink

class Sink
{
   public:
    Sink(const sink::Sink& aSink);

    Sink(const Sink& aSink);

    void enable();
    void disable();

    void addChannel(const String& aChannel);
    void removeChannel(const String& aChannel);

    static Sink Console(const Severity& aSeverity);

   private:
    Unique<sink::Sink> sinkUPtr_;
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
