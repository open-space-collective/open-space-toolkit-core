/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Container_Pair, Constructor)
{
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;
    using ostk::core::type::String;

    {
        const Pair<Integer, String> pair = {123, "abc"};
    }
}

TEST(OpenSpaceToolkit_Core_Container_Pair, Getters)
{
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;
    using ostk::core::type::String;

    {
        const Pair<Integer, String> pair = {123, "abc"};

        EXPECT_EQ(123, pair.first);
        EXPECT_EQ("abc", pair.second);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Pair, Setters)
{
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;
    using ostk::core::type::String;

    {
        Pair<Integer, String> pair = {123, "abc"};

        EXPECT_EQ(123, pair.first);
        EXPECT_EQ("abc", pair.second);

        pair.first = 456;
        pair.second = "def";

        EXPECT_EQ(456, pair.first);
        EXPECT_EQ("def", pair.second);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Pair, Unpack)
{
    using ostk::core::container::Pair;
    using ostk::core::container::Unpack;
    using ostk::core::type::Integer;
    using ostk::core::type::String;

    {
        const Pair<Integer, String> pair = {123, "abc"};

        Integer integer = Integer(0);
        String string = String::Empty();

        Unpack(integer, string) = pair;

        EXPECT_EQ(123, integer);
        EXPECT_EQ("abc", string);
    }
}
