////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/Real.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Triple.hpp>
#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Types/Real.hpp>

#include <cmath>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Types_Real, DefaultConstructor)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real(0.0)) ;
    EXPECT_NO_THROW(Real(1.0)) ;
    EXPECT_NO_THROW(Real(123.0)) ;
    EXPECT_NO_THROW(Real(+123.0)) ;
    EXPECT_NO_THROW(Real(-123.0)) ;

}

TEST (Library_Core_Types_Real, AssignmentOperator)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real a = 0.0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Real a = 0.0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Real a = 1.0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Real a = 123.0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Real a = +123.0 ; (void) a ; ) ;
    EXPECT_NO_THROW(Real a = -123.0 ; (void) a ; ) ;

}

TEST (Library_Core_Types_Real, EqualToOperator)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(0.0) == Real(0.0)) ;
        EXPECT_TRUE(Real(123.0) == Real(123.0)) ;
        EXPECT_TRUE(Real(+123.0) == Real(+123.0)) ;
        EXPECT_TRUE(Real(-123.0) == Real(-123.0)) ;

    }

    {

        EXPECT_FALSE(Real(0.0) == Real(1.0)) ;
        EXPECT_FALSE(Real(1.0) == Real(0.0)) ;
        EXPECT_FALSE(Real(-1.0) == Real(+1.0)) ;

        EXPECT_FALSE(Real::Undefined() == Real::Undefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity() == Real::PositiveInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() == Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::PositiveInfinity() == Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() == Real::PositiveInfinity()) ;

    }    

}

