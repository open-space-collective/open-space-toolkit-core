/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Source_Source__
#define __OpenSpaceToolkit_Core_Logger_Source_Source__

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{
namespace source
{

using ostk::core::container::Array;
using ostk::core::logger::Severity;
using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief                      Log source base

class Source
{
    friend class Pump;

   public:
    Source(const String& aChannel);

    Source(const Source& aSource);

    ~Source();

    virtual Source* clone() const;

    Source& operator=(const Source& aSource) = delete;

    void* accessLogger();

   private:
    class Impl;

    Unique<Source::Impl> implPtr_;
};

}  // namespace source
}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
