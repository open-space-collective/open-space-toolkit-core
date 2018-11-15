////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/Integer.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Triple.hpp>
#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/Index.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Types_Integer, DefaultConstructor)
{

    using library::core::types::Integer ;

    EXPECT_NO_THROW(Integer(0)) ;
    EXPECT_NO_THROW(Integer(1)) ;
    EXPECT_NO_THROW(Integer(123)) ;
    EXPECT_NO_THROW(Integer(+123)) ;
    EXPECT_NO_THROW(Integer(-123)) ;

}

TEST (Library_Core_Types_Integer, AssignmentOperator)
{

    using library::core::types::Integer ;

    EXPECT_NO_THROW(Integer a = 0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Integer a = 0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Integer a = 1 ; (void) a ; ) ;
    EXPECT_NO_THROW(Integer a = 123 ; (void) a ; ) ;
    EXPECT_NO_THROW(Integer a = +123 ; (void) a ; ) ;
    EXPECT_NO_THROW(Integer a = -123 ; (void) a ; ) ;

}

TEST (Library_Core_Types_Integer, EqualToOperator)
{

    using library::core::types::Integer ;

    {

        EXPECT_TRUE(Integer(0) == Integer(0)) ;
        EXPECT_TRUE(Integer(123) == Integer(123)) ;
        EXPECT_TRUE(Integer(+123) == Integer(+123)) ;
        EXPECT_TRUE(Integer(-123) == Integer(-123)) ;

        EXPECT_FALSE(Integer(0) == Integer(1)) ;
        EXPECT_FALSE(Integer(1) == Integer(0)) ;
        EXPECT_FALSE(Integer(-1) == Integer(+1)) ;

        EXPECT_FALSE(Integer::Undefined() == Integer::Undefined()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() == Integer::PositiveInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() == Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() == Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() == Integer::PositiveInfinity()) ;

    }

    {

        EXPECT_TRUE(Integer(0) == 0) ;
        EXPECT_TRUE(Integer(123) == 123) ;
        EXPECT_TRUE(Integer(+123) == +123) ;
        EXPECT_TRUE(Integer(-123) == -123) ;

        EXPECT_FALSE(Integer(0) == 1) ;
        EXPECT_FALSE(Integer(1) == 0) ;
        EXPECT_FALSE(Integer(-1) == +1) ;

    }

}

TEST (Library_Core_Types_Integer, NotEqualToOperator)
{

    using library::core::types::Integer ;

    {

        EXPECT_TRUE(Integer(0) != Integer(1)) ;
        EXPECT_TRUE(Integer(1) != Integer(0)) ;
        EXPECT_TRUE(Integer(-1) != Integer(+1)) ;

        EXPECT_FALSE(Integer(0) != Integer(0)) ;
        EXPECT_FALSE(Integer(123) != Integer(123)) ;
        EXPECT_FALSE(Integer(+123) != Integer(+123)) ;
        EXPECT_FALSE(Integer(-123) != Integer(-123)) ;

        EXPECT_FALSE(Integer::Undefined() != Integer::Undefined()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() != Integer::PositiveInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() != Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() != Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() != Integer::PositiveInfinity()) ;

    }

    {

        EXPECT_TRUE(Integer(0) != 1) ;
        EXPECT_TRUE(Integer(1) != 0) ;
        EXPECT_TRUE(Integer(-1) != +1) ;

        EXPECT_FALSE(Integer(0) != 0) ;
        EXPECT_FALSE(Integer(123) != 123) ;
        EXPECT_FALSE(Integer(+123) != +123) ;
        EXPECT_FALSE(Integer(-123) != -123) ;

    }    

}

TEST (Library_Core_Types_Integer, LessThanOperator)
{

    using library::core::types::Integer ;

    {

        EXPECT_TRUE(Integer(0) < Integer(1)) ;
        EXPECT_TRUE(Integer(1) < Integer(2)) ;
        EXPECT_TRUE(Integer(-1) < Integer(0)) ;
        EXPECT_TRUE(Integer(-1) < Integer(+1)) ;
        EXPECT_TRUE(Integer(-123) < Integer(+123)) ;

        EXPECT_FALSE(Integer(0) < Integer(0)) ;
        EXPECT_FALSE(Integer(1) < Integer(0)) ;
        EXPECT_FALSE(Integer(+1) < Integer(-1)) ;
        EXPECT_FALSE(Integer(+123) < Integer(-123)) ;
        EXPECT_FALSE(Integer(+123) < Integer(+123)) ;
        EXPECT_FALSE(Integer(-123) < Integer(-123)) ;
        
        EXPECT_FALSE(Integer::Undefined() < Integer::Undefined()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() < Integer::PositiveInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() < Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() < Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() < Integer::PositiveInfinity()) ;

    }

    {

        EXPECT_TRUE(Integer(0) < 1) ;
        EXPECT_TRUE(Integer(1) < 2) ;
        EXPECT_TRUE(Integer(-1) < 0) ;
        EXPECT_TRUE(Integer(-1) < +1) ;
        EXPECT_TRUE(Integer(-123) < +123) ;

        EXPECT_FALSE(Integer(0) < 0) ;
        EXPECT_FALSE(Integer(1) < 0) ;
        EXPECT_FALSE(Integer(+1) < -1) ;
        EXPECT_FALSE(Integer(+123) < -123) ;
        EXPECT_FALSE(Integer(+123) < +123) ;
        EXPECT_FALSE(Integer(-123) < -123) ;

    }

}

TEST (Library_Core_Types_Integer, LessThanOrEqualToOperator)
{

    using library::core::types::Integer ;

    {

        EXPECT_TRUE(Integer(0) <= Integer(1)) ;
        EXPECT_TRUE(Integer(1) <= Integer(2)) ;
        EXPECT_TRUE(Integer(-1) <= Integer(0)) ;
        EXPECT_TRUE(Integer(-1) <= Integer(+1)) ;
        EXPECT_TRUE(Integer(-123) <= Integer(+123)) ;
        EXPECT_TRUE(Integer(0) <= Integer(0)) ;
        EXPECT_TRUE(Integer(+123) <= Integer(+123)) ;
        EXPECT_TRUE(Integer(-123) <= Integer(-123)) ;

        EXPECT_FALSE(Integer(1) <= Integer(0)) ;
        EXPECT_FALSE(Integer(+1) <= Integer(-1)) ;
        EXPECT_FALSE(Integer(+123) <= Integer(-123)) ;
        
        EXPECT_FALSE(Integer::Undefined() <= Integer::Undefined()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() <= Integer::PositiveInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() <= Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() <= Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() <= Integer::PositiveInfinity()) ;

    }

    {

        EXPECT_TRUE(Integer(0) <= 1) ;
        EXPECT_TRUE(Integer(1) <= 2) ;
        EXPECT_TRUE(Integer(-1) <= 0) ;
        EXPECT_TRUE(Integer(-1) <= +1) ;
        EXPECT_TRUE(Integer(-123) <= +123) ;
        EXPECT_TRUE(Integer(0) <= 0) ;
        EXPECT_TRUE(Integer(+123) <= +123) ;
        EXPECT_TRUE(Integer(-123) <= -123) ;

        EXPECT_FALSE(Integer(1) <= 0) ;
        EXPECT_FALSE(Integer(+1) <= -1) ;
        EXPECT_FALSE(Integer(+123) <= -123) ;

    }

}

