/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Sink_Python__
#define __OpenSpaceToolkit_Core_Logger_Sink_Python__

#include <functional>

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
namespace sink
{

using ostk::core::logger::Severity;
using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief Log sink that forwards messages to a Python logging callback
///
/// This sink enables integration with Python's logging module by accepting
/// a callback function that receives log messages. The callback is typically
/// connected to Python's logging.log() function.

class Python : public Sink
{
   public:
    /// Callback type: (severity_level, channel, message) -> void
    using LogCallback = std::function<void(int, const std::string&, const std::string&)>;

    /// @brief Constructor
    /// @param aSeverity Minimum severity level to log
    /// @param aCallback Python logging callback function
    Python(const Severity& aSeverity, const LogCallback& aCallback);

    /// @brief Copy constructor
    Python(const Python& aPython);

    /// @brief Destructor
    virtual ~Python() override;

    /// @brief Clone the sink
    virtual Python* clone() const override;

    /// @brief Enable the sink
    virtual void enable() override;

    /// @brief Disable the sink
    virtual void disable() override;

    /// @brief Set the Python logging callback
    /// @param aCallback The callback function to set
    void setCallback(const LogCallback& aCallback);

   private:
    class Impl;

    Unique<Python::Impl> implUPtr_;
};

}  // namespace sink
}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
