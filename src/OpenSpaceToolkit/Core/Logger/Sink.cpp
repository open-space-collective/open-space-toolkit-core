/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Logger/Sink.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sink/Console.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

Sink::Sink(const sink::Sink& aSink)
    : sinkUPtr_(aSink.clone())
{
}

Sink::Sink(const Sink& aSink)
    : sinkUPtr_(aSink.sinkUPtr_ ? std::unique_ptr<sink::Sink>(aSink.sinkUPtr_->clone()) : nullptr)
{
}

void Sink::enable()
{
    if (sinkUPtr_)
    {
        sinkUPtr_->enable();
    }
}

void Sink::disable()
{
    if (sinkUPtr_)
    {
        sinkUPtr_->disable();
    }
}

void Sink::addChannel(const String& aChannel)
{
    if (sinkUPtr_)
    {
        sinkUPtr_->addChannel(aChannel);
    }
}

void Sink::removeChannel(const String& aChannel)
{
    if (sinkUPtr_)
    {
        sinkUPtr_->removeChannel(aChannel);
    }
}

Sink Sink::Console(const Severity& aSeverity)
{
    return Sink(sink::Console(aSeverity));
}

}  // namespace logger
}  // namespace core
}  // namespace ostk
