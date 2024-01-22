/// Apache License 2.0

#include <cmath>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>
#include <OpenSpaceToolkit/Core/Containers/Triple.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Types_Real, DefaultConstructor)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real(0.0));
    EXPECT_NO_THROW(Real(1.0));
    EXPECT_NO_THROW(Real(123.0));
    EXPECT_NO_THROW(Real(+123.0));
    EXPECT_NO_THROW(Real(-123.0));
}

TEST(OpenSpaceToolkit_Core_Types_Real, AssignmentOperator)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real a = 0.0; (void)a;);
    EXPECT_NO_THROW(Real a = 0.0; (void)a;);
    EXPECT_NO_THROW(Real a = 1.0; (void)a;);
    EXPECT_NO_THROW(Real a = 123.0; (void)a;);
    EXPECT_NO_THROW(Real a = +123.0; (void)a;);
    EXPECT_NO_THROW(Real a = -123.0; (void)a;);
}

TEST(OpenSpaceToolkit_Core_Types_Real, EqualToOperator)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0) == Real(0.0));
        EXPECT_TRUE(Real(123.0) == Real(123.0));
        EXPECT_TRUE(Real(+123.0) == Real(+123.0));
        EXPECT_TRUE(Real(-123.0) == Real(-123.0));
    }

    {
        EXPECT_FALSE(Real(0.0) == Real(1.0));
        EXPECT_FALSE(Real(1.0) == Real(0.0));
        EXPECT_FALSE(Real(-1.0) == Real(+1.0));

        EXPECT_FALSE(Real::Undefined() == Real::Undefined());
        EXPECT_FALSE(Real::PositiveInfinity() == Real::PositiveInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() == Real::NegativeInfinity());
        EXPECT_FALSE(Real::PositiveInfinity() == Real::NegativeInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() == Real::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, NotEqualToOperator)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0) != Real(1.0));
        EXPECT_TRUE(Real(1.0) != Real(0.0));
        EXPECT_TRUE(Real(-1.0) != Real(+1.0));
    }

    {
        EXPECT_FALSE(Real(0.0) != Real(0.0));
        EXPECT_FALSE(Real(123.0) != Real(123.0));
        EXPECT_FALSE(Real(+123.0) != Real(+123.0));
        EXPECT_FALSE(Real(-123.0) != Real(-123.0));

        EXPECT_FALSE(Real::Undefined() != Real::Undefined());
        EXPECT_FALSE(Real::PositiveInfinity() != Real::PositiveInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() != Real::NegativeInfinity());
        EXPECT_FALSE(Real::PositiveInfinity() != Real::NegativeInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() != Real::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, LessThanOperator)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0) < Real(1.0));
        EXPECT_TRUE(Real(1.0) < Real(2.0));
        EXPECT_TRUE(Real(-1.0) < Real(0.0));
        EXPECT_TRUE(Real(-1.0) < Real(+1.0));
        EXPECT_TRUE(Real(-123.0) < Real(+123.0));
    }

    {
        EXPECT_FALSE(Real(0.0) < Real(0.0));
        EXPECT_FALSE(Real(1.0) < Real(0.0));
        EXPECT_FALSE(Real(+1.0) < Real(-1.0));
        EXPECT_FALSE(Real(+123.0) < Real(-123.0));
        EXPECT_FALSE(Real(+123.0) < Real(+123.0));
        EXPECT_FALSE(Real(-123.0) < Real(-123.0));

        EXPECT_FALSE(Real::Undefined() < Real::Undefined());
        EXPECT_FALSE(Real::PositiveInfinity() < Real::PositiveInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() < Real::NegativeInfinity());
        EXPECT_FALSE(Real::PositiveInfinity() < Real::NegativeInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() < Real::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, LessThanOrEqualToOperator)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0) <= Real(1.0));
        EXPECT_TRUE(Real(1.0) <= Real(2.0));
        EXPECT_TRUE(Real(-1.0) <= Real(0.0));
        EXPECT_TRUE(Real(-1.0) <= Real(+1.0));
        EXPECT_TRUE(Real(-123.0) <= Real(+123.0));
        EXPECT_TRUE(Real(0.0) <= Real(0.0));
        EXPECT_TRUE(Real(+123.0) <= Real(+123.0));
        EXPECT_TRUE(Real(-123.0) <= Real(-123.0));
    }

    {
        EXPECT_FALSE(Real(1.0) <= Real(0.0));
        EXPECT_FALSE(Real(+1.0) <= Real(-1.0));
        EXPECT_FALSE(Real(+123.0) <= Real(-123.0));

        EXPECT_FALSE(Real::Undefined() <= Real::Undefined());
        EXPECT_FALSE(Real::PositiveInfinity() <= Real::PositiveInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() <= Real::NegativeInfinity());
        EXPECT_FALSE(Real::PositiveInfinity() <= Real::NegativeInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() <= Real::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, GreaterThanOperator)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(1.0) > Real(0.0));
        EXPECT_TRUE(Real(2.0) > Real(1.0));
        EXPECT_TRUE(Real(+1.0) > Real(0.0));
        EXPECT_TRUE(Real(+1.0) > Real(-1.0));
        EXPECT_TRUE(Real(+123.0) > Real(-123.0));
    }

    {
        EXPECT_FALSE(Real(0.0) > Real(0.0));
        EXPECT_FALSE(Real(0.0) > Real(1.0));
        EXPECT_FALSE(Real(-1.0) > Real(+1.0));
        EXPECT_FALSE(Real(-123.0) > Real(+123.0));
        EXPECT_FALSE(Real(+123.0) > Real(+123.0));
        EXPECT_FALSE(Real(-123.0) > Real(-123.0));

        EXPECT_FALSE(Real::Undefined() > Real::Undefined());
        EXPECT_FALSE(Real::PositiveInfinity() > Real::PositiveInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() > Real::NegativeInfinity());
        EXPECT_FALSE(Real::PositiveInfinity() > Real::NegativeInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() > Real::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, GreaterThanOrEqualToOperator)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(1.0) >= Real(0.0));
        EXPECT_TRUE(Real(2.0) >= Real(1.0));
        EXPECT_TRUE(Real(+1.0) >= Real(0.0));
        EXPECT_TRUE(Real(+1.0) >= Real(-1.0));
        EXPECT_TRUE(Real(+123.0) >= Real(-123.0));
        EXPECT_TRUE(Real(0.0) >= Real(0.0));
        EXPECT_TRUE(Real(+123.0) >= Real(+123.0));
        EXPECT_TRUE(Real(-123.0) >= Real(-123.0));
    }

    {
        EXPECT_FALSE(Real(0.0) >= Real(1.0));
        EXPECT_FALSE(Real(-1.0) >= Real(+1.0));
        EXPECT_FALSE(Real(-123.0) >= Real(+123.0));

        EXPECT_FALSE(Real::Undefined() >= Real::Undefined());
        EXPECT_FALSE(Real::PositiveInfinity() >= Real::PositiveInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() >= Real::NegativeInfinity());
        EXPECT_FALSE(Real::PositiveInfinity() >= Real::NegativeInfinity());
        EXPECT_FALSE(Real::NegativeInfinity() >= Real::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, AdditionOperator)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Triple;
    using ostk::core::ctnr::Array;

    Array<Triple<Real, Real, Real>> testCases = {

        {Real::Undefined(), Real::Undefined(), Real::Undefined()},
        {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
        {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
        {Real::Undefined(), -2.0, Real::Undefined()},
        {Real::Undefined(), -1.0, Real::Undefined()},
        {Real::Undefined(), +0.0, Real::Undefined()},
        {Real::Undefined(), +1.0, Real::Undefined()},
        {Real::Undefined(), +2.0, Real::Undefined()},
        {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
        {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

        {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
        {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::NegativeInfinity()},
        {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
        {Real::NegativeInfinity(), -2.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), -1.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), +0.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
        {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::Undefined()},

        {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
        {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(),
         std::numeric_limits<Real::ValueType>::lowest(),
         Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), +0.0, std::numeric_limits<Real::ValueType>::lowest()},
        {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest() + 1},
        {std::numeric_limits<Real::ValueType>::lowest(), +2.0, std::numeric_limits<Real::ValueType>::lowest() + 2},
        {std::numeric_limits<Real::ValueType>::lowest(),
         std::numeric_limits<Real::ValueType>::max(),
         std::numeric_limits<Real::ValueType>::lowest() + std::numeric_limits<Real::ValueType>::max()},
        {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), Real::PositiveInfinity()},

        {-2.0, Real::Undefined(), Real::Undefined()},
        {-2.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
        {-2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
        {-2.0, -2.0, -4.0},
        {-2.0, -1.0, -3.0},
        {-2.0, +0.0, -2.0},
        {-2.0, +1.0, -1.0},
        {-2.0, +2.0, +0.0},
        {-2.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max() - 2},
        {-2.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

        {-1.0, Real::Undefined(), Real::Undefined()},
        {-1.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
        {-1.0, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
        {-1.0, -2.0, -3.0},
        {-1.0, -1.0, -2.0},
        {-1.0, +0.0, -1.0},
        {-1.0, +1.0, +0.0},
        {-1.0, +2.0, +1.0},
        {-1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max() - 1},
        {-1.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

        {+0.0, Real::Undefined(), Real::Undefined()},
        {+0.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
        {+0.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest()},
        {+0.0, -2.0, -2.0},
        {+0.0, -1.0, -1.0},
        {+0.0, +0.0, +0.0},
        {+0.0, +1.0, +1.0},
        {+0.0, +2.0, +2.0},
        {+0.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max()},
        {+0.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

        {+1.0, Real::Undefined(), Real::Undefined()},
        {+1.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
        {+1.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest() + 1},
        {+1.0, -2.0, -1.0},
        {+1.0, -1.0, +0.0},
        {+1.0, +0.0, +1.0},
        {+1.0, +1.0, +2.0},
        {+1.0, +2.0, +3.0},
        {+1.0, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
        {+1.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

        {+2.0, Real::Undefined(), Real::Undefined()},
        {+2.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
        {+2.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest() + 2},
        {+2.0, -2.0, +0.0},
        {+2.0, -1.0, +1.0},
        {+2.0, +0.0, +2.0},
        {+2.0, +1.0, +3.0},
        {+2.0, +2.0, +4.0},
        {+2.0, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
        {+2.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

        {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
        {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::max(),
         std::numeric_limits<Real::ValueType>::lowest(),
         std::numeric_limits<Real::ValueType>::max() + std::numeric_limits<Real::ValueType>::lowest()},
        {std::numeric_limits<Real::ValueType>::max(), -2.0, std::numeric_limits<Real::ValueType>::max() - 2},
        {std::numeric_limits<Real::ValueType>::max(), -1.0, std::numeric_limits<Real::ValueType>::max() - 1},
        {std::numeric_limits<Real::ValueType>::max(), +0.0, std::numeric_limits<Real::ValueType>::max()},
        {std::numeric_limits<Real::ValueType>::max(), +1.0, Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(),
         std::numeric_limits<Real::ValueType>::max(),
         Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), Real::PositiveInfinity()},

        {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
        {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::Undefined()},
        {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
        {Real::PositiveInfinity(), -2.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), -1.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), +0.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
        {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::PositiveInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Real& a = testCase.first;
        const Real& b = testCase.second;
        const Real& c = testCase.third;

        if (c.isDefined())
        {
            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a + b).isPositiveInfinity());
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a + b).isNegativeInfinity());
            }
            else
            {
                EXPECT_EQ(c, a + b);
            }
        }
        else
        {
            EXPECT_FALSE((a + b).isDefined());
        }
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, SubtractionOperator)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Triple;
    using ostk::core::ctnr::Array;

    Array<Triple<Real, Real, Real>> testCases = {

        {Real::Undefined(), Real::Undefined(), Real::Undefined()},
        {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
        {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
        {Real::Undefined(), -2.0, Real::Undefined()},
        {Real::Undefined(), -1.0, Real::Undefined()},
        {Real::Undefined(), +0.0, Real::Undefined()},
        {Real::Undefined(), +1.0, Real::Undefined()},
        {Real::Undefined(), +2.0, Real::Undefined()},
        {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
        {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

        {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
        {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::Undefined()},
        {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
        {Real::NegativeInfinity(), -2.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), -1.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), +0.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
        {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
        {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::NegativeInfinity()},

        {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
        {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), +0.0},
        {std::numeric_limits<Real::ValueType>::lowest(), -2.0, std::numeric_limits<Real::ValueType>::lowest() + 2},
        {std::numeric_limits<Real::ValueType>::lowest(), -1.0, std::numeric_limits<Real::ValueType>::lowest() + 1},
        {std::numeric_limits<Real::ValueType>::lowest(), +0.0, std::numeric_limits<Real::ValueType>::lowest()},
        {std::numeric_limits<Real::ValueType>::lowest(), +1.0, Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), +2.0, Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(),
         std::numeric_limits<Real::ValueType>::max(),
         Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), Real::NegativeInfinity()},

        {-2.0, Real::Undefined(), Real::Undefined()},
        {-2.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
        {-2.0, std::numeric_limits<Real::ValueType>::lowest(), -2 - std::numeric_limits<Real::ValueType>::lowest()},
        {-2.0, -2.0, +0.0},
        {-2.0, -1.0, -1.0},
        {-2.0, +0.0, -2.0},
        {-2.0, +1.0, -3.0},
        {-2.0, +2.0, -4.0},
        {-2.0, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
        {-2.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

        {-1.0, Real::Undefined(), Real::Undefined()},
        {-1.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
        {-1.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max()},
        {-1.0, -2.0, +1.0},
        {-1.0, -1.0, +0.0},
        {-1.0, +0.0, -1.0},
        {-1.0, +1.0, -2.0},
        {-1.0, +2.0, -3.0},
        {-1.0, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
        {-1.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

        {+0.0, Real::Undefined(), Real::Undefined()},
        {+0.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
        {+0.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
        {+0.0, -2.0, +2.0},
        {+0.0, -1.0, +1.0},
        {+0.0, +0.0, +0.0},
        {+0.0, +1.0, -1.0},
        {+0.0, +2.0, -2.0},
        {+0.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + 1},
        {+0.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

        {+1.0, Real::Undefined(), Real::Undefined()},
        {+1.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
        {+1.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
        {+1.0, -2.0, +3.0},
        {+1.0, -1.0, +2.0},
        {+1.0, +0.0, +1.0},
        {+1.0, +1.0, +0.0},
        {+1.0, +2.0, -1.0},
        {+1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + 2},
        {+1.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

        {+2.0, Real::Undefined(), Real::Undefined()},
        {+2.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
        {+2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
        {+2.0, -2.0, +4.0},
        {+2.0, -1.0, +3.0},
        {+2.0, +0.0, +2.0},
        {+2.0, +1.0, +1.0},
        {+2.0, +2.0, +0.0},
        {+2.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + 3},
        {+2.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

        {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
        {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(),
         std::numeric_limits<Real::ValueType>::lowest(),
         Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), -1.0, Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), +0.0, std::numeric_limits<Real::ValueType>::max()},
        {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max() - 1},
        {std::numeric_limits<Real::ValueType>::max(), +2.0, std::numeric_limits<Real::ValueType>::max() - 2},
        {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), +0.0},
        {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), Real::NegativeInfinity()},

        {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
        {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::PositiveInfinity()},
        {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
        {Real::PositiveInfinity(), -2.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), -1.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), +0.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
        {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
        {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::Undefined()}

    };

    for (const auto& testCase : testCases)
    {
        const Real& a = testCase.first;
        const Real& b = testCase.second;
        const Real& c = testCase.third;

        if (c.isDefined())
        {
            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a - b).isPositiveInfinity());
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a - b).isNegativeInfinity());
            }
            else
            {
                EXPECT_EQ(c, a - b);
            }
        }
        else
        {
            EXPECT_FALSE((a - b).isDefined());
        }
    }
}

// TEST (OpenSpaceToolkit_Core_Types_Real, MultiplicationOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Array ;

//     Array<Triple<Real, Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined(), Real::Undefined()},
//         {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
//         {Real::Undefined(), -2.0, Real::Undefined()},
//         {Real::Undefined(), -1.0, Real::Undefined()},
//         {Real::Undefined(), +0.0, Real::Undefined()},
//         {Real::Undefined(), +1.0, Real::Undefined()},
//         {Real::Undefined(), +2.0, Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
//         {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

//         {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -2.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -1.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), +0.0, Real::Undefined()},
//         {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(),
//         Real::PositiveInfinity()}, {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(),
//         Real::NegativeInfinity()}, {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(),
//         Real::NegativeInfinity()},

//         {-1073741823, Real::Undefined(), Real::Undefined()},
//         {-1073741823, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-1073741823, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-1073741823, -3.0, Real::PositiveInfinity()},
//         {-1073741823, -2.0, +2147483646},
//         {-1073741823, -1.0, +1073741823},
//         {-1073741823, +0.0, +0.0},
//         {-1073741823, +1.0, -1073741823},
//         {-1073741823, +2.0, -2147483646},
//         {-1073741823, +3.0, Real::NegativeInfinity()},
//         {-1073741823, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {-1073741823, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {-2.0, Real::Undefined(), Real::Undefined()},
//         {-2.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-2.0, -2.0, +4.0},
//         {-2.0, -1.0, +2.0},
//         {-2.0, +0.0, +0.0},
//         {-2.0, +1.0, -2.0},
//         {-2.0, +2.0, -4.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {-2.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {-1.0, Real::Undefined(), Real::Undefined()},
//         {-1.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-1.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-1.0, -2.0, +2.0},
//         {-1.0, -1.0, +1.0},
//         {-1.0, +0.0, +0.0},
//         {-1.0, +1.0, -1.0},
//         {-1.0, +2.0, -2.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::max(), -std::numeric_limits<Real::ValueType>::max()},
//         {-1.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {+0.0, Real::Undefined(), Real::Undefined()},
//         {+0.0, Real::NegativeInfinity(), Real::Undefined()},
//         {+0.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+0.0, -2.0, +0.0},
//         {+0.0, -1.0, +0.0},
//         {+0.0, +0.0, +0.0},
//         {+0.0, +1.0, +0.0},
//         {+0.0, +2.0, +0.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+0.0, Real::PositiveInfinity(), Real::Undefined()},

//         {+1.0, Real::Undefined(), Real::Undefined()},
//         {+1.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+1.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest()},
//         {+1.0, -2.0, -2.0},
//         {+1.0, -1.0, -1.0},
//         {+1.0, +0.0, +0.0},
//         {+1.0, +1.0, +1.0},
//         {+1.0, +2.0, +2.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max()},
//         {+1.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+2.0, Real::Undefined(), Real::Undefined()},
//         {+2.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {+2.0, -2.0, -4.0},
//         {+2.0, -1.0, -2.0},
//         {+2.0, +0.0, +0.0},
//         {+2.0, +1.0, +2.0},
//         {+2.0, +2.0, +4.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {+2.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+1073741823, Real::Undefined(), Real::Undefined()},
//         {+1073741823, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+1073741823, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {+1073741823, -3.0, Real::NegativeInfinity()},
//         {+1073741823, -2.0, -2147483646},
//         {+1073741823, -1.0, -1073741823},
//         {+1073741823, +0.0, +0.0},
//         {+1073741823, +1.0, +1073741823},
//         {+1073741823, +2.0, +2147483646},
//         {+1073741823, +3.0, Real::PositiveInfinity()},
//         {+1073741823, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {+1073741823, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(),
//         Real::NegativeInfinity()}, {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, -std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(),
//         Real::PositiveInfinity()}, {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(),
//         Real::PositiveInfinity()},

//         {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -2.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -1.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), +0.0, Real::Undefined()},
//         {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::PositiveInfinity()}

//     } ;

//     for (const auto& testCase : testCases)
//     {

//         const Real& a = testCase.first ;
//         const Real& b = testCase.second ;
//         const Real& c = testCase.third ;

//         if (c.isDefined())
//         {

//             if (c.isPositiveInfinity())
//             {
//                 EXPECT_TRUE((a * b).isPositiveInfinity()) ;
//             }
//             else if (c.isNegativeInfinity())
//             {
//                 EXPECT_TRUE((a * b).isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(c, a * b) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE((a * b).isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, DivisionOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Array ;

//     Array<Triple<Real, Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined(), Real::Undefined()},
//         {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
//         {Real::Undefined(), -2.0, Real::Undefined()},
//         {Real::Undefined(), -1.0, Real::Undefined()},
//         {Real::Undefined(), +0.0, Real::Undefined()},
//         {Real::Undefined(), +1.0, Real::Undefined()},
//         {Real::Undefined(), +2.0, Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
//         {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

//         {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -2.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -1.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), +0.0, Real::Undefined()},
//         {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::Undefined()},

//         {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), 1},
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, std::numeric_limits<Real::ValueType>::lowest() /
//         -2.0}, {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, std::numeric_limits<Real::ValueType>::lowest() / 2},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), -1.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), +0.0},

//         {-2.0, Real::Undefined(), Real::Undefined()},
//         {-2.0, Real::NegativeInfinity(), +0.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {-2.0, -2.0, +1.0},
//         {-2.0, -1.0, +2.0},
//         {-2.0, +0.0, Real::Undefined()},
//         {-2.0, +1.0, -2.0},
//         {-2.0, +2.0, -1.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {-2.0, Real::PositiveInfinity(), +0.0},

//         {-1.0, Real::Undefined(), Real::Undefined()},
//         {-1.0, Real::NegativeInfinity(), +0.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {-1.0, -2.0, +0.0},
//         {-1.0, -1.0, +1.0},
//         {-1.0, +0.0, Real::Undefined()},
//         {-1.0, +1.0, -1.0},
//         {-1.0, +2.0, +0.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {-1.0, Real::PositiveInfinity(), +0.0},

//         {+0.0, Real::Undefined(), Real::Undefined()},
//         {+0.0, Real::NegativeInfinity(), +0.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+0.0, -2.0, +0.0},
//         {+0.0, -1.0, +0.0},
//         {+0.0, +0.0, Real::Undefined()},
//         {+0.0, +1.0, +0.0},
//         {+0.0, +2.0, +0.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+0.0, Real::PositiveInfinity(), +0.0},

//         {+1.0, Real::Undefined(), Real::Undefined()},
//         {+1.0, Real::NegativeInfinity(), +0.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+1.0, -2.0, +0.0},
//         {+1.0, -1.0, -1.0},
//         {+1.0, +0.0, Real::Undefined()},
//         {+1.0, +1.0, +1.0},
//         {+1.0, +2.0, +0.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+1.0, Real::PositiveInfinity(), +0.0},

//         {+2.0, Real::Undefined(), Real::Undefined()},
//         {+2.0, Real::NegativeInfinity(), +0.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+2.0, -2.0, -1.0},
//         {+2.0, -1.0, -2.0},
//         {+2.0, +0.0, Real::Undefined()},
//         {+2.0, +1.0, +2.0},
//         {+2.0, +2.0, +1.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+2.0, Real::PositiveInfinity(), +0.0},

//         {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, std::numeric_limits<Real::ValueType>::max() / -2.0},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, std::numeric_limits<Real::ValueType>::max() / -1.0},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, std::numeric_limits<Real::ValueType>::max() / 2},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), +1.0},
//         {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), +0.0},

//         {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -2.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -1.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), +0.0, Real::Undefined()},
//         {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::Undefined()}

//     } ;

//     for (const auto& testCase : testCases)
//     {

//         const Real& a = testCase.first ;
//         const Real& b = testCase.second ;
//         const Real& c = testCase.third ;

//         if (c.isDefined())
//         {

//             if (c.isPositiveInfinity())
//             {
//                 EXPECT_TRUE((a / b).isPositiveInfinity()) ;
//             }
//             else if (c.isNegativeInfinity())
//             {
//                 EXPECT_TRUE((a / b).isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(c, a / b) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE((a / b).isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, AdditionAssignmentOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Array ;

//     Array<Triple<Real, Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined(), Real::Undefined()},
//         {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
//         {Real::Undefined(), -2.0, Real::Undefined()},
//         {Real::Undefined(), -1.0, Real::Undefined()},
//         {Real::Undefined(), +0.0, Real::Undefined()},
//         {Real::Undefined(), +1.0, Real::Undefined()},
//         {Real::Undefined(), +2.0, Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
//         {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

//         {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), -2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), -1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +0.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::Undefined()},

//         {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(),
//         Real::NegativeInfinity()}, {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest() + 1},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, std::numeric_limits<Real::ValueType>::lowest() + 2},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(),
//         std::numeric_limits<Real::ValueType>::lowest() + std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {-2.0, Real::Undefined(), Real::Undefined()},
//         {-2.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {-2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {-2.0, -2.0, -4.0},
//         {-2.0, -1.0, -3.0},
//         {-2.0, +0.0, -2.0},
//         {-2.0, +1.0, -1.0},
//         {-2.0, +2.0, +0.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max() - 2},
//         {-2.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {-1.0, Real::Undefined(), Real::Undefined()},
//         {-1.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {-1.0, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {-1.0, -2.0, -3.0},
//         {-1.0, -1.0, -2.0},
//         {-1.0, +0.0, -1.0},
//         {-1.0, +1.0, +0.0},
//         {-1.0, +2.0, +1.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max() - 1},
//         {-1.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+0.0, Real::Undefined(), Real::Undefined()},
//         {+0.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+0.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest()},
//         {+0.0, -2.0, -2.0},
//         {+0.0, -1.0, -1.0},
//         {+0.0, +0.0, +0.0},
//         {+0.0, +1.0, +1.0},
//         {+0.0, +2.0, +2.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max()},
//         {+0.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+1.0, Real::Undefined(), Real::Undefined()},
//         {+1.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+1.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest() + 1},
//         {+1.0, -2.0, -1.0},
//         {+1.0, -1.0, +0.0},
//         {+1.0, +0.0, +1.0},
//         {+1.0, +1.0, +2.0},
//         {+1.0, +2.0, +3.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {+1.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+2.0, Real::Undefined(), Real::Undefined()},
//         {+2.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+2.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest() + 2},
//         {+2.0, -2.0, +0.0},
//         {+2.0, -1.0, +1.0},
//         {+2.0, +0.0, +2.0},
//         {+2.0, +1.0, +3.0},
//         {+2.0, +2.0, +4.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {+2.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(),
//         std::numeric_limits<Real::ValueType>::max() + std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, std::numeric_limits<Real::ValueType>::max() - 2},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, std::numeric_limits<Real::ValueType>::max() - 1},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(),
//         Real::PositiveInfinity()}, {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(),
//         Real::PositiveInfinity()},

//         {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), -2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), -1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +0.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::PositiveInfinity()}

//     } ;

//     for (auto& testCase : testCases)
//     {

//         Real& a = testCase.first ;
//         const Real& b = testCase.second ;
//         const Real& c = testCase.third ;

//         a += b ;

//         if (c.isDefined())
//         {

//             if (c.isPositiveInfinity())
//             {
//                 EXPECT_TRUE(a.isPositiveInfinity()) ;
//             }
//             else if (c.isNegativeInfinity())
//             {
//                 EXPECT_TRUE(a.isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(c, a) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE(a.isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, SubtractionAssignmentOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Array ;

//     Array<Triple<Real, Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined(), Real::Undefined()},
//         {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
//         {Real::Undefined(), -2.0, Real::Undefined()},
//         {Real::Undefined(), -1.0, Real::Undefined()},
//         {Real::Undefined(), +0.0, Real::Undefined()},
//         {Real::Undefined(), +1.0, Real::Undefined()},
//         {Real::Undefined(), +2.0, Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
//         {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

//         {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), -2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), -1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +0.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, std::numeric_limits<Real::ValueType>::lowest() + 2},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, std::numeric_limits<Real::ValueType>::lowest() + 1},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(),
//         Real::NegativeInfinity()}, {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(),
//         Real::NegativeInfinity()},

//         {-2.0, Real::Undefined(), Real::Undefined()},
//         {-2.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-2.0, std::numeric_limits<Real::ValueType>::lowest(), -2 - std::numeric_limits<Real::ValueType>::lowest()},
//         {-2.0, -2.0, +0.0},
//         {-2.0, -1.0, -1.0},
//         {-2.0, +0.0, -2.0},
//         {-2.0, +1.0, -3.0},
//         {-2.0, +2.0, -4.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {-2.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {-1.0, Real::Undefined(), Real::Undefined()},
//         {-1.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-1.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max()},
//         {-1.0, -2.0, +1.0},
//         {-1.0, -1.0, +0.0},
//         {-1.0, +0.0, -1.0},
//         {-1.0, +1.0, -2.0},
//         {-1.0, +2.0, -3.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest()},
//         {-1.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {+0.0, Real::Undefined(), Real::Undefined()},
//         {+0.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {+0.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {+0.0, -2.0, +2.0},
//         {+0.0, -1.0, +1.0},
//         {+0.0, +0.0, +0.0},
//         {+0.0, +1.0, -1.0},
//         {+0.0, +2.0, -2.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + 1},
//         {+0.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {+1.0, Real::Undefined(), Real::Undefined()},
//         {+1.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {+1.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {+1.0, -2.0, +3.0},
//         {+1.0, -1.0, +2.0},
//         {+1.0, +0.0, +1.0},
//         {+1.0, +1.0, +0.0},
//         {+1.0, +2.0, -1.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + 2},
//         {+1.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {+2.0, Real::Undefined(), Real::Undefined()},
//         {+2.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {+2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {+2.0, -2.0, +4.0},
//         {+2.0, -1.0, +3.0},
//         {+2.0, +0.0, +2.0},
//         {+2.0, +1.0, +1.0},
//         {+2.0, +2.0, +0.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + 3},
//         {+2.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(),
//         Real::PositiveInfinity()}, {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max() - 1},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, std::numeric_limits<Real::ValueType>::max() - 2},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), -2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), -1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +0.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::Undefined()}

//     } ;

//     for (auto& testCase : testCases)
//     {

//         Real& a = testCase.first ;
//         const Real& b = testCase.second ;
//         const Real& c = testCase.third ;

//         a -= b ;

//         if (c.isDefined())
//         {

//             if (c.isPositiveInfinity())
//             {
//                 EXPECT_TRUE(a.isPositiveInfinity()) ;
//             }
//             else if (c.isNegativeInfinity())
//             {
//                 EXPECT_TRUE(a.isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(c, a) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE(a.isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, MultiplicationAssignmentOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Array ;

//     Array<Triple<Real, Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined(), Real::Undefined()},
//         {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
//         {Real::Undefined(), -2.0, Real::Undefined()},
//         {Real::Undefined(), -1.0, Real::Undefined()},
//         {Real::Undefined(), +0.0, Real::Undefined()},
//         {Real::Undefined(), +1.0, Real::Undefined()},
//         {Real::Undefined(), +2.0, Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
//         {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

//         {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -2.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -1.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), +0.0, Real::Undefined()},
//         {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(),
//         Real::PositiveInfinity()}, {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(),
//         Real::NegativeInfinity()}, {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(),
//         Real::NegativeInfinity()},

//         {-1073741823, Real::Undefined(), Real::Undefined()},
//         {-1073741823, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-1073741823, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-1073741823, -3.0, Real::PositiveInfinity()},
//         {-1073741823, -2.0, +2147483646},
//         {-1073741823, -1.0, +1073741823},
//         {-1073741823, +0.0, +0.0},
//         {-1073741823, +1.0, -1073741823},
//         {-1073741823, +2.0, -2147483646},
//         {-1073741823, +3.0, Real::NegativeInfinity()},
//         {-1073741823, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {-1073741823, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {-2.0, Real::Undefined(), Real::Undefined()},
//         {-2.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-2.0, -2.0, +4.0},
//         {-2.0, -1.0, +2.0},
//         {-2.0, +0.0, +0.0},
//         {-2.0, +1.0, -2.0},
//         {-2.0, +2.0, -4.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {-2.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {-1.0, Real::Undefined(), Real::Undefined()},
//         {-1.0, Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {-1.0, std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-1.0, -2.0, +2.0},
//         {-1.0, -1.0, +1.0},
//         {-1.0, +0.0, +0.0},
//         {-1.0, +1.0, -1.0},
//         {-1.0, +2.0, -2.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::max(), -std::numeric_limits<Real::ValueType>::max()},
//         {-1.0, Real::PositiveInfinity(), Real::NegativeInfinity()},

//         {+0.0, Real::Undefined(), Real::Undefined()},
//         {+0.0, Real::NegativeInfinity(), Real::Undefined()},
//         {+0.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+0.0, -2.0, +0.0},
//         {+0.0, -1.0, +0.0},
//         {+0.0, +0.0, +0.0},
//         {+0.0, +1.0, +0.0},
//         {+0.0, +2.0, +0.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+0.0, Real::PositiveInfinity(), Real::Undefined()},

//         {+1.0, Real::Undefined(), Real::Undefined()},
//         {+1.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+1.0, std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest()},
//         {+1.0, -2.0, -2.0},
//         {+1.0, -1.0, -1.0},
//         {+1.0, +0.0, +0.0},
//         {+1.0, +1.0, +1.0},
//         {+1.0, +2.0, +2.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max()},
//         {+1.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+2.0, Real::Undefined(), Real::Undefined()},
//         {+2.0, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+2.0, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {+2.0, -2.0, -4.0},
//         {+2.0, -1.0, -2.0},
//         {+2.0, +0.0, +0.0},
//         {+2.0, +1.0, +2.0},
//         {+2.0, +2.0, +4.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {+2.0, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {+1073741823, Real::Undefined(), Real::Undefined()},
//         {+1073741823, Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {+1073741823, std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {+1073741823, -3.0, Real::NegativeInfinity()},
//         {+1073741823, -2.0, -2147483646},
//         {+1073741823, -1.0, -1073741823},
//         {+1073741823, +0.0, +0.0},
//         {+1073741823, +1.0, +1073741823},
//         {+1073741823, +2.0, +2147483646},
//         {+1073741823, +3.0, Real::PositiveInfinity()},
//         {+1073741823, std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {+1073741823, Real::PositiveInfinity(), Real::PositiveInfinity()},

//         {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(),
//         Real::NegativeInfinity()}, {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, -std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(),
//         Real::PositiveInfinity()}, {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(),
//         Real::PositiveInfinity()},

//         {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -2.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -1.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), +0.0, Real::Undefined()},
//         {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::PositiveInfinity()}

//     } ;

//     for (auto& testCase : testCases)
//     {

//         Real& a = testCase.first ;
//         const Real& b = testCase.second ;
//         const Real& c = testCase.third ;

//         a *= b ;

//         if (c.isDefined())
//         {

//             if (c.isPositiveInfinity())
//             {
//                 EXPECT_TRUE(a.isPositiveInfinity()) ;
//             }
//             else if (c.isNegativeInfinity())
//             {
//                 EXPECT_TRUE(a.isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(c, a) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE(a.isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, DivisionAssignmentOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Triple ;
//     using ostk::core::ctnr::Array ;

//     Array<Triple<Real, Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined(), Real::Undefined()},
//         {Real::Undefined(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined()},
//         {Real::Undefined(), -2.0, Real::Undefined()},
//         {Real::Undefined(), -1.0, Real::Undefined()},
//         {Real::Undefined(), +0.0, Real::Undefined()},
//         {Real::Undefined(), +1.0, Real::Undefined()},
//         {Real::Undefined(), +2.0, Real::Undefined()},
//         {Real::Undefined(), std::numeric_limits<Real::ValueType>::max(), Real::Undefined()},
//         {Real::Undefined(), Real::PositiveInfinity(), Real::Undefined()},

//         {Real::NegativeInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -2.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), -1.0, Real::PositiveInfinity()},
//         {Real::NegativeInfinity(), +0.0, Real::Undefined()},
//         {Real::NegativeInfinity(), +1.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), +2.0, Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity(), Real::Undefined()},

//         {std::numeric_limits<Real::ValueType>::lowest(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity(), +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), 1},
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, std::numeric_limits<Real::ValueType>::lowest() /
//         -2.0}, {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, std::numeric_limits<Real::ValueType>::lowest() / 2},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), -1.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), +0.0},

//         {-2.0, Real::Undefined(), Real::Undefined()},
//         {-2.0, Real::NegativeInfinity(), +0.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {-2.0, -2.0, +1.0},
//         {-2.0, -1.0, +2.0},
//         {-2.0, +0.0, Real::Undefined()},
//         {-2.0, +1.0, -2.0},
//         {-2.0, +2.0, -1.0},
//         {-2.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {-2.0, Real::PositiveInfinity(), +0.0},

//         {-1.0, Real::Undefined(), Real::Undefined()},
//         {-1.0, Real::NegativeInfinity(), +0.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {-1.0, -2.0, +0.0},
//         {-1.0, -1.0, +1.0},
//         {-1.0, +0.0, Real::Undefined()},
//         {-1.0, +1.0, -1.0},
//         {-1.0, +2.0, +0.0},
//         {-1.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {-1.0, Real::PositiveInfinity(), +0.0},

//         {+0.0, Real::Undefined(), Real::Undefined()},
//         {+0.0, Real::NegativeInfinity(), +0.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+0.0, -2.0, +0.0},
//         {+0.0, -1.0, +0.0},
//         {+0.0, +0.0, Real::Undefined()},
//         {+0.0, +1.0, +0.0},
//         {+0.0, +2.0, +0.0},
//         {+0.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+0.0, Real::PositiveInfinity(), +0.0},

//         {+1.0, Real::Undefined(), Real::Undefined()},
//         {+1.0, Real::NegativeInfinity(), +0.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+1.0, -2.0, +0.0},
//         {+1.0, -1.0, -1.0},
//         {+1.0, +0.0, Real::Undefined()},
//         {+1.0, +1.0, +1.0},
//         {+1.0, +2.0, +0.0},
//         {+1.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+1.0, Real::PositiveInfinity(), +0.0},

//         {+2.0, Real::Undefined(), Real::Undefined()},
//         {+2.0, Real::NegativeInfinity(), +0.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {+2.0, -2.0, -1.0},
//         {+2.0, -1.0, -2.0},
//         {+2.0, +0.0, Real::Undefined()},
//         {+2.0, +1.0, +2.0},
//         {+2.0, +2.0, +1.0},
//         {+2.0, std::numeric_limits<Real::ValueType>::max(), +0.0},
//         {+2.0, Real::PositiveInfinity(), +0.0},

//         {std::numeric_limits<Real::ValueType>::max(), Real::Undefined(), Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity(), +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, std::numeric_limits<Real::ValueType>::max() / -2.0},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, std::numeric_limits<Real::ValueType>::max() / -1.0},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, Real::Undefined()},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, std::numeric_limits<Real::ValueType>::max() / 2},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), +1.0},
//         {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), +0.0},

//         {Real::PositiveInfinity(), Real::Undefined(), Real::Undefined()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity(), Real::Undefined()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -2.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), -1.0, Real::NegativeInfinity()},
//         {Real::PositiveInfinity(), +0.0, Real::Undefined()},
//         {Real::PositiveInfinity(), +1.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), +2.0, Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity(), Real::Undefined()}

//     } ;

//     for (auto& testCase : testCases)
//     {

//         Real& a = testCase.first ;
//         const Real& b = testCase.second ;
//         const Real& c = testCase.third ;

//         a /= b ;

//         if (c.isDefined())
//         {

//             if (c.isPositiveInfinity())
//             {
//                 EXPECT_TRUE(a.isPositiveInfinity()) ;
//             }
//             else if (c.isNegativeInfinity())
//             {
//                 EXPECT_TRUE(a.isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(c, a) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE(a.isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, UnaryPlusOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Pair ;
//     using ostk::core::ctnr::Array ;

//     Array<Pair<Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest()},
//         {-2.0, -2.0},
//         {-1.0, -1.0},
//         {+0.0, +0.0},
//         {+1.0, +1.0},
//         {+2.0, +2.0},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max()},
//         {Real::PositiveInfinity(), Real::PositiveInfinity()}

//     } ;

//     for (const auto& testCase : testCases)
//     {

//         const Real& a = testCase.first ;
//         const Real& b = testCase.second ;

//         Real c = +a ;

//         if (b.isDefined())
//         {

//             if (b.isPositiveInfinity())
//             {
//                 EXPECT_TRUE(c.isPositiveInfinity()) ;
//             }
//             else if (b.isNegativeInfinity())
//             {
//                 EXPECT_TRUE(c.isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(b, c) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE(c.isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, UnaryMinusOperator)
// {

//     using ostk::core::types::Real ;
//     using ostk::core::ctnr::Pair ;
//     using ostk::core::ctnr::Array ;

//     Array<Pair<Real, Real>> testCases =
//     {

//         {Real::Undefined(), Real::Undefined()},
//         {Real::NegativeInfinity(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {-2.0, +2.0},
//         {-1.0, +1.0},
//         {+0.0, +0.0},
//         {+1.0, -1.0},
//         {+2.0, -2.0},
//         {std::numeric_limits<Real::ValueType>::max(), -std::numeric_limits<Real::ValueType>::max()},
//         {Real::PositiveInfinity(), Real::NegativeInfinity()}

//     } ;

//     for (const auto& testCase : testCases)
//     {

//         const Real& a = testCase.first ;
//         const Real& b = testCase.second ;

//         Real c = -a ;

//         if (b.isDefined())
//         {

//             if (b.isPositiveInfinity())
//             {
//                 EXPECT_TRUE(c.isPositiveInfinity()) ;
//             }
//             else if (b.isNegativeInfinity())
//             {
//                 EXPECT_TRUE(c.isNegativeInfinity()) ;
//             }
//             else
//             {
//                 EXPECT_EQ(b, c) ;
//             }

//         }
//         else
//         {
//             EXPECT_FALSE(c.isDefined()) ;
//         }

//     }

// }

// TEST (OpenSpaceToolkit_Core_Types_Real, ValueTypeOperator)
// {

//     using ostk::core::types::Real ;

//     {

//         EXPECT_ANY_THROW( Real::ValueType a = Real::Undefined() ; (void) a ; ) ;

//     }

//     {

//         EXPECT_ANY_THROW( Real::ValueType a = Real::NegativeInfinity() ; (void) a ; ) ;

//     }

//     {

//         Real::ValueType a = Real(std::numeric_limits<Real::ValueType>::lowest()) ;

//         EXPECT_EQ(std::numeric_limits<Real::ValueType>::lowest(), a) ;

//     }

//     {

//         Real::ValueType a = Real(-1.0) ;

//         EXPECT_EQ(-1.0, a) ;

//     }

//     {

//         Real::ValueType a = Real(+0.0) ;

//         EXPECT_EQ(+0.0, a) ;

//     }

//     {

//         Real::ValueType a = Real(+1.0) ;

//         EXPECT_EQ(+1.0, a) ;

//     }

//     {

//         EXPECT_ANY_THROW( Real::ValueType a = Real::PositiveInfinity() ; (void) a ; ) ;

//     }

// }

// // TEST (OpenSpaceToolkit_Core_Types_Real, StreamOperator)
// // {

// //     using ostk::core::types::Real ;

// //     FAIL() ;

// // }

TEST(OpenSpaceToolkit_Core_Types_Real, IsDefined)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real(0.0).isDefined());
    EXPECT_TRUE(Real(-1.0).isDefined());
    EXPECT_TRUE(Real(+0.0).isDefined());
    EXPECT_TRUE(Real(+1.0).isDefined());
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isDefined());
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isDefined());
    EXPECT_TRUE(Real::NegativeInfinity().isDefined());
    EXPECT_TRUE(Real::PositiveInfinity().isDefined());

    EXPECT_FALSE(Real::Undefined().isDefined());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsZero)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real(0.0).isZero());
    EXPECT_TRUE(Real(+0.0).isZero());

    EXPECT_FALSE(Real(-1.0).isZero());
    EXPECT_FALSE(Real(+1.0).isZero());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isZero());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isZero());
    EXPECT_FALSE(Real::NegativeInfinity().isZero());
    EXPECT_FALSE(Real::PositiveInfinity().isZero());
    EXPECT_FALSE(Real::Undefined().isZero());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsPositive)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real(0.0).isPositive());
    EXPECT_TRUE(Real(+0.0).isPositive());
    EXPECT_TRUE(Real(+1.0).isPositive());
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isPositive());
    EXPECT_TRUE(Real::PositiveInfinity().isPositive());

    EXPECT_FALSE(Real::Undefined().isPositive());
    EXPECT_FALSE(Real(-1.0).isPositive());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isPositive());
    EXPECT_FALSE(Real::NegativeInfinity().isPositive());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsNegative)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real(0.0).isNegative());
    EXPECT_TRUE(Real(-1.0).isNegative());
    EXPECT_TRUE(Real(+0.0).isNegative());
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isNegative());
    EXPECT_TRUE(Real::NegativeInfinity().isNegative());

    EXPECT_FALSE(Real::Undefined().isNegative());
    EXPECT_FALSE(Real(+1.0).isNegative());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isNegative());
    EXPECT_FALSE(Real::PositiveInfinity().isNegative());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsStrictlyPositive)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real(+1.0).isStrictlyPositive());
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isStrictlyPositive());
    EXPECT_TRUE(Real::PositiveInfinity().isStrictlyPositive());

    EXPECT_FALSE(Real::Undefined().isStrictlyPositive());
    EXPECT_FALSE(Real(0.0).isStrictlyPositive());
    EXPECT_FALSE(Real(-1.0).isStrictlyPositive());
    EXPECT_FALSE(Real(+0.0).isStrictlyPositive());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isStrictlyPositive());
    EXPECT_FALSE(Real::NegativeInfinity().isStrictlyPositive());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsStrictlyNegative)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real(-1.0).isStrictlyNegative());
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isStrictlyNegative());
    EXPECT_TRUE(Real::NegativeInfinity().isStrictlyNegative());

    EXPECT_FALSE(Real::Undefined().isStrictlyNegative());
    EXPECT_FALSE(Real(0.0).isStrictlyNegative());
    EXPECT_FALSE(Real(+1.0).isStrictlyNegative());
    EXPECT_FALSE(Real(+0.0).isStrictlyNegative());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isStrictlyNegative());
    EXPECT_FALSE(Real::PositiveInfinity().isStrictlyNegative());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsInfinity)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real::NegativeInfinity().isInfinity());
    EXPECT_TRUE(Real::PositiveInfinity().isInfinity());

    EXPECT_FALSE(Real::Undefined().isInfinity());
    EXPECT_FALSE(Real(0.0).isInfinity());
    EXPECT_FALSE(Real(-1.0).isInfinity());
    EXPECT_FALSE(Real(+0.0).isInfinity());
    EXPECT_FALSE(Real(+1.0).isInfinity());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isInfinity());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isInfinity());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsPositiveInfinity)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real::PositiveInfinity().isPositiveInfinity());

    EXPECT_FALSE(Real::Undefined().isPositiveInfinity());
    EXPECT_FALSE(Real(0.0).isPositiveInfinity());
    EXPECT_FALSE(Real(-1.0).isPositiveInfinity());
    EXPECT_FALSE(Real(+0.0).isPositiveInfinity());
    EXPECT_FALSE(Real(+1.0).isPositiveInfinity());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isPositiveInfinity());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isPositiveInfinity());
    EXPECT_FALSE(Real::NegativeInfinity().isPositiveInfinity());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsNegativeInfinity)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real::NegativeInfinity().isNegativeInfinity());

    EXPECT_FALSE(Real::Undefined().isNegativeInfinity());
    EXPECT_FALSE(Real(0.0).isNegativeInfinity());
    EXPECT_FALSE(Real(-1.0).isNegativeInfinity());
    EXPECT_FALSE(Real(+0.0).isNegativeInfinity());
    EXPECT_FALSE(Real(+1.0).isNegativeInfinity());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isNegativeInfinity());
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isNegativeInfinity());
    EXPECT_FALSE(Real::PositiveInfinity().isNegativeInfinity());
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsInteger)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0).isInteger());
        EXPECT_TRUE(Real(1.0).isInteger());

        EXPECT_TRUE(Real(-1.0).isInteger());
        EXPECT_TRUE(Real(+1.0).isInteger());

        EXPECT_TRUE(Real(-999.0).isInteger());
        EXPECT_TRUE(Real(+999.0).isInteger());

        EXPECT_TRUE(Real(-1.0e6).isInteger());
        EXPECT_TRUE(Real(+1.0e6).isInteger());

        EXPECT_TRUE(Real(-1.0e+300).isInteger());
        EXPECT_TRUE(Real(+1.0e+300).isInteger());
    }

    {
        EXPECT_FALSE(Real(0.1).isInteger());
        EXPECT_FALSE(Real(1.1).isInteger());
        EXPECT_FALSE(Real(0.999999999999).isInteger());

        EXPECT_FALSE(Real(-1.0e-6).isInteger());
        EXPECT_FALSE(Real(+1.0e-6).isInteger());
    }

    {
        EXPECT_FALSE(Real::Undefined().isInteger());
        EXPECT_FALSE(Real::NegativeInfinity().isInteger());
        EXPECT_FALSE(Real::PositiveInfinity().isInteger());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsFinite)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0).isFinite());
        EXPECT_TRUE(Real(-1.0).isFinite());
        EXPECT_TRUE(Real(+0.0).isFinite());
        EXPECT_TRUE(Real(+1.0).isFinite());
        EXPECT_TRUE(Real(-1.0e+300).isFinite());
        EXPECT_TRUE(Real(+1.0e+300).isFinite());
        EXPECT_TRUE(Real(-1.0e-300).isFinite());
        EXPECT_TRUE(Real(+1.0e-300).isFinite());
        EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isFinite());
        EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isFinite());
    }

    {
        EXPECT_FALSE(Real::Undefined().isFinite());
        EXPECT_FALSE(Real::NegativeInfinity().isFinite());
        EXPECT_FALSE(Real::PositiveInfinity().isFinite());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, IsNear)
{
    using ostk::core::types::Real;

    {
        EXPECT_TRUE(Real(0.0).isNear(Real(0.0), 0.0));
        EXPECT_TRUE(Real(-1.0).isNear(Real(-1.0), 0.0));
        EXPECT_TRUE(Real(+0.0).isNear(Real(+0.0), 0.0));
        EXPECT_TRUE(Real(+1.0).isNear(Real(+1.0), 0.0));

        EXPECT_TRUE(Real(0.0).isNear(Real(1.0), 1.0));
    }

    {
        EXPECT_FALSE(Real(0.0).isNear(Real(1.1), 1.0));

        EXPECT_FALSE(Real::NegativeInfinity().isNear(Real::NegativeInfinity(), 0.0));
        EXPECT_FALSE(Real::PositiveInfinity().isNear(Real::PositiveInfinity(), 0.0));
    }

    {
        EXPECT_ANY_THROW(Real::Undefined().isNear(Real::Undefined(), Real::Undefined()));
        EXPECT_ANY_THROW(Real::Undefined().isNear(Real::Undefined(), 0.0));
        EXPECT_ANY_THROW(Real::Undefined().isNear(0.0, 0.0));
        EXPECT_ANY_THROW(Real(0.0).isNear(Real::Undefined(), 0.0));
        EXPECT_ANY_THROW(Real(0.0).isNear(0.0, Real::Undefined()));
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, GetSign)
{
    using ostk::core::types::Sign;
    using ostk::core::types::Real;

    EXPECT_EQ(Sign::Undefined, Real::Undefined().getSign());
    EXPECT_EQ(Sign::None, Real(0.0).getSign());
    EXPECT_EQ(Sign::Negative, Real(-1.0).getSign());
    EXPECT_EQ(Sign::None, Real(+0.0).getSign());
    EXPECT_EQ(Sign::Positive, Real(+1.0).getSign());
    EXPECT_EQ(Sign::Negative, Real(std::numeric_limits<Real::ValueType>::lowest()).getSign());
    EXPECT_EQ(Sign::Positive, Real(std::numeric_limits<Real::ValueType>::max()).getSign());
    EXPECT_EQ(Sign::Negative, Real::NegativeInfinity().getSign());
    EXPECT_EQ(Sign::Positive, Real::PositiveInfinity().getSign());
}

TEST(OpenSpaceToolkit_Core_Types_Real, ToString)
{
    using ostk::core::types::Real;

    {
        EXPECT_EQ("0.0", Real(0.0).toString());

        EXPECT_EQ("-1.0", Real(-1.0).toString());
        EXPECT_EQ("0.0", Real(+0.0).toString());
        EXPECT_EQ("1.0", Real(+1.0).toString());

        EXPECT_EQ("1.1000000000000001", Real(1.1).toString());
        EXPECT_EQ("1.1200000000000001", Real(1.12).toString());
        EXPECT_EQ("1.123", Real(1.123).toString());
        EXPECT_EQ("1.1234", Real(1.1234).toString());
        EXPECT_EQ("1.1234500000000001", Real(1.12345).toString());
        EXPECT_EQ("1.123456", Real(1.123456).toString());
        EXPECT_EQ("1.1234567", Real(1.1234567).toString());
        EXPECT_EQ("1.1234567799999999", Real(1.12345678).toString());
        EXPECT_EQ("1.123456789", Real(1.123456789).toString());
        EXPECT_EQ("1.1234567891", Real(1.1234567891).toString());
        EXPECT_EQ("1.12345678912", Real(1.12345678912).toString());
        EXPECT_EQ("1.1234567891230001", Real(1.123456789123).toString());
        EXPECT_EQ("1.1234567891234", Real(1.1234567891234).toString());
        EXPECT_EQ("1.1234567891234499", Real(1.12345678912345).toString());
        EXPECT_EQ("1.1234567891234559", Real(1.123456789123456).toString());
        EXPECT_EQ("1.1234567891234566", Real(1.1234567891234567).toString());
        EXPECT_EQ("1.1234567891234568", Real(1.12345678912345678).toString());
        EXPECT_EQ("1.1234567891234568", Real(1.123456789123456789).toString());

        EXPECT_EQ("-1.1000000000000001", Real(-1.1).toString());
        EXPECT_EQ("-1.1200000000000001", Real(-1.12).toString());
        EXPECT_EQ("-1.123", Real(-1.123).toString());
        EXPECT_EQ("-1.1234", Real(-1.1234).toString());
        EXPECT_EQ("-1.1234500000000001", Real(-1.12345).toString());
        EXPECT_EQ("-1.123456", Real(-1.123456).toString());
        EXPECT_EQ("-1.1234567", Real(-1.1234567).toString());
        EXPECT_EQ("-1.1234567799999999", Real(-1.12345678).toString());
        EXPECT_EQ("-1.123456789", Real(-1.123456789).toString());
        EXPECT_EQ("-1.1234567891", Real(-1.1234567891).toString());
        EXPECT_EQ("-1.12345678912", Real(-1.12345678912).toString());
        EXPECT_EQ("-1.1234567891230001", Real(-1.123456789123).toString());
        EXPECT_EQ("-1.1234567891234", Real(-1.1234567891234).toString());
        EXPECT_EQ("-1.1234567891234499", Real(-1.12345678912345).toString());
        EXPECT_EQ("-1.1234567891234559", Real(-1.123456789123456).toString());
        EXPECT_EQ("-1.1234567891234566", Real(-1.1234567891234567).toString());
        EXPECT_EQ("-1.1234567891234568", Real(-1.12345678912345678).toString());
        EXPECT_EQ("-1.1234567891234568", Real(-1.123456789123456789).toString());

        EXPECT_EQ("1.1000000000000001", Real(1.1).toString());
        EXPECT_EQ("11.199999999999999", Real(11.2).toString());
        EXPECT_EQ("112.3", Real(112.3).toString());
        EXPECT_EQ("1123.4000000000001", Real(1123.4).toString());
        EXPECT_EQ("11234.5", Real(11234.5).toString());
        EXPECT_EQ("112345.60000000001", Real(112345.6).toString());
        EXPECT_EQ("1123456.7", Real(1123456.7).toString());
        EXPECT_EQ("11234567.800000001", Real(11234567.8).toString());
        EXPECT_EQ("112345678.90000001", Real(112345678.9).toString());
        EXPECT_EQ("1123456789.0999999", Real(1123456789.1).toString());
        EXPECT_EQ("11234567891.200001", Real(11234567891.2).toString());
        EXPECT_EQ("112345678912.3", Real(112345678912.3).toString());
        EXPECT_EQ("1123456789123.3999", Real(1123456789123.4).toString());
        EXPECT_EQ("11234567891234.5", Real(11234567891234.5).toString());
        EXPECT_EQ("112345678912345.59", Real(112345678912345.6).toString());
        EXPECT_EQ("1123456789123456.8", Real(1123456789123456.7).toString());
        EXPECT_EQ("11234567891234568.0", Real(11234567891234567.8).toString());
        EXPECT_EQ("1.1234567891234568e+17", Real(112345678912345678.9).toString());
    }

    {
        EXPECT_EQ("0.000", Real(0.0).toString(3));

        EXPECT_EQ("-1.000", Real(-1.0).toString(3));
        EXPECT_EQ("0.000", Real(+0.0).toString(3));
        EXPECT_EQ("1.000", Real(+1.0).toString(3));

        EXPECT_EQ("1.100", Real(1.1).toString(3));
        EXPECT_EQ("1.120", Real(1.12).toString(3));
        EXPECT_EQ("1.123", Real(1.123).toString(3));
        EXPECT_EQ("1.123", Real(1.1234).toString(3));
        EXPECT_EQ("1.123", Real(1.12345).toString(3));
        EXPECT_EQ("1.123", Real(1.123456).toString(3));
        EXPECT_EQ("1.123", Real(1.1234567).toString(3));
        EXPECT_EQ("1.123", Real(1.12345678).toString(3));
        EXPECT_EQ("1.123", Real(1.123456789).toString(3));
        EXPECT_EQ("1.123", Real(1.1234567891).toString(3));
        EXPECT_EQ("1.123", Real(1.12345678912).toString(3));
        EXPECT_EQ("1.123", Real(1.123456789123).toString(3));
        EXPECT_EQ("1.123", Real(1.1234567891234).toString(3));
        EXPECT_EQ("1.123", Real(1.12345678912345).toString(3));
        EXPECT_EQ("1.123", Real(1.123456789123456).toString(3));
        EXPECT_EQ("1.123", Real(1.1234567891234567).toString(3));
        EXPECT_EQ("1.123", Real(1.12345678912345678).toString(3));
        EXPECT_EQ("1.123", Real(1.123456789123456789).toString(3));

        EXPECT_EQ("-1.100", Real(-1.1).toString(3));
        EXPECT_EQ("-1.120", Real(-1.12).toString(3));
        EXPECT_EQ("-1.123", Real(-1.123).toString(3));
        EXPECT_EQ("-1.123", Real(-1.1234).toString(3));
        EXPECT_EQ("-1.123", Real(-1.12345).toString(3));
        EXPECT_EQ("-1.123", Real(-1.123456).toString(3));
        EXPECT_EQ("-1.123", Real(-1.1234567).toString(3));
        EXPECT_EQ("-1.123", Real(-1.12345678).toString(3));
        EXPECT_EQ("-1.123", Real(-1.123456789).toString(3));
        EXPECT_EQ("-1.123", Real(-1.1234567891).toString(3));
        EXPECT_EQ("-1.123", Real(-1.12345678912).toString(3));
        EXPECT_EQ("-1.123", Real(-1.123456789123).toString(3));
        EXPECT_EQ("-1.123", Real(-1.1234567891234).toString(3));
        EXPECT_EQ("-1.123", Real(-1.12345678912345).toString(3));
        EXPECT_EQ("-1.123", Real(-1.123456789123456).toString(3));
        EXPECT_EQ("-1.123", Real(-1.1234567891234567).toString(3));
        EXPECT_EQ("-1.123", Real(-1.12345678912345678).toString(3));
        EXPECT_EQ("-1.123", Real(-1.123456789123456789).toString(3));

        EXPECT_EQ("1.100", Real(1.1).toString(3));
        EXPECT_EQ("11.200", Real(11.2).toString(3));
        EXPECT_EQ("112.300", Real(112.3).toString(3));
        EXPECT_EQ("1123.400", Real(1123.4).toString(3));
        EXPECT_EQ("11234.500", Real(11234.5).toString(3));
        EXPECT_EQ("112345.600", Real(112345.6).toString(3));
        EXPECT_EQ("1123456.700", Real(1123456.7).toString(3));
        EXPECT_EQ("11234567.800", Real(11234567.8).toString(3));
        EXPECT_EQ("112345678.900", Real(112345678.9).toString(3));
        EXPECT_EQ("1123456789.100", Real(1123456789.1).toString(3));
        EXPECT_EQ("11234567891.200", Real(11234567891.2).toString(3));
        EXPECT_EQ("112345678912.300", Real(112345678912.3).toString(3));
        EXPECT_EQ("1123456789123.400", Real(1123456789123.4).toString(3));
        EXPECT_EQ("11234567891234.500", Real(11234567891234.5).toString(3));
        EXPECT_EQ("112345678912345.594", Real(112345678912345.6).toString(3));
        EXPECT_EQ("1123456789123456.750", Real(1123456789123456.7).toString(3));
        EXPECT_EQ("11234567891234568.000", Real(11234567891234567.8).toString(3));
    }

    {
        EXPECT_EQ("0.00000", Real(0.0).toString(5));

        EXPECT_EQ("-1.00000", Real(-1.0).toString(5));
        EXPECT_EQ("0.00000", Real(+0.0).toString(5));
        EXPECT_EQ("1.00000", Real(+1.0).toString(5));

        EXPECT_EQ("1.10000", Real(1.1).toString(5));
        EXPECT_EQ("1.12000", Real(1.12).toString(5));
        EXPECT_EQ("1.12300", Real(1.123).toString(5));
        EXPECT_EQ("1.12340", Real(1.1234).toString(5));
        EXPECT_EQ("1.12345", Real(1.12345).toString(5));
        EXPECT_EQ("1.12346", Real(1.123456).toString(5));
        EXPECT_EQ("1.12346", Real(1.1234567).toString(5));
        EXPECT_EQ("1.12346", Real(1.12345678).toString(5));
        EXPECT_EQ("1.12346", Real(1.123456789).toString(5));
        EXPECT_EQ("1.12346", Real(1.1234567891).toString(5));
        EXPECT_EQ("1.12346", Real(1.12345678912).toString(5));
        EXPECT_EQ("1.12346", Real(1.123456789123).toString(5));
        EXPECT_EQ("1.12346", Real(1.1234567891234).toString(5));
        EXPECT_EQ("1.12346", Real(1.12345678912345).toString(5));
        EXPECT_EQ("1.12346", Real(1.123456789123456).toString(5));
        EXPECT_EQ("1.12346", Real(1.1234567891234567).toString(5));
        EXPECT_EQ("1.12346", Real(1.12345678912345678).toString(5));
        EXPECT_EQ("1.12346", Real(1.123456789123456789).toString(5));

        EXPECT_EQ("-1.10000", Real(-1.1).toString(5));
        EXPECT_EQ("-1.12000", Real(-1.12).toString(5));
        EXPECT_EQ("-1.12300", Real(-1.123).toString(5));
        EXPECT_EQ("-1.12340", Real(-1.1234).toString(5));
        EXPECT_EQ("-1.12345", Real(-1.12345).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.123456).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.1234567).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.12345678).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.123456789).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.1234567891).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.12345678912).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.123456789123).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.1234567891234).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.12345678912345).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.123456789123456).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.1234567891234567).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.12345678912345678).toString(5));
        EXPECT_EQ("-1.12346", Real(-1.123456789123456789).toString(5));

        EXPECT_EQ("1.10000", Real(1.1).toString(5));
        EXPECT_EQ("11.20000", Real(11.2).toString(5));
        EXPECT_EQ("112.30000", Real(112.3).toString(5));
        EXPECT_EQ("1123.40000", Real(1123.4).toString(5));
        EXPECT_EQ("11234.50000", Real(11234.5).toString(5));
        EXPECT_EQ("112345.60000", Real(112345.6).toString(5));
        EXPECT_EQ("1123456.70000", Real(1123456.7).toString(5));
        EXPECT_EQ("11234567.80000", Real(11234567.8).toString(5));
        EXPECT_EQ("112345678.90000", Real(112345678.9).toString(5));
        EXPECT_EQ("1123456789.10000", Real(1123456789.1).toString(5));
        EXPECT_EQ("11234567891.20000", Real(11234567891.2).toString(5));
        EXPECT_EQ("112345678912.30000", Real(112345678912.3).toString(5));
        EXPECT_EQ("1123456789123.39990", Real(1123456789123.4).toString(5));
        EXPECT_EQ("11234567891234.50000", Real(11234567891234.5).toString(5));
        EXPECT_EQ("112345678912345.59375", Real(112345678912345.6).toString(5));
        EXPECT_EQ("1123456789123456.75000", Real(1123456789123456.7).toString(5));
        EXPECT_EQ("11234567891234568.00000", Real(11234567891234567.8).toString(5));
    }

    {
        EXPECT_EQ("1.0000000000000001e+300", Real(1e+300).toString()) << Real(1e+300).toString();
        EXPECT_EQ("1.0000000000000001e-30", Real(1e-30).toString()) << Real(1e-30).toString();
        EXPECT_EQ("1e+30", Real(1e+30).toString()) << Real(1e+30).toString();
        EXPECT_EQ("1e-300", Real(1e-300).toString()) << Real(1e-300).toString();

        EXPECT_EQ("-1.0000000000000001e+300", Real(-1e+300).toString()) << Real(-1e+300).toString();
        EXPECT_EQ("-1.0000000000000001e-30", Real(-1e-30).toString()) << Real(-1e-30).toString();
        EXPECT_EQ("-1e+30", Real(-1e+30).toString()) << Real(-1e+30).toString();
        EXPECT_EQ("-1e-300", Real(-1e-300).toString()) << Real(-1e-300).toString();

        EXPECT_EQ("1.1000000000000001e+300", Real(1.1e+300).toString()) << Real(1.1e+300).toString();
        EXPECT_EQ("1.0999999999999999e-30", Real(1.1e-30).toString()) << Real(1.1e-30).toString();
        EXPECT_EQ("1.1e+30", Real(1.1e+30).toString()) << Real(1.1e+30).toString();
        EXPECT_EQ("1.1e-300", Real(1.1e-300).toString()) << Real(1.1e-300).toString();

        EXPECT_EQ("-1.1000000000000001e+300", Real(-1.1e+300).toString()) << Real(-1.1e+300).toString();
        EXPECT_EQ("-1.0999999999999999e-30", Real(-1.1e-30).toString()) << Real(-1.1e-30).toString();
        EXPECT_EQ("-1.1e+30", Real(-1.1e+30).toString()) << Real(-1.1e+30).toString();
        EXPECT_EQ("-1.1e-300", Real(-1.1e-300).toString()) << Real(-1.1e-300).toString();
    }

    {
        EXPECT_EQ("-Inf", Real::NegativeInfinity().toString(3));
        EXPECT_EQ("+Inf", Real::PositiveInfinity().toString(3));
    }

    {
        EXPECT_EQ("Undefined", Real::Undefined().toString(3));
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, ToInteger)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;

    {
        EXPECT_EQ(0, Real(0.0).toInteger());

        EXPECT_EQ(+1, Real(+1.0).toInteger());
        EXPECT_EQ(-1, Real(-1.0).toInteger());

        EXPECT_EQ(+123, Real(+123.0).toInteger());
        EXPECT_EQ(-123, Real(-123.0).toInteger());
    }

    {
        EXPECT_ANY_THROW(Real::Undefined().toInteger());
        EXPECT_ANY_THROW(Real(0.1).toInteger());
        EXPECT_ANY_THROW(Real(10.1).toInteger());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, Abs)
{
    using ostk::core::types::Real;

    {
        EXPECT_EQ(0.0, Real(0.0).abs());
        EXPECT_EQ(1.0, Real(+1.0).abs());
        EXPECT_EQ(1.0, Real(-1.0).abs());
        EXPECT_EQ(2.0, Real(+2.0).abs());
        EXPECT_EQ(2.0, Real(-2.0).abs());
    }

    {
        EXPECT_NO_THROW(Real::Undefined().abs());

        EXPECT_FALSE(Real::Undefined().abs().isDefined());
    }

    {
        EXPECT_NO_THROW(Real::PositiveInfinity().abs());
        EXPECT_NO_THROW(Real::NegativeInfinity().abs());

        EXPECT_TRUE(Real::PositiveInfinity().abs().isDefined());
        EXPECT_TRUE(Real::NegativeInfinity().abs().isDefined());

        EXPECT_TRUE(Real::PositiveInfinity().abs().isPositiveInfinity());
        EXPECT_TRUE(Real::NegativeInfinity().abs().isPositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, Floor)
{
    using ostk::core::types::Real;

    {
        EXPECT_EQ(+0, Real(0.0).floor());
        EXPECT_EQ(+1, Real(+1.0).floor());
        EXPECT_EQ(+1, Real(+1.1).floor());
        EXPECT_EQ(-1, Real(-1.0).floor());
        EXPECT_EQ(-2, Real(-1.1).floor());
        EXPECT_EQ(+2.0, Real(+2.0).floor());
        EXPECT_EQ(-2.0, Real(-2.0).floor());
    }

    {
        EXPECT_NO_THROW(Real::Undefined().floor());
        EXPECT_NO_THROW(Real::PositiveInfinity().floor());
        EXPECT_NO_THROW(Real::NegativeInfinity().floor());

        EXPECT_FALSE(Real::Undefined().floor().isDefined());
        EXPECT_FALSE(Real::PositiveInfinity().floor().isDefined());
        EXPECT_FALSE(Real::NegativeInfinity().floor().isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, Sqrt)
{
    using ostk::core::types::Real;

    {
        EXPECT_EQ(0.0, Real(0.0).sqrt());
        EXPECT_EQ(1.0, Real(+1.0).sqrt());
        EXPECT_EQ(2.0, Real(+4.0).sqrt());
    }

    {
        EXPECT_NO_THROW(Real(-1.0).sqrt());
        EXPECT_NO_THROW(Real(-2.0).sqrt());

        EXPECT_FALSE(Real(-1.0).sqrt().isDefined());
        EXPECT_FALSE(Real(-2.0).sqrt().isDefined());
    }

    {
        EXPECT_NO_THROW(Real::Undefined().sqrt());

        EXPECT_FALSE(Real::Undefined().sqrt().isDefined());
    }

    {
        EXPECT_NO_THROW(Real::PositiveInfinity().sqrt());
        EXPECT_NO_THROW(Real::NegativeInfinity().sqrt());

        EXPECT_TRUE(Real::PositiveInfinity().sqrt().isDefined());
        EXPECT_FALSE(Real::NegativeInfinity().sqrt().isDefined());

        EXPECT_TRUE(Real::PositiveInfinity().sqrt().isPositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, Undefined)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::Undefined());

    EXPECT_FALSE(Real::Undefined().isDefined());
    EXPECT_FALSE(Real::Undefined().isInfinity());
}

TEST(OpenSpaceToolkit_Core_Types_Real, Zero)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::Zero());
    EXPECT_TRUE(Real::Zero().isDefined());

    EXPECT_EQ(0.0, Real::Zero());
}

TEST(OpenSpaceToolkit_Core_Types_Real, Pi)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::Pi());
    EXPECT_TRUE(Real::Pi().isDefined());

    EXPECT_EQ(M_PI, Real::Pi());
}

