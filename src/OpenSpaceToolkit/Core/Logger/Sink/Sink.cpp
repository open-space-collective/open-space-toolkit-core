/// Apache License 2.0

#include <algorithm>

#include <OpenSpaceToolkit/Core/Logger/Sink/Sink.hpp>

namespace ostk
{
namespace core
{
namespace logger
{
namespace sink
{

Sink::Sink(const Severity& aSeverity)
    : enabled_(true),
      severity_(aSeverity),
      lineIdEnabled_(false),
      severityEnabled_(true),
      timestampEnabled_(true),
      threadEnabled_(false),
      scopeEnabled_(false),
      fileEnabled_(false),
      lineEnabled_(false),
      functionEnabled_(false),
      channelEnabled_(true),
      channels_()
{
}

Sink::~Sink() = default;

bool Sink::isEnabled() const
{
    return enabled_;
}

bool Sink::isLineIdLogged() const
{
    return lineIdEnabled_;
}

bool Sink::isSeverityLogged() const
{
    return severityEnabled_;
}

bool Sink::isTimestampLogged() const
{
    return timestampEnabled_;
}

bool Sink::isThreadLogged() const
{
    return threadEnabled_;
}

bool Sink::isScopeLogged() const
{
    return scopeEnabled_;
}

bool Sink::isFileLogged() const
{
    return fileEnabled_;
}

bool Sink::isLineLogged() const
{
    return lineEnabled_;
}

bool Sink::isFunctionLogged() const
{
    return functionEnabled_;
}

bool Sink::isChannelLogged() const
{
    return channelEnabled_;
}

void Sink::addChannel(const String& aChannel)
{
    if (std::find(channels_.begin(), channels_.end(), aChannel) == channels_.end())
    {
        channels_.add(aChannel);
    }
}

void Sink::removeChannel(const String& aChannel)
{
    auto it = std::find(channels_.begin(), channels_.end(), aChannel);

    if (it != channels_.end())
    {
        channels_.remove(aChannel);
    }
}

}  // namespace sink
}  // namespace logger
}  // namespace core
}  // namespace ostk
