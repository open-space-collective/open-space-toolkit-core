/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Logger/Source.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

Source::Source(const String& aChannel)
    : sourceUPtr_(std::make_unique<source::Source>(aChannel))
{
}

Source::Source(const Source& aSource)
    : sourceUPtr_(aSource.sourceUPtr_ ? std::unique_ptr<source::Source>(aSource.sourceUPtr_->clone()) : nullptr)
{
}

Source& Source::operator=(const Source& aSource)
{
    if (this != &aSource)
    {
        sourceUPtr_ = aSource.sourceUPtr_ ? std::unique_ptr<source::Source>(aSource.sourceUPtr_->clone()) : nullptr;
    }

    return *this;
}

bool Source::isDefined() const
{
    return sourceUPtr_ != nullptr;
}

Source Source::Undefined()
{
    Source source("");
    source.sourceUPtr_.reset();
    return source;
}

}  // namespace logger
}  // namespace core
}  // namespace ostk
