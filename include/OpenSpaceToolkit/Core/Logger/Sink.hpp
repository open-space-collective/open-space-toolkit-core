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

/// @brief Log sink
///
/// Represents a destination for log messages, with channel filtering.
class Sink
{
   public:
    /// @brief Constructor from internal sink
    ///
    /// @param [in] aSink An internal sink implementation
    Sink(const sink::Sink& aSink);

    /// @brief Copy constructor
    ///
    /// @param [in] aSink A sink
    Sink(const Sink& aSink);

    /// @brief Enable the sink
    void enable();

    /// @brief Disable the sink
    void disable();

    /// @brief Add a channel to the sink filter
    ///
    /// @param [in] aChannel A channel name
    void addChannel(const String& aChannel);

    /// @brief Remove a channel from the sink filter
    ///
    /// @param [in] aChannel A channel name
    void removeChannel(const String& aChannel);

    /// @brief Construct a console sink with a severity filter
    ///
    /// @param [in] aSeverity A minimum severity level
    /// @return Console sink
    static Sink Console(const Severity& aSeverity);

   private:
    Unique<sink::Sink> sinkUPtr_;
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
