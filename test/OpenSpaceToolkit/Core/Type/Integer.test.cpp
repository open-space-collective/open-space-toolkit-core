/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/Container/Triple.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Type_Integer, DefaultConstructor)
{
    using ostk::core::type::Integer;

    EXPECT_NO_THROW(Integer(0));
    EXPECT_NO_THROW(Integer(1));
    EXPECT_NO_THROW(Integer(123));
    EXPECT_NO_THROW(Integer(+123));
    EXPECT_NO_THROW(Integer(-123));
}

TEST(OpenSpaceToolkit_Core_Type_Integer, AssignmentOperator)
{
    using ostk::core::type::Integer;

    EXPECT_NO_THROW(Integer a = 0; (void)a;);
    EXPECT_NO_THROW(Integer a = 0; (void)a;);
    EXPECT_NO_THROW(Integer a = 1; (void)a;);
    EXPECT_NO_THROW(Integer a = 123; (void)a;);
    EXPECT_NO_THROW(Integer a = +123; (void)a;);
    EXPECT_NO_THROW(Integer a = -123; (void)a;);
}

TEST(OpenSpaceToolkit_Core_Type_Integer, EqualToOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_TRUE(Integer(0) == Integer(0));
        EXPECT_TRUE(Integer(123) == Integer(123));
        EXPECT_TRUE(Integer(+123) == Integer(+123));
        EXPECT_TRUE(Integer(-123) == Integer(-123));

        EXPECT_FALSE(Integer(0) == Integer(1));
        EXPECT_FALSE(Integer(1) == Integer(0));
        EXPECT_FALSE(Integer(-1) == Integer(+1));

        EXPECT_FALSE(Integer::PositiveInfinity() == Integer::PositiveInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() == Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::PositiveInfinity() == Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() == Integer::PositiveInfinity());
    }

    {
        EXPECT_TRUE(Integer(0) == 0);
        EXPECT_TRUE(Integer(123) == 123);
        EXPECT_TRUE(Integer(+123) == +123);
        EXPECT_TRUE(Integer(-123) == -123);

        EXPECT_FALSE(Integer(0) == 1);
        EXPECT_FALSE(Integer(1) == 0);
        EXPECT_FALSE(Integer(-1) == +1);
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, NotEqualToOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_TRUE(Integer(0) != Integer(1));
        EXPECT_TRUE(Integer(1) != Integer(0));
        EXPECT_TRUE(Integer(-1) != Integer(+1));

        EXPECT_FALSE(Integer(0) != Integer(0));
        EXPECT_FALSE(Integer(123) != Integer(123));
        EXPECT_FALSE(Integer(+123) != Integer(+123));
        EXPECT_FALSE(Integer(-123) != Integer(-123));

        EXPECT_FALSE(Integer::PositiveInfinity() != Integer::PositiveInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() != Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::PositiveInfinity() != Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() != Integer::PositiveInfinity());
    }

    {
        EXPECT_TRUE(Integer(0) != 1);
        EXPECT_TRUE(Integer(1) != 0);
        EXPECT_TRUE(Integer(-1) != +1);

        EXPECT_FALSE(Integer(0) != 0);
        EXPECT_FALSE(Integer(123) != 123);
        EXPECT_FALSE(Integer(+123) != +123);
        EXPECT_FALSE(Integer(-123) != -123);
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, LessThanOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_TRUE(Integer(0) < Integer(1));
        EXPECT_TRUE(Integer(1) < Integer(2));
        EXPECT_TRUE(Integer(-1) < Integer(0));
        EXPECT_TRUE(Integer(-1) < Integer(+1));
        EXPECT_TRUE(Integer(-123) < Integer(+123));

        EXPECT_FALSE(Integer(0) < Integer(0));
        EXPECT_FALSE(Integer(1) < Integer(0));
        EXPECT_FALSE(Integer(+1) < Integer(-1));
        EXPECT_FALSE(Integer(+123) < Integer(-123));
        EXPECT_FALSE(Integer(+123) < Integer(+123));
        EXPECT_FALSE(Integer(-123) < Integer(-123));

        EXPECT_FALSE(Integer::PositiveInfinity() < Integer::PositiveInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() < Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::PositiveInfinity() < Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() < Integer::PositiveInfinity());
    }

    {
        EXPECT_TRUE(Integer(0) < 1);
        EXPECT_TRUE(Integer(1) < 2);
        EXPECT_TRUE(Integer(-1) < 0);
        EXPECT_TRUE(Integer(-1) < +1);
        EXPECT_TRUE(Integer(-123) < +123);

        EXPECT_FALSE(Integer(0) < 0);
        EXPECT_FALSE(Integer(1) < 0);
        EXPECT_FALSE(Integer(+1) < -1);
        EXPECT_FALSE(Integer(+123) < -123);
        EXPECT_FALSE(Integer(+123) < +123);
        EXPECT_FALSE(Integer(-123) < -123);
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, LessThanOrEqualToOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_TRUE(Integer(0) <= Integer(1));
        EXPECT_TRUE(Integer(1) <= Integer(2));
        EXPECT_TRUE(Integer(-1) <= Integer(0));
        EXPECT_TRUE(Integer(-1) <= Integer(+1));
        EXPECT_TRUE(Integer(-123) <= Integer(+123));
        EXPECT_TRUE(Integer(0) <= Integer(0));
        EXPECT_TRUE(Integer(+123) <= Integer(+123));
        EXPECT_TRUE(Integer(-123) <= Integer(-123));

        EXPECT_FALSE(Integer(1) <= Integer(0));
        EXPECT_FALSE(Integer(+1) <= Integer(-1));
        EXPECT_FALSE(Integer(+123) <= Integer(-123));

        EXPECT_FALSE(Integer::PositiveInfinity() <= Integer::PositiveInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() <= Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::PositiveInfinity() <= Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() <= Integer::PositiveInfinity());
    }

    {
        EXPECT_TRUE(Integer(0) <= 1);
        EXPECT_TRUE(Integer(1) <= 2);
        EXPECT_TRUE(Integer(-1) <= 0);
        EXPECT_TRUE(Integer(-1) <= +1);
        EXPECT_TRUE(Integer(-123) <= +123);
        EXPECT_TRUE(Integer(0) <= 0);
        EXPECT_TRUE(Integer(+123) <= +123);
        EXPECT_TRUE(Integer(-123) <= -123);

        EXPECT_FALSE(Integer(1) <= 0);
        EXPECT_FALSE(Integer(+1) <= -1);
        EXPECT_FALSE(Integer(+123) <= -123);
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, GreaterThanOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_TRUE(Integer(1) > Integer(0));
        EXPECT_TRUE(Integer(2) > Integer(1));
        EXPECT_TRUE(Integer(+1) > Integer(0));
        EXPECT_TRUE(Integer(+1) > Integer(-1));
        EXPECT_TRUE(Integer(+123) > Integer(-123));

        EXPECT_FALSE(Integer(0) > Integer(0));
        EXPECT_FALSE(Integer(0) > Integer(1));
        EXPECT_FALSE(Integer(-1) > Integer(+1));
        EXPECT_FALSE(Integer(-123) > Integer(+123));
        EXPECT_FALSE(Integer(+123) > Integer(+123));
        EXPECT_FALSE(Integer(-123) > Integer(-123));

        EXPECT_FALSE(Integer::PositiveInfinity() > Integer::PositiveInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() > Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::PositiveInfinity() > Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() > Integer::PositiveInfinity());
    }

    {
        EXPECT_TRUE(Integer(1) > 0);
        EXPECT_TRUE(Integer(2) > 1);
        EXPECT_TRUE(Integer(+1) > 0);
        EXPECT_TRUE(Integer(+1) > -1);
        EXPECT_TRUE(Integer(+123) > -123);

        EXPECT_FALSE(Integer(0) > 0);
        EXPECT_FALSE(Integer(0) > 1);
        EXPECT_FALSE(Integer(-1) > +1);
        EXPECT_FALSE(Integer(-123) > +123);
        EXPECT_FALSE(Integer(+123) > +123);
        EXPECT_FALSE(Integer(-123) > -123);
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, GreaterThanOrEqualToOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_TRUE(Integer(1) >= Integer(0));
        EXPECT_TRUE(Integer(2) >= Integer(1));
        EXPECT_TRUE(Integer(+1) >= Integer(0));
        EXPECT_TRUE(Integer(+1) >= Integer(-1));
        EXPECT_TRUE(Integer(+123) >= Integer(-123));
        EXPECT_TRUE(Integer(0) >= Integer(0));
        EXPECT_TRUE(Integer(+123) >= Integer(+123));
        EXPECT_TRUE(Integer(-123) >= Integer(-123));

        EXPECT_FALSE(Integer(0) >= Integer(1));
        EXPECT_FALSE(Integer(-1) >= Integer(+1));
        EXPECT_FALSE(Integer(-123) >= Integer(+123));

        EXPECT_FALSE(Integer::PositiveInfinity() >= Integer::PositiveInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() >= Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::PositiveInfinity() >= Integer::NegativeInfinity());
        EXPECT_FALSE(Integer::NegativeInfinity() >= Integer::PositiveInfinity());
    }

    {
        EXPECT_TRUE(Integer(1) >= 0);
        EXPECT_TRUE(Integer(2) >= 1);
        EXPECT_TRUE(Integer(+1) >= 0);
        EXPECT_TRUE(Integer(+1) >= -1);
        EXPECT_TRUE(Integer(+123) >= -123);
        EXPECT_TRUE(Integer(0) >= 0);
        EXPECT_TRUE(Integer(+123) >= +123);
        EXPECT_TRUE(Integer(-123) >= -123);

        EXPECT_FALSE(Integer(0) >= 1);
        EXPECT_FALSE(Integer(-1) >= +1);
        EXPECT_FALSE(Integer(-123) >= +123);
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, AdditionOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min() + std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -2, -4},
        {-2, -1, -3},
        {-2, +0, -2},
        {-2, +1, -1},
        {-2, +2, +0},
        {-2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 2},
        {-2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-1, -2, -3},
        {-1, -1, -2},
        {-1, +0, -1},
        {-1, +1, +0},
        {-1, +2, +1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {-1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+0, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+0, -2, -2},
        {+0, -1, -1},
        {+0, +0, +0},
        {+0, +1, +1},
        {+0, +2, +2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+0, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+1, -2, -1},
        {+1, -1, +0},
        {+1, +0, +1},
        {+1, +1, +2},
        {+1, +2, +3},
        {+1, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+2, -2, +0},
        {+2, -1, +1},
        {+2, +0, +2},
        {+2, +1, +3},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max() + std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

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

    // Indeterminate forms throw
    EXPECT_ANY_THROW(Integer::PositiveInfinity() + Integer::NegativeInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() + Integer::PositiveInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, SubtractionOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2 - std::numeric_limits<Integer::ValueType>::min()},
        {-2, -2, +0},
        {-2, -1, -1},
        {-2, +0, -2},
        {-2, +1, -3},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max()},
        {-1, -2, +1},
        {-1, -1, +0},
        {-1, +0, -1},
        {-1, +1, -2},
        {-1, +2, -3},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+0, -2, +2},
        {+0, -1, +1},
        {+0, +0, +0},
        {+0, +1, -1},
        {+0, +2, -2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+0, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+1, -2, +3},
        {+1, -1, +2},
        {+1, +0, +1},
        {+1, +1, +0},
        {+1, +2, -1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+2, -2, +4},
        {+2, -1, +3},
        {+2, +0, +2},
        {+2, +1, +1},
        {+2, +2, +0},
        {+2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 3},
        {+2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

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

    // Indeterminate forms throw
    EXPECT_ANY_THROW(Integer::PositiveInfinity() - Integer::PositiveInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() - Integer::NegativeInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, MultiplicationOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1073741823, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1073741823, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-1073741823, -3, Integer::PositiveInfinity()},
        {-1073741823, -2, +2147483646},
        {-1073741823, -1, +1073741823},
        {-1073741823, +0, +0},
        {-1073741823, +1, -1073741823},
        {-1073741823, +2, -2147483646},
        {-1073741823, +3, Integer::NegativeInfinity()},
        {-1073741823, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-1073741823, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-2, -2, +4},
        {-2, -1, +2},
        {-2, +0, +0},
        {-2, +1, -2},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-1, -2, +2},
        {-1, -1, +1},
        {-1, +0, +0},
        {-1, +1, -1},
        {-1, +2, -2},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -std::numeric_limits<Integer::ValueType>::max()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},

        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+1, -2, -2},
        {+1, -1, -1},
        {+1, +0, +0},
        {+1, +1, +1},
        {+1, +2, +2},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {+2, -2, -4},
        {+2, -1, -2},
        {+2, +0, +0},
        {+2, +1, +2},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1073741823, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1073741823, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {+1073741823, -3, Integer::NegativeInfinity()},
        {+1073741823, -2, -2147483646},
        {+1073741823, -1, -1073741823},
        {+1073741823, +0, +0},
        {+1073741823, +1, +1073741823},
        {+1073741823, +2, +2147483646},
        {+1073741823, +3, Integer::PositiveInfinity()},
        {+1073741823, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+1073741823, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, -std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        if (c.isPositiveInfinity())
        {
            EXPECT_TRUE((a * b).isPositiveInfinity());
        }
        else if (c.isNegativeInfinity())
        {
            EXPECT_TRUE((a * b).isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(c, a * b);
        }
    }

    // Indeterminate forms throw
    EXPECT_ANY_THROW(Integer::PositiveInfinity() * Integer(0));
    EXPECT_ANY_THROW(Integer(0) * Integer::PositiveInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() * Integer(0));
    EXPECT_ANY_THROW(Integer(0) * Integer::NegativeInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, DivisionOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), 1},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() / -2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() / 2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), +0},

        {-2, Integer::NegativeInfinity(), +0},
        {-2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-2, -2, +1},
        {-2, -1, +2},
        {-2, +1, -2},
        {-2, +2, -1},
        {-2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-2, Integer::PositiveInfinity(), +0},

        {-1, Integer::NegativeInfinity(), +0},
        {-1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-1, -2, +0},
        {-1, -1, +1},
        {-1, +1, -1},
        {-1, +2, +0},
        {-1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-1, Integer::PositiveInfinity(), +0},

        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::NegativeInfinity(), +0},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+1, -2, +0},
        {+1, -1, -1},
        {+1, +1, +1},
        {+1, +2, +0},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+1, Integer::PositiveInfinity(), +0},

        {+2, Integer::NegativeInfinity(), +0},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+2, -2, -1},
        {+2, -1, -2},
        {+2, +1, +2},
        {+2, +2, +1},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+2, Integer::PositiveInfinity(), +0},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() / -2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() / -1},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() / 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +1},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), +0},

        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        if (c.isPositiveInfinity())
        {
            EXPECT_TRUE((a / b).isPositiveInfinity());
        }
        else if (c.isNegativeInfinity())
        {
            EXPECT_TRUE((a / b).isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(c, a / b);
        }
    }

    // Indeterminate forms throw
    EXPECT_ANY_THROW(Integer::PositiveInfinity() / Integer::PositiveInfinity());
    EXPECT_ANY_THROW(Integer::PositiveInfinity() / Integer::NegativeInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() / Integer::PositiveInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() / Integer::NegativeInfinity());

    // Division by zero throws
    EXPECT_ANY_THROW(Integer(-2) / Integer(0));
    EXPECT_ANY_THROW(Integer(-1) / Integer(0));
    EXPECT_ANY_THROW(Integer(0) / Integer(0));
    EXPECT_ANY_THROW(Integer(+1) / Integer(0));
    EXPECT_ANY_THROW(Integer(+2) / Integer(0));
    EXPECT_ANY_THROW(Integer(std::numeric_limits<Integer::ValueType>::min()) / Integer(0));
    EXPECT_ANY_THROW(Integer(std::numeric_limits<Integer::ValueType>::max()) / Integer(0));
    EXPECT_ANY_THROW(Integer::NegativeInfinity() / Integer(0));
    EXPECT_ANY_THROW(Integer::PositiveInfinity() / Integer(0));
}

