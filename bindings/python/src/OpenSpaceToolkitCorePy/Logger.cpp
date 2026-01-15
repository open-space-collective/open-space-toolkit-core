/// Apache License 2.0

#include <functional>
#include <memory>
#include <mutex>

#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <OpenSpaceToolkit/Core/Logger.hpp>
#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sink/Python.hpp>

namespace
{

// Global state for Python logging integration
std::once_flag pythonLoggingSetupFlag;
std::unique_ptr<ostk::core::logger::sink::Python> globalPythonSinkPtr;
bool pythonLoggingEnabled = false;

/// @brief Set up Python logging integration
/// @param loggerName The Python logger name to use (default: "ostk")
void setupPythonLogging(const std::string& loggerName = "ostk")
{
    using namespace ostk::core;
    using namespace ostk::core::logger;
    using namespace ostk::core::logger::sink;

    std::call_once(
        pythonLoggingSetupFlag,
        [&loggerName]()
        {
            // Get or create the Python logger
            pybind11::module_ logging = pybind11::module_::import("logging");
            pybind11::object pyLogger = logging.attr("getLogger")(loggerName);

            // Create a callback that uses Python's logger
            // Python's logger will handle level filtering based on its configuration
            Python::LogCallback callback =
                [pyLogger](int level, const std::string& channel, const std::string& msg)
            {
                pybind11::gil_scoped_acquire acquire;
                try
                {
                    // Check if the logger is enabled for this level
                    // This respects Python's logging configuration
                    if (pyLogger.attr("isEnabledFor")(level).cast<bool>())
                    {
                        // Format message with channel
                        std::string fullMsg = "[" + channel + "] " + msg;
                        pyLogger.attr("log")(level, fullMsg);
                    }
                }
                catch (const pybind11::error_already_set&)
                {
                    // Silently ignore Python exceptions in logging
                }
            };

            // Create Python sink - no C++ filtering, let Python handle it
            globalPythonSinkPtr = std::make_unique<Python>(Severity::Trace, callback);

            // Add to global logger (use fully qualified name to avoid ambiguity)
            Logger::Global().addSink(ostk::core::logger::Sink(*globalPythonSinkPtr));

            pythonLoggingEnabled = true;
        }
    );
}

}  // anonymous namespace

