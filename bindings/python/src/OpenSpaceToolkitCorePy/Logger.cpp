/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Logger.hpp>

using ostk::core::Logger;
using ostk::core::String;

inline void OpenSpaceToolkitCorePy_Logger(pybind11::module& aModule)
{
    using namespace pybind11;

    pybind11::class_<Logger> loggerClass(aModule, "Logger");

    pybind11::enum_<Logger::Level>(loggerClass, "Level")
        .value("Trace", Logger::Level::Trace)
        .value("Debug", Logger::Level::Debug)
        .value("Info", Logger::Level::Info)
        .value("Warning", Logger::Level::Warning)
        .value("Error", Logger::Level::Error)
        .value("Fatal", Logger::Level::Fatal)
        .export_values()
    ;


    loggerClass
        .def_static(
            "set_logger_level",
            static_cast<void (*)(const Logger::Level&)>(&Logger::SetLoggerLevel),
            arg("level"),
            R"doc(
                Set the logger level using enum Level.

                Args:
                    level (Logger.Level): The logger level to set.
            )doc"
        )
        .def_static(
            "set_logger_level",
            static_cast<void (*)(const String&)>(&Logger::SetLoggerLevel),
            arg("level"),
            R"doc(
                Set the logger level using string.

                Args:
                    level (str): The logger level to set. Valid levels are: "trace", "debug", "info", "warning", "error", "fatal".
            )doc"
        )
        .def_static(
            "string_from_level",
            &Logger::StringFromLevel,
            arg("level"),
            R"doc(
                Convert a logger level enum to string.

                Args:
                    level (Logger.Level): The logger level enum.
                
                Returns:
                    str: String representation of the log level.
            )doc"
        )
        .def_static(
            "level_from_string",
            &Logger::LevelFromString,
            arg("level"),
            R"doc(
                Convert a string to a logger level enum.

                Args:
                    level (str): The logger level string.
                
                Returns:
                    Logger.Level: The logger level enum.
            )doc"
        )
    ;
}
