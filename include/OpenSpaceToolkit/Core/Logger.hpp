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

/// @brief Log management
///
/// Provides logging capabilities with configurable channels, severity levels, and sinks.
///
/// @code
///     Logger logger = Logger::Console(Severity::Debug) ;
///     LOG_DEBUG(logger) << "Debug message" ;
/// @endcode
class Logger
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aChannel A channel name
    Logger(const String& aChannel);

    /// @brief Function call operator to create a log pump
    ///
    /// @param [in] aSeverity A severity level
    /// @param [in] aLine A line number
    /// @param [in] aFile A file name
    /// @param [in] aFunction A function name
    /// @return Log pump
    Pump operator()(const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction);

    /// @brief Stream operator to log an object
    ///
    /// @param [in] anObject An object to log
    /// @return Log pump
    template <class T>
    Pump operator<<(const T& anObject)
    {
        Pump pump(Severity::Info, Integer::Undefined(), String::Empty(), String::Empty(), &source_);

        pump << anObject;

        return std::move(pump);
    }

    /// @brief Get the channel name
    ///
    /// @return Channel name
    String getChannel() const;

    /// @brief Construct a console logger with a severity filter
    ///
    /// @param [in] aSeverity A minimum severity level
    /// @return Console logger
    static Logger Console(const Severity& aSeverity);

    /// @brief Construct a console logger with a channel name and severity filter
    ///
    /// @param [in] aChannel A channel name
    /// @param [in] aSeverity A minimum severity level
    /// @return Console logger
    static Logger Console(const String& aChannel, const Severity& aSeverity);

    /// @brief Access the global logger instance
    ///
    /// @return Reference to global logger
    static Logger& Global();

   private:
    String channel_;
    Source source_;
    Array<Sink> sinks_;
};

}  // namespace core
}  // namespace ostk

/// @brief Log macro with severity, file, line, and function information
///
/// @param aLogger A logger instance
/// @param aSeverity A severity level
#define LOG(aLogger, aSeverity) aLogger(aSeverity, __LINE__, __FILE__, __PRETTY_FUNCTION__)

/// @brief Log trace macro
#define LOG_TRACE(aLogger) LOG(aLogger, ostk::core::logger::Severity::Trace)

/// @brief Log debug macro
#define LOG_DEBUG(aLogger) LOG(aLogger, ostk::core::logger::Severity::Debug)

/// @brief Log info macro
#define LOG_INFO(aLogger) LOG(aLogger, ostk::core::logger::Severity::Info)

/// @brief Log warning macro
#define LOG_WARNING(aLogger) LOG(aLogger, ostk::core::logger::Severity::Warning)

/// @brief Log error macro
#define LOG_ERROR(aLogger) LOG(aLogger, ostk::core::logger::Severity::Error)

/// @brief Log fatal macro
#define LOG_FATAL(aLogger) LOG(aLogger, ostk::core::logger::Severity::Fatal)

/// @brief Global log trace macro
#define GLOBAL_LOG_TRACE LOG_TRACE(ostk::core::Logger::Global())

/// @brief Global log debug macro
#define GLOBAL_LOG_DEBUG LOG_DEBUG(ostk::core::Logger::Global())

/// @brief Global log info macro
#define GLOBAL_LOG_INFO LOG_INFO(ostk::core::Logger::Global())

/// @brief Global log warning macro
#define GLOBAL_LOG_WARNING LOG_WARNING(ostk::core::Logger::Global())

/// @brief Global log error macro
#define GLOBAL_LOG_ERROR LOG_ERROR(ostk::core::Logger::Global())

/// @brief Global log fatal macro
#define GLOBAL_LOG_FATAL LOG_FATAL(ostk::core::Logger::Global())

#define GET_MACRO(_0, _1, _2, NAME, ...) NAME

/// @brief Log scope macro (no arguments)
#define LOG_SCOPE0() BOOST_LOG_NAMED_SCOPE("?")

/// @brief Log scope macro (single scope name)
#define LOG_SCOPE1(aScope) BOOST_LOG_NAMED_SCOPE(aScope)

/// @brief Log scope macro (class and method names)
#define LOG_SCOPE2(aClass, aMethod) BOOST_LOG_NAMED_SCOPE(aClass " ▸ " aMethod)

/// @brief Log scope macro (variadic)
#define LOG_SCOPE(...) GET_MACRO(_0, ##__VA_ARGS__, LOG_SCOPE2, LOG_SCOPE1, LOG_SCOPE0)(__VA_ARGS__)

#endif
