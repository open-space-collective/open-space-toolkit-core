/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Container_Triple, Constructor)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Triple;

    {
        const Triple<bool, Integer, String> triple = {true, 123, "abc"};
    }
}

TEST(OpenSpaceToolkit_Core_Container_Triple, Getters)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Triple;

    {
        const Triple<bool, Integer, String> triple = {true, 123, "abc"};

        EXPECT_EQ(true, triple.first);
        EXPECT_EQ(123, triple.second);
        EXPECT_EQ("abc", triple.third);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Triple, Setters)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Triple;

    {
        Triple<bool, Integer, String> triple = {true, 123, "abc"};

        EXPECT_EQ(true, triple.first);
        EXPECT_EQ(123, triple.second);
        EXPECT_EQ("abc", triple.third);

        triple.first = false;
        triple.second = 456;
        triple.third = "def";

        EXPECT_EQ(false, triple.first);
        EXPECT_EQ(456, triple.second);
        EXPECT_EQ("def", triple.third);
    }
}

// TEST (OpenSpaceToolkit_Core_Container_Triple, Unpack)
// {

//     using ostk::core::type::Integer ;
//     using ostk::core::type::String ;
//     using ostk::core::container::Triple ;
//     using ostk::core::container::Unpack ;

//     {

//         const Triple<bool, Integer, String> triple = {true, 123, "abc"} ;

//         bool boolean = false ;
//         Integer integer = Integer::Undefined() ;
//         String string = String::Empty() ;

//         Unpack(boolean, integer, string) = triple ;

//         EXPECT_EQ(true, boolean) ;
//         EXPECT_EQ(123, integer) ;
//         EXPECT_EQ("abc", string) ;

//     }

// }