TEST(OpenSpaceToolkit_Core_Types_Real, HalfPi)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::HalfPi());
    EXPECT_TRUE(Real::HalfPi().isDefined());

    EXPECT_EQ(M_PI / 2.0, Real::HalfPi());
}

TEST(OpenSpaceToolkit_Core_Types_Real, TwoPi)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::TwoPi());
    EXPECT_TRUE(Real::TwoPi().isDefined());

    EXPECT_EQ(2.0 * M_PI, Real::TwoPi());
}

TEST(OpenSpaceToolkit_Core_Types_Real, Epsilon)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::Epsilon());
    EXPECT_TRUE(Real::Epsilon().isDefined());
    EXPECT_FALSE(Real::Epsilon().isZero());

    EXPECT_EQ(1e-15, Real::Epsilon());
}

TEST(OpenSpaceToolkit_Core_Types_Real, PositiveInfinity)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::PositiveInfinity());

    EXPECT_TRUE(Real::PositiveInfinity().isDefined());
    EXPECT_TRUE(Real::PositiveInfinity().isInfinity());
    EXPECT_TRUE(Real::PositiveInfinity().isPositiveInfinity());
}

TEST(OpenSpaceToolkit_Core_Types_Real, NegativeInfinity)
{
    using ostk::core::types::Real;

    EXPECT_NO_THROW(Real::NegativeInfinity());

    EXPECT_TRUE(Real::NegativeInfinity().isDefined());
    EXPECT_TRUE(Real::NegativeInfinity().isInfinity());
    EXPECT_TRUE(Real::NegativeInfinity().isNegativeInfinity());
}

