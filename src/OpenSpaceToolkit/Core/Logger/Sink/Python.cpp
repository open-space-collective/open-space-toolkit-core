/// Apache License 2.0

#include <sstream>

#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/basic_sink_backend.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/shared_ptr.hpp>

#include <OpenSpaceToolkit/Core/Logger/Sink/Python.hpp>

namespace ostk
{
namespace core
{
namespace logger
{
namespace sink
{

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

// Declare attribute placeholders
BOOST_LOG_ATTRIBUTE_KEYWORD(severity_attr, "Severity", Severity)
BOOST_LOG_ATTRIBUTE_KEYWORD(channel_attr, "Channel", std::string)

/// @brief Custom sink backend that forwards log messages to a Python callback
class PythonSinkBackend : public sinks::basic_formatted_sink_backend<char, sinks::synchronized_feeding>
{
   public:
    explicit PythonSinkBackend(const Python::LogCallback& aCallback)
        : callback_(aCallback)
    {
    }

    void consume(const logging::record_view& aRecord, const string_type& aMessage)
    {
        // Extract severity
        auto severityOpt = aRecord[severity_attr];
        Severity severity = severityOpt ? severityOpt.get() : Severity::Info;

        // Extract channel
        auto channelOpt = aRecord[channel_attr];
        std::string channel = channelOpt ? channelOpt.get() : "ostk";

        // Convert severity to Python logging level
        int pythonLevel = 20;  // INFO by default
        switch (severity)
        {
            case Severity::Trace:
                pythonLevel = 5;  // TRACE (custom level below DEBUG)
                break;
            case Severity::Debug:
                pythonLevel = 10;  // DEBUG
                break;
            case Severity::Info:
                pythonLevel = 20;  // INFO
                break;
            case Severity::Warning:
                pythonLevel = 30;  // WARNING
                break;
            case Severity::Error:
                pythonLevel = 40;  // ERROR
                break;
            case Severity::Fatal:
                pythonLevel = 50;  // CRITICAL
                break;
        }

        // Call the Python callback - it will check Python's logger level
        if (callback_)
        {
            callback_(pythonLevel, channel, aMessage);
        }
    }

    void setCallback(const Python::LogCallback& aCallback)
    {
        callback_ = aCallback;
    }

   private:
    Python::LogCallback callback_;
};

typedef sinks::synchronous_sink<PythonSinkBackend> PythonSink;

class Python::Impl
{
   public:
    Impl(const Severity& aSeverity, const LogCallback& aCallback)
        : backendPtr_(boost::make_shared<PythonSinkBackend>(aCallback)),
          sinkPtr_(boost::make_shared<PythonSink>(backendPtr_)),
          enabled_(true)
    {
        // Set simple formatter - just pass through the message
        sinkPtr_->set_formatter(expr::stream << expr::smessage);

        // No filtering at C++ level - let Python's logger do the filtering
        // This allows Python's logging configuration to control what gets logged

        // Register sink with logging core
        logging::core::get()->add_sink(sinkPtr_);
    }

    Impl(const Impl& anImpl)
        : backendPtr_(anImpl.backendPtr_),
          sinkPtr_(anImpl.sinkPtr_),
          enabled_(anImpl.enabled_)
    {
    }

    ~Impl()
    {
        logging::core::get()->remove_sink(sinkPtr_);
    }

    void enable()
    {
        enabled_ = true;
        sinkPtr_->set_filter([](const logging::attribute_value_set&) { return true; });
    }

    void disable()
    {
        enabled_ = false;
        sinkPtr_->set_filter([](const logging::attribute_value_set&) { return false; });
    }

    void setCallback(const LogCallback& aCallback)
    {
        backendPtr_->setCallback(aCallback);
    }

   private:
    boost::shared_ptr<PythonSinkBackend> backendPtr_;
    boost::shared_ptr<PythonSink> sinkPtr_;
    bool enabled_;
};

Python::Python(const Severity& aSeverity, const LogCallback& aCallback)
    : Sink(aSeverity),
      implUPtr_(std::make_unique<Python::Impl>(aSeverity, aCallback))
{
}

Python::Python(const Python& aPython)
    : Sink(aPython.severity_),
      implUPtr_(std::make_unique<Python::Impl>(*aPython.implUPtr_))
{
}

Python::~Python() = default;

Python* Python::clone() const
{
    return new Python(*this);
}

void Python::enable()
{
    enabled_ = true;
    implUPtr_->enable();
}

void Python::disable()
{
    enabled_ = false;
    implUPtr_->disable();
}

void Python::setCallback(const LogCallback& aCallback)
{
    implUPtr_->setCallback(aCallback);
}

}  // namespace sink
}  // namespace logger
}  // namespace core
}  // namespace ostk