TEST(OpenSpaceToolkit_Core_Type_Integer, ModuloOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), -1, +0},
        {Integer::NegativeInfinity(), +1, +0},

        {std::numeric_limits<Integer::ValueType>::min(),
         Integer::NegativeInfinity(),
         std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), -2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(),
         Integer::PositiveInfinity(),
         std::numeric_limits<Integer::ValueType>::min()},

        {-2, Integer::NegativeInfinity(), -2},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2},
        {-2, -3, -2},
        {-2, -2, +0},
        {-2, -1, +0},
        {-2, +1, +0},
        {-2, +2, +0},
        {-2, +3, -2},
        {-2, std::numeric_limits<Integer::ValueType>::max(), -2},
        {-2, Integer::PositiveInfinity(), -2},

        {-1, Integer::NegativeInfinity(), -1},
        {-1, std::numeric_limits<Integer::ValueType>::min(), -1},
        {-1, -3, -1},
        {-1, -2, -1},
        {-1, -1, +0},
        {-1, +1, +0},
        {-1, +2, -1},
        {-1, +3, -1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -1},
        {-1, Integer::PositiveInfinity(), -1},

        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -3, +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, +3, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::NegativeInfinity(), +1},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +1},
        {+1, -3, +1},
        {+1, -2, +1},
        {+1, -1, +0},
        {+1, +1, +0},
        {+1, +2, +1},
        {+1, +3, +1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +1},
        {+1, Integer::PositiveInfinity(), +1},

        {+2, Integer::NegativeInfinity(), +2},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +2},
        {+2, -3, +2},
        {+2, -2, +0},
        {+2, -1, +0},
        {+2, +1, +0},
        {+2, +2, +0},
        {+2, +3, +2},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +2},
        {+2, Integer::PositiveInfinity(), +2},

        {std::numeric_limits<Integer::ValueType>::max(),
         Integer::NegativeInfinity(),
         std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(),
         Integer::PositiveInfinity(),
         std::numeric_limits<Integer::ValueType>::max()},

        {Integer::PositiveInfinity(), -1, +0},
        {Integer::PositiveInfinity(), +1, +0}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        EXPECT_EQ(c, a % b);
    }

    // Modulo by zero throws
    EXPECT_ANY_THROW(Integer(-2) % Integer(0));
    EXPECT_ANY_THROW(Integer(-1) % Integer(0));
    EXPECT_ANY_THROW(Integer(0) % Integer(0));
    EXPECT_ANY_THROW(Integer(+1) % Integer(0));
    EXPECT_ANY_THROW(Integer(+2) % Integer(0));
    EXPECT_ANY_THROW(Integer(std::numeric_limits<Integer::ValueType>::min()) % Integer(0));
    EXPECT_ANY_THROW(Integer(std::numeric_limits<Integer::ValueType>::max()) % Integer(0));
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer(0));
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer(0));

    // Infinity % anything (except +/-1) throws
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer::PositiveInfinity());
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer::NegativeInfinity());
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer(std::numeric_limits<Integer::ValueType>::min()));
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer(-2));
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer(+2));
    EXPECT_ANY_THROW(Integer::PositiveInfinity() % Integer(std::numeric_limits<Integer::ValueType>::max()));
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer::PositiveInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer::NegativeInfinity());
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer(std::numeric_limits<Integer::ValueType>::min()));
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer(-2));
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer(+2));
    EXPECT_ANY_THROW(Integer::NegativeInfinity() % Integer(std::numeric_limits<Integer::ValueType>::max()));
}