TEST (Library_Core_Types_Real, NotEqualToOperator)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(0.0) != Real(1.0)) ;
        EXPECT_TRUE(Real(1.0) != Real(0.0)) ;
        EXPECT_TRUE(Real(-1.0) != Real(+1.0)) ;

    }

    {

        EXPECT_FALSE(Real(0.0) != Real(0.0)) ;
        EXPECT_FALSE(Real(123.0) != Real(123.0)) ;
        EXPECT_FALSE(Real(+123.0) != Real(+123.0)) ;
        EXPECT_FALSE(Real(-123.0) != Real(-123.0)) ;

        EXPECT_FALSE(Real::Undefined() != Real::Undefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity() != Real::PositiveInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() != Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::PositiveInfinity() != Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() != Real::PositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, LessThanOperator)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(0.0) < Real(1.0)) ;
        EXPECT_TRUE(Real(1.0) < Real(2.0)) ;
        EXPECT_TRUE(Real(-1.0) < Real(0.0)) ;
        EXPECT_TRUE(Real(-1.0) < Real(+1.0)) ;
        EXPECT_TRUE(Real(-123.0) < Real(+123.0)) ;

    }

    {

        EXPECT_FALSE(Real(0.0) < Real(0.0)) ;
        EXPECT_FALSE(Real(1.0) < Real(0.0)) ;
        EXPECT_FALSE(Real(+1.0) < Real(-1.0)) ;
        EXPECT_FALSE(Real(+123.0) < Real(-123.0)) ;
        EXPECT_FALSE(Real(+123.0) < Real(+123.0)) ;
        EXPECT_FALSE(Real(-123.0) < Real(-123.0)) ;
        
        EXPECT_FALSE(Real::Undefined() < Real::Undefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity() < Real::PositiveInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() < Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::PositiveInfinity() < Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() < Real::PositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, LessThanOrEqualToOperator)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(0.0) <= Real(1.0)) ;
        EXPECT_TRUE(Real(1.0) <= Real(2.0)) ;
        EXPECT_TRUE(Real(-1.0) <= Real(0.0)) ;
        EXPECT_TRUE(Real(-1.0) <= Real(+1.0)) ;
        EXPECT_TRUE(Real(-123.0) <= Real(+123.0)) ;
        EXPECT_TRUE(Real(0.0) <= Real(0.0)) ;
        EXPECT_TRUE(Real(+123.0) <= Real(+123.0)) ;
        EXPECT_TRUE(Real(-123.0) <= Real(-123.0)) ;

    }

    {

        EXPECT_FALSE(Real(1.0) <= Real(0.0)) ;
        EXPECT_FALSE(Real(+1.0) <= Real(-1.0)) ;
        EXPECT_FALSE(Real(+123.0) <= Real(-123.0)) ;
        
        EXPECT_FALSE(Real::Undefined() <= Real::Undefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity() <= Real::PositiveInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() <= Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::PositiveInfinity() <= Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() <= Real::PositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, GreaterThanOperator)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(1.0) > Real(0.0)) ;
        EXPECT_TRUE(Real(2.0) > Real(1.0)) ;
        EXPECT_TRUE(Real(+1.0) > Real(0.0)) ;
        EXPECT_TRUE(Real(+1.0) > Real(-1.0)) ;
        EXPECT_TRUE(Real(+123.0) > Real(-123.0)) ;

    }

    {

        EXPECT_FALSE(Real(0.0) > Real(0.0)) ;
        EXPECT_FALSE(Real(0.0) > Real(1.0)) ;
        EXPECT_FALSE(Real(-1.0) > Real(+1.0)) ;
        EXPECT_FALSE(Real(-123.0) > Real(+123.0)) ;
        EXPECT_FALSE(Real(+123.0) > Real(+123.0)) ;
        EXPECT_FALSE(Real(-123.0) > Real(-123.0)) ;
        
        EXPECT_FALSE(Real::Undefined() > Real::Undefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity() > Real::PositiveInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() > Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::PositiveInfinity() > Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() > Real::PositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, GreaterThanOrEqualToOperator)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(1.0) >= Real(0.0)) ;
        EXPECT_TRUE(Real(2.0) >= Real(1.0)) ;
        EXPECT_TRUE(Real(+1.0) >= Real(0.0)) ;
        EXPECT_TRUE(Real(+1.0) >= Real(-1.0)) ;
        EXPECT_TRUE(Real(+123.0) >= Real(-123.0)) ;
        EXPECT_TRUE(Real(0.0) >= Real(0.0)) ;
        EXPECT_TRUE(Real(+123.0) >= Real(+123.0)) ;
        EXPECT_TRUE(Real(-123.0) >= Real(-123.0)) ;

    }

    {

        EXPECT_FALSE(Real(0.0) >= Real(1.0)) ;
        EXPECT_FALSE(Real(-1.0) >= Real(+1.0)) ;
        EXPECT_FALSE(Real(-123.0) >= Real(+123.0)) ;
        
        EXPECT_FALSE(Real::Undefined() >= Real::Undefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity() >= Real::PositiveInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() >= Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::PositiveInfinity() >= Real::NegativeInfinity()) ;
        EXPECT_FALSE(Real::NegativeInfinity() >= Real::PositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, AdditionOperator)
{

    using library::core::types::Real ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Real, Real, Real>> testCases =
    {

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
        {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::NegativeInfinity()},
        {std::numeric_limits<Real::ValueType>::lowest(), +0.0, std::numeric_limits<Real::ValueType>::lowest()},
        {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest() + 1},
        {std::numeric_limits<Real::ValueType>::lowest(), +2.0, std::numeric_limits<Real::ValueType>::lowest() + 2},
        {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + std::numeric_limits<Real::ValueType>::max()},
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
        {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max() + std::numeric_limits<Real::ValueType>::lowest()},
        {std::numeric_limits<Real::ValueType>::max(), -2.0, std::numeric_limits<Real::ValueType>::max() - 2},
        {std::numeric_limits<Real::ValueType>::max(), -1.0, std::numeric_limits<Real::ValueType>::max() - 1},
        {std::numeric_limits<Real::ValueType>::max(), +0.0, std::numeric_limits<Real::ValueType>::max()},
        {std::numeric_limits<Real::ValueType>::max(), +1.0, Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
        {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
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

    } ;

    for (const auto& testCase : testCases)
    {

        const Real& a = testCase.first ;
        const Real& b = testCase.second ;
        const Real& c = testCase.third ;

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

TEST (Library_Core_Types_Real, SubtractionOperator)
{

    using library::core::types::Real ;
    using library::core::ctnr::Triple ;
    using library::core::ctnr::Array ;

    Array<Triple<Real, Real, Real>> testCases =
    {

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
        {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
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
        {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
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

    } ;

    for (const auto& testCase : testCases)
    {

        const Real& a = testCase.first ;
        const Real& b = testCase.second ;
        const Real& c = testCase.third ;
        
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

// TEST (Library_Core_Types_Real, MultiplicationOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Triple ;
//     using library::core::ctnr::Array ;

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
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), Real::NegativeInfinity()},

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
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, -std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), Real::PositiveInfinity()},

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

// TEST (Library_Core_Types_Real, DivisionOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Triple ;
//     using library::core::ctnr::Array ;

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
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, std::numeric_limits<Real::ValueType>::lowest() / -2.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
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

// TEST (Library_Core_Types_Real, AdditionAssignmentOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Triple ;
//     using library::core::ctnr::Array ;

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
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest() + 1},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, std::numeric_limits<Real::ValueType>::lowest() + 2},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest() + std::numeric_limits<Real::ValueType>::max()},
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
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max() + std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, std::numeric_limits<Real::ValueType>::max() - 2},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, std::numeric_limits<Real::ValueType>::max() - 1},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), Real::PositiveInfinity()},

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

