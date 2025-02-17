# Apache License 2.0

import sys
from io import StringIO

from ostk.core import Logger


def test_logger_level_enum():
    """Test Logger.Level enum values"""
    assert hasattr(Logger.Level, "Trace")
    assert hasattr(Logger.Level, "Debug")
    assert hasattr(Logger.Level, "Info")
    assert hasattr(Logger.Level, "Warning")
    assert hasattr(Logger.Level, "Error")
    assert hasattr(Logger.Level, "Fatal")


def test_set_logger_level_enum():
    """Test setting logger level using enum values"""
    Logger.set_logger_level(Logger.Level.Trace)
    Logger.set_logger_level(Logger.Level.Debug)
    Logger.set_logger_level(Logger.Level.Info)
    Logger.set_logger_level(Logger.Level.Warning)
    Logger.set_logger_level(Logger.Level.Error)
    Logger.set_logger_level(Logger.Level.Fatal)


def test_set_logger_level_string():
    """Test setting logger level using string values"""
    Logger.set_logger_level("trace")
    Logger.set_logger_level("debug")
    Logger.set_logger_level("info")
    Logger.set_logger_level("warning")
    Logger.set_logger_level("error")
    Logger.set_logger_level("fatal")


def test_string_from_level():
    """Test string conversion from level enum"""
    test_cases = [
        (Logger.Level.Trace, "Trace"),
        (Logger.Level.Debug, "Debug"),
        (Logger.Level.Info, "Info"),
        (Logger.Level.Warning, "Warning"),
        (Logger.Level.Error, "Error"),
        (Logger.Level.Fatal, "Fatal"),
    ]

    for level_enum, expected_string in test_cases:
        assert Logger.string_from_level(level_enum) == expected_string


def test_level_from_string():
    """Test level enum conversion from string"""
    test_cases = [
        ("trace", Logger.Level.Trace),
        ("debug", Logger.Level.Debug),
        ("info", Logger.Level.Info),
        ("warning", Logger.Level.Warning),
        ("error", Logger.Level.Error),
        ("fatal", Logger.Level.Fatal),
    ]

    for level_string, expected_enum in test_cases:
        assert Logger.level_from_string(level_string) == expected_enum
