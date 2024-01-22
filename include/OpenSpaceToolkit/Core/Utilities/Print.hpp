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

class Print
{
   public:
    class LineBuffer
    {
       public:
        LineBuffer(std::ostream& anOutputStream, uint anIndentation);

        LineBuffer(const LineBuffer& aLineBuffer) = delete;

        LineBuffer(LineBuffer&& aLineBuffer) = default;

        ~LineBuffer();

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

    Print() = delete;

    static void Header(std::ostream& anOutputStream, const types::String& aName);

    static Print::LineBuffer Line(std::ostream& anOutputStream, uint anIndentation = 1);

    static void Separator(std::ostream& anOutputStream, const types::String& aName = "");

    static void Footer(std::ostream& anOutputStream);
};

}  // namespace utils
}  // namespace core
}  // namespace ostk

#endif
