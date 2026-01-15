/// Apache License 2.0

#include <mutex>

#include <boost/log/attributes.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <OpenSpaceToolkit/Core/Logger.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sink/Console.hpp>

namespace ostk
{
namespace core
{

using ostk::core::logger::sink::Console;

// Initialize static member
Severity Logger::globalSeverity_ = Severity::Debug;

Logger::Logger(const String& aChannel)
    : channel_(aChannel),
      source_(aChannel),
      sinks_()
{
}

Pump Logger::operator()(const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction)
{
    return Pump(aSeverity, aLine, aFile, aFunction, &source_);
}

String Logger::getChannel() const
{
    return channel_;
}

void Logger::addSink(const Sink& aSink)
{
    sinks_.add(aSink);
}

Logger Logger::Console(const Severity& aSeverity)
{
    return Logger::Console("Global", aSeverity);
}

Logger Logger::Console(const String& aChannel, const Severity& aSeverity)
{
    Logger logger(aChannel);

    logger.sinks_.add(Sink::Console(aSeverity));

    return logger;
}

Logger& Logger::Global()
{
    static std::once_flag onceFlag;
    static Logger* globalLoggerPtr = nullptr;

    std::call_once(
        onceFlag,
        []()
        {
            boost::log::add_common_attributes();

            globalLoggerPtr = new Logger(Logger::Console(globalSeverity_));
        }
    );

    return *globalLoggerPtr;
}

void Logger::SetGlobalSeverity(const Severity& aSeverity)
{
    globalSeverity_ = aSeverity;
}

Severity Logger::GetGlobalSeverity()
{
    return globalSeverity_;
}

}  // namespace core
}  // namespace ostk