TEST(OpenSpaceToolkit_Core_Type_Integer, AdditionAssignmentOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min() + std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -2, -4},
        {-2, -1, -3},
        {-2, +0, -2},
        {-2, +1, -1},
        {-2, +2, +0},
        {-2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 2},
        {-2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-1, -2, -3},
        {-1, -1, -2},
        {-1, +0, -1},
        {-1, +1, +0},
        {-1, +2, +1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {-1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+0, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+0, -2, -2},
        {+0, -1, -1},
        {+0, +0, +0},
        {+0, +1, +1},
        {+0, +2, +2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+0, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+1, -2, -1},
        {+1, -1, +0},
        {+1, +0, +1},
        {+1, +1, +2},
        {+1, +2, +3},
        {+1, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+2, -2, +0},
        {+2, -1, +1},
        {+2, +0, +2},
        {+2, +1, +3},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max() + std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        a += b;

        if (c.isPositiveInfinity())
        {
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (c.isNegativeInfinity())
        {
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(c, a);
        }
    }

    // Indeterminate forms throw
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a += Integer::NegativeInfinity());
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a += Integer::PositiveInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, SubtractionAssignmentOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2 - std::numeric_limits<Integer::ValueType>::min()},
        {-2, -2, +0},
        {-2, -1, -1},
        {-2, +0, -2},
        {-2, +1, -3},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max()},
        {-1, -2, +1},
        {-1, -1, +0},
        {-1, +0, -1},
        {-1, +1, -2},
        {-1, +2, -3},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+0, -2, +2},
        {+0, -1, +1},
        {+0, +0, +0},
        {+0, +1, -1},
        {+0, +2, -2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+0, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+1, -2, +3},
        {+1, -1, +2},
        {+1, +0, +1},
        {+1, +1, +0},
        {+1, +2, -1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+2, -2, +4},
        {+2, -1, +3},
        {+2, +0, +2},
        {+2, +1, +1},
        {+2, +2, +0},
        {+2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 3},
        {+2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        a -= b;

        if (c.isPositiveInfinity())
        {
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (c.isNegativeInfinity())
        {
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(c, a);
        }
    }

    // Indeterminate forms throw
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a -= Integer::PositiveInfinity());
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a -= Integer::NegativeInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, MultiplicationAssignmentOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1073741823, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1073741823, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-1073741823, -3, Integer::PositiveInfinity()},
        {-1073741823, -2, +2147483646},
        {-1073741823, -1, +1073741823},
        {-1073741823, +0, +0},
        {-1073741823, +1, -1073741823},
        {-1073741823, +2, -2147483646},
        {-1073741823, +3, Integer::NegativeInfinity()},
        {-1073741823, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-1073741823, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-2, -2, +4},
        {-2, -1, +2},
        {-2, +0, +0},
        {-2, +1, -2},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-1, -2, +2},
        {-1, -1, +1},
        {-1, +0, +0},
        {-1, +1, -1},
        {-1, +2, -2},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -std::numeric_limits<Integer::ValueType>::max()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},

        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+1, -2, -2},
        {+1, -1, -1},
        {+1, +0, +0},
        {+1, +1, +1},
        {+1, +2, +2},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {+2, -2, -4},
        {+2, -1, -2},
        {+2, +0, +0},
        {+2, +1, +2},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1073741823, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1073741823, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {+1073741823, -3, Integer::NegativeInfinity()},
        {+1073741823, -2, -2147483646},
        {+1073741823, -1, -1073741823},
        {+1073741823, +0, +0},
        {+1073741823, +1, +1073741823},
        {+1073741823, +2, +2147483646},
        {+1073741823, +3, Integer::PositiveInfinity()},
        {+1073741823, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+1073741823, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, -std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::max(),
         Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        a *= b;

        if (c.isPositiveInfinity())
        {
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (c.isNegativeInfinity())
        {
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(c, a);
        }
    }

    // Indeterminate forms throw
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a *= Integer(0));
    }
    {
        Integer a = Integer(0);
        EXPECT_ANY_THROW(a *= Integer::PositiveInfinity());
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a *= Integer(0));
    }
    {
        Integer a = Integer(0);
        EXPECT_ANY_THROW(a *= Integer::NegativeInfinity());
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, DivisionAssignmentOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), 1},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() / -2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() / 2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), +0},

        {-2, Integer::NegativeInfinity(), +0},
        {-2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-2, -2, +1},
        {-2, -1, +2},
        {-2, +1, -2},
        {-2, +2, -1},
        {-2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-2, Integer::PositiveInfinity(), +0},

        {-1, Integer::NegativeInfinity(), +0},
        {-1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-1, -2, +0},
        {-1, -1, +1},
        {-1, +1, -1},
        {-1, +2, +0},
        {-1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-1, Integer::PositiveInfinity(), +0},

        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::NegativeInfinity(), +0},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+1, -2, +0},
        {+1, -1, -1},
        {+1, +1, +1},
        {+1, +2, +0},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+1, Integer::PositiveInfinity(), +0},

        {+2, Integer::NegativeInfinity(), +0},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+2, -2, -1},
        {+2, -1, -2},
        {+2, +1, +2},
        {+2, +2, +1},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+2, Integer::PositiveInfinity(), +0},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() / -2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() / -1},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() / 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +1},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), +0},

        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        a /= b;

        if (c.isPositiveInfinity())
        {
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (c.isNegativeInfinity())
        {
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(c, a);
        }
    }

    // Indeterminate forms throw
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a /= Integer::PositiveInfinity());
    }
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a /= Integer::NegativeInfinity());
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a /= Integer::PositiveInfinity());
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a /= Integer::NegativeInfinity());
    }

    // Division by zero throws
    {
        Integer a = Integer(1);
        EXPECT_ANY_THROW(a /= Integer(0));
    }
    {
        Integer a = Integer(0);
        EXPECT_ANY_THROW(a /= Integer(0));
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a /= Integer(0));
    }
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a /= Integer(0));
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, ModuloAssignmentOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Triple;
    using ostk::core::type::Integer;

    Array<Triple<Integer, Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), -1, +0},
        {Integer::NegativeInfinity(), +1, +0},

        {std::numeric_limits<Integer::ValueType>::min(),
         Integer::NegativeInfinity(),
         std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), -2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(),
         Integer::PositiveInfinity(),
         std::numeric_limits<Integer::ValueType>::min()},

        {-2, Integer::NegativeInfinity(), -2},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2},
        {-2, -3, -2},
        {-2, -2, +0},
        {-2, -1, +0},
        {-2, +1, +0},
        {-2, +2, +0},
        {-2, +3, -2},
        {-2, std::numeric_limits<Integer::ValueType>::max(), -2},
        {-2, Integer::PositiveInfinity(), -2},

        {-1, Integer::NegativeInfinity(), -1},
        {-1, std::numeric_limits<Integer::ValueType>::min(), -1},
        {-1, -3, -1},
        {-1, -2, -1},
        {-1, -1, +0},
        {-1, +1, +0},
        {-1, +2, -1},
        {-1, +3, -1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -1},
        {-1, Integer::PositiveInfinity(), -1},

        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -3, +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, +3, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::NegativeInfinity(), +1},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +1},
        {+1, -3, +1},
        {+1, -2, +1},
        {+1, -1, +0},
        {+1, +1, +0},
        {+1, +2, +1},
        {+1, +3, +1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +1},
        {+1, Integer::PositiveInfinity(), +1},

        {+2, Integer::NegativeInfinity(), +2},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +2},
        {+2, -3, +2},
        {+2, -2, +0},
        {+2, -1, +0},
        {+2, +1, +0},
        {+2, +2, +0},
        {+2, +3, +2},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +2},
        {+2, Integer::PositiveInfinity(), +2},

        {std::numeric_limits<Integer::ValueType>::max(),
         Integer::NegativeInfinity(),
         std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(),
         std::numeric_limits<Integer::ValueType>::min(),
         std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(),
         Integer::PositiveInfinity(),
         std::numeric_limits<Integer::ValueType>::max()},

        {Integer::PositiveInfinity(), -1, +0},
        {Integer::PositiveInfinity(), +1, +0}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;
        const Integer& c = testCase.third;

        a %= b;

        EXPECT_EQ(c, a);
    }

    // Modulo by zero throws
    {
        Integer a = Integer(1);
        EXPECT_ANY_THROW(a %= Integer(0));
    }
    {
        Integer a = Integer(0);
        EXPECT_ANY_THROW(a %= Integer(0));
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a %= Integer(0));
    }
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a %= Integer(0));
    }

    // Infinity % anything (except +/-1) throws
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a %= Integer::PositiveInfinity());
    }
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a %= Integer(-2));
    }
    {
        Integer a = Integer::PositiveInfinity();
        EXPECT_ANY_THROW(a %= Integer(+2));
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a %= Integer::NegativeInfinity());
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a %= Integer(-2));
    }
    {
        Integer a = Integer::NegativeInfinity();
        EXPECT_ANY_THROW(a %= Integer(+2));
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, UnaryPlusOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;

    Array<Pair<Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {-2, -2},
        {-1, -1},
        {+0, +0},
        {+1, +1},
        {+2, +2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;

        Integer c = +a;

        if (b.isPositiveInfinity())
        {
            EXPECT_TRUE(c.isPositiveInfinity());
        }
        else if (b.isNegativeInfinity())
        {
            EXPECT_TRUE(c.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(b, c);
        }
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, UnaryMinusOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;

    Array<Pair<Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-2, +2},
        {-1, +1},
        {+0, +0},
        {+1, -1},
        {+2, -2},
        {std::numeric_limits<Integer::ValueType>::max(), -std::numeric_limits<Integer::ValueType>::max()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity()}

    };

    for (const auto& testCase : testCases)
    {
        const Integer& a = testCase.first;
        const Integer& b = testCase.second;

        Integer c = -a;

        if (b.isPositiveInfinity())
        {
            EXPECT_TRUE(c.isPositiveInfinity());
        }
        else if (b.isNegativeInfinity())
        {
            EXPECT_TRUE(c.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(b, c);
        }
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, PrefixIncrementOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;

    Array<Pair<Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {-2, -1},
        {-1, +0},
        {+0, +1},
        {+1, +2},
        {+2, +3},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;

        Integer c = ++a;

        if (b.isPositiveInfinity())
        {
            EXPECT_TRUE(c.isPositiveInfinity());
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (b.isNegativeInfinity())
        {
            EXPECT_TRUE(c.isNegativeInfinity());
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(b, c);
            EXPECT_EQ(b, a);
        }
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, PrefixDecrementOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;

    Array<Pair<Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -3},
        {-1, -2},
        {+0, -1},
        {+1, +0},
        {+2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer& b = testCase.second;

        Integer c = --a;

        if (b.isPositiveInfinity())
        {
            EXPECT_TRUE(c.isPositiveInfinity());
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (b.isNegativeInfinity())
        {
            EXPECT_TRUE(c.isNegativeInfinity());
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(b, c);
            EXPECT_EQ(b, a);
        }
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, PostfixIncrementOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;

    Array<Pair<Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {-2, -1},
        {-1, +0},
        {+0, +1},
        {+1, +2},
        {+2, +3},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer aCopy = a;
        const Integer& b = testCase.second;

        Integer c = a++;

        // c should equal original value
        if (aCopy.isPositiveInfinity())
        {
            EXPECT_TRUE(c.isPositiveInfinity());
        }
        else if (aCopy.isNegativeInfinity())
        {
            EXPECT_TRUE(c.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(aCopy, c);
        }

        // a should equal incremented value
        if (b.isPositiveInfinity())
        {
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (b.isNegativeInfinity())
        {
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(b, a);
        }
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, PostfixDecrementOperator)
{
    using ostk::core::container::Array;
    using ostk::core::container::Pair;
    using ostk::core::type::Integer;

    Array<Pair<Integer, Integer>> testCases = {

        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -3},
        {-1, -2},
        {+0, -1},
        {+1, +0},
        {+2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    };

    for (auto& testCase : testCases)
    {
        Integer& a = testCase.first;
        const Integer aCopy = a;
        const Integer& b = testCase.second;

        Integer c = a--;

        // c should equal original value
        if (aCopy.isPositiveInfinity())
        {
            EXPECT_TRUE(c.isPositiveInfinity());
        }
        else if (aCopy.isNegativeInfinity())
        {
            EXPECT_TRUE(c.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(aCopy, c);
        }

        // a should equal decremented value
        if (b.isPositiveInfinity())
        {
            EXPECT_TRUE(a.isPositiveInfinity());
        }
        else if (b.isNegativeInfinity())
        {
            EXPECT_TRUE(a.isNegativeInfinity());
        }
        else
        {
            EXPECT_EQ(b, a);
        }
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, ValueTypeOperator)
{
    using ostk::core::type::Integer;

    {
        EXPECT_ANY_THROW(Integer::ValueType a = Integer::NegativeInfinity(); (void)a;);
    }

    {
        Integer::ValueType a = Integer(std::numeric_limits<Integer::ValueType>::min());

        EXPECT_EQ(std::numeric_limits<Integer::ValueType>::min(), a);
    }

    {
        Integer::ValueType a = Integer(-1);

        EXPECT_EQ(-1, a);
    }

    {
        Integer::ValueType a = Integer(+0);

        EXPECT_EQ(+0, a);
    }

    {
        Integer::ValueType a = Integer(+1);

        EXPECT_EQ(+1, a);
    }

    {
        EXPECT_ANY_THROW(Integer::ValueType a = Integer::PositiveInfinity(); (void)a;);
    }
}

// TEST (OpenSpaceToolkit_Core_Type_Integer, StreamOperator)
// {

//     using ostk::core::type::Integer ;

//     FAIL() ;

// }

TEST(OpenSpaceToolkit_Core_Type_Integer, IsZero)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(0).isZero());
    EXPECT_TRUE(Integer(+0).isZero());

    EXPECT_FALSE(Integer(-1).isZero());
    EXPECT_FALSE(Integer(+1).isZero());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isZero());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isZero());
    EXPECT_FALSE(Integer::NegativeInfinity().isZero());
    EXPECT_FALSE(Integer::PositiveInfinity().isZero());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsPositive)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(0).isPositive());
    EXPECT_TRUE(Integer(+0).isPositive());
    EXPECT_TRUE(Integer(+1).isPositive());
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isPositive());
    EXPECT_TRUE(Integer::PositiveInfinity().isPositive());

    EXPECT_FALSE(Integer(-1).isPositive());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isPositive());
    EXPECT_FALSE(Integer::NegativeInfinity().isPositive());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsNegative)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(0).isNegative());
    EXPECT_TRUE(Integer(-1).isNegative());
    EXPECT_TRUE(Integer(+0).isNegative());
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isNegative());
    EXPECT_TRUE(Integer::NegativeInfinity().isNegative());

    EXPECT_FALSE(Integer(+1).isNegative());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isNegative());
    EXPECT_FALSE(Integer::PositiveInfinity().isNegative());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsStrictlyPositive)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(+1).isStrictlyPositive());
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isStrictlyPositive());
    EXPECT_TRUE(Integer::PositiveInfinity().isStrictlyPositive());

    EXPECT_FALSE(Integer(0).isStrictlyPositive());
    EXPECT_FALSE(Integer(-1).isStrictlyPositive());
    EXPECT_FALSE(Integer(+0).isStrictlyPositive());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isStrictlyPositive());
    EXPECT_FALSE(Integer::NegativeInfinity().isStrictlyPositive());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsStrictlyNegative)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(-1).isStrictlyNegative());
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isStrictlyNegative());
    EXPECT_TRUE(Integer::NegativeInfinity().isStrictlyNegative());

    EXPECT_FALSE(Integer(0).isStrictlyNegative());
    EXPECT_FALSE(Integer(+1).isStrictlyNegative());
    EXPECT_FALSE(Integer(+0).isStrictlyNegative());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isStrictlyNegative());
    EXPECT_FALSE(Integer::PositiveInfinity().isStrictlyNegative());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsInfinity)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer::NegativeInfinity().isInfinity());
    EXPECT_TRUE(Integer::PositiveInfinity().isInfinity());

    EXPECT_FALSE(Integer(0).isInfinity());
    EXPECT_FALSE(Integer(-1).isInfinity());
    EXPECT_FALSE(Integer(+0).isInfinity());
    EXPECT_FALSE(Integer(+1).isInfinity());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isInfinity());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsPositiveInfinity)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer::PositiveInfinity().isPositiveInfinity());

    EXPECT_FALSE(Integer(0).isPositiveInfinity());
    EXPECT_FALSE(Integer(-1).isPositiveInfinity());
    EXPECT_FALSE(Integer(+0).isPositiveInfinity());
    EXPECT_FALSE(Integer(+1).isPositiveInfinity());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isPositiveInfinity());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isPositiveInfinity());
    EXPECT_FALSE(Integer::NegativeInfinity().isPositiveInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsNegativeInfinity)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer::NegativeInfinity().isNegativeInfinity());

    EXPECT_FALSE(Integer(0).isNegativeInfinity());
    EXPECT_FALSE(Integer(-1).isNegativeInfinity());
    EXPECT_FALSE(Integer(+0).isNegativeInfinity());
    EXPECT_FALSE(Integer(+1).isNegativeInfinity());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isNegativeInfinity());
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isNegativeInfinity());
    EXPECT_FALSE(Integer::PositiveInfinity().isNegativeInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsFinite)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(0).isFinite());
    EXPECT_TRUE(Integer(-1).isFinite());
    EXPECT_TRUE(Integer(+0).isFinite());
    EXPECT_TRUE(Integer(+1).isFinite());
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isFinite());
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isFinite());

    EXPECT_FALSE(Integer::NegativeInfinity().isFinite());
    EXPECT_FALSE(Integer::PositiveInfinity().isFinite());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsEven)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(0).isEven());

    EXPECT_TRUE(Integer(-4).isEven());
    EXPECT_TRUE(Integer(-2).isEven());
    EXPECT_TRUE(Integer(+0).isEven());
    EXPECT_TRUE(Integer(+2).isEven());
    EXPECT_TRUE(Integer(+4).isEven());

    EXPECT_FALSE(Integer(-3).isEven());
    EXPECT_FALSE(Integer(-1).isEven());
    EXPECT_FALSE(Integer(+1).isEven());
    EXPECT_FALSE(Integer(+3).isEven());

    EXPECT_FALSE(Integer::NegativeInfinity().isEven());
    EXPECT_FALSE(Integer::PositiveInfinity().isEven());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, IsOdd)
{
    using ostk::core::type::Integer;

    EXPECT_TRUE(Integer(-3).isOdd());
    EXPECT_TRUE(Integer(-1).isOdd());
    EXPECT_TRUE(Integer(+1).isOdd());
    EXPECT_TRUE(Integer(+3).isOdd());

    EXPECT_FALSE(Integer(-2).isOdd());
    EXPECT_FALSE(Integer(+0).isOdd());
    EXPECT_FALSE(Integer(+2).isOdd());

    EXPECT_FALSE(Integer::NegativeInfinity().isOdd());
    EXPECT_FALSE(Integer::PositiveInfinity().isOdd());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, GetSign)
{
    using ostk::core::type::Integer;
    using ostk::core::type::Sign;

    EXPECT_EQ(Sign::None, Integer(0).getSign());
    EXPECT_EQ(Sign::Negative, Integer(-1).getSign());
    EXPECT_EQ(Sign::None, Integer(+0).getSign());
    EXPECT_EQ(Sign::Positive, Integer(+1).getSign());
    EXPECT_EQ(Sign::Negative, Integer(std::numeric_limits<Integer::ValueType>::min()).getSign());
    EXPECT_EQ(Sign::Positive, Integer(std::numeric_limits<Integer::ValueType>::max()).getSign());
    EXPECT_EQ(Sign::Negative, Integer::NegativeInfinity().getSign());
    EXPECT_EQ(Sign::Positive, Integer::PositiveInfinity().getSign());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, ToString)
{
    using ostk::core::type::Integer;

    EXPECT_EQ("0", Integer(0).toString());
    EXPECT_EQ("-1", Integer(-1).toString());
    EXPECT_EQ("0", Integer(+0).toString());
    EXPECT_EQ("1", Integer(+1).toString());
    EXPECT_EQ("-Inf", Integer::NegativeInfinity().toString());
    EXPECT_EQ("+Inf", Integer::PositiveInfinity().toString());
}

