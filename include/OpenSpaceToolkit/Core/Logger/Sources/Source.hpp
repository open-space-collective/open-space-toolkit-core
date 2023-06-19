/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Sources_Source__
#define __OpenSpaceToolkit_Core_Logger_Sources_Source__

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{
namespace sources
{

using ostk::core::types::Unique;
using ostk::core::types::String;
using ostk::core::ctnr::Array;
using ostk::core::logger::Severity;

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

}  // namespace sources
}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
