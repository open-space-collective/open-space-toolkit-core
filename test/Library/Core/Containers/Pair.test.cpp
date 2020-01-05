////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Containers/Pair.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Pair.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Containers_Pair, Constructor)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Pair ;

    {

        const Pair<Integer, String> pair = {123, "abc"} ;

    }

}

TEST (Library_Core_Containers_Pair, Getters)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Pair ;

    {

        const Pair<Integer, String> pair = {123, "abc"} ;

        EXPECT_EQ(123, pair.first) ;
        EXPECT_EQ("abc", pair.second) ;

    }

}

TEST (Library_Core_Containers_Pair, Setters)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Pair ;

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

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Pair ;
    using library::core::ctnr::Unpack ;

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