TEST (Library_Core_Types_Integer, GreaterThanOperator)
{

    using library::core::types::Integer ;

    {

        EXPECT_TRUE(Integer(1) > Integer(0)) ;
        EXPECT_TRUE(Integer(2) > Integer(1)) ;
        EXPECT_TRUE(Integer(+1) > Integer(0)) ;
        EXPECT_TRUE(Integer(+1) > Integer(-1)) ;
        EXPECT_TRUE(Integer(+123) > Integer(-123)) ;

        EXPECT_FALSE(Integer(0) > Integer(0)) ;
        EXPECT_FALSE(Integer(0) > Integer(1)) ;
        EXPECT_FALSE(Integer(-1) > Integer(+1)) ;
        EXPECT_FALSE(Integer(-123) > Integer(+123)) ;
        EXPECT_FALSE(Integer(+123) > Integer(+123)) ;
        EXPECT_FALSE(Integer(-123) > Integer(-123)) ;
        
        EXPECT_FALSE(Integer::Undefined() > Integer::Undefined()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() > Integer::PositiveInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() > Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() > Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() > Integer::PositiveInfinity()) ;

    }

    {

        EXPECT_TRUE(Integer(1) > 0) ;
        EXPECT_TRUE(Integer(2) > 1) ;
        EXPECT_TRUE(Integer(+1) > 0) ;
        EXPECT_TRUE(Integer(+1) > -1) ;
        EXPECT_TRUE(Integer(+123) > -123) ;

        EXPECT_FALSE(Integer(0) > 0) ;
        EXPECT_FALSE(Integer(0) > 1) ;
        EXPECT_FALSE(Integer(-1) > +1) ;
        EXPECT_FALSE(Integer(-123) > +123) ;
        EXPECT_FALSE(Integer(+123) > +123) ;
        EXPECT_FALSE(Integer(-123) > -123) ;

    }

}

TEST (Library_Core_Types_Integer, GreaterThanOrEqualToOperator)
{

    using library::core::types::Integer ;

    {

        EXPECT_TRUE(Integer(1) >= Integer(0)) ;
        EXPECT_TRUE(Integer(2) >= Integer(1)) ;
        EXPECT_TRUE(Integer(+1) >= Integer(0)) ;
        EXPECT_TRUE(Integer(+1) >= Integer(-1)) ;
        EXPECT_TRUE(Integer(+123) >= Integer(-123)) ;
        EXPECT_TRUE(Integer(0) >= Integer(0)) ;
        EXPECT_TRUE(Integer(+123) >= Integer(+123)) ;
        EXPECT_TRUE(Integer(-123) >= Integer(-123)) ;

        EXPECT_FALSE(Integer(0) >= Integer(1)) ;
        EXPECT_FALSE(Integer(-1) >= Integer(+1)) ;
        EXPECT_FALSE(Integer(-123) >= Integer(+123)) ;
        
        EXPECT_FALSE(Integer::Undefined() >= Integer::Undefined()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() >= Integer::PositiveInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() >= Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::PositiveInfinity() >= Integer::NegativeInfinity()) ;
        EXPECT_FALSE(Integer::NegativeInfinity() >= Integer::PositiveInfinity()) ;

    }

    {

        EXPECT_TRUE(Integer(1) >= 0) ;
        EXPECT_TRUE(Integer(2) >= 1) ;
        EXPECT_TRUE(Integer(+1) >= 0) ;
        EXPECT_TRUE(Integer(+1) >= -1) ;
        EXPECT_TRUE(Integer(+123) >= -123) ;
        EXPECT_TRUE(Integer(0) >= 0) ;
        EXPECT_TRUE(Integer(+123) >= +123) ;
        EXPECT_TRUE(Integer(-123) >= -123) ;

        EXPECT_FALSE(Integer(0) >= 1) ;
        EXPECT_FALSE(Integer(-1) >= +1) ;
        EXPECT_FALSE(Integer(-123) >= +123) ;

    }

}

