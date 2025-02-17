/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger__
#define __OpenSpaceToolkit_Core_Logger__

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{

using ostk::core::type::String;

/// @brief                      Log management

class Logger
{
    public:
    enum class Level
    {

        Trace,
        Debug,
        Info,
        Warning,
        Error,
        Fatal

    };


    /// @brief                  Set the logger level
    ///
    /// @code
    /// Logger::SetLoggerLevel(Logger::Level::Trace);
    /// @endcode
    ///
    /// @param level            The logger level to set
    static void SetLoggerLevel(const Logger::Level& level);

    /// @brief                  Set the logger level
    ///
    /// @code
    /// Logger::SetLoggerLevel("trace");
    /// @endcode
    ///
    /// @param level            The logger level to set
    static void SetLoggerLevel(const String& level);

    /// @brief                  Convert a logger level enum to string
    ///
    /// @code
    /// String levelString = Logger::StringFromLevel(Logger::Level::Trace);
    /// @endcode
    ///
    /// @param aLevel           The logger level enum
    static String StringFromLevel(const Logger::Level& aLevel);

    /// @brief                  Convert a string to a logger level enum
    ///
    /// @code
    /// Logger::Level level = Logger::LevelFromString("trace");
    /// @endcode
    ///
    /// @param level            The logger level string
    /// @return                 The logger level enum
    static Logger::Level LevelFromString(const String& level);

    
};

}  // namespace core
}  // namespace ostk

#endif
