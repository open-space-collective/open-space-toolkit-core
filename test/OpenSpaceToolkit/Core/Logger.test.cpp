/// Apache License 2.0

#include <sstream>
#include <thread>

#include <OpenSpaceToolkit/Core/Logger.hpp>
#include <OpenSpaceToolkit/Core/Logger/Pump.hpp>
#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>
#include <OpenSpaceToolkit/Core/Logger/Sink.hpp>
#include <OpenSpaceToolkit/Core/Logger/Source.hpp>

#include <Global.test.hpp>

using ostk::core::Logger;

namespace logger = ostk::core::logger;

using Pump = logger::Pump;
using Severity = logger::Severity;
using Sink = logger::Sink;
using Source = logger::Source;

// ------------------------------------------------------------------------------------------------
// Logger Tests
// ------------------------------------------------------------------------------------------------

TEST(OpenSpaceToolkit_Core_Logger, Constructor)
{
    {
        EXPECT_NO_THROW(Logger logger("TestChannel"));
    }

    {
        EXPECT_NO_THROW(Logger logger(""));
    }

    {
        EXPECT_NO_THROW(Logger logger("My.Module.Name"));
    }

    {
        EXPECT_NO_THROW(Logger logger("Channel-With-Dashes"));
    }

    {
        EXPECT_NO_THROW(Logger logger("Channel_With_Underscores"));
    }
}

TEST(OpenSpaceToolkit_Core_Logger, GetChannel)
{
    {
        Logger logger("TestChannel");
        EXPECT_EQ("TestChannel", logger.getChannel());
    }

    {
        Logger logger("");
        EXPECT_EQ("", logger.getChannel());
    }

    {
        Logger logger("My.Module.Name");
        EXPECT_EQ("My.Module.Name", logger.getChannel());
    }

    {
        Logger logger("Astrodynamics");
        EXPECT_EQ("Astrodynamics", logger.getChannel());
    }
}

TEST(OpenSpaceToolkit_Core_Logger, Console_SingleArg)
{
    {
        EXPECT_NO_THROW(Logger logger = Logger::Console(Severity::Trace));
    }

    {
        EXPECT_NO_THROW(Logger logger = Logger::Console(Severity::Debug));
    }

    {
        EXPECT_NO_THROW(Logger logger = Logger::Console(Severity::Info));
    }

    {
        EXPECT_NO_THROW(Logger logger = Logger::Console(Severity::Warning));
    }

    {
        EXPECT_NO_THROW(Logger logger = Logger::Console(Severity::Error));
    }

    {
        EXPECT_NO_THROW(Logger logger = Logger::Console(Severity::Fatal));
    }
}

TEST(OpenSpaceToolkit_Core_Logger, Console_TwoArgs)
{
    {
        EXPECT_NO_THROW(Logger logger = Logger::Console("MyChannel", Severity::Debug));
    }

    {
        Logger logger = Logger::Console("MyChannel", Severity::Info);
        EXPECT_EQ("MyChannel", logger.getChannel());
    }

    {
        Logger logger = Logger::Console("Astrodynamics", Severity::Warning);
        EXPECT_EQ("Astrodynamics", logger.getChannel());
    }

    {
        Logger logger = Logger::Console("Physics.Gravity", Severity::Error);
        EXPECT_EQ("Physics.Gravity", logger.getChannel());
    }
}

TEST(OpenSpaceToolkit_Core_Logger, Global)
{
    {
        EXPECT_NO_THROW({ Logger& logger = Logger::Global(); (void)logger; });
    }

    {
        // Global logger should be a singleton
        Logger& logger1 = Logger::Global();
        Logger& logger2 = Logger::Global();

        EXPECT_EQ(&logger1, &logger2);
    }

    {
        // Global logger should have "Global" channel
        Logger& logger = Logger::Global();
        EXPECT_EQ("Global", logger.getChannel());
    }
}

TEST(OpenSpaceToolkit_Core_Logger, SetGlobalSeverity)
{
    {
        EXPECT_NO_THROW(Logger::SetGlobalSeverity(Severity::Trace));
    }

    {
        EXPECT_NO_THROW(Logger::SetGlobalSeverity(Severity::Debug));
    }

    {
        EXPECT_NO_THROW(Logger::SetGlobalSeverity(Severity::Info));
    }

    {
        EXPECT_NO_THROW(Logger::SetGlobalSeverity(Severity::Warning));
    }

    {
        EXPECT_NO_THROW(Logger::SetGlobalSeverity(Severity::Error));
    }

    {
        EXPECT_NO_THROW(Logger::SetGlobalSeverity(Severity::Fatal));
    }

    // Reset to debug
    Logger::SetGlobalSeverity(Severity::Debug);
}