TEST (Library_Core_Types_Integer, AdditionOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::Undefined()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -2, -4},
        {-2, -1, -3},
        {-2, +0, -2},
        {-2, +1, -1},
        {-2, +2, +0},
        {-2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 2},
        {-2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-1, -2, -3},
        {-1, -1, -2},
        {-1, +0, -1},
        {-1, +1, +0},
        {-1, +2, +1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {-1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+0, -2, -2},
        {+0, -1, -1},
        {+0, +0, +0},
        {+0, +1, +1},
        {+0, +2, +2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+0, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+1, -2, -1},
        {+1, -1, +0},
        {+1, +0, +1},
        {+1, +1, +2},
        {+1, +2, +3},
        {+1, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},
        
        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+2, -2, +0},
        {+2, -1, +1},
        {+2, +0, +2},
        {+2, +1, +3},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max() + std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;

        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a + b).isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a + b).isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a + b) ;
            }

        }
        else
        {
            EXPECT_FALSE((a + b).isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, SubtractionOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2 - std::numeric_limits<Integer::ValueType>::min()},
        {-2, -2, +0},
        {-2, -1, -1},
        {-2, +0, -2},
        {-2, +1, -3},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max()},
        {-1, -2, +1},
        {-1, -1, +0},
        {-1, +0, -1},
        {-1, +1, -2},
        {-1, +2, -3},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+0, -2, +2},
        {+0, -1, +1},
        {+0, +0, +0},
        {+0, +1, -1},
        {+0, +2, -2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+0, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+1, -2, +3},
        {+1, -1, +2},
        {+1, +0, +1},
        {+1, +1, +0},
        {+1, +2, -1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},
        
        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+2, -2, +4},
        {+2, -1, +3},
        {+2, +0, +2},
        {+2, +1, +1},
        {+2, +2, +0},
        {+2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 3},
        {+2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::Undefined()}

    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;
        
        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a - b).isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a - b).isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a - b) ;
            }

        }
        else
        {
            EXPECT_FALSE((a - b).isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, MultiplicationOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::Undefined()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1073741823, Integer::Undefined(), Integer::Undefined()},
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

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-2, -2, +4},
        {-2, -1, +2},
        {-2, +0, +0},
        {-2, +1, -2},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},
        
        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-1, -2, +2},
        {-1, -1, +1},
        {-1, +0, +0},
        {-1, +1, -1},
        {-1, +2, -2},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -std::numeric_limits<Integer::ValueType>::max()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), Integer::Undefined()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), Integer::Undefined()},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+1, -2, -2},
        {+1, -1, -1},
        {+1, +0, +0},
        {+1, +1, +1},
        {+1, +2, +2},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {+2, -2, -4},
        {+2, -1, -2},
        {+2, +0, +0},
        {+2, +1, +2},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1073741823, Integer::Undefined(), Integer::Undefined()},
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

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, -std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::Undefined()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;
        
        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a * b).isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a * b).isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a * b) ;
            }

        }
        else
        {
            EXPECT_FALSE((a * b).isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, DivisionOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::Undefined()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::Undefined()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), 1},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() / -2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() / 2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), +0},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), +0},
        {-2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-2, -2, +1},
        {-2, -1, +2},
        {-2, +0, Integer::Undefined()},
        {-2, +1, -2},
        {-2, +2, -1},
        {-2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-2, Integer::PositiveInfinity(), +0},
        
        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), +0},
        {-1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-1, -2, +0},
        {-1, -1, +1},
        {-1, +0, Integer::Undefined()},
        {-1, +1, -1},
        {-1, +2, +0},
        {-1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-1, Integer::PositiveInfinity(), +0},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, Integer::Undefined()},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), +0},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+1, -2, +0},
        {+1, -1, -1},
        {+1, +0, Integer::Undefined()},
        {+1, +1, +1},
        {+1, +2, +0},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+1, Integer::PositiveInfinity(), +0},

        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), +0},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+2, -2, -1},
        {+2, -1, -2},
        {+2, +0, Integer::Undefined()},
        {+2, +1, +2},
        {+2, +2, +1},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+2, Integer::PositiveInfinity(), +0},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() / -2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() / -1},
        {std::numeric_limits<Integer::ValueType>::max(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() / 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +1},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), +0},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::Undefined()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::Undefined()}

    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;
        
        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a / b).isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a / b).isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a / b) ;
            }

        }
        else
        {
            EXPECT_FALSE((a / b).isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, ModuloOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::NegativeInfinity(), -2, Integer::Undefined()},
        {Integer::NegativeInfinity(), -1, +0},
        {Integer::NegativeInfinity(), +0, Integer::Undefined()},
        {Integer::NegativeInfinity(), +1, +0},
        {Integer::NegativeInfinity(), +2, Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::Undefined()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), -2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min()},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), -2},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2},
        {-2, -3, -2},
        {-2, -2, +0},
        {-2, -1, +0},
        {-2, +0, Integer::Undefined()},
        {-2, +1, +0},
        {-2, +2, +0},
        {-2, +3, -2},
        {-2, std::numeric_limits<Integer::ValueType>::max(), -2},
        {-2, Integer::PositiveInfinity(), -2},
        
        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), -1},
        {-1, std::numeric_limits<Integer::ValueType>::min(), -1},
        {-1, -3, -1},
        {-1, -2, -1},
        {-1, -1, +0},
        {-1, +0, Integer::Undefined()},
        {-1, +1, +0},
        {-1, +2, -1},
        {-1, +3, -1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -1},
        {-1, Integer::PositiveInfinity(), -1},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -3, +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, Integer::Undefined()},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, +3, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), +1},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +1},
        {+1, -3, +1},
        {+1, -2, +1},
        {+1, -1, +0},
        {+1, +0, Integer::Undefined()},
        {+1, +1, +0},
        {+1, +2, +1},
        {+1, +3, +1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +1},
        {+1, Integer::PositiveInfinity(), +1},

        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), +2},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +2},
        {+2, -3, +2},
        {+2, -2, +0},
        {+2, -1, +0},
        {+2, +0, Integer::Undefined()},
        {+2, +1, +0},
        {+2, +2, +0},
        {+2, +3, +2},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +2},
        {+2, Integer::PositiveInfinity(), +2},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::PositiveInfinity(), -2, Integer::Undefined()},
        {Integer::PositiveInfinity(), -1, +0},
        {Integer::PositiveInfinity(), +0, Integer::Undefined()},
        {Integer::PositiveInfinity(), +1, +0},
        {Integer::PositiveInfinity(), +2, Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::Undefined()}

    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;
        
        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE((a % b).isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE((a % b).isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a % b) ;
            }

        }
        else
        {
            EXPECT_FALSE((a % b).isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, AdditionAssignmentOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::Undefined()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -2, -4},
        {-2, -1, -3},
        {-2, +0, -2},
        {-2, +1, -1},
        {-2, +2, +0},
        {-2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 2},
        {-2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-1, -2, -3},
        {-1, -1, -2},
        {-1, +0, -1},
        {-1, +1, +0},
        {-1, +2, +1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {-1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+0, -2, -2},
        {+0, -1, -1},
        {+0, +0, +0},
        {+0, +1, +1},
        {+0, +2, +2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+0, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+1, -2, -1},
        {+1, -1, +0},
        {+1, +0, +1},
        {+1, +1, +2},
        {+1, +2, +3},
        {+1, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},
        
        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+2, -2, +0},
        {+2, -1, +1},
        {+2, +0, +2},
        {+2, +1, +3},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max() + std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;

        a += b ;

        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a) ;
            }

        }
        else
        {
            EXPECT_FALSE(a.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, SubtractionAssignmentOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() + 2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, std::numeric_limits<Integer::ValueType>::min() + 1},
        {std::numeric_limits<Integer::ValueType>::min(), +0, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2 - std::numeric_limits<Integer::ValueType>::min()},
        {-2, -2, +0},
        {-2, -1, -1},
        {-2, +0, -2},
        {-2, +1, -3},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max()},
        {-1, -2, +1},
        {-1, -1, +0},
        {-1, +0, -1},
        {-1, +1, -2},
        {-1, +2, -3},
        {-1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+0, -2, +2},
        {+0, -1, +1},
        {+0, +0, +0},
        {+0, +1, -1},
        {+0, +2, -2},
        {+0, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {+0, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+1, -2, +3},
        {+1, -1, +2},
        {+1, +0, +1},
        {+1, +1, +0},
        {+1, +2, -1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 2},
        {+1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},
        
        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {+2, -2, +4},
        {+2, -1, +3},
        {+2, +0, +2},
        {+2, +1, +1},
        {+2, +2, +0},
        {+2, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min() + 3},
        {+2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max() - 1},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() - 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::Undefined()}

    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;

        a -= b ;

        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a) ;
            }

        }
        else
        {
            EXPECT_FALSE(a.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, MultiplicationAssignmentOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::Undefined()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {-1073741823, Integer::Undefined(), Integer::Undefined()},
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

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-2, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-2, -2, +4},
        {-2, -1, +2},
        {-2, +0, +0},
        {-2, +1, -2},
        {-2, +2, -4},
        {-2, std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {-2, Integer::PositiveInfinity(), Integer::NegativeInfinity()},
        
        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {-1, std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-1, -2, +2},
        {-1, -1, +1},
        {-1, +0, +0},
        {-1, +1, -1},
        {-1, +2, -2},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -std::numeric_limits<Integer::ValueType>::max()},
        {-1, Integer::PositiveInfinity(), Integer::NegativeInfinity()},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), Integer::Undefined()},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, +0},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), Integer::Undefined()},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+1, std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {+1, -2, -2},
        {+1, -1, -1},
        {+1, +0, +0},
        {+1, +1, +1},
        {+1, +2, +2},
        {+1, std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {+1, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {+2, std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {+2, -2, -4},
        {+2, -1, -2},
        {+2, +0, +0},
        {+2, +1, +2},
        {+2, +2, +4},
        {+2, std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {+2, Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {+1073741823, Integer::Undefined(), Integer::Undefined()},
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

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), -1, -std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +0, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), Integer::PositiveInfinity()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::Undefined()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::PositiveInfinity()}

    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;

        a *= b ;

        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a) ;
            }

        }
        else
        {
            EXPECT_FALSE(a.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, DivisionAssignmentOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -2, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), -1, Integer::PositiveInfinity()},
        {Integer::NegativeInfinity(), +0, Integer::Undefined()},
        {Integer::NegativeInfinity(), +1, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), +2, Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::Undefined()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), 1},
        {std::numeric_limits<Integer::ValueType>::min(), -2, std::numeric_limits<Integer::ValueType>::min() / -2},
        {std::numeric_limits<Integer::ValueType>::min(), -1, Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), +2, std::numeric_limits<Integer::ValueType>::min() / 2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), +0},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), +0},
        {-2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-2, -2, +1},
        {-2, -1, +2},
        {-2, +0, Integer::Undefined()},
        {-2, +1, -2},
        {-2, +2, -1},
        {-2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-2, Integer::PositiveInfinity(), +0},
        
        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), +0},
        {-1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {-1, -2, +0},
        {-1, -1, +1},
        {-1, +0, Integer::Undefined()},
        {-1, +1, -1},
        {-1, +2, +0},
        {-1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {-1, Integer::PositiveInfinity(), +0},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, Integer::Undefined()},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), +0},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+1, -2, +0},
        {+1, -1, -1},
        {+1, +0, Integer::Undefined()},
        {+1, +1, +1},
        {+1, +2, +0},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+1, Integer::PositiveInfinity(), +0},

        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), +0},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+2, -2, -1},
        {+2, -1, -2},
        {+2, +0, Integer::Undefined()},
        {+2, +1, +2},
        {+2, +2, +1},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+2, Integer::PositiveInfinity(), +0},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), -2, std::numeric_limits<Integer::ValueType>::max() / -2},
        {std::numeric_limits<Integer::ValueType>::max(), -1, std::numeric_limits<Integer::ValueType>::max() / -1},
        {std::numeric_limits<Integer::ValueType>::max(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), +2, std::numeric_limits<Integer::ValueType>::max() / 2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +1},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), +0},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -2, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), -1, Integer::NegativeInfinity()},
        {Integer::PositiveInfinity(), +0, Integer::Undefined()},
        {Integer::PositiveInfinity(), +1, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), +2, Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::Undefined()}

    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;

        a /= b ;

        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a) ;
            }

        }
        else
        {
            EXPECT_FALSE(a.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, ModuloAssignmentOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Integer, Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined(), Integer::Undefined()},
        {Integer::Undefined(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::Undefined(), -2, Integer::Undefined()},
        {Integer::Undefined(), -1, Integer::Undefined()},
        {Integer::Undefined(), +0, Integer::Undefined()},
        {Integer::Undefined(), +1, Integer::Undefined()},
        {Integer::Undefined(), +2, Integer::Undefined()},
        {Integer::Undefined(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::Undefined(), Integer::PositiveInfinity(), Integer::Undefined()},

        {Integer::NegativeInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::NegativeInfinity(), -2, Integer::Undefined()},
        {Integer::NegativeInfinity(), -1, +0},
        {Integer::NegativeInfinity(), +0, Integer::Undefined()},
        {Integer::NegativeInfinity(), +1, +0},
        {Integer::NegativeInfinity(), +2, Integer::Undefined()},
        {Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity(), Integer::Undefined()},

        {std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::min()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min(), +0},
        {std::numeric_limits<Integer::ValueType>::min(), -3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), -2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::min(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +2, +0},
        {std::numeric_limits<Integer::ValueType>::min(), +3, -2},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max(), -1},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min()},

        {-2, Integer::Undefined(), Integer::Undefined()},
        {-2, Integer::NegativeInfinity(), -2},
        {-2, std::numeric_limits<Integer::ValueType>::min(), -2},
        {-2, -3, -2},
        {-2, -2, +0},
        {-2, -1, +0},
        {-2, +0, Integer::Undefined()},
        {-2, +1, +0},
        {-2, +2, +0},
        {-2, +3, -2},
        {-2, std::numeric_limits<Integer::ValueType>::max(), -2},
        {-2, Integer::PositiveInfinity(), -2},
        
        {-1, Integer::Undefined(), Integer::Undefined()},
        {-1, Integer::NegativeInfinity(), -1},
        {-1, std::numeric_limits<Integer::ValueType>::min(), -1},
        {-1, -3, -1},
        {-1, -2, -1},
        {-1, -1, +0},
        {-1, +0, Integer::Undefined()},
        {-1, +1, +0},
        {-1, +2, -1},
        {-1, +3, -1},
        {-1, std::numeric_limits<Integer::ValueType>::max(), -1},
        {-1, Integer::PositiveInfinity(), -1},

        {+0, Integer::Undefined(), Integer::Undefined()},
        {+0, Integer::NegativeInfinity(), +0},
        {+0, std::numeric_limits<Integer::ValueType>::min(), +0},
        {+0, -3, +0},
        {+0, -2, +0},
        {+0, -1, +0},
        {+0, +0, Integer::Undefined()},
        {+0, +1, +0},
        {+0, +2, +0},
        {+0, +3, +0},
        {+0, std::numeric_limits<Integer::ValueType>::max(), +0},
        {+0, Integer::PositiveInfinity(), +0},

        {+1, Integer::Undefined(), Integer::Undefined()},
        {+1, Integer::NegativeInfinity(), +1},
        {+1, std::numeric_limits<Integer::ValueType>::min(), +1},
        {+1, -3, +1},
        {+1, -2, +1},
        {+1, -1, +0},
        {+1, +0, Integer::Undefined()},
        {+1, +1, +0},
        {+1, +2, +1},
        {+1, +3, +1},
        {+1, std::numeric_limits<Integer::ValueType>::max(), +1},
        {+1, Integer::PositiveInfinity(), +1},

        {+2, Integer::Undefined(), Integer::Undefined()},
        {+2, Integer::NegativeInfinity(), +2},
        {+2, std::numeric_limits<Integer::ValueType>::min(), +2},
        {+2, -3, +2},
        {+2, -2, +0},
        {+2, -1, +0},
        {+2, +0, Integer::Undefined()},
        {+2, +1, +0},
        {+2, +2, +0},
        {+2, +3, +2},
        {+2, std::numeric_limits<Integer::ValueType>::max(), +2},
        {+2, Integer::PositiveInfinity(), +2},

        {std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined(), Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::NegativeInfinity(), std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::max()},
        {std::numeric_limits<Integer::ValueType>::max(), -2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), -1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +0, Integer::Undefined()},
        {std::numeric_limits<Integer::ValueType>::max(), +1, +0},
        {std::numeric_limits<Integer::ValueType>::max(), +2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max(), +0},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max()},

        {Integer::PositiveInfinity(), Integer::Undefined(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity(), Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::min(), Integer::Undefined()},
        {Integer::PositiveInfinity(), -2, Integer::Undefined()},
        {Integer::PositiveInfinity(), -1, +0},
        {Integer::PositiveInfinity(), +0, Integer::Undefined()},
        {Integer::PositiveInfinity(), +1, +0},
        {Integer::PositiveInfinity(), +2, Integer::Undefined()},
        {Integer::PositiveInfinity(), std::numeric_limits<Integer::ValueType>::max(), Integer::Undefined()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity(), Integer::Undefined()}

    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        const Integer& c = testCase.third ;

        a %= b ;

        if (c.isDefined())
        {

            if (c.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (c.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(c, a) ;
            }

        }
        else
        {
            EXPECT_FALSE(a.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, UnaryPlusOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;

    Array<Pair<Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min()},
        {-2, -2},
        {-1, -1},
        {+0, +0},
        {+1, +1},
        {+2, +2},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}
        
    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;

        Integer c = +a ;
        
        if (b.isDefined())
        {

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, c) ;
            }

        }
        else
        {
            EXPECT_FALSE(c.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, UnaryMinusOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;

    Array<Pair<Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::PositiveInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::PositiveInfinity()},
        {-2, +2},
        {-1, +1},
        {+0, +0},
        {+1, -1},
        {+2, -2},
        {std::numeric_limits<Integer::ValueType>::max(), -std::numeric_limits<Integer::ValueType>::max()},
        {Integer::PositiveInfinity(), Integer::NegativeInfinity()}
        
    } ;

    for (const auto& testCase : testCases)
    {

        const Integer& a = testCase.first ;
        const Integer& b = testCase.second ;

        Integer c = -a ;
        
        if (b.isDefined())
        {

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, c) ;
            }

        }
        else
        {
            EXPECT_FALSE(c.isDefined()) ;
        }

    }

}

