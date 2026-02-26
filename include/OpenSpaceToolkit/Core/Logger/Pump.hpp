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

using ostk::core::logger::Severity;
using ostk::core::type::Integer;
using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief Log pump
///
/// Temporary object that collects log message content via stream operators and
/// flushes the message to the log source upon destruction.
class Pump
{
   public:
    using StreamManipulator = std::ostream&(std::ostream&);

    /// @brief Constructor
    ///
    /// @param [in] aSeverity A severity level
    /// @param [in] aLine A source line number
    /// @param [in] aFile A source file name
    /// @param [in] aFunction A source function name
    /// @param [in] aSource A pointer to the log source
    Pump(
        const Severity& aSeverity, const Integer& aLine, const String& aFile, const String& aFunction, Source* aSource
    );

    /// @brief Copy constructor (disabled)
    Pump(const Pump& aPump) = delete;

    /// @brief Move constructor
    ///
    /// @param [in] aPump A pump to move from
    Pump(Pump&& aPump);

    /// @brief Destructor (flushes the log message)
    ~Pump();

    /// @brief Copy assignment operator (disabled)
    Pump& operator=(const Pump& aPump) = delete;

    /// @brief Stream insertion operator
    ///
    /// @param [in] anObject An object to insert into the log message
    /// @return Reference to pump
    template <class T>
    Pump& operator<<(const T& anObject)
    {
        if (this->canAccessStream())
        {
            this->accessStream() << anObject;
        }

        return *this;
    }

    /// @brief Stream manipulator operator (e.g., std::endl)
    ///
    /// @param [in] aStreamManipulator A stream manipulator
    /// @return Reference to pump
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
