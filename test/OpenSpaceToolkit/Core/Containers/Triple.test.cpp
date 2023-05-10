/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Containers_Triple, Constructor)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Triple;

    {
        const Triple<bool, Integer, String> triple = {true, 123, "abc"};
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Triple, Getters)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Triple;

    {
        const Triple<bool, Integer, String> triple = {true, 123, "abc"};

        EXPECT_EQ(true, triple.first);
        EXPECT_EQ(123, triple.second);
        EXPECT_EQ("abc", triple.third);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Triple, Setters)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Triple;

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

// TEST (OpenSpaceToolkit_Core_Containers_Triple, Unpack)
// {

//     using ostk::core::types::Integer ;
//     using ostk::core::types::String ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Unpack ;

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
