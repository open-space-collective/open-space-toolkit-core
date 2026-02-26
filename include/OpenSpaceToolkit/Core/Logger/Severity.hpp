/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Logger_Severity__
#define __OpenSpaceToolkit_Core_Logger_Severity__

namespace ostk
{
namespace core
{
namespace logger
{

/// @brief Log severity
enum class Severity
{

    Trace,    ///< Detailed tracing information
    Debug,    ///< Debug-level information
    Info,     ///< General informational messages
    Warning,  ///< Warning conditions
    Error,    ///< Error conditions
    Fatal     ///< Fatal error conditions
};

}  // namespace logger
}  // namespace core
}  // namespace ostk

#endif
