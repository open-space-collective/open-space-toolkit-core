/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Error_RuntimeError, Constructor)
{
    using ostk::core::error::RuntimeError;

    {
        EXPECT_THROW(throw RuntimeError("This is a test."), RuntimeError);

        EXPECT_THROW(throw RuntimeError("This is a list [{}, {}, {}].", 123, 456, 789), RuntimeError);
    }

    {
        try
        {
            throw RuntimeError("This is a test.");
        }
        catch (const RuntimeError& anError)
        {
            EXPECT_EQ("", anError.getScope());
            EXPECT_EQ("This is a test.", anError.getMessage());

            EXPECT_FALSE(anError.getStackTrace().empty());
            EXPECT_EQ(anError.getStackTrace().getHead(3), " 0#");

            EXPECT_EQ(anError.getStackTrace() + anError.getMessage(), std::string(anError.what()));
        }

        try
        {
            throw RuntimeError("This is a list [{}, {}, {}].", 123, 456, 789);
        }
        catch (const RuntimeError& anError)
        {
            EXPECT_EQ("", anError.getScope());
            EXPECT_EQ("This is a list [123, 456, 789].", anError.getMessage());

            EXPECT_FALSE(anError.getStackTrace().empty());
            EXPECT_EQ(anError.getStackTrace().getHead(3), " 0#");

            EXPECT_EQ(anError.getStackTrace() + anError.getMessage(), std::string(anError.what()));
        }
    }
}
