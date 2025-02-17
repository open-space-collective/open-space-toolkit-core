/// Apache License 2.0

#include <gtest/gtest.h>
#include <OpenSpaceToolkit/Core/Logger.hpp>

using ostk::core::Logger;

TEST(OpenSpaceToolkit_Core_Logger, SetLoggerLevel_Enum)
{
    // Test all enum logging levels
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel(ostk::core::Logger::Level::Trace));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel(ostk::core::Logger::Level::Debug));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel(ostk::core::Logger::Level::Info));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel(ostk::core::Logger::Level::Warning));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel(ostk::core::Logger::Level::Error));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel(ostk::core::Logger::Level::Fatal));
}

TEST(OpenSpaceToolkit_Core_Logger, SetLoggerLeve_String)
{
    // Test all string logging levels
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("trace"));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("debug"));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("info"));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("warning"));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("error"));
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("fatal"));
    
    // Test with invalid level - should default to info
    EXPECT_NO_THROW(ostk::core::Logger::SetLoggerLevel("invalid_level"));
}

TEST(OpenSpaceToolkit_Core_Logger, StringFromLevel)
{
    EXPECT_EQ(Logger::StringFromLevel(Logger::Level::Trace), "Trace");
    EXPECT_EQ(Logger::StringFromLevel(Logger::Level::Debug), "Debug");
    EXPECT_EQ(Logger::StringFromLevel(Logger::Level::Info), "Info");
    EXPECT_EQ(Logger::StringFromLevel(Logger::Level::Warning), "Warning");
    EXPECT_EQ(Logger::StringFromLevel(Logger::Level::Error), "Error");
    EXPECT_EQ(Logger::StringFromLevel(Logger::Level::Fatal), "Fatal");
}

TEST(OpenSpaceToolkit_Core_Logger, LevelFromString)
{
    EXPECT_EQ(Logger::LevelFromString("trace"), Logger::Level::Trace);
    EXPECT_EQ(Logger::LevelFromString("debug"), Logger::Level::Debug);
    EXPECT_EQ(Logger::LevelFromString("info"), Logger::Level::Info);
    EXPECT_EQ(Logger::LevelFromString("warning"), Logger::Level::Warning);
    EXPECT_EQ(Logger::LevelFromString("error"), Logger::Level::Error);
    EXPECT_EQ(Logger::LevelFromString("fatal"), Logger::Level::Fatal);
    
    // Test invalid string defaults to Info
    EXPECT_EQ(Logger::LevelFromString("invalid_level"), Logger::Level::Info);
}

TEST(OpenSpaceToolkit_Core_Logger, LoggingFunctionality)
{
    // Set log level to error using enum
    Logger::SetLoggerLevel(Logger::Level::Error);
    
    // Capture stderr to verify logging output
    testing::internal::CaptureStdout();
    
    BOOST_LOG_TRIVIAL(trace) << "Trace message";   // Should not appear
    BOOST_LOG_TRIVIAL(debug) << "Debug message";   // Should not appear
    BOOST_LOG_TRIVIAL(info) << "Info message";     // Should not appear
    BOOST_LOG_TRIVIAL(warning) << "Warning message"; // Should not appear
    BOOST_LOG_TRIVIAL(error) << "Error message";   // Should appear
    BOOST_LOG_TRIVIAL(fatal) << "Fatal message";   // Should appear
    
    std::string output = testing::internal::GetCapturedStdout();

    // Verify that only error and fatal messages are present
    EXPECT_EQ(std::count(output.begin(), output.end(), '\n'), 2);
    EXPECT_NE(output.find("Error message"), std::string::npos);
    EXPECT_NE(output.find("Fatal message"), std::string::npos);
    
    // Verify that debug message is not present
    EXPECT_EQ(output.find("Debug message"), std::string::npos);
}