TEST(OpenSpaceToolkit_Core_Logger, GetGlobalSeverity)
{
    {
        Logger::SetGlobalSeverity(Severity::Trace);
        EXPECT_EQ(Severity::Trace, Logger::GetGlobalSeverity());
    }

    {
        Logger::SetGlobalSeverity(Severity::Debug);
        EXPECT_EQ(Severity::Debug, Logger::GetGlobalSeverity());
    }

    {
        Logger::SetGlobalSeverity(Severity::Info);
        EXPECT_EQ(Severity::Info, Logger::GetGlobalSeverity());
    }

    {
        Logger::SetGlobalSeverity(Severity::Warning);
        EXPECT_EQ(Severity::Warning, Logger::GetGlobalSeverity());
    }

    {
        Logger::SetGlobalSeverity(Severity::Error);
        EXPECT_EQ(Severity::Error, Logger::GetGlobalSeverity());
    }

    {
        Logger::SetGlobalSeverity(Severity::Fatal);
        EXPECT_EQ(Severity::Fatal, Logger::GetGlobalSeverity());
    }

    // Reset to debug for other tests
    Logger::SetGlobalSeverity(Severity::Debug);
}

TEST(OpenSpaceToolkit_Core_Logger, AddSink)
{
    {
        Logger logger("Test");
        Sink consoleSink = Sink::Console(Severity::Debug);
        EXPECT_NO_THROW(logger.addSink(consoleSink));
    }

    {
        Logger logger("Test");
        EXPECT_NO_THROW(logger.addSink(Sink::Console(Severity::Info)));
        EXPECT_NO_THROW(logger.addSink(Sink::Console(Severity::Warning)));
    }
}

TEST(OpenSpaceToolkit_Core_Logger, StreamOperator)
{
    {
        Logger logger = Logger::Console("Test", Severity::Debug);
        EXPECT_NO_THROW(logger << "Test message");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Debug);
        EXPECT_NO_THROW(logger << "Value: " << 42);
    }

    {
        Logger logger = Logger::Console("Test", Severity::Debug);
        EXPECT_NO_THROW(logger << "Float: " << 3.14159);
    }

    {
        Logger logger = Logger::Console("Test", Severity::Debug);
        EXPECT_NO_THROW(logger << "Multiple " << "strings " << "concatenated");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Debug);
        EXPECT_NO_THROW(logger << "Mixed: " << 42 << " and " << 3.14 << " and " << "text");
    }
}

TEST(OpenSpaceToolkit_Core_Logger, LogMacros)
{
    {
        Logger logger = Logger::Console("Test", Severity::Trace);
        EXPECT_NO_THROW(LOG_TRACE(logger) << "Trace message");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Debug);
        EXPECT_NO_THROW(LOG_DEBUG(logger) << "Debug message");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Info);
        EXPECT_NO_THROW(LOG_INFO(logger) << "Info message");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Warning);
        EXPECT_NO_THROW(LOG_WARNING(logger) << "Warning message");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Error);
        EXPECT_NO_THROW(LOG_ERROR(logger) << "Error message");
    }

    {
        Logger logger = Logger::Console("Test", Severity::Fatal);
        EXPECT_NO_THROW(LOG_FATAL(logger) << "Fatal message");
    }
}

TEST(OpenSpaceToolkit_Core_Logger, LogMacros_WithValues)
{
    Logger logger = Logger::Console("Test", Severity::Debug);

    {
        int value = 42;
        EXPECT_NO_THROW(LOG_DEBUG(logger) << "Integer value: " << value);
    }

    {
        double value = 3.14159;
        EXPECT_NO_THROW(LOG_INFO(logger) << "Double value: " << value);
    }

    {
        std::string value = "test string";
        EXPECT_NO_THROW(LOG_WARNING(logger) << "String value: " << value);
    }

    {
        bool value = true;
        EXPECT_NO_THROW(LOG_ERROR(logger) << "Boolean value: " << value);
    }
}

TEST(OpenSpaceToolkit_Core_Logger, GlobalLogMacros)
{
    {
        EXPECT_NO_THROW(GLOBAL_LOG_TRACE << "Trace message");
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_DEBUG << "Debug message");
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_INFO << "Info message");
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_WARNING << "Warning message");
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_ERROR << "Error message");
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_FATAL << "Fatal message");
    }
}

TEST(OpenSpaceToolkit_Core_Logger, GlobalLogMacros_WithValues)
{
    {
        EXPECT_NO_THROW(GLOBAL_LOG_DEBUG << "Value: " << 42);
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_INFO << "Pi: " << 3.14159);
    }

    {
        EXPECT_NO_THROW(GLOBAL_LOG_WARNING << "Message: " << "warning text");
    }

    {
        std::vector<int> vec = {1, 2, 3};
        EXPECT_NO_THROW(GLOBAL_LOG_DEBUG << "Vector size: " << vec.size());
    }
}

