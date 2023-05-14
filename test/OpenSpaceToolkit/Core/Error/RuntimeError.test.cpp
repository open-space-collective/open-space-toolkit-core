/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Error_RuntimeError, Constructor)
{
    using ostk::core::error::RuntimeError;

    {
        EXPECT_THROW(throw RuntimeError("This is a test."), RuntimeError);
        // EXPECT_THROW(throw RuntimeError("This is a scope.", "This is a test."), RuntimeError) ;

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
            EXPECT_EQ("This is a test.", std::string(anError.what()));
        }

        // try
        // {
        //     throw RuntimeError("This is a scope.", "This is a test.") ;
        // }
        // catch (const RuntimeError& anError)
        // {
        //     EXPECT_EQ("This is a scope.", anError.getScope()) ;
        //     EXPECT_EQ("This is a test.", std::string(anError.what())) ;
        // }

        try
        {
            throw RuntimeError("This is a list [{}, {}, {}].", 123, 456, 789);
        }
        catch (const RuntimeError& anError)
        {
            EXPECT_EQ("", anError.getScope());
            EXPECT_EQ("This is a list [123, 456, 789].", std::string(anError.what()));
        }
    }
}
