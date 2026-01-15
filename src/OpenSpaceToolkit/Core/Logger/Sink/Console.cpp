/// Apache License 2.0

#include <iomanip>
#include <iostream>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/shared_ptr.hpp>

#include <OpenSpaceToolkit/Core/Logger/Sink/Console.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

// Define operator<< for Severity at namespace level so Boost.Log can find it via ADL
std::ostream& operator<<(std::ostream& strm, const Severity& severity)
{
    switch (severity)
    {
        case Severity::Trace:
            strm << "TRACE";
            break;
        case Severity::Debug:
            strm << "DEBUG";
            break;
        case Severity::Info:
            strm << "INFO ";
            break;
        case Severity::Warning:
            strm << "WARN ";
            break;
        case Severity::Error:
            strm << "ERROR";
            break;
        case Severity::Fatal:
            strm << "FATAL";
            break;
        default:
            strm << "?????";
            break;
    }
    return strm;
}

namespace sink
{

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

typedef sinks::synchronous_sink<sinks::text_ostream_backend> TextSink;

// Declare severity attribute placeholder
BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", Severity)
BOOST_LOG_ATTRIBUTE_KEYWORD(channel, "Channel", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(timestamp, "TimeStamp", attrs::local_clock::value_type)

class Console::Impl
{
   public:
    Impl(const Severity& aSeverity)
        : sinkPtr_(boost::make_shared<TextSink>()),
          minimumSeverity_(aSeverity)
    {
        // Add console stream (cout)
        sinkPtr_->locked_backend()->add_stream(boost::shared_ptr<std::ostream>(&std::cout, [](std::ostream*) {}));

        // Set auto-flush
        sinkPtr_->locked_backend()->auto_flush(true);

        // Set format
        sinkPtr_->set_formatter(
            expr::stream << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
                         << "] "
                         << "[" << severity << "] "
                         << "[" << channel << "] " << expr::smessage
        );

        // Set filter based on minimum severity
        sinkPtr_->set_filter(severity >= minimumSeverity_);

        // Register sink with logging core
        logging::core::get()->add_sink(sinkPtr_);
    }

    Impl(const Impl& anImpl)
        : sinkPtr_(anImpl.sinkPtr_),
          minimumSeverity_(anImpl.minimumSeverity_)
    {
    }

    ~Impl()
    {
        logging::core::get()->remove_sink(sinkPtr_);
    }

    void enable()
    {
        sinkPtr_->set_filter(severity >= minimumSeverity_);
    }

    void disable()
    {
        sinkPtr_->set_filter([](const logging::attribute_value_set&) { return false; });
    }

   private:
    boost::shared_ptr<TextSink> sinkPtr_;
    Severity minimumSeverity_;
};

Console::Console(const Severity& aSeverity)
    : Sink(aSeverity),
      implUPtr_(std::make_unique<Console::Impl>(aSeverity))
{
}

Console::Console(const Console& aConsole)
    : Sink(aConsole.severity_),
      implUPtr_(std::make_unique<Console::Impl>(*aConsole.implUPtr_))
{
}

Console::~Console() = default;

Console* Console::clone() const
{
    return new Console(*this);
}

void Console::enable()
{
    enabled_ = true;
    implUPtr_->enable();
}

void Console::disable()
{
    enabled_ = false;
    implUPtr_->disable();
}

String Console::ColorizeMessage(const String& aMessage, const Console::Color& aColor)
{
    static const char* colorCodes[] = {
        "\033[30m",  // Black
        "\033[31m",  // Red
        "\033[32m",  // Green
        "\033[33m",  // Yellow
        "\033[34m",  // Blue
        "\033[35m",  // Magenta
        "\033[36m",  // Cyan
        "\033[37m",  // LightGray
        "\033[90m",  // DarkGray
        "\033[91m",  // LightRed
        "\033[92m",  // LightGreen
        "\033[93m",  // LightYellow
        "\033[94m",  // LightBlue
        "\033[95m",  // LightMagenta
        "\033[96m",  // LightCyan
        "\033[97m"   // White
    };

    const int colorIndex = static_cast<int>(aColor);
    const char* resetCode = "\033[0m";

    return String(colorCodes[colorIndex]) + aMessage + String(resetCode);
}

}  // namespace sink
}  // namespace logger
}  // namespace core
}  // namespace ostk