// TEST (Library_Core_Types_Real, SubtractionAssignmentOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Triple ;
//     using library::core::ctnr::Array ;

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
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), Real::NegativeInfinity()},

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
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::PositiveInfinity()},
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

// TEST (Library_Core_Types_Real, MultiplicationAssignmentOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Triple ;
//     using library::core::ctnr::Array ;

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
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), +1.0, std::numeric_limits<Real::ValueType>::lowest()},
//         {std::numeric_limits<Real::ValueType>::lowest(), +2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), std::numeric_limits<Real::ValueType>::max(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::lowest(), Real::PositiveInfinity(), Real::NegativeInfinity()},

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
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::lowest(), Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -2.0, Real::NegativeInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), -1.0, -std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +0.0, +0.0},
//         {std::numeric_limits<Real::ValueType>::max(), +1.0, std::numeric_limits<Real::ValueType>::max()},
//         {std::numeric_limits<Real::ValueType>::max(), +2.0, Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity()},
//         {std::numeric_limits<Real::ValueType>::max(), Real::PositiveInfinity(), Real::PositiveInfinity()},

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

// TEST (Library_Core_Types_Real, DivisionAssignmentOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Triple ;
//     using library::core::ctnr::Array ;

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
//         {std::numeric_limits<Real::ValueType>::lowest(), -2.0, std::numeric_limits<Real::ValueType>::lowest() / -2.0},
//         {std::numeric_limits<Real::ValueType>::lowest(), -1.0, Real::PositiveInfinity()},
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

// TEST (Library_Core_Types_Real, UnaryPlusOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Pair ;
//     using library::core::ctnr::Array ;

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

// TEST (Library_Core_Types_Real, UnaryMinusOperator)
// {

//     using library::core::types::Real ;
//     using library::core::ctnr::Pair ;
//     using library::core::ctnr::Array ;

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

// TEST (Library_Core_Types_Real, ValueTypeOperator)
// {

//     using library::core::types::Real ;
    
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

// // TEST (Library_Core_Types_Real, StreamOperator)
// // {

// //     using library::core::types::Real ;

// //     FAIL() ;

// // }

