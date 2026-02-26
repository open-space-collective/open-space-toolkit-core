/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Sink_Console__
#define __OpenSpaceToolkit_Core_Logger_Sink_Console__

#include <OpenSpaceToolkit/Core/Logger/Sink/Sink.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace logger
{
namespace sink
{

using ostk::core::logger::Severity;
using ostk::core::type::Unique;

/// @brief Log console sink
class Console : public Sink
{
   public:
    enum class Color
    {

        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Magenta,
        Cyan,
        LightGray,
        DarkGray,
        LightRed,
        LightGreen,
        LightYellow,
        LightBlue,
        LightMagenta,
        LightCyan,
        White

    };

    Console(const Severity& aSeverity);

    Console(const Console& aConsole);

    virtual ~Console() override;

    virtual Console* clone() const override;

    virtual void enable() override;
    virtual void disable() override;

    static String ColorizeMessage(const String& aMessage, const Console::Color& aColor);

   private:
    class Impl;

    friend class Console::Impl;

    Unique<Console::Impl> implUPtr_;
};

}  // namespace sink
}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
