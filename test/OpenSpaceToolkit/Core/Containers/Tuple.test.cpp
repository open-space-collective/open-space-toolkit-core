/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Tuple.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Containers_Tuple, Constructor)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::containers::Tuple;

    {
        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"};
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Tuple, Getters)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::containers::Tuple;

    {
        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"};

        EXPECT_EQ(123, std::get<0>(tuple));
        EXPECT_EQ("abc", std::get<1>(tuple));
        EXPECT_EQ(456, std::get<2>(tuple));
        EXPECT_EQ("def", std::get<3>(tuple));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Tuple, Setters)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::containers::Tuple;

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

TEST(OpenSpaceToolkit_Core_Containers_Tuple, Unpack)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::containers::Tuple;
    using ostk::core::containers::Unpack;

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