TEST (Library_Core_Types_Real, IsDefined)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real(0.0).isDefined()) ;
    EXPECT_TRUE(Real(-1.0).isDefined()) ;
    EXPECT_TRUE(Real(+0.0).isDefined()) ;
    EXPECT_TRUE(Real(+1.0).isDefined()) ;
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isDefined()) ;
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isDefined()) ;
    EXPECT_TRUE(Real::NegativeInfinity().isDefined()) ;
    EXPECT_TRUE(Real::PositiveInfinity().isDefined()) ;

    EXPECT_FALSE(Real::Undefined().isDefined()) ;

}

TEST (Library_Core_Types_Real, IsZero)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real(0.0).isZero()) ;
    EXPECT_TRUE(Real(+0.0).isZero()) ;

    EXPECT_FALSE(Real(-1.0).isZero()) ;
    EXPECT_FALSE(Real(+1.0).isZero()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isZero()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isZero()) ;
    EXPECT_FALSE(Real::NegativeInfinity().isZero()) ;
    EXPECT_FALSE(Real::PositiveInfinity().isZero()) ;
    EXPECT_FALSE(Real::Undefined().isZero()) ;

}

TEST (Library_Core_Types_Real, IsPositive)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real(0.0).isPositive()) ;
    EXPECT_TRUE(Real(+0.0).isPositive()) ;
    EXPECT_TRUE(Real(+1.0).isPositive()) ;
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isPositive()) ;
    EXPECT_TRUE(Real::PositiveInfinity().isPositive()) ;

    EXPECT_FALSE(Real::Undefined().isPositive()) ;
    EXPECT_FALSE(Real(-1.0).isPositive()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isPositive()) ;
    EXPECT_FALSE(Real::NegativeInfinity().isPositive()) ;

}

TEST (Library_Core_Types_Real, IsNegative)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real(0.0).isNegative()) ;
    EXPECT_TRUE(Real(-1.0).isNegative()) ;
    EXPECT_TRUE(Real(+0.0).isNegative()) ;
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isNegative()) ;
    EXPECT_TRUE(Real::NegativeInfinity().isNegative()) ;

    EXPECT_FALSE(Real::Undefined().isNegative()) ;
    EXPECT_FALSE(Real(+1.0).isNegative()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isNegative()) ;
    EXPECT_FALSE(Real::PositiveInfinity().isNegative()) ;

}

TEST (Library_Core_Types_Real, IsStrictlyPositive)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real(+1.0).isStrictlyPositive()) ;
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isStrictlyPositive()) ;
    EXPECT_TRUE(Real::PositiveInfinity().isStrictlyPositive()) ;

    EXPECT_FALSE(Real::Undefined().isStrictlyPositive()) ;
    EXPECT_FALSE(Real(0.0).isStrictlyPositive()) ;
    EXPECT_FALSE(Real(-1.0).isStrictlyPositive()) ;
    EXPECT_FALSE(Real(+0.0).isStrictlyPositive()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isStrictlyPositive()) ;
    EXPECT_FALSE(Real::NegativeInfinity().isStrictlyPositive()) ;

}

TEST (Library_Core_Types_Real, IsStrictlyNegative)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real(-1.0).isStrictlyNegative()) ;
    EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isStrictlyNegative()) ;
    EXPECT_TRUE(Real::NegativeInfinity().isStrictlyNegative()) ;

    EXPECT_FALSE(Real::Undefined().isStrictlyNegative()) ;
    EXPECT_FALSE(Real(0.0).isStrictlyNegative()) ;
    EXPECT_FALSE(Real(+1.0).isStrictlyNegative()) ;
    EXPECT_FALSE(Real(+0.0).isStrictlyNegative()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isStrictlyNegative()) ;
    EXPECT_FALSE(Real::PositiveInfinity().isStrictlyNegative()) ;

}

