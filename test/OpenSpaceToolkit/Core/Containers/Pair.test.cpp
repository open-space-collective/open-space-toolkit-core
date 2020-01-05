////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Containers/Pair.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Containers_Pair, Constructor)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Pair ;

    {

        const Pair<Integer, String> pair = {123, "abc"} ;

    }

}

TEST (Library_Core_Containers_Pair, Getters)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Pair ;

    {

        const Pair<Integer, String> pair = {123, "abc"} ;

        EXPECT_EQ(123, pair.first) ;
        EXPECT_EQ("abc", pair.second) ;

    }

}

TEST (Library_Core_Containers_Pair, Setters)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Pair ;

    {

        Pair<Integer, String> pair = {123, "abc"} ;

        EXPECT_EQ(123, pair.first) ;
        EXPECT_EQ("abc", pair.second) ;

        pair.first = 456 ;
        pair.second = "def" ;

        EXPECT_EQ(456, pair.first) ;
        EXPECT_EQ("def", pair.second) ;

    }

}

TEST (Library_Core_Containers_Pair, Unpack)
{

    using ostk::core::types::Integer ;
    using ostk::core::types::String ;
    using ostk::core::ctnr::Pair ;
    using ostk::core::ctnr::Unpack ;

    {

        const Pair<Integer, String> pair = {123, "abc"} ;

        Integer integer = Integer::Undefined() ;
        String string = String::Empty() ;

        Unpack(integer, string) = pair ;

        EXPECT_EQ(123, integer) ;
        EXPECT_EQ("abc", string) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
