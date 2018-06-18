////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Triple.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Triple.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Containers_Triple, Constructor)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Triple ;
    
    {

        Triple<bool, Integer, String> triple = {true, 123, "abc"} ;

    }

}

TEST (Library_Core_Containers_Triple, Getters)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Triple ;
    
    {

        Triple<bool, Integer, String> triple = {true, 123, "abc"} ;

        EXPECT_EQ(true, triple.first) ;
        EXPECT_EQ(123, triple.second) ;
        EXPECT_EQ("abc", triple.third) ;

    }

}

TEST (Library_Core_Containers_Triple, Setters)
{

    using library::core::types::Integer ;
    using library::core::types::String ;
    using library::core::ctnr::Triple ;
    
    {

        Triple<bool, Integer, String> triple = {true, 123, "abc"} ;

        EXPECT_EQ(true, triple.first) ;
        EXPECT_EQ(123, triple.second) ;
        EXPECT_EQ("abc", triple.third) ;

        triple.first = false ;
        triple.second = 456 ;
        triple.third = "def" ;

        EXPECT_EQ(false, triple.first) ;
        EXPECT_EQ(456, triple.second) ;
        EXPECT_EQ("def", triple.third) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////