TEST (Library_Core_Types_Integer, PrefixIncrementOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;

    Array<Pair<Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {-2, -1},
        {-1, +0},
        {+0, +1},
        {+1, +2},
        {+2, +3},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}
        
    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        
        if (b.isDefined())
        {

            Integer c = ++a ;

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, c) ;
            }

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, a) ;
            }

        }
        else
        {

            Integer c = ++a ;

            EXPECT_FALSE(c.isDefined()) ;

            EXPECT_FALSE(a.isDefined()) ;

        }

    }

}

TEST (Library_Core_Types_Integer, PrefixDecrementOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;

    Array<Pair<Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -3},
        {-1, -2},
        {+0, -1},
        {+1, +0},
        {+2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}
        
    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer& b = testCase.second ;
        
        if (b.isDefined())
        {

            Integer c = --a ;

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, c) ;
            }

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, a) ;
            }

        }
        else
        {

            Integer c = --a ;

            EXPECT_FALSE(c.isDefined()) ;

            EXPECT_FALSE(a.isDefined()) ;

        }

    }

}

TEST (Library_Core_Types_Integer, PostfixIncrementOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;

    Array<Pair<Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), std::numeric_limits<Integer::ValueType>::min() + 1},
        {-2, -1},
        {-1, +0},
        {+0, +1},
        {+1, +2},
        {+2, +3},
        {std::numeric_limits<Integer::ValueType>::max(), Integer::PositiveInfinity()},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}
        
    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer aCopy = a ;
        const Integer& b = testCase.second ;
        
        if (b.isDefined())
        {

            Integer c = a++ ;

            if (!aCopy.isDefined())
            {
                EXPECT_FALSE(c.isDefined()) ;
            }
            else if (aCopy.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (aCopy.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(aCopy, c) ;
            }

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, a) ;
            }

        }
        else
        {

            Integer c = a++ ;

            if (!aCopy.isDefined())
            {
                EXPECT_FALSE(c.isDefined()) ;
            }
            else if (aCopy.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (aCopy.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(aCopy, c) ;
            }

            EXPECT_FALSE(a.isDefined()) ;

        }

    }

}