TEST (Library_Core_Types_Real, IsInfinity)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real::NegativeInfinity().isInfinity()) ;
    EXPECT_TRUE(Real::PositiveInfinity().isInfinity()) ;

    EXPECT_FALSE(Real::Undefined().isInfinity()) ;
    EXPECT_FALSE(Real(0.0).isInfinity()) ;
    EXPECT_FALSE(Real(-1.0).isInfinity()) ;
    EXPECT_FALSE(Real(+0.0).isInfinity()) ;
    EXPECT_FALSE(Real(+1.0).isInfinity()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isInfinity()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isInfinity()) ;

}

TEST (Library_Core_Types_Real, IsPositiveInfinity)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real::PositiveInfinity().isPositiveInfinity()) ;

    EXPECT_FALSE(Real::Undefined().isPositiveInfinity()) ;
    EXPECT_FALSE(Real(0.0).isPositiveInfinity()) ;
    EXPECT_FALSE(Real(-1.0).isPositiveInfinity()) ;
    EXPECT_FALSE(Real(+0.0).isPositiveInfinity()) ;
    EXPECT_FALSE(Real(+1.0).isPositiveInfinity()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isPositiveInfinity()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isPositiveInfinity()) ;
    EXPECT_FALSE(Real::NegativeInfinity().isPositiveInfinity()) ;

}

TEST (Library_Core_Types_Real, IsNegativeInfinity)
{

    using library::core::types::Real ;

    EXPECT_TRUE(Real::NegativeInfinity().isNegativeInfinity()) ;

    EXPECT_FALSE(Real::Undefined().isNegativeInfinity()) ;
    EXPECT_FALSE(Real(0.0).isNegativeInfinity()) ;
    EXPECT_FALSE(Real(-1.0).isNegativeInfinity()) ;
    EXPECT_FALSE(Real(+0.0).isNegativeInfinity()) ;
    EXPECT_FALSE(Real(+1.0).isNegativeInfinity()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::lowest()).isNegativeInfinity()) ;
    EXPECT_FALSE(Real(std::numeric_limits<Real::ValueType>::max()).isNegativeInfinity()) ;
    EXPECT_FALSE(Real::PositiveInfinity().isNegativeInfinity()) ;

}

TEST (Library_Core_Types_Real, IsInteger)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(0.0).isInteger()) ;
        EXPECT_TRUE(Real(1.0).isInteger()) ;
        
        EXPECT_TRUE(Real(-1.0).isInteger()) ;
        EXPECT_TRUE(Real(+1.0).isInteger()) ;

        EXPECT_TRUE(Real(-999.0).isInteger()) ;
        EXPECT_TRUE(Real(+999.0).isInteger()) ;

        EXPECT_TRUE(Real(-1.0e6).isInteger()) ;
        EXPECT_TRUE(Real(+1.0e6).isInteger()) ;

        EXPECT_TRUE(Real(-1.0e+300).isInteger()) ;
        EXPECT_TRUE(Real(+1.0e+300).isInteger()) ;

    }

    {

        EXPECT_FALSE(Real(0.1).isInteger()) ;
        EXPECT_FALSE(Real(1.1).isInteger()) ;
        EXPECT_FALSE(Real(0.999999999999).isInteger()) ;
        
        EXPECT_FALSE(Real(-1.0e-6).isInteger()) ;
        EXPECT_FALSE(Real(+1.0e-6).isInteger()) ;

    }

    {

        EXPECT_FALSE(Real::Undefined().isInteger()) ;
        EXPECT_FALSE(Real::NegativeInfinity().isInteger()) ;
        EXPECT_FALSE(Real::PositiveInfinity().isInteger()) ;

    }

}

