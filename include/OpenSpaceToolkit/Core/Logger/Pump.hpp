/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Pump__
#define __OpenSpaceToolkit_Core_Logger_Pump__

#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Source.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

using ostk::core::type::Unique;
using ostk::core::type::Integer;
using ostk::core::type::String;
using ostk::core::logger::Severity;

/// @brief                      Log pump

class Pump
{
   public:
    using StreamManipulator = std::ostream&(std::ostream&);

    Pump(
        const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction, Source* aSource
    );

    Pump(const Pump& aPump) = delete;

    Pump(Pump&& aPump);

    ~Pump();

    Pump& operator=(const Pump& aPump) = delete;

    template <class T>
    Pump& operator<<(const T& anObject)
    {
        if (this->canAccessStream())
        {
            this->accessStream() << anObject;
        }

        return *this;
    }

    Pump& operator<<(StreamManipulator aStreamManipulator)
    {
        if (this->canAccessStream())
        {
            this->accessStream() << aStreamManipulator;
        }

        return *this;
    }

   private:
    class Impl;

    Unique<Pump::Impl> implPtr_;

    bool canAccessStream() const;

    std::ostream& accessStream();
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
