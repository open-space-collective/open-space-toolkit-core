/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Severity__
#define __OpenSpaceToolkit_Core_Logger_Severity__

#include <ostream>

namespace ostk
{
namespace core
{
namespace logger
{

/// @brief                      Log severity

enum class Severity
{

    Trace,
    Debug,
    Info,
    Warning,
    Error,
    Fatal

};

/// @brief Stream operator for Severity (declaration for ADL)
std::ostream& operator<<(std::ostream& strm, const Severity& severity);

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