TEST (Library_Core_Types_Real, IsFinite)
{

    using library::core::types::Real ;

    {

        EXPECT_TRUE(Real(0.0).isFinite()) ;
        EXPECT_TRUE(Real(-1.0).isFinite()) ;
        EXPECT_TRUE(Real(+0.0).isFinite()) ;
        EXPECT_TRUE(Real(+1.0).isFinite()) ;
        EXPECT_TRUE(Real(-1.0e+300).isFinite()) ;
        EXPECT_TRUE(Real(+1.0e+300).isFinite()) ;
        EXPECT_TRUE(Real(-1.0e-300).isFinite()) ;
        EXPECT_TRUE(Real(+1.0e-300).isFinite()) ;
        EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::lowest()).isFinite()) ;
        EXPECT_TRUE(Real(std::numeric_limits<Real::ValueType>::max()).isFinite()) ;

    }

    {

        EXPECT_FALSE(Real::Undefined().isFinite()) ;
        EXPECT_FALSE(Real::NegativeInfinity().isFinite()) ;
        EXPECT_FALSE(Real::PositiveInfinity().isFinite()) ;

    }

}

TEST (Library_Core_Types_Real, GetSign)
{

    using library::core::types::Sign ;
    using library::core::types::Real ;

    EXPECT_EQ(Sign::Undefined, Real::Undefined().getSign()) ;
    EXPECT_EQ(Sign::None, Real(0.0).getSign()) ;
    EXPECT_EQ(Sign::Negative, Real(-1.0).getSign()) ;
    EXPECT_EQ(Sign::None, Real(+0.0).getSign()) ;
    EXPECT_EQ(Sign::Positive, Real(+1.0).getSign()) ;
    EXPECT_EQ(Sign::Negative, Real(std::numeric_limits<Real::ValueType>::lowest()).getSign()) ;
    EXPECT_EQ(Sign::Positive, Real(std::numeric_limits<Real::ValueType>::max()).getSign()) ;
    EXPECT_EQ(Sign::Negative, Real::NegativeInfinity().getSign()) ;
    EXPECT_EQ(Sign::Positive, Real::PositiveInfinity().getSign()) ;

}

TEST (Library_Core_Types_Real, ToString)
{

    using library::core::types::Real ;

    EXPECT_EQ("Undefined", Real::Undefined().toString()) ;
    EXPECT_EQ("0.0", Real(0.0).toString()) ;
    EXPECT_EQ("-1.1", Real(-1.1).toString()) ;
    EXPECT_EQ("-1.0", Real(-1.0).toString()) ;
    EXPECT_EQ("0.0", Real(+0.0).toString()) ;
    EXPECT_EQ("1.0", Real(+1.0).toString()) ;
    EXPECT_EQ("1.1", Real(+1.1).toString()) ;
    EXPECT_EQ("-Inf", Real::NegativeInfinity().toString()) ;
    EXPECT_EQ("+Inf", Real::PositiveInfinity().toString()) ;

}

TEST (Library_Core_Types_Real, ToInteger)
{

    using library::core::types::Integer ;
    using library::core::types::Real ;

    {

        EXPECT_EQ(0, Real(0.0).toInteger()) ;

        EXPECT_EQ(+1, Real(+1.0).toInteger()) ;
        EXPECT_EQ(-1, Real(-1.0).toInteger()) ;

        EXPECT_EQ(+123, Real(+123.0).toInteger()) ;
        EXPECT_EQ(-123, Real(-123.0).toInteger()) ;

    }

    {

        EXPECT_ANY_THROW(Real::Undefined().toInteger()) ;
        EXPECT_ANY_THROW(Real(0.1).toInteger()) ;
        EXPECT_ANY_THROW(Real(10.1).toInteger()) ;

    }

}