TEST(OpenSpaceToolkit_Core_Logger, LogScope)
{
    {
        EXPECT_NO_THROW({ LOG_SCOPE_DEFAULT(); });
    }

    {
        EXPECT_NO_THROW({ LOG_SCOPE_NAMED("TestScope"); });
    }

    {
        EXPECT_NO_THROW({ LOG_SCOPE("TestClass", "TestMethod"); });
    }
}

TEST(OpenSpaceToolkit_Core_Logger, ThreadSafety)
{
    Logger& logger = Logger::Global();

    auto logFunction = [&logger](int threadId)
    {
        for (int i = 0; i < 10; ++i)
        {
            LOG_DEBUG(logger) << "Thread " << threadId << " iteration " << i;
        }
    };

    std::vector<std::thread> threads;

    for (int i = 0; i < 4; ++i)
    {
        threads.emplace_back(logFunction, i);
    }

    for (auto& thread : threads)
    {
        EXPECT_NO_THROW(thread.join());
    }
}

// ------------------------------------------------------------------------------------------------
// Severity Tests
// ------------------------------------------------------------------------------------------------

TEST(OpenSpaceToolkit_Core_Logger_Severity, Values)
{
    {
        EXPECT_TRUE(Severity::Trace < Severity::Debug);
        EXPECT_TRUE(Severity::Debug < Severity::Info);
        EXPECT_TRUE(Severity::Info < Severity::Warning);
        EXPECT_TRUE(Severity::Warning < Severity::Error);
        EXPECT_TRUE(Severity::Error < Severity::Fatal);
    }

    {
        EXPECT_FALSE(Severity::Debug < Severity::Trace);
        EXPECT_FALSE(Severity::Info < Severity::Debug);
        EXPECT_FALSE(Severity::Warning < Severity::Info);
        EXPECT_FALSE(Severity::Error < Severity::Warning);
        EXPECT_FALSE(Severity::Fatal < Severity::Error);
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Severity, Comparison)
{
    {
        EXPECT_TRUE(Severity::Trace <= Severity::Trace);
        EXPECT_TRUE(Severity::Debug <= Severity::Debug);
        EXPECT_TRUE(Severity::Info <= Severity::Info);
    }

    {
        EXPECT_TRUE(Severity::Trace >= Severity::Trace);
        EXPECT_TRUE(Severity::Fatal >= Severity::Error);
        EXPECT_TRUE(Severity::Fatal >= Severity::Trace);
    }
}

// ------------------------------------------------------------------------------------------------
// Sink Tests
// ------------------------------------------------------------------------------------------------

TEST(OpenSpaceToolkit_Core_Logger_Sink, Console)
{
    {
        EXPECT_NO_THROW(Sink sink = Sink::Console(Severity::Debug));
    }

    {
        EXPECT_NO_THROW(Sink sink = Sink::Console(Severity::Info));
    }

    {
        EXPECT_NO_THROW(Sink sink = Sink::Console(Severity::Warning));
    }

    {
        EXPECT_NO_THROW(Sink sink = Sink::Console(Severity::Error));
    }

    {
        EXPECT_NO_THROW(Sink sink = Sink::Console(Severity::Fatal));
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Sink, EnableDisable)
{
    {
        Sink sink = Sink::Console(Severity::Debug);
        EXPECT_NO_THROW(sink.enable());
        EXPECT_NO_THROW(sink.disable());
        EXPECT_NO_THROW(sink.enable());
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Sink, AddRemoveChannel)
{
    {
        Sink sink = Sink::Console(Severity::Debug);
        EXPECT_NO_THROW(sink.addChannel("TestChannel"));
        EXPECT_NO_THROW(sink.addChannel("AnotherChannel"));
        EXPECT_NO_THROW(sink.removeChannel("TestChannel"));
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Sink, CopyConstructor)
{
    {
        Sink sink1 = Sink::Console(Severity::Debug);
        EXPECT_NO_THROW(Sink sink2(sink1));
    }
}

// ------------------------------------------------------------------------------------------------
// Source Tests
// ------------------------------------------------------------------------------------------------

TEST(OpenSpaceToolkit_Core_Logger_Source, Constructor)
{
    {
        EXPECT_NO_THROW(Source source("TestChannel"));
    }

    {
        EXPECT_NO_THROW(Source source(""));
    }

    {
        EXPECT_NO_THROW(Source source("My.Module.Name"));
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Source, IsDefined)
{
    {
        Source source("TestChannel");
        EXPECT_TRUE(source.isDefined());
    }

    {
        Source source = Source::Undefined();
        EXPECT_FALSE(source.isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Source, CopyConstructor)
{
    {
        Source source1("TestChannel");
        Source source2(source1);
        EXPECT_TRUE(source2.isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Source, AssignmentOperator)
{
    {
        Source source1("Channel1");
        Source source2("Channel2");
        source2 = source1;
        EXPECT_TRUE(source2.isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_Logger_Source, Undefined)
{
    {
        Source source = Source::Undefined();
        EXPECT_FALSE(source.isDefined());
    }
}