TEST (Library_Core_Types_Integer, PostfixDecrementOperator)
{

    using library::core::types::Integer ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Array ;

    Array<Pair<Integer, Integer>> testCases =
    {

        {Integer::Undefined(), Integer::Undefined()},
        {Integer::NegativeInfinity(), Integer::NegativeInfinity()},
        {std::numeric_limits<Integer::ValueType>::min(), Integer::NegativeInfinity()},
        {-2, -3},
        {-1, -2},
        {+0, -1},
        {+1, +0},
        {+2, +1},
        {std::numeric_limits<Integer::ValueType>::max(), std::numeric_limits<Integer::ValueType>::max() - 1},
        {Integer::PositiveInfinity(), Integer::PositiveInfinity()}
        
    } ;

    for (auto& testCase : testCases)
    {

        Integer& a = testCase.first ;
        const Integer aCopy = a ;
        const Integer& b = testCase.second ;
        
        if (b.isDefined())
        {

            Integer c = a-- ;

            if (!aCopy.isDefined())
            {
                EXPECT_FALSE(c.isDefined()) ;
            }
            else if (aCopy.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (aCopy.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(aCopy, c) ;
            }

            if (b.isPositiveInfinity())
            {
                EXPECT_TRUE(a.isPositiveInfinity()) ;
            }
            else if (b.isNegativeInfinity())
            {
                EXPECT_TRUE(a.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(b, a) ;
            }

        }
        else
        {

            Integer c = a-- ;

            if (!aCopy.isDefined())
            {
                EXPECT_FALSE(c.isDefined()) ;
            }
            else if (aCopy.isPositiveInfinity())
            {
                EXPECT_TRUE(c.isPositiveInfinity()) ;
            }
            else if (aCopy.isNegativeInfinity())
            {
                EXPECT_TRUE(c.isNegativeInfinity()) ;
            }
            else
            {
                EXPECT_EQ(aCopy, c) ;
            }

            EXPECT_FALSE(a.isDefined()) ;

        }

    }

}

TEST (Library_Core_Types_Integer, ValueTypeOperator)
{

    using library::core::types::Integer ;
    
    {

        EXPECT_ANY_THROW( Integer::ValueType a = Integer::Undefined() ; (void) a ; ) ;

    }

    {

        EXPECT_ANY_THROW( Integer::ValueType a = Integer::NegativeInfinity() ; (void) a ; ) ;

    }

    {

        Integer::ValueType a = Integer(std::numeric_limits<Integer::ValueType>::min()) ;

        EXPECT_EQ(std::numeric_limits<Integer::ValueType>::min(), a) ;

    }

    {

        Integer::ValueType a = Integer(-1) ;

        EXPECT_EQ(-1, a) ;

    }

    {

        Integer::ValueType a = Integer(+0) ;

        EXPECT_EQ(+0, a) ;

    }

    {

        Integer::ValueType a = Integer(+1) ;

        EXPECT_EQ(+1, a) ;

    }

    {

        EXPECT_ANY_THROW( Integer::ValueType a = Integer::PositiveInfinity() ; (void) a ; ) ;

    }

}

// TEST (Library_Core_Types_Integer, StreamOperator)
// {

//     using library::core::types::Integer ;

//     FAIL() ;

// }

TEST (Library_Core_Types_Integer, IsDefined)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(0).isDefined()) ;
    EXPECT_TRUE(Integer(-1).isDefined()) ;
    EXPECT_TRUE(Integer(+0).isDefined()) ;
    EXPECT_TRUE(Integer(+1).isDefined()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isDefined()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isDefined()) ;
    EXPECT_TRUE(Integer::NegativeInfinity().isDefined()) ;
    EXPECT_TRUE(Integer::PositiveInfinity().isDefined()) ;

    EXPECT_FALSE(Integer::Undefined().isDefined()) ;

}

