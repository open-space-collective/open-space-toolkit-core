/// Apache License 2.0

#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>

#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Source/Source.hpp>

namespace ostk
{
namespace core
{
namespace logger
{
namespace source
{

typedef boost::log::sources::severity_channel_logger_mt<Severity, std::string> BoostLogger;

class Source::Impl
{
   public:
    Impl(const String& aChannel)
        : logger_(boost::log::keywords::channel = aChannel)
    {
    }

    Impl(const Impl& anImpl)
        : logger_(anImpl.logger_)
    {
    }

    BoostLogger& accessLogger()
    {
        return logger_;
    }

   private:
    BoostLogger logger_;
};

Source::Source(const String& aChannel)
    : implPtr_(std::make_unique<Source::Impl>(aChannel))
{
}

Source::Source(const Source& aSource)
    : implPtr_(std::make_unique<Source::Impl>(*aSource.implPtr_))
{
}

Source::~Source() = default;

Source* Source::clone() const
{
    return new Source(*this);
}

void* Source::accessLogger()
{
    return &implPtr_->accessLogger();
}

}  // namespace source
}  // namespace logger
}  // namespace core
}  // namespace ostk
