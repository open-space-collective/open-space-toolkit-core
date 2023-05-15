/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Types/Sign.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Types_Sign, DefaultConstructor)
{
    using ostk::core::types::Sign;

    EXPECT_NO_THROW(Sign sign = Sign::Undefined; (void)sign;);
    EXPECT_NO_THROW(Sign sign = Sign::Positive; (void)sign;);
    EXPECT_NO_THROW(Sign sign = Sign::Negative; (void)sign;);
    EXPECT_NO_THROW(Sign sign = Sign::None; (void)sign;);
}
