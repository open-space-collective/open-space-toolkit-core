////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Tuple.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Tuple.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Containers_Tuple, Constructor)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    
    {

        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"} ;

    }

}

TEST (Library_Core_Containers_Tuple, Getters)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    
    {

        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"} ;

        EXPECT_EQ(123, std::get<0>(tuple)) ;
        EXPECT_EQ("abc", std::get<1>(tuple)) ;
        EXPECT_EQ(456, std::get<2>(tuple)) ;
        EXPECT_EQ("def", std::get<3>(tuple)) ;

    }

}

TEST (Library_Core_Containers_Tuple, Setters)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    
    {

        Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"} ;

        EXPECT_EQ(123, std::get<0>(tuple)) ;
        EXPECT_EQ("abc", std::get<1>(tuple)) ;
        EXPECT_EQ(456, std::get<2>(tuple)) ;
        EXPECT_EQ("def", std::get<3>(tuple)) ;

        std::get<2>(tuple) = 789 ;
        std::get<3>(tuple) = "ghi" ;

        EXPECT_EQ(123, std::get<0>(tuple)) ;
        EXPECT_EQ("abc", std::get<1>(tuple)) ;
        EXPECT_EQ(789, std::get<2>(tuple)) ;
        EXPECT_EQ("ghi", std::get<3>(tuple)) ;

    }

}

TEST (Library_Core_Containers_Tuple, Unpack)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Tuple ;
    using library::core::ctnr::Unpack ;
    
    {

        const Tuple<Integer, String, Integer, String> tuple = {123, "abc", 456, "def"} ;

        Integer firstInteger = Integer::Undefined() ;
        Integer secondInteger = Integer::Undefined() ;
        String firstString = String::Empty() ;
        String secondString = String::Empty() ;

        Unpack(firstInteger, firstString, secondInteger, secondString) = tuple ;

        EXPECT_EQ(123, firstInteger) ;
        EXPECT_EQ(456, secondInteger) ;
        EXPECT_EQ("abc", firstString) ;
        EXPECT_EQ("def", secondString) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////