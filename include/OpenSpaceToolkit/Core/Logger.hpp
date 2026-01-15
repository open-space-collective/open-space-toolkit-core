/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger__
#define __OpenSpaceToolkit_Core_Logger__

#include <boost/log/attributes.hpp>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Logger/Pump.hpp>
#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sink.hpp>
#include <OpenSpaceToolkit/Core/Logger/Source.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{

using ostk::core::container::Array;
using ostk::core::logger::Pump;
using ostk::core::logger::Severity;
using ostk::core::logger::Sink;
using ostk::core::logger::Source;
using ostk::core::type::Integer;
using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief                      Log management
///
/// The Logger class provides a thread-safe logging facility built on Boost.Log.
/// It supports multiple output sinks (console, Python callbacks) and severity levels.
///
/// @code{.cpp}
/// // Basic usage with global logger
/// GLOBAL_LOG_INFO << "Application started";
/// GLOBAL_LOG_DEBUG << "Debug value: " << value;
///
/// // Using a custom logger
/// Logger myLogger = Logger::Console("MyModule", Severity::Debug);
/// LOG_INFO(myLogger) << "Module initialized";
///
/// // In other C++ libraries using OSTK
/// #include <OpenSpaceToolkit/Core/Logger.hpp>
/// LOG_DEBUG(ostk::core::Logger::Global()) << "Processing data...";
/// @endcode

class Logger
{
   public:
    /// @brief                      Constructor
    /// @param aChannel             Logger channel name
    Logger(const String& aChannel);

    /// @brief                      Logging operator
    /// @param aSeverity            Log severity level
    /// @param aLine                Source line number
    /// @param aFile                Source file name
    /// @param aFunction            Source function name
    /// @return                     Log pump for message streaming
    Pump operator()(const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction);

    /// @brief                      Stream operator for direct logging at Info level
    /// @tparam T                   Type of object to log
    /// @param anObject             Object to log
    /// @return                     Log pump for continued streaming
    template <class T>
    Pump operator<<(const T& anObject)
    {
        Pump pump(Severity::Info, Integer::Undefined(), String::Empty(), String::Empty(), &source_);

        pump << anObject;

        return pump;
    }

    /// @brief                      Get the logger channel name
    /// @return                     Channel name
    String getChannel() const;

    /// @brief                      Add a sink to this logger
    /// @param aSink                Sink to add
    void addSink(const Sink& aSink);

    /// @brief                      Create a console logger with default channel
    /// @param aSeverity            Minimum severity level
    /// @return                     Console logger
    static Logger Console(const Severity& aSeverity);

    /// @brief                      Create a console logger with custom channel
    /// @param aChannel             Channel name
    /// @param aSeverity            Minimum severity level
    /// @return                     Console logger
    static Logger Console(const String& aChannel, const Severity& aSeverity);

    /// @brief                      Get the global logger instance
    /// @return                     Reference to global logger
    static Logger& Global();

    /// @brief                      Set the global logger minimum severity
    /// @param aSeverity            Minimum severity level
    static void SetGlobalSeverity(const Severity& aSeverity);

    /// @brief                      Get the global logger minimum severity
    /// @return                     Current minimum severity level
    static Severity GetGlobalSeverity();

   private:
    String channel_;
    Source source_;
    Array<Sink> sinks_;
    static Severity globalSeverity_;
};

}  // namespace core
}  // namespace ostk

#define LOG(aLogger, aSeverity) aLogger(aSeverity, __LINE__, __FILE__, __PRETTY_FUNCTION__)

#define LOG_TRACE(aLogger) LOG(aLogger, ostk::core::logger::Severity::Trace)
#define LOG_DEBUG(aLogger) LOG(aLogger, ostk::core::logger::Severity::Debug)
#define LOG_INFO(aLogger) LOG(aLogger, ostk::core::logger::Severity::Info)
#define LOG_WARNING(aLogger) LOG(aLogger, ostk::core::logger::Severity::Warning)
#define LOG_ERROR(aLogger) LOG(aLogger, ostk::core::logger::Severity::Error)
#define LOG_FATAL(aLogger) LOG(aLogger, ostk::core::logger::Severity::Fatal)

#define GLOBAL_LOG_TRACE LOG_TRACE(ostk::core::Logger::Global())
#define GLOBAL_LOG_DEBUG LOG_DEBUG(ostk::core::Logger::Global())
#define GLOBAL_LOG_INFO LOG_INFO(ostk::core::Logger::Global())
#define GLOBAL_LOG_WARNING LOG_WARNING(ostk::core::Logger::Global())
#define GLOBAL_LOG_ERROR LOG_ERROR(ostk::core::Logger::Global())
#define GLOBAL_LOG_FATAL LOG_FATAL(ostk::core::Logger::Global())

// LOG_SCOPE macros for named scopes
// Use LOG_SCOPE("class", "method") for class + method scope (existing usage)
// Use LOG_SCOPE_DEFAULT() for default "?" scope
// Use LOG_SCOPE_NAMED("name") for single-name scope
#define LOG_SCOPE(aClass, aMethod) BOOST_LOG_NAMED_SCOPE(aClass " > " aMethod)
#define LOG_SCOPE_DEFAULT() BOOST_LOG_NAMED_SCOPE("?")
#define LOG_SCOPE_NAMED(aScope) BOOST_LOG_NAMED_SCOPE(aScope)

#endif
