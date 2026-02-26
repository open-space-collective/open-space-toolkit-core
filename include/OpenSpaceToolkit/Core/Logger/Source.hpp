/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Source__
#define __OpenSpaceToolkit_Core_Logger_Source__

#include <OpenSpaceToolkit/Core/Logger/Source/Source.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{

using ostk::core::type::String;
using ostk::core::type::Unique;

/// @brief Log source
///
/// Represents a named logging source associated with a channel.
class Source
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aChannel A channel name
    Source(const String& aChannel);

    /// @brief Copy constructor
    ///
    /// @param [in] aSource A source
    Source(const Source& aSource);

    /// @brief Copy assignment operator
    ///
    /// @param [in] aSource A source
    /// @return Reference to source
    Source& operator=(const Source& aSource);

    /// @brief Check if source is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Construct an undefined source
    ///
    /// @return Undefined source
    static Source Undefined();

    // private:

    Unique<source::Source> sourceUPtr_;
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
