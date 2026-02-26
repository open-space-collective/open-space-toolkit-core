/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Utility_Print__
#define __OpenSpaceToolkit_Core_Utility_Print__

#include <iomanip>
#include <ostream>

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace utils
{

/// @brief Formatted print utilities for structured output
class Print
{
   public:
    /// @brief Line buffer for formatted output
    ///
    /// Collects output via stream operators and formats it with fixed-width columns.
    class LineBuffer
    {
       public:
        /// @brief Constructor
        ///
        /// @param [in] anOutputStream An output stream
        /// @param [in] anIndentation An indentation level
        LineBuffer(std::ostream& anOutputStream, uint anIndentation);

        /// @brief Copy constructor (disabled)
        LineBuffer(const LineBuffer& aLineBuffer) = delete;

        /// @brief Move constructor
        LineBuffer(LineBuffer&& aLineBuffer) = default;

        /// @brief Destructor (flushes the line)
        ~LineBuffer();

        /// @brief Stream insertion operator
        ///
        /// @param [in] anObject An object to insert
        /// @return Reference to line buffer
        template <class T>
        LineBuffer& operator<<(const T& anObject)
        {
            stream_ << std::setw(40) << std::setfill(' ') << anObject << " ";

            return *this;
        }

       private:
        std::ostream& stream_;
        uint indentation_;
    };

    /// @brief Default constructor (disabled)
    Print() = delete;

    /// @brief Print a section header
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aName A header name
    static void Header(std::ostream& anOutputStream, const type::String& aName);

    /// @brief Create a formatted line buffer
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anIndentation An indentation level (default: 1)
    /// @return Line buffer
    static Print::LineBuffer Line(std::ostream& anOutputStream, uint anIndentation = 1);

    /// @brief Print a separator line
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aName An optional separator label (default: empty)
    static void Separator(std::ostream& anOutputStream, const type::String& aName = "");

    /// @brief Print a section footer
    ///
    /// @param [in] anOutputStream An output stream
    static void Footer(std::ostream& anOutputStream);
};

}  // namespace utils
}  // namespace core
}  // namespace ostk

#endif
