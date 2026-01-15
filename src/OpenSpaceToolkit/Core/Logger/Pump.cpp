/// Apache License 2.0

#include <sstream>

#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

#include <OpenSpaceToolkit/Core/Logger/Pump.hpp>
#include <OpenSpaceToolkit/Core/Logger/Source/Source.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

typedef boost::log::sources::severity_channel_logger_mt<Severity, std::string> BoostLogger;

class Pump::Impl
{
   public:
    Impl(const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction, Source* aSource)
        : severity_(aSeverity),
          line_(aLine),
          file_(aFile),
          function_(aFunction),
          sourcePtr_(aSource),
          stringStream_(),
          hasRecord_(false)
    {
        if (sourcePtr_ != nullptr && sourcePtr_->sourceUPtr_ != nullptr)
        {
            BoostLogger* loggerPtr = static_cast<BoostLogger*>(sourcePtr_->sourceUPtr_->accessLogger());
            record_ = loggerPtr->open_record(boost::log::keywords::severity = severity_);
            hasRecord_ = static_cast<bool>(record_);

            if (hasRecord_)
            {
                // Add metadata to log message
                if (!file_.isEmpty())
                {
                    // Extract just the filename from the path
                    const std::string fileStr = file_;
                    const size_t lastSlash = fileStr.find_last_of("/\\");
                    const std::string fileName =
                        (lastSlash != std::string::npos) ? fileStr.substr(lastSlash + 1) : fileStr;

                    stringStream_ << "[" << fileName;

                    if (line_.isDefined())
                    {
                        stringStream_ << ":" << static_cast<int>(line_);
                    }

                    stringStream_ << "] ";
                }

                if (!function_.isEmpty())
                {
                    stringStream_ << function_ << " | ";
                }
            }
        }
    }

    ~Impl()
    {
        if (hasRecord_ && sourcePtr_ != nullptr && sourcePtr_->sourceUPtr_ != nullptr)
        {
            BoostLogger* loggerPtr = static_cast<BoostLogger*>(sourcePtr_->sourceUPtr_->accessLogger());

            // Write the accumulated string to the record
            boost::log::record_ostream recordStream(record_);
            recordStream << stringStream_.str();
            recordStream.flush();

            loggerPtr->push_record(std::move(record_));
        }
    }

    bool canAccessStream() const
    {
        return hasRecord_;
    }

    std::ostream& accessStream()
    {
        return stringStream_;
    }

   private:
    Severity severity_;
    Integer line_;
    String file_;
    String function_;
    Source* sourcePtr_;
    std::ostringstream stringStream_;
    boost::log::record record_;
    bool hasRecord_;
};

Pump::Pump(
    const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction, Source* aSource
)
    : implPtr_(std::make_unique<Pump::Impl>(aSeverity, aLine, aFile, aFunction, aSource))
{
}

Pump::Pump(Pump&& aPump)
    : implPtr_(std::move(aPump.implPtr_))
{
}

Pump::~Pump() = default;

bool Pump::canAccessStream() const
{
    return implPtr_ && implPtr_->canAccessStream();
}

std::ostream& Pump::accessStream()
{
    return implPtr_->accessStream();
}

}  // namespace logger
}  // namespace core
}  // namespace ostk