TEST(OpenSpaceToolkit_Core_Types_Real, Integer)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;

    {
        EXPECT_NO_THROW(Real::Integer(Integer(123)));

        EXPECT_TRUE(Real::Integer(Integer(123)).isDefined());
        EXPECT_TRUE(Real::Integer(Integer(123)).isInteger());
        EXPECT_TRUE(Real::Integer(Integer(123)).isFinite());

        EXPECT_EQ(Integer(123), Real::Integer(Integer(123)).toInteger());
    }

    {
        EXPECT_NO_THROW(Real::Integer(Integer::Undefined()));

        EXPECT_FALSE(Real::Integer(Integer::Undefined()).isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_Types_Real, CanParse)
{
    using ostk::core::types::Real;

    EXPECT_TRUE(Real::CanParse("Undefined"));

    EXPECT_TRUE(Real::CanParse("0"));
    EXPECT_TRUE(Real::CanParse("-1"));
    EXPECT_TRUE(Real::CanParse("+0"));
    EXPECT_TRUE(Real::CanParse("+1"));

    EXPECT_TRUE(Real::CanParse("0.0"));
    EXPECT_TRUE(Real::CanParse("-1.0"));
    EXPECT_TRUE(Real::CanParse("+0.0"));
    EXPECT_TRUE(Real::CanParse("+1.0"));

    EXPECT_TRUE(Real::CanParse("-2147483648.0"));
    EXPECT_TRUE(Real::CanParse("+2147483647.0"));

    EXPECT_TRUE(Real::CanParse("-2147483649.0"));
    EXPECT_TRUE(Real::CanParse("2147483648.0"));
    EXPECT_TRUE(Real::CanParse("+2147483648.0"));

    EXPECT_TRUE(Real::CanParse("NaN"));
    EXPECT_TRUE(Real::CanParse("-NaN"));
    EXPECT_TRUE(Real::CanParse("+NaN"));
    EXPECT_TRUE(Real::CanParse("nan"));
    EXPECT_TRUE(Real::CanParse("NAN"));

    EXPECT_TRUE(Real::CanParse("Inf"));
    EXPECT_TRUE(Real::CanParse("-Inf"));
    EXPECT_TRUE(Real::CanParse("+Inf"));
    EXPECT_TRUE(Real::CanParse("inf"));
    EXPECT_TRUE(Real::CanParse("INF"));

    EXPECT_FALSE(Real::CanParse(""));

    EXPECT_FALSE(Real::CanParse("abc"));

    EXPECT_FALSE(Real::CanParse("-1e600"));
    EXPECT_FALSE(Real::CanParse("+1e600"));
}

TEST(OpenSpaceToolkit_Core_Types_Real, Parse)
{
    using ostk::core::types::Real;

    EXPECT_FALSE(Real::Parse("Undefined").isDefined());
    EXPECT_FALSE(Real::Parse("NaN").isDefined());

    EXPECT_EQ(+0.0, Real::Parse("0"));
    EXPECT_EQ(-1.0, Real::Parse("-1"));
    EXPECT_EQ(+0.0, Real::Parse("+0"));
    EXPECT_EQ(+1.0, Real::Parse("+1"));

    EXPECT_EQ(+0.0, Real::Parse("0.0"));
    EXPECT_EQ(-1.0, Real::Parse("-1.0"));
    EXPECT_EQ(+0.0, Real::Parse("+0.0"));
    EXPECT_EQ(+1.0, Real::Parse("+1.0"));

    EXPECT_EQ(-2147483648.0, Real::Parse("-2147483648.0"));
    EXPECT_EQ(+2147483647.0, Real::Parse("+2147483647.0"));

    EXPECT_TRUE(Real::Parse("-Inf").isNegativeInfinity());
    EXPECT_TRUE(Real::Parse("Inf").isPositiveInfinity());
    EXPECT_TRUE(Real::Parse("+Inf").isPositiveInfinity());

    EXPECT_NO_THROW(Real::Parse("-2147483649.0"));
    EXPECT_NO_THROW(Real::Parse("2147483648.0"));
    EXPECT_NO_THROW(Real::Parse("+2147483648.0"));

    EXPECT_ANY_THROW(Real::Parse(""));

    EXPECT_ANY_THROW(Real::Parse("-NaN"));
    EXPECT_ANY_THROW(Real::Parse("+NaN"));
    EXPECT_ANY_THROW(Real::Parse("nan"));
    EXPECT_ANY_THROW(Real::Parse("NAN"));

    EXPECT_ANY_THROW(Real::Parse("abc"));

    EXPECT_ANY_THROW(Real::Parse("-1e600"));
    EXPECT_ANY_THROW(Real::Parse("+1e600"));
}