TEST (Library_Core_Types_Integer, IsZero)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(0).isZero()) ;
    EXPECT_TRUE(Integer(+0).isZero()) ;

    EXPECT_FALSE(Integer(-1).isZero()) ;
    EXPECT_FALSE(Integer(+1).isZero()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isZero()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isZero()) ;
    EXPECT_FALSE(Integer::NegativeInfinity().isZero()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isZero()) ;
    EXPECT_FALSE(Integer::Undefined().isZero()) ;

}

TEST (Library_Core_Types_Integer, IsPositive)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(0).isPositive()) ;
    EXPECT_TRUE(Integer(+0).isPositive()) ;
    EXPECT_TRUE(Integer(+1).isPositive()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isPositive()) ;
    EXPECT_TRUE(Integer::PositiveInfinity().isPositive()) ;

    EXPECT_FALSE(Integer::Undefined().isPositive()) ;
    EXPECT_FALSE(Integer(-1).isPositive()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isPositive()) ;
    EXPECT_FALSE(Integer::NegativeInfinity().isPositive()) ;

}

TEST (Library_Core_Types_Integer, IsNegative)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(0).isNegative()) ;
    EXPECT_TRUE(Integer(-1).isNegative()) ;
    EXPECT_TRUE(Integer(+0).isNegative()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isNegative()) ;
    EXPECT_TRUE(Integer::NegativeInfinity().isNegative()) ;

    EXPECT_FALSE(Integer::Undefined().isNegative()) ;
    EXPECT_FALSE(Integer(+1).isNegative()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isNegative()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isNegative()) ;

}

TEST (Library_Core_Types_Integer, IsStrictlyPositive)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(+1).isStrictlyPositive()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isStrictlyPositive()) ;
    EXPECT_TRUE(Integer::PositiveInfinity().isStrictlyPositive()) ;

    EXPECT_FALSE(Integer::Undefined().isStrictlyPositive()) ;
    EXPECT_FALSE(Integer(0).isStrictlyPositive()) ;
    EXPECT_FALSE(Integer(-1).isStrictlyPositive()) ;
    EXPECT_FALSE(Integer(+0).isStrictlyPositive()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isStrictlyPositive()) ;
    EXPECT_FALSE(Integer::NegativeInfinity().isStrictlyPositive()) ;

}

TEST (Library_Core_Types_Integer, IsStrictlyNegative)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(-1).isStrictlyNegative()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isStrictlyNegative()) ;
    EXPECT_TRUE(Integer::NegativeInfinity().isStrictlyNegative()) ;

    EXPECT_FALSE(Integer::Undefined().isStrictlyNegative()) ;
    EXPECT_FALSE(Integer(0).isStrictlyNegative()) ;
    EXPECT_FALSE(Integer(+1).isStrictlyNegative()) ;
    EXPECT_FALSE(Integer(+0).isStrictlyNegative()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isStrictlyNegative()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isStrictlyNegative()) ;

}

TEST (Library_Core_Types_Integer, IsInfinity)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer::NegativeInfinity().isInfinity()) ;
    EXPECT_TRUE(Integer::PositiveInfinity().isInfinity()) ;

    EXPECT_FALSE(Integer::Undefined().isInfinity()) ;
    EXPECT_FALSE(Integer(0).isInfinity()) ;
    EXPECT_FALSE(Integer(-1).isInfinity()) ;
    EXPECT_FALSE(Integer(+0).isInfinity()) ;
    EXPECT_FALSE(Integer(+1).isInfinity()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isInfinity()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isInfinity()) ;

}

TEST (Library_Core_Types_Integer, IsPositiveInfinity)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer::PositiveInfinity().isPositiveInfinity()) ;

    EXPECT_FALSE(Integer::Undefined().isPositiveInfinity()) ;
    EXPECT_FALSE(Integer(0).isPositiveInfinity()) ;
    EXPECT_FALSE(Integer(-1).isPositiveInfinity()) ;
    EXPECT_FALSE(Integer(+0).isPositiveInfinity()) ;
    EXPECT_FALSE(Integer(+1).isPositiveInfinity()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isPositiveInfinity()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isPositiveInfinity()) ;
    EXPECT_FALSE(Integer::NegativeInfinity().isPositiveInfinity()) ;

}

TEST (Library_Core_Types_Integer, IsNegativeInfinity)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer::NegativeInfinity().isNegativeInfinity()) ;

    EXPECT_FALSE(Integer::Undefined().isNegativeInfinity()) ;
    EXPECT_FALSE(Integer(0).isNegativeInfinity()) ;
    EXPECT_FALSE(Integer(-1).isNegativeInfinity()) ;
    EXPECT_FALSE(Integer(+0).isNegativeInfinity()) ;
    EXPECT_FALSE(Integer(+1).isNegativeInfinity()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::min()).isNegativeInfinity()) ;
    EXPECT_FALSE(Integer(std::numeric_limits<Integer::ValueType>::max()).isNegativeInfinity()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isNegativeInfinity()) ;

}

TEST (Library_Core_Types_Integer, IsFinite)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(0).isFinite()) ;
    EXPECT_TRUE(Integer(-1).isFinite()) ;
    EXPECT_TRUE(Integer(+0).isFinite()) ;
    EXPECT_TRUE(Integer(+1).isFinite()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::min()).isFinite()) ;
    EXPECT_TRUE(Integer(std::numeric_limits<Integer::ValueType>::max()).isFinite()) ;

    EXPECT_FALSE(Integer::NegativeInfinity().isFinite()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isFinite()) ;
    EXPECT_FALSE(Integer::Undefined().isFinite()) ;

}

TEST (Library_Core_Types_Integer, IsEven)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(0).isEven()) ;
    
    EXPECT_TRUE(Integer(-4).isEven()) ;
    EXPECT_TRUE(Integer(-2).isEven()) ;
    EXPECT_TRUE(Integer(+0).isEven()) ;
    EXPECT_TRUE(Integer(+2).isEven()) ;
    EXPECT_TRUE(Integer(+4).isEven()) ;

    EXPECT_FALSE(Integer(-3).isEven()) ;
    EXPECT_FALSE(Integer(-1).isEven()) ;
    EXPECT_FALSE(Integer(+1).isEven()) ;
    EXPECT_FALSE(Integer(+3).isEven()) ;
    
    EXPECT_FALSE(Integer::NegativeInfinity().isEven()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isEven()) ;
    EXPECT_FALSE(Integer::Undefined().isEven()) ;

}

TEST (Library_Core_Types_Integer, IsOdd)
{

    using library::core::types::Integer ;

    EXPECT_TRUE(Integer(-3).isOdd()) ;
    EXPECT_TRUE(Integer(-1).isOdd()) ;
    EXPECT_TRUE(Integer(+1).isOdd()) ;
    EXPECT_TRUE(Integer(+3).isOdd()) ;

    EXPECT_FALSE(Integer(-2).isOdd()) ;
    EXPECT_FALSE(Integer(+0).isOdd()) ;
    EXPECT_FALSE(Integer(+2).isOdd()) ;
    
    EXPECT_FALSE(Integer::NegativeInfinity().isOdd()) ;
    EXPECT_FALSE(Integer::PositiveInfinity().isOdd()) ;
    EXPECT_FALSE(Integer::Undefined().isOdd()) ;

}

