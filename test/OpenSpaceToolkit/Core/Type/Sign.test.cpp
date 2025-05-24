/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Sign.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Type_Sign, DefaultConstructor)
{
    using ostk::core::type::Sign;

    EXPECT_NO_THROW(Sign sign = Sign::Undefined; (void)sign;);
    EXPECT_NO_THROW(Sign sign = Sign::Positive; (void)sign;);
    EXPECT_NO_THROW(Sign sign = Sign::Negative; (void)sign;);
    EXPECT_NO_THROW(Sign sign = Sign::None; (void)sign;);
}

TEST(OpenSpaceToolkit_Core_Type_Sign, StringFromEnum_Test)
{
    using ostk::core::type::Sign;
    using ostk::core::type::String;
    using ostk::core::type::StringFromEnum; // Updated function name

    EXPECT_EQ("Undefined", StringFromEnum(Sign::Undefined));
    EXPECT_EQ("Positive", StringFromEnum(Sign::Positive));
    EXPECT_EQ("Negative", StringFromEnum(Sign::Negative));
    EXPECT_EQ("None", StringFromEnum(Sign::None));
}

TEST(OpenSpaceToolkit_Core_Type_Sign, EnumFromString_ValidInputs_Test)
{
    using ostk::core::type::Sign;
    using ostk::core::type::String;
    using ostk::core::type::EnumFromString;

    std::optional<Sign> undefinedResult = EnumFromString("Undefined");
    ASSERT_TRUE(undefinedResult.has_value());
    EXPECT_EQ(Sign::Undefined, undefinedResult.value());

    std::optional<Sign> positiveResult = EnumFromString("Positive");
    ASSERT_TRUE(positiveResult.has_value());
    EXPECT_EQ(Sign::Positive, positiveResult.value());

    std::optional<Sign> negativeResult = EnumFromString("Negative");
    ASSERT_TRUE(negativeResult.has_value());
    EXPECT_EQ(Sign::Negative, negativeResult.value());

    std::optional<Sign> noneResult = EnumFromString("None");
    ASSERT_TRUE(noneResult.has_value());
    EXPECT_EQ(Sign::None, noneResult.value());
}

TEST(OpenSpaceToolkit_Core_Type_Sign, EnumFromString_InvalidInputs_Test)
{
    using ostk::core::type::Sign;
    using ostk::core::type::String;
    using ostk::core::type::EnumFromString;

    EXPECT_FALSE(EnumFromString("InvalidInput").has_value());
    EXPECT_FALSE(EnumFromString("").has_value());
    EXPECT_FALSE(EnumFromString("positive").has_value()); // Case-sensitive
    EXPECT_FALSE(EnumFromString("UNDEFINED").has_value()); // Case-sensitive
}
