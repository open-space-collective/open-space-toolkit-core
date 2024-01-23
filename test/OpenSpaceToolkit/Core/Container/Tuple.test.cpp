/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Container_Tuple, Constructor)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Tuple;

    {
        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"};
    }
}

TEST(OpenSpaceToolkit_Core_Container_Tuple, Getters)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Tuple;

    {
        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"};

        EXPECT_EQ(123, std::get<0>(tuple));
        EXPECT_EQ("abc", std::get<1>(tuple));
        EXPECT_EQ(456, std::get<2>(tuple));
        EXPECT_EQ("def", std::get<3>(tuple));
    }
}

TEST(OpenSpaceToolkit_Core_Container_Tuple, Setters)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Tuple;

    {
        Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"};

        EXPECT_EQ(123, std::get<0>(tuple));
        EXPECT_EQ("abc", std::get<1>(tuple));
        EXPECT_EQ(456, std::get<2>(tuple));
        EXPECT_EQ("def", std::get<3>(tuple));

        std::get<2>(tuple) = 789;
        std::get<3>(tuple) = "ghi";

        EXPECT_EQ(123, std::get<0>(tuple));
        EXPECT_EQ("abc", std::get<1>(tuple));
        EXPECT_EQ(789, std::get<2>(tuple));
        EXPECT_EQ("ghi", std::get<3>(tuple));
    }
}

TEST(OpenSpaceToolkit_Core_Container_Tuple, Unpack)
{
    using ostk::core::type::Integer;
    using ostk::core::type::String;
    using ostk::core::container::Tuple;
    using ostk::core::container::Unpack;

    {
        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"};

        Integer firstInteger = Integer::Undefined();
        Integer secondInteger = Integer::Undefined();
        String firstString = String::Empty();
        String secondString = String::Empty();

        Unpack(firstInteger, firstString, secondInteger, secondString) = tuple;

        EXPECT_EQ(123, firstInteger);
        EXPECT_EQ(456, secondInteger);
        EXPECT_EQ("abc", firstString);
        EXPECT_EQ("def", secondString);
    }
}