TEST (Library_Core_Types_Integer, GetSign)
{

    using library::core::types::Sign ;
    using library::core::types::Integer ;

    EXPECT_EQ(Sign::Undefined, Integer::Undefined().getSign()) ;
    EXPECT_EQ(Sign::None, Integer(0).getSign()) ;
    EXPECT_EQ(Sign::Negative, Integer(-1).getSign()) ;
    EXPECT_EQ(Sign::None, Integer(+0).getSign()) ;
    EXPECT_EQ(Sign::Positive, Integer(+1).getSign()) ;
    EXPECT_EQ(Sign::Negative, Integer(std::numeric_limits<Integer::ValueType>::min()).getSign()) ;
    EXPECT_EQ(Sign::Positive, Integer(std::numeric_limits<Integer::ValueType>::max()).getSign()) ;
    EXPECT_EQ(Sign::Negative, Integer::NegativeInfinity().getSign()) ;
    EXPECT_EQ(Sign::Positive, Integer::PositiveInfinity().getSign()) ;

}

TEST (Library_Core_Types_Integer, ToString)
{

    using library::core::types::Integer ;

    EXPECT_EQ("Undefined", Integer::Undefined().toString()) ;
    EXPECT_EQ("0", Integer(0).toString()) ;
    EXPECT_EQ("-1", Integer(-1).toString()) ;
    EXPECT_EQ("0", Integer(+0).toString()) ;
    EXPECT_EQ("1", Integer(+1).toString()) ;
    EXPECT_EQ("-Inf", Integer::NegativeInfinity().toString()) ;
    EXPECT_EQ("+Inf", Integer::PositiveInfinity().toString()) ;

}

// TEST (Library_Core_Types_Integer, GetObject)
// {

//     using library::core::types::Integer ;

//     FAIL() ;

// }

TEST (Library_Core_Types_Integer, Undefined)
{

    using library::core::types::Integer ;

    EXPECT_NO_THROW(Integer::Undefined()) ;
   
    EXPECT_FALSE(Integer::Undefined().isDefined()) ;
    EXPECT_FALSE(Integer::Undefined().isInfinity()) ;

}

TEST (Library_Core_Types_Integer, PositiveInfinity)
{

    using library::core::types::Integer ;

    EXPECT_NO_THROW(Integer::PositiveInfinity()) ;

    EXPECT_TRUE(Integer::PositiveInfinity().isDefined()) ;
    EXPECT_TRUE(Integer::PositiveInfinity().isInfinity()) ;
    EXPECT_TRUE(Integer::PositiveInfinity().isPositiveInfinity()) ;

}

TEST (Library_Core_Types_Integer, NegativeInfinity)
{

    using library::core::types::Integer ;

    EXPECT_NO_THROW(Integer::NegativeInfinity()) ;
    
    EXPECT_TRUE(Integer::NegativeInfinity().isDefined()) ;
    EXPECT_TRUE(Integer::NegativeInfinity().isInfinity()) ;
    EXPECT_TRUE(Integer::NegativeInfinity().isNegativeInfinity()) ;

}

TEST (Library_Core_Types_Integer, Int8)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Int8(library::core::types::Int8(0))) ;
        
        EXPECT_NO_THROW(Integer::Int8(library::core::types::Int8(-1))) ;
        EXPECT_NO_THROW(Integer::Int8(library::core::types::Int8(+1))) ;

        EXPECT_NO_THROW(Integer::Int8(library::core::types::Int8(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_NO_THROW(Integer::Int8(library::core::types::Int8(std::numeric_limits<library::core::types::Int8>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Int8(library::core::types::Int8(0))) ;
        
        EXPECT_EQ(-1, Integer::Int8(library::core::types::Int8(-1))) ;
        EXPECT_EQ(+1, Integer::Int8(library::core::types::Int8(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::min(), Integer::Int8(library::core::types::Int8(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::max(), Integer::Int8(library::core::types::Int8(std::numeric_limits<library::core::types::Int8>::max()))) ;

    }

}

TEST (Library_Core_Types_Integer, Int16)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(0))) ;
        
        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(-1))) ;
        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(+1))) ;

        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int8>::max()))) ;

        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int16>::min()))) ;
        EXPECT_NO_THROW(Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int16>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Int16(library::core::types::Int16(0))) ;
        
        EXPECT_EQ(-1, Integer::Int16(library::core::types::Int16(-1))) ;
        EXPECT_EQ(+1, Integer::Int16(library::core::types::Int16(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::min(), Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::max(), Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int8>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int16>::min(), Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int16>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int16>::max(), Integer::Int16(library::core::types::Int16(std::numeric_limits<library::core::types::Int16>::max()))) ;

    }

}

TEST (Library_Core_Types_Integer, Int32)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(0))) ;
        
        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(-1))) ;
        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(+1))) ;

        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int8>::max()))) ;

        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int16>::min()))) ;
        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int16>::max()))) ;

        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int32>::min()))) ;
        EXPECT_NO_THROW(Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int32>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Int32(library::core::types::Int32(0))) ;
        
        EXPECT_EQ(-1, Integer::Int32(library::core::types::Int32(-1))) ;
        EXPECT_EQ(+1, Integer::Int32(library::core::types::Int32(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::min(), Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::max(), Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int8>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int16>::min(), Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int16>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int16>::max(), Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int16>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int32>::min(), Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int32>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int32>::max(), Integer::Int32(library::core::types::Int32(std::numeric_limits<library::core::types::Int32>::max()))) ;

    }

}

TEST (Library_Core_Types_Integer, Int64)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(0))) ;
        
        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(-1))) ;
        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(+1))) ;

        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int8>::max()))) ;

        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int16>::min()))) ;
        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int16>::max()))) ;

        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int32>::min()))) ;
        EXPECT_NO_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int32>::max()))) ;

        EXPECT_ANY_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int32>::min()) - 1)) ;
        EXPECT_ANY_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int32>::max()) + 1)) ;

        EXPECT_ANY_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int64>::min()))) ;
        EXPECT_ANY_THROW(Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int64>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Int64(library::core::types::Int64(0))) ;
        
        EXPECT_EQ(-1, Integer::Int64(library::core::types::Int64(-1))) ;
        EXPECT_EQ(+1, Integer::Int64(library::core::types::Int64(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::min(), Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int8>::max(), Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int8>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int16>::min(), Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int16>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int16>::max(), Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int16>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Int32>::min(), Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int32>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Int32>::max(), Integer::Int64(library::core::types::Int64(std::numeric_limits<library::core::types::Int32>::max()))) ;

    }

}