inline void OpenSpaceToolkitCorePy_Logger(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::Logger;
    using ostk::core::logger::Severity;
    using ostk::core::logger::Sink;
    using ostk::core::logger::sink::Python;
    using ostk::core::type::String;

    // Create "logger" python submodule
    auto loggerModule = aModule.def_submodule(
        "logger",
        R"doc(
        Logging module for Open Space Toolkit.

        This submodule provides logging facilities that integrate with
        Python's built-in logging module. When you import ostk.core,
        C++ log messages are automatically forwarded to Python's logging
        system under the "ostk" logger.

        Configure logging using Python's standard logging configuration:

        Example:
            >>> import logging
            >>>
            >>> # Configure Python logging
            >>> logging.basicConfig(level=logging.DEBUG)
            >>>
            >>> # Or configure just the OSTK logger
            >>> logging.getLogger("ostk").setLevel(logging.WARNING)
            >>>
            >>> # C++ library logs will now respect Python's logging level
    )doc"
    );

    // Expose Severity enum
    enum_<Severity>(
        loggerModule,
        "Severity",
        R"doc(
            Log severity levels.

            Severity levels from least to most severe: Trace, Debug, Info, Warning, Error, Fatal.

            These map to Python logging levels:
            - Trace -> 5 (custom, below DEBUG)
            - Debug -> 10 (DEBUG)
            - Info -> 20 (INFO)
            - Warning -> 30 (WARNING)
            - Error -> 40 (ERROR)
            - Fatal -> 50 (CRITICAL)

            Example:
                >>> from ostk.core.logger import Severity
                >>> Severity.Debug
                <Severity.Debug: 1>
        )doc"
    )
        .value("Trace", Severity::Trace, R"doc(Detailed tracing information (Python level 5).)doc")
        .value("Debug", Severity::Debug, R"doc(Debug information (Python level 10/DEBUG).)doc")
        .value("Info", Severity::Info, R"doc(General informational messages (Python level 20/INFO).)doc")
        .value("Warning", Severity::Warning, R"doc(Warning conditions (Python level 30/WARNING).)doc")
        .value("Error", Severity::Error, R"doc(Error conditions (Python level 40/ERROR).)doc")
        .value("Fatal", Severity::Fatal, R"doc(Fatal errors (Python level 50/CRITICAL).)doc")
        .export_values();

    // Expose Logger class at module level (ostk.core.Logger)
    class_<Logger>(
        aModule,
        "Logger",
        R"doc(
            Thread-safe logging facility built on Boost.Log.

            The Logger class provides logging with automatic integration to
            Python's logging module. All C++ log messages are forwarded to
            the "ostk" Python logger, so you can control logging levels
            using Python's standard logging configuration.

            Example:
                >>> import logging
                >>> from ostk.core import Logger
                >>>
                >>> # Configure Python's logging
                >>> logging.basicConfig(
                ...     level=logging.DEBUG,
                ...     format='%(name)s - %(levelname)s - %(message)s'
                ... )
                >>>
                >>> # C++ library logs will appear in Python's output
                >>> # Control OSTK log level via Python:
                >>> logging.getLogger("ostk").setLevel(logging.WARNING)
        )doc"
    )
        .def(
            init<const String&>(),
            R"doc(
                Construct a Logger with a channel name.

                Args:
                    channel (str): The channel name for this logger.

                Example:
                    >>> logger = Logger("MyModule")
            )doc",
            arg("channel")
        )
        .def(
            "get_channel",
            &Logger::getChannel,
            R"doc(
                Get the logger channel name.

                Returns:
                    str: The channel name.
            )doc"
        )
        .def(
            "log",
            [](Logger& self, const Severity& severity, const std::string& message)
            {
                self(severity, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty()) << message;
            },
            R"doc(
                Log a message at the specified severity level.

                Args:
                    severity (Severity): The severity level.
                    message (str): The message to log.

                Example:
                    >>> logger = Logger.global_logger()
                    >>> logger.log(Severity.Info, "Hello, World!")
            )doc",
            arg("severity"),
            arg("message")
        )
        .def(
            "trace",
            [](Logger& self, const std::string& message)
            {
                self(Severity::Trace, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty())
                    << message;
            },
            R"doc(Log a trace message.)doc",
            arg("message")
        )
        .def(
            "debug",
            [](Logger& self, const std::string& message)
            {
                self(Severity::Debug, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty())
                    << message;
            },
            R"doc(Log a debug message.)doc",
            arg("message")
        )
        .def(
            "info",
            [](Logger& self, const std::string& message)
            {
                self(Severity::Info, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty())
                    << message;
            },
            R"doc(Log an info message.)doc",
            arg("message")
        )
        .def(
            "warning",
            [](Logger& self, const std::string& message)
            {
                self(Severity::Warning, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty())
                    << message;
            },
            R"doc(Log a warning message.)doc",
            arg("message")
        )
        .def(
            "error",
            [](Logger& self, const std::string& message)
            {
                self(Severity::Error, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty())
                    << message;
            },
            R"doc(Log an error message.)doc",
            arg("message")
        )
        .def(
            "fatal",
            [](Logger& self, const std::string& message)
            {
                self(Severity::Fatal, ostk::core::type::Integer::Undefined(), String::Empty(), String::Empty())
                    << message;
            },
            R"doc(Log a fatal message.)doc",
            arg("message")
        )
        .def_static(
            "console",
            static_cast<Logger (*)(const Severity&)>(&Logger::Console),
            R"doc(
                Create a console logger with default channel.

                Args:
                    severity (Severity): Minimum severity level to log.

                Returns:
                    Logger: A new console logger.
            )doc",
            arg("severity")
        )
        .def_static(
            "console",
            static_cast<Logger (*)(const String&, const Severity&)>(&Logger::Console),
            R"doc(
                Create a console logger with custom channel.

                Args:
                    channel (str): The channel name.
                    severity (Severity): Minimum severity level to log.

                Returns:
                    Logger: A new console logger.
            )doc",
            arg("channel"),
            arg("severity")
        )
        .def_static(
            "global_logger",
            &Logger::Global,
            return_value_policy::reference,
            R"doc(
                Get the global logger instance.

                Returns:
                    Logger: Reference to the global logger.
            )doc"
        )
        .def_static(
            "set_global_severity",
            &Logger::SetGlobalSeverity,
            R"doc(
                Set the global logger minimum severity for C++ console output.

                Note: This only affects the C++ console sink. To control what
                gets logged to Python, configure Python's logging level instead:

                    logging.getLogger("ostk").setLevel(logging.WARNING)

                Args:
                    severity (Severity): The minimum severity level.
            )doc",
            arg("severity")
        )
        .def_static(
            "get_global_severity",
            &Logger::GetGlobalSeverity,
            R"doc(
                Get the global logger minimum severity.

                Returns:
                    Severity: The current minimum severity level.
            )doc"
        )
        .def_static(
            "use_python_logger",
            [](const std::string& loggerName)
            { setupPythonLogging(loggerName); },
            R"doc(
                Enable forwarding C++ logs to a Python logger.

                After calling this, all C++ log messages from OSTK libraries
                will be forwarded to the specified Python logger. The Python
                logger's level configuration controls what gets logged.

                This is called automatically when importing ostk.core, using
                the default logger name "ostk".

                Args:
                    logger_name (str): The Python logger name to use.

                Example:
                    >>> import logging
                    >>> logging.basicConfig(level=logging.DEBUG)
                    >>>
                    >>> # Use a custom logger name
                    >>> Logger.use_python_logger("my_app.ostk")
                    >>>
                    >>> # Configure that logger
                    >>> logging.getLogger("my_app.ostk").setLevel(logging.INFO)
            )doc",
            arg("logger_name") = "ostk"
        )
        .def_static(
            "is_python_logging_enabled",
            []() { return pythonLoggingEnabled; },
            R"doc(
                Check if Python logging integration is enabled.

                Returns:
                    bool: True if C++ logs are being forwarded to Python.
            )doc"
        );

    // Automatically set up Python logging when the module is imported
    // This makes it "just work" - users configure Python logging and C++ follows
    setupPythonLogging("ostk");
}