TEST (Library_Core_Types_Real, Abs)
{

    using library::core::types::Real ;

    {

        EXPECT_EQ(0.0, Real(0.0).abs()) ;
        EXPECT_EQ(1.0, Real(+1.0).abs()) ;
        EXPECT_EQ(1.0, Real(-1.0).abs()) ;
        EXPECT_EQ(2.0, Real(+2.0).abs()) ;
        EXPECT_EQ(2.0, Real(-2.0).abs()) ;

    }

    {

        EXPECT_NO_THROW(Real::Undefined().abs()) ;

        EXPECT_FALSE(Real::Undefined().abs().isDefined()) ;

    }

    {

        EXPECT_NO_THROW(Real::PositiveInfinity().abs()) ;
        EXPECT_NO_THROW(Real::NegativeInfinity().abs()) ;

        EXPECT_TRUE(Real::PositiveInfinity().abs().isDefined()) ;
        EXPECT_TRUE(Real::NegativeInfinity().abs().isDefined()) ;

        EXPECT_TRUE(Real::PositiveInfinity().abs().isPositiveInfinity()) ;
        EXPECT_TRUE(Real::NegativeInfinity().abs().isPositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, Floor)
{

    using library::core::types::Real ;

    {

        EXPECT_EQ(+0, Real(0.0).floor()) ;
        EXPECT_EQ(+1, Real(+1.0).floor()) ;
        EXPECT_EQ(+1, Real(+1.1).floor()) ;
        EXPECT_EQ(-1, Real(-1.0).floor()) ;
        EXPECT_EQ(-2, Real(-1.1).floor()) ;
        EXPECT_EQ(+2.0, Real(+2.0).floor()) ;
        EXPECT_EQ(-2.0, Real(-2.0).floor()) ;

    }

    {

        EXPECT_NO_THROW(Real::Undefined().floor()) ;
        EXPECT_NO_THROW(Real::PositiveInfinity().floor()) ;
        EXPECT_NO_THROW(Real::NegativeInfinity().floor()) ;

        EXPECT_FALSE(Real::Undefined().floor().isDefined()) ;
        EXPECT_FALSE(Real::PositiveInfinity().floor().isDefined()) ;
        EXPECT_FALSE(Real::NegativeInfinity().floor().isDefined()) ;

    }

}

TEST (Library_Core_Types_Real, Sqrt)
{

    using library::core::types::Real ;

    {

        EXPECT_EQ(0.0, Real(0.0).sqrt()) ;
        EXPECT_EQ(1.0, Real(+1.0).sqrt()) ;
        EXPECT_EQ(2.0, Real(+4.0).sqrt()) ;

    }

    {

        EXPECT_NO_THROW(Real(-1.0).sqrt()) ;
        EXPECT_NO_THROW(Real(-2.0).sqrt()) ;

        EXPECT_FALSE(Real(-1.0).sqrt().isDefined()) ;
        EXPECT_FALSE(Real(-2.0).sqrt().isDefined()) ;
        
    }
    
    {

        EXPECT_NO_THROW(Real::Undefined().sqrt()) ;

        EXPECT_FALSE(Real::Undefined().sqrt().isDefined()) ;

    }

    {

        EXPECT_NO_THROW(Real::PositiveInfinity().sqrt()) ;
        EXPECT_NO_THROW(Real::NegativeInfinity().sqrt()) ;

        EXPECT_TRUE(Real::PositiveInfinity().sqrt().isDefined()) ;
        EXPECT_FALSE(Real::NegativeInfinity().sqrt().isDefined()) ;

        EXPECT_TRUE(Real::PositiveInfinity().sqrt().isPositiveInfinity()) ;

    }

}

TEST (Library_Core_Types_Real, Undefined)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::Undefined()) ;
   
    EXPECT_FALSE(Real::Undefined().isDefined()) ;
    EXPECT_FALSE(Real::Undefined().isInfinity()) ;

}

TEST (Library_Core_Types_Real, Zero)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::Zero()) ;
    EXPECT_TRUE(Real::Zero().isDefined()) ;

    EXPECT_EQ(0.0, Real::Zero()) ;

}

TEST (Library_Core_Types_Real, Pi)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::Pi()) ;
    EXPECT_TRUE(Real::Pi().isDefined()) ;

    EXPECT_EQ(M_PI, Real::Pi()) ;

}

TEST (Library_Core_Types_Real, HalfPi)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::HalfPi()) ;
    EXPECT_TRUE(Real::HalfPi().isDefined()) ;

    EXPECT_EQ(M_PI / 2.0, Real::HalfPi()) ;

}

