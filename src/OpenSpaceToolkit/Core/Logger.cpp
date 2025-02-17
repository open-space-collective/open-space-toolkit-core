/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Logger.hpp>

namespace ostk
{
namespace core
{

void Logger::SetLoggerLevel(const Logger::Level& level)
{
    auto logLevel = boost::log::trivial::info; // default level
    
    if (level == Logger::Level::Trace) {
        logLevel = boost::log::trivial::trace;
    } else if (level == Logger::Level::Debug) {
        logLevel = boost::log::trivial::debug;
    } else if (level == Logger::Level::Info) {
        logLevel = boost::log::trivial::info;
    } else if (level == Logger::Level::Warning) {
        logLevel = boost::log::trivial::warning;
    } else if (level == Logger::Level::Error) {
        logLevel = boost::log::trivial::error;
    } else if (level == Logger::Level::Fatal) {
        logLevel = boost::log::trivial::fatal;
    }
    
    boost::log::core::get()->set_filter(
        boost::log::trivial::severity >= logLevel
    );
}

void Logger::SetLoggerLevel(const String& level)
{
    return Logger::SetLoggerLevel(Logger::LevelFromString(level));
}

String Logger::StringFromLevel(const Logger::Level& aLevel)
{
    switch (aLevel)
    {
        case Logger::Level::Trace:
            return "Trace";

        case Logger::Level::Debug:
            return "Debug";

        case Logger::Level::Info:
            return "Info";

        case Logger::Level::Warning:
            return "Warning";

        case Logger::Level::Error:
            return "Error";

        case Logger::Level::Fatal:
            return "Fatal";

        default:
            throw ostk::core::error::runtime::Wrong("Level");
    }

    return String::Empty();
}

Logger::Level Logger::LevelFromString(const String& level)
{
    if (level == "trace") {
        return Logger::Level::Trace;
    } else if (level == "debug") {
        return Logger::Level::Debug;
    } else if (level == "info") {
        return Logger::Level::Info;
    } else if (level == "warning") {
        return Logger::Level::Warning;
    } else if (level == "error") {
        return Logger::Level::Error;
    } else if (level == "fatal") {
        return Logger::Level::Fatal;
    } else {
        return Logger::Level::Info;
    }
}

}  // namespace core
}  // namespace ostk