TEST (Library_Core_Types_Integer, Uint8)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Uint8(library::core::types::Uint8(0))) ;
        
        EXPECT_NO_THROW(Integer::Uint8(library::core::types::Uint8(+1))) ;

        EXPECT_NO_THROW(Integer::Uint8(library::core::types::Uint8(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint8(library::core::types::Uint8(std::numeric_limits<library::core::types::Uint8>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Uint8(library::core::types::Uint8(0))) ;
        
        EXPECT_EQ(+1, Integer::Uint8(library::core::types::Uint8(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::min(), Integer::Uint8(library::core::types::Uint8(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::max(), Integer::Uint8(library::core::types::Uint8(std::numeric_limits<library::core::types::Uint8>::max()))) ;

    }

}

TEST (Library_Core_Types_Integer, Uint16)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Uint16(library::core::types::Uint16(0))) ;
        
        EXPECT_NO_THROW(Integer::Uint16(library::core::types::Uint16(+1))) ;

        EXPECT_NO_THROW(Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint8>::max()))) ;

        EXPECT_NO_THROW(Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint16>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint16>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Uint16(library::core::types::Uint16(0))) ;
        
        EXPECT_EQ(+1, Integer::Uint16(library::core::types::Uint16(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::min(), Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::max(), Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint8>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint16>::min(), Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint16>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint16>::max(), Integer::Uint16(library::core::types::Uint16(std::numeric_limits<library::core::types::Uint16>::max()))) ;

    }

}

TEST (Library_Core_Types_Integer, Uint32)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(0))) ;
        
        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(+1))) ;

        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint8>::min()))) ;

        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint16>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint16>::min()))) ;

        EXPECT_NO_THROW(Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint32>::min()))) ;
        
        EXPECT_ANY_THROW(Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint32>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Uint32(library::core::types::Uint32(0))) ;
        
        EXPECT_EQ(+1, Integer::Uint32(library::core::types::Uint32(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::min(), Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::max(), Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint8>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint16>::min(), Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint16>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint16>::max(), Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint16>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint32>::min(), Integer::Uint32(library::core::types::Uint32(std::numeric_limits<library::core::types::Uint32>::min()))) ;

    }

}

TEST (Library_Core_Types_Integer, Uint64)
{

    using library::core::types::Integer ;

    {

        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(0))) ;
        
        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(+1))) ;

        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint8>::max()))) ;

        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint16>::min()))) ;
        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint16>::max()))) ;

        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint32>::min()))) ;

        EXPECT_NO_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint64>::min()))) ;
        
        EXPECT_ANY_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint32>::max()))) ;
        EXPECT_ANY_THROW(Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint64>::max()))) ;

    }

    {

        EXPECT_EQ(0, Integer::Uint64(library::core::types::Uint64(0))) ;
        
        EXPECT_EQ(+1, Integer::Uint64(library::core::types::Uint64(+1))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::min(), Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint8>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint8>::max(), Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint8>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint16>::min(), Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint16>::min()))) ;
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint16>::max(), Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint16>::max()))) ;

        EXPECT_EQ(std::numeric_limits<library::core::types::Uint32>::min(), Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint32>::min()))) ;
        
        EXPECT_EQ(std::numeric_limits<library::core::types::Uint64>::min(), Integer::Uint64(library::core::types::Uint64(std::numeric_limits<library::core::types::Uint64>::min()))) ;

    }

}

TEST (Library_Core_Types_Integer, Index)
{

    using library::core::types::Index ;
    using library::core::types::Integer ;

    {

        EXPECT_EQ(0, Integer::Index(Index(0))) ;
        EXPECT_EQ(1, Integer::Index(Index(1))) ;

    }

    {

        EXPECT_ANY_THROW(Integer::Index(Index(std::numeric_limits<Index>::max()))) ;

    }
    
}

TEST (Library_Core_Types_Integer, Size)
{

    using library::core::types::Size ;
    using library::core::types::Integer ;

    {

        EXPECT_EQ(0, Integer::Size(Size(0))) ;
        EXPECT_EQ(1, Integer::Size(Size(1))) ;

    }

    {

        EXPECT_ANY_THROW(Integer::Size(Size(std::numeric_limits<Size>::max()))) ;

    }
    
}

TEST (Library_Core_Types_Integer, CanParse)
{

    using library::core::types::Integer ;

    // Char

    {

        EXPECT_TRUE(Integer::CanParse('0')) ;
        EXPECT_TRUE(Integer::CanParse('1')) ;
        EXPECT_TRUE(Integer::CanParse('2')) ;
        EXPECT_TRUE(Integer::CanParse('3')) ;
        EXPECT_TRUE(Integer::CanParse('9')) ;

        EXPECT_FALSE(Integer::CanParse('a')) ;
        EXPECT_FALSE(Integer::CanParse('-')) ;
        EXPECT_FALSE(Integer::CanParse('+')) ;
        
    }

    // String

    {

        EXPECT_TRUE(Integer::CanParse("Undefined")) ;

        EXPECT_TRUE(Integer::CanParse("0")) ;
        EXPECT_TRUE(Integer::CanParse("-1")) ;
        EXPECT_TRUE(Integer::CanParse("+0")) ;
        EXPECT_TRUE(Integer::CanParse("+1")) ;

        EXPECT_TRUE(Integer::CanParse("-2147483648")) ;
        EXPECT_TRUE(Integer::CanParse("+2147483647")) ;

        EXPECT_TRUE(Integer::CanParse("-Inf")) ;
        EXPECT_TRUE(Integer::CanParse("Inf")) ;
        EXPECT_TRUE(Integer::CanParse("+Inf")) ;

        EXPECT_FALSE(Integer::CanParse("")) ;
        EXPECT_FALSE(Integer::CanParse("abc")) ;
        EXPECT_FALSE(Integer::CanParse("NaN")) ;
        EXPECT_FALSE(Integer::CanParse("-2147483649")) ;
        EXPECT_FALSE(Integer::CanParse("2147483648")) ;
        EXPECT_FALSE(Integer::CanParse("+2147483648")) ;

    }

}

TEST (Library_Core_Types_Integer, Parse)
{

    using library::core::types::Integer ;

    // Char

    {

        EXPECT_EQ(0, Integer::Parse('0')) ;
        EXPECT_EQ(1, Integer::Parse('1')) ;
        EXPECT_EQ(2, Integer::Parse('2')) ;
        EXPECT_EQ(3, Integer::Parse('3')) ;
        EXPECT_EQ(9, Integer::Parse('9')) ;

        EXPECT_ANY_THROW(Integer::Parse('a')) ;
        EXPECT_ANY_THROW(Integer::Parse('-')) ;
        EXPECT_ANY_THROW(Integer::Parse('+')) ;

    }

    // String
    
    {

        EXPECT_FALSE(Integer::Parse("Undefined").isDefined()) ;

        EXPECT_EQ(+0, Integer::Parse("0")) ;
        EXPECT_EQ(-1, Integer::Parse("-1")) ;
        EXPECT_EQ(+0, Integer::Parse("+0")) ;
        EXPECT_EQ(+1, Integer::Parse("+1")) ;

        EXPECT_EQ(-2147483648, Integer::Parse("-2147483648")) ;
        EXPECT_EQ(+2147483647, Integer::Parse("+2147483647")) ;

        EXPECT_TRUE(Integer::Parse("-Inf").isNegativeInfinity()) ;
        EXPECT_TRUE(Integer::Parse("Inf").isPositiveInfinity()) ;
        EXPECT_TRUE(Integer::Parse("+Inf").isPositiveInfinity()) ;

        EXPECT_ANY_THROW(Integer::Parse("")) ;
        EXPECT_ANY_THROW(Integer::Parse("abc")) ;
        EXPECT_ANY_THROW(Integer::Parse("NaN")) ;
        EXPECT_ANY_THROW(Integer::Parse("-2147483649")) ;
        EXPECT_ANY_THROW(Integer::Parse("2147483648")) ;
        EXPECT_ANY_THROW(Integer::Parse("+2147483648")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////