TEST (Library_Core_Types_Real, TwoPi)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::TwoPi()) ;
    EXPECT_TRUE(Real::TwoPi().isDefined()) ;

    EXPECT_EQ(2.0 * M_PI, Real::TwoPi()) ;

}

TEST (Library_Core_Types_Real, Epsilon)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::Epsilon()) ;
    EXPECT_TRUE(Real::Epsilon().isDefined()) ;
    EXPECT_FALSE(Real::Epsilon().isZero()) ;

    EXPECT_EQ(1e-15, Real::Epsilon()) ;

}

TEST (Library_Core_Types_Real, PositiveInfinity)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::PositiveInfinity()) ;

    EXPECT_TRUE(Real::PositiveInfinity().isDefined()) ;
    EXPECT_TRUE(Real::PositiveInfinity().isInfinity()) ;
    EXPECT_TRUE(Real::PositiveInfinity().isPositiveInfinity()) ;

}

TEST (Library_Core_Types_Real, NegativeInfinity)
{

    using library::core::types::Real ;

    EXPECT_NO_THROW(Real::NegativeInfinity()) ;
    
    EXPECT_TRUE(Real::NegativeInfinity().isDefined()) ;
    EXPECT_TRUE(Real::NegativeInfinity().isInfinity()) ;
    EXPECT_TRUE(Real::NegativeInfinity().isNegativeInfinity()) ;

}

TEST (Library_Core_Types_Real, Integer)
{

    using library::core::types::Integer ;
    using library::core::types::Real ;

    {

        EXPECT_NO_THROW(Real::Integer(Integer(123))) ;
    
        EXPECT_TRUE(Real::Integer(Integer(123)).isDefined()) ;
        EXPECT_TRUE(Real::Integer(Integer(123)).isInteger()) ;
        EXPECT_TRUE(Real::Integer(Integer(123)).isFinite()) ;
        
        EXPECT_EQ(Integer(123), Real::Integer(Integer(123)).toInteger()) ;

    }

    {

        EXPECT_NO_THROW(Real::Integer(Integer::Undefined())) ;

        EXPECT_FALSE(Real::Integer(Integer::Undefined()).isDefined()) ;

    }

}

TEST (Library_Core_Types_Real, Parse)
{

    using library::core::types::Real ;

    EXPECT_FALSE(Real::Parse("").isDefined()) ;
    EXPECT_FALSE(Real::Parse("Undefined").isDefined()) ;

    EXPECT_EQ(+0.0, Real::Parse("0")) ;
    EXPECT_EQ(-1.0, Real::Parse("-1")) ;
    EXPECT_EQ(+0.0, Real::Parse("+0")) ;
    EXPECT_EQ(+1.0, Real::Parse("+1")) ;
    
    EXPECT_EQ(+0.0, Real::Parse("0.0")) ;
    EXPECT_EQ(-1.0, Real::Parse("-1.0")) ;
    EXPECT_EQ(+0.0, Real::Parse("+0.0")) ;
    EXPECT_EQ(+1.0, Real::Parse("+1.0")) ;

    EXPECT_EQ(-2147483648.0, Real::Parse("-2147483648.0")) ;
    EXPECT_EQ(+2147483647.0, Real::Parse("+2147483647.0")) ;

    EXPECT_NO_THROW(Real::Parse("-2147483649.0")) ;
    EXPECT_NO_THROW(Real::Parse("2147483648.0")) ;
    EXPECT_NO_THROW(Real::Parse("+2147483648.0")) ;

    EXPECT_ANY_THROW(Real::Parse("-1e600")) ;
    EXPECT_ANY_THROW(Real::Parse("+1e600")) ;

    EXPECT_TRUE(Real::Parse("-Inf").isNegativeInfinity()) ;
    EXPECT_TRUE(Real::Parse("Inf").isPositiveInfinity()) ;
    EXPECT_TRUE(Real::Parse("+Inf").isPositiveInfinity()) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////