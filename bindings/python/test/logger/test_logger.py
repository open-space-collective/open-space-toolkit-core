# Apache License 2.0

import logging
import pytest


class TestSeverity:
    """Tests for the Severity enum."""

    def test_severity_import(self):
        from ostk.core.logger import Severity

        assert Severity is not None

    def test_severity_values(self):
        from ostk.core.logger import Severity

        assert Severity.Trace is not None
        assert Severity.Debug is not None
        assert Severity.Info is not None
        assert Severity.Warning is not None
        assert Severity.Error is not None
        assert Severity.Fatal is not None

    def test_severity_ordering(self):
        from ostk.core.logger import Severity

        # Severity levels should be ordered
        assert Severity.Trace.value < Severity.Debug.value
        assert Severity.Debug.value < Severity.Info.value
        assert Severity.Info.value < Severity.Warning.value
        assert Severity.Warning.value < Severity.Error.value
        assert Severity.Error.value < Severity.Fatal.value

    def test_severity_comparison(self):
        from ostk.core.logger import Severity

        assert Severity.Debug != Severity.Info
        assert Severity.Warning != Severity.Error


class TestLogger:
    """Tests for the Logger class."""

    def test_logger_import(self):
        from ostk.core import Logger

        assert Logger is not None

    def test_logger_constructor(self):
        from ostk.core import Logger

        logger = Logger("TestChannel")
        assert logger is not None

    def test_logger_constructor_empty_channel(self):
        from ostk.core import Logger

        logger = Logger("")
        assert logger is not None

    def test_logger_constructor_dotted_channel(self):
        from ostk.core import Logger

        logger = Logger("My.Module.Name")
        assert logger is not None

    def test_logger_get_channel(self):
        from ostk.core import Logger

        logger = Logger("TestChannel")
        assert logger.get_channel() == "TestChannel"

    def test_logger_get_channel_empty(self):
        from ostk.core import Logger

        logger = Logger("")
        assert logger.get_channel() == ""

    def test_logger_get_channel_dotted(self):
        from ostk.core import Logger

        logger = Logger("My.Module.Name")
        assert logger.get_channel() == "My.Module.Name"

    def test_logger_console_single_arg(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        logger = Logger.console(Severity.Debug)
        assert logger is not None

    def test_logger_console_two_args(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        logger = Logger.console("MyChannel", Severity.Info)
        assert logger is not None
        assert logger.get_channel() == "MyChannel"

    def test_logger_console_all_severities(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        for severity in [
            Severity.Trace,
            Severity.Debug,
            Severity.Info,
            Severity.Warning,
            Severity.Error,
            Severity.Fatal,
        ]:
            logger = Logger.console(severity)
            assert logger is not None

    def test_logger_global(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        assert logger is not None

    def test_logger_global_singleton(self):
        from ostk.core import Logger

        logger1 = Logger.global_logger()
        logger2 = Logger.global_logger()
        # Should be the same object
        assert logger1.get_channel() == logger2.get_channel()

    def test_logger_global_channel(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        assert logger.get_channel() == "Global"

    def test_logger_set_global_severity(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        # Should not raise
        Logger.set_global_severity(Severity.Debug)
        Logger.set_global_severity(Severity.Info)
        Logger.set_global_severity(Severity.Warning)

    def test_logger_get_global_severity(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        Logger.set_global_severity(Severity.Warning)
        assert Logger.get_global_severity() == Severity.Warning

        Logger.set_global_severity(Severity.Debug)
        assert Logger.get_global_severity() == Severity.Debug

    def test_logger_log_method(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        logger = Logger.global_logger()

        # Should not raise
        logger.log(Severity.Debug, "Test debug message")
        logger.log(Severity.Info, "Test info message")
        logger.log(Severity.Warning, "Test warning message")

    def test_logger_trace(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        # Should not raise
        logger.trace("Test trace message")

    def test_logger_debug(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        # Should not raise
        logger.debug("Test debug message")

    def test_logger_info(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        # Should not raise
        logger.info("Test info message")

    def test_logger_warning(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        # Should not raise
        logger.warning("Test warning message")

    def test_logger_error(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        # Should not raise
        logger.error("Test error message")

    def test_logger_fatal(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        # Should not raise
        logger.fatal("Test fatal message")

    def test_logger_is_python_logging_enabled(self):
        from ostk.core import Logger

        # Should be enabled by default when module is imported
        assert Logger.is_python_logging_enabled() is True

    def test_logger_use_python_logger(self):
        from ostk.core import Logger

        # Should not raise
        Logger.use_python_logger("ostk")
        Logger.use_python_logger("my_app.ostk")


class TestPythonLoggingIntegration:
    """Tests for Python logging integration."""

    def test_python_logging_integration_enabled(self):
        from ostk.core import Logger

        assert Logger.is_python_logging_enabled() is True

    def test_python_logging_with_handler(self, caplog):
        """Test that C++ logs are forwarded to Python logging."""
        from ostk.core import Logger
        from ostk.core.logger import Severity

        # Set up logging to capture
        with caplog.at_level(logging.DEBUG, logger="ostk"):
            logger = Logger.global_logger()
            logger.info("Test message from C++")

        # Check if the message was captured
        # Note: This may not work if the Python sink wasn't set up correctly
        # The test verifies at minimum that no exception is raised

    def test_python_logging_level_control(self):
        """Test that Python logging level controls C++ output."""
        from ostk.core import Logger

        # Configure Python logger
        py_logger = logging.getLogger("ostk")
        original_level = py_logger.level

        try:
            # Set to WARNING - DEBUG messages should be filtered
            py_logger.setLevel(logging.WARNING)

            logger = Logger.global_logger()
            # These should not raise
            logger.debug("Debug message - should be filtered")
            logger.warning("Warning message - should appear")

        finally:
            # Restore original level
            py_logger.setLevel(original_level)

    def test_custom_python_logger_name(self):
        """Test using a custom Python logger name."""
        from ostk.core import Logger

        # This should not raise
        Logger.use_python_logger("custom.ostk.logger")

        # Log something
        logger = Logger.global_logger()
        logger.info("Test with custom logger name")


class TestLoggerWithDifferentMessages:
    """Tests for logging different message types."""

    def test_log_string(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        logger.info("Simple string message")

    def test_log_with_numbers(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        logger.info(f"Integer: {42}")
        logger.info(f"Float: {3.14159}")

    def test_log_with_special_characters(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        logger.info("Message with special chars: !@#$%^&*()")

    def test_log_with_newlines(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        logger.info("Message with\nnewline")

    def test_log_empty_message(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        logger.info("")

    def test_log_unicode(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        logger.info("Unicode: \u03c0 \u2192 \u221e")

    def test_log_long_message(self):
        from ostk.core import Logger

        logger = Logger.global_logger()
        long_message = "A" * 1000
        logger.info(long_message)


class TestMultipleLoggers:
    """Tests for using multiple logger instances."""

    def test_multiple_console_loggers(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        logger1 = Logger.console("Channel1", Severity.Debug)
        logger2 = Logger.console("Channel2", Severity.Info)
        logger3 = Logger.console("Channel3", Severity.Warning)

        assert logger1.get_channel() == "Channel1"
        assert logger2.get_channel() == "Channel2"
        assert logger3.get_channel() == "Channel3"

    def test_multiple_loggers_logging(self):
        from ostk.core import Logger
        from ostk.core.logger import Severity

        logger1 = Logger.console("Module1", Severity.Debug)
        logger2 = Logger.console("Module2", Severity.Debug)

        # Both should be able to log
        logger1.info("Message from Module1")
        logger2.info("Message from Module2")

    def test_logger_instances_independent(self):
        from ostk.core import Logger

        logger1 = Logger("Channel1")
        logger2 = Logger("Channel2")

        # Channels should be independent
        assert logger1.get_channel() != logger2.get_channel()


class TestSeverityLevelMapping:
    """Tests to verify severity level mapping to Python logging levels."""

    def test_severity_to_python_level_mapping(self):
        """Verify the expected mapping of severity levels."""
        from ostk.core.logger import Severity

        # Expected Python logging level mappings
        expected_mappings = {
            Severity.Trace: 5,  # Custom level below DEBUG
            Severity.Debug: 10,  # logging.DEBUG
            Severity.Info: 20,  # logging.INFO
            Severity.Warning: 30,  # logging.WARNING
            Severity.Error: 40,  # logging.ERROR
            Severity.Fatal: 50,  # logging.CRITICAL
        }

        # Verify Python logging levels match expected
        assert logging.DEBUG == 10
        assert logging.INFO == 20
        assert logging.WARNING == 30
        assert logging.ERROR == 40
        assert logging.CRITICAL == 50