// TEST (OpenSpaceToolkit_Core_Type_Integer, GetObject)
// {

//     using ostk::core::type::Integer ;

//     FAIL() ;

// }

TEST(OpenSpaceToolkit_Core_Type_Integer, PositiveInfinity)
{
    using ostk::core::type::Integer;

    EXPECT_NO_THROW(Integer::PositiveInfinity());

    EXPECT_TRUE(Integer::PositiveInfinity().isInfinity());
    EXPECT_TRUE(Integer::PositiveInfinity().isPositiveInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, NegativeInfinity)
{
    using ostk::core::type::Integer;

    EXPECT_NO_THROW(Integer::NegativeInfinity());

    EXPECT_TRUE(Integer::NegativeInfinity().isInfinity());
    EXPECT_TRUE(Integer::NegativeInfinity().isNegativeInfinity());
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Int8)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Int8(ostk::core::type::Int8(0)));

        EXPECT_NO_THROW(Integer::Int8(ostk::core::type::Int8(-1)));
        EXPECT_NO_THROW(Integer::Int8(ostk::core::type::Int8(+1)));

        EXPECT_NO_THROW(Integer::Int8(ostk::core::type::Int8(std::numeric_limits<ostk::core::type::Int8>::min())));
        EXPECT_NO_THROW(Integer::Int8(ostk::core::type::Int8(std::numeric_limits<ostk::core::type::Int8>::max())));
    }

    {
        EXPECT_EQ(0, Integer::Int8(ostk::core::type::Int8(0)));

        EXPECT_EQ(-1, Integer::Int8(ostk::core::type::Int8(-1)));
        EXPECT_EQ(+1, Integer::Int8(ostk::core::type::Int8(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::min(),
            Integer::Int8(ostk::core::type::Int8(std::numeric_limits<ostk::core::type::Int8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::max(),
            Integer::Int8(ostk::core::type::Int8(std::numeric_limits<ostk::core::type::Int8>::max()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Int16)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(0)));

        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(-1)));
        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(+1)));

        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int8>::min())));
        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int8>::max())));

        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int16>::min())));
        EXPECT_NO_THROW(Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int16>::max())));
    }

    {
        EXPECT_EQ(0, Integer::Int16(ostk::core::type::Int16(0)));

        EXPECT_EQ(-1, Integer::Int16(ostk::core::type::Int16(-1)));
        EXPECT_EQ(+1, Integer::Int16(ostk::core::type::Int16(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::min(),
            Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::max(),
            Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int8>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int16>::min(),
            Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int16>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int16>::max(),
            Integer::Int16(ostk::core::type::Int16(std::numeric_limits<ostk::core::type::Int16>::max()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Int32)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(0)));

        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(-1)));
        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(+1)));

        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int8>::min())));
        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int8>::max())));

        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int16>::min())));
        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int16>::max())));

        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int32>::min())));
        EXPECT_NO_THROW(Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int32>::max())));
    }

    {
        EXPECT_EQ(0, Integer::Int32(ostk::core::type::Int32(0)));

        EXPECT_EQ(-1, Integer::Int32(ostk::core::type::Int32(-1)));
        EXPECT_EQ(+1, Integer::Int32(ostk::core::type::Int32(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::min(),
            Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::max(),
            Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int8>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int16>::min(),
            Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int16>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int16>::max(),
            Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int16>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int32>::min(),
            Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int32>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int32>::max(),
            Integer::Int32(ostk::core::type::Int32(std::numeric_limits<ostk::core::type::Int32>::max()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Int64)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(0)));

        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(-1)));
        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(+1)));

        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int8>::min())));
        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int8>::max())));

        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int16>::min())));
        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int16>::max())));

        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int32>::min())));
        EXPECT_NO_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int32>::max())));

        EXPECT_ANY_THROW(
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int32>::min()) - 1)
        );
        EXPECT_ANY_THROW(
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int32>::max()) + 1)
        );

        EXPECT_ANY_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int64>::min())));
        EXPECT_ANY_THROW(Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int64>::max())));
    }

    {
        EXPECT_EQ(0, Integer::Int64(ostk::core::type::Int64(0)));

        EXPECT_EQ(-1, Integer::Int64(ostk::core::type::Int64(-1)));
        EXPECT_EQ(+1, Integer::Int64(ostk::core::type::Int64(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::min(),
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int8>::max(),
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int8>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int16>::min(),
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int16>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int16>::max(),
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int16>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int32>::min(),
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int32>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Int32>::max(),
            Integer::Int64(ostk::core::type::Int64(std::numeric_limits<ostk::core::type::Int32>::max()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Uint8)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Uint8(ostk::core::type::Uint8(0)));

        EXPECT_NO_THROW(Integer::Uint8(ostk::core::type::Uint8(+1)));

        EXPECT_NO_THROW(Integer::Uint8(ostk::core::type::Uint8(std::numeric_limits<ostk::core::type::Uint8>::min())));
        EXPECT_NO_THROW(Integer::Uint8(ostk::core::type::Uint8(std::numeric_limits<ostk::core::type::Uint8>::max())));
    }

    {
        EXPECT_EQ(0, Integer::Uint8(ostk::core::type::Uint8(0)));

        EXPECT_EQ(+1, Integer::Uint8(ostk::core::type::Uint8(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::min(),
            Integer::Uint8(ostk::core::type::Uint8(std::numeric_limits<ostk::core::type::Uint8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::max(),
            Integer::Uint8(ostk::core::type::Uint8(std::numeric_limits<ostk::core::type::Uint8>::max()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Uint16)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Uint16(ostk::core::type::Uint16(0)));

        EXPECT_NO_THROW(Integer::Uint16(ostk::core::type::Uint16(+1)));

        EXPECT_NO_THROW(Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint8>::min())));
        EXPECT_NO_THROW(Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint8>::max())));

        EXPECT_NO_THROW(Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );
        EXPECT_NO_THROW(Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint16>::max()))
        );
    }

    {
        EXPECT_EQ(0, Integer::Uint16(ostk::core::type::Uint16(0)));

        EXPECT_EQ(+1, Integer::Uint16(ostk::core::type::Uint16(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::min(),
            Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::max(),
            Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint8>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint16>::min(),
            Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint16>::max(),
            Integer::Uint16(ostk::core::type::Uint16(std::numeric_limits<ostk::core::type::Uint16>::max()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Uint32)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(0)));

        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(+1)));

        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint8>::min())));
        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint8>::min())));

        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );
        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );

        EXPECT_NO_THROW(Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint32>::min()))
        );

        EXPECT_ANY_THROW(Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint32>::max()))
        );
    }

    {
        EXPECT_EQ(0, Integer::Uint32(ostk::core::type::Uint32(0)));

        EXPECT_EQ(+1, Integer::Uint32(ostk::core::type::Uint32(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::min(),
            Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::max(),
            Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint8>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint16>::min(),
            Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint16>::max(),
            Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint16>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint32>::min(),
            Integer::Uint32(ostk::core::type::Uint32(std::numeric_limits<ostk::core::type::Uint32>::min()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Uint64)
{
    using ostk::core::type::Integer;

    {
        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(0)));

        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(+1)));

        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint8>::min())));
        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint8>::max())));

        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );
        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint16>::max()))
        );

        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint32>::min()))
        );

        EXPECT_NO_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint64>::min()))
        );

        EXPECT_ANY_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint32>::max()))
        );
        EXPECT_ANY_THROW(Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint64>::max()))
        );
    }

    {
        EXPECT_EQ(0, Integer::Uint64(ostk::core::type::Uint64(0)));

        EXPECT_EQ(+1, Integer::Uint64(ostk::core::type::Uint64(+1)));

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::min(),
            Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint8>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint8>::max(),
            Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint8>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint16>::min(),
            Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint16>::min()))
        );
        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint16>::max(),
            Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint16>::max()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint32>::min(),
            Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint32>::min()))
        );

        EXPECT_EQ(
            std::numeric_limits<ostk::core::type::Uint64>::min(),
            Integer::Uint64(ostk::core::type::Uint64(std::numeric_limits<ostk::core::type::Uint64>::min()))
        );
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Index)
{
    using ostk::core::type::Index;
    using ostk::core::type::Integer;

    {
        EXPECT_EQ(0, Integer::Index(Index(0)));
        EXPECT_EQ(1, Integer::Index(Index(1)));
    }

    {
        EXPECT_ANY_THROW(Integer::Index(Index(std::numeric_limits<Index>::max())));
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Size)
{
    using ostk::core::type::Integer;
    using ostk::core::type::Size;

    {
        EXPECT_EQ(0, Integer::Size(Size(0)));
        EXPECT_EQ(1, Integer::Size(Size(1)));
    }

    {
        EXPECT_ANY_THROW(Integer::Size(Size(std::numeric_limits<Size>::max())));
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, CanParse)
{
    using ostk::core::type::Integer;

    // Char

    {
        EXPECT_TRUE(Integer::CanParse('0'));
        EXPECT_TRUE(Integer::CanParse('1'));
        EXPECT_TRUE(Integer::CanParse('2'));
        EXPECT_TRUE(Integer::CanParse('3'));
        EXPECT_TRUE(Integer::CanParse('9'));

        EXPECT_FALSE(Integer::CanParse('a'));
        EXPECT_FALSE(Integer::CanParse('-'));
        EXPECT_FALSE(Integer::CanParse('+'));
    }

    // String

    {
        EXPECT_TRUE(Integer::CanParse("0"));
        EXPECT_TRUE(Integer::CanParse("-1"));
        EXPECT_TRUE(Integer::CanParse("+0"));
        EXPECT_TRUE(Integer::CanParse("+1"));

        EXPECT_TRUE(Integer::CanParse("-2147483648"));
        EXPECT_TRUE(Integer::CanParse("+2147483647"));

        EXPECT_TRUE(Integer::CanParse("-Inf"));
        EXPECT_TRUE(Integer::CanParse("Inf"));
        EXPECT_TRUE(Integer::CanParse("+Inf"));

        EXPECT_FALSE(Integer::CanParse(""));
        EXPECT_FALSE(Integer::CanParse("abc"));
        EXPECT_FALSE(Integer::CanParse("NaN"));
        EXPECT_FALSE(Integer::CanParse("-2147483649"));
        EXPECT_FALSE(Integer::CanParse("2147483648"));
        EXPECT_FALSE(Integer::CanParse("+2147483648"));
    }
}

TEST(OpenSpaceToolkit_Core_Type_Integer, Parse)
{
    using ostk::core::type::Integer;

    // Char

    {
        EXPECT_EQ(0, Integer::Parse('0'));
        EXPECT_EQ(1, Integer::Parse('1'));
        EXPECT_EQ(2, Integer::Parse('2'));
        EXPECT_EQ(3, Integer::Parse('3'));
        EXPECT_EQ(9, Integer::Parse('9'));

        EXPECT_ANY_THROW(Integer::Parse('a'));
        EXPECT_ANY_THROW(Integer::Parse('-'));
        EXPECT_ANY_THROW(Integer::Parse('+'));
    }

    // String

    {
        EXPECT_EQ(+0, Integer::Parse("0"));
        EXPECT_EQ(-1, Integer::Parse("-1"));
        EXPECT_EQ(+0, Integer::Parse("+0"));
        EXPECT_EQ(+1, Integer::Parse("+1"));

        EXPECT_EQ(-2147483648, Integer::Parse("-2147483648"));
        EXPECT_EQ(+2147483647, Integer::Parse("+2147483647"));

        EXPECT_TRUE(Integer::Parse("-Inf").isNegativeInfinity());
        EXPECT_TRUE(Integer::Parse("Inf").isPositiveInfinity());
        EXPECT_TRUE(Integer::Parse("+Inf").isPositiveInfinity());

        EXPECT_ANY_THROW(Integer::Parse(""));
        EXPECT_ANY_THROW(Integer::Parse("abc"));
        EXPECT_ANY_THROW(Integer::Parse("NaN"));
        EXPECT_ANY_THROW(Integer::Parse("-2147483649"));
        EXPECT_ANY_THROW(Integer::Parse("2147483648"));
        EXPECT_ANY_THROW(Integer::Parse("+2147483648"));
    }
}
