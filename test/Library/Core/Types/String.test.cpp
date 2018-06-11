////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/String.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Global.test.hpp>

#include <Library/Core/Types/String.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_Types_String, DefaultConstructor)
{

    using library::core::types::String ;

    EXPECT_NO_THROW(String()) ;
    EXPECT_NO_THROW(String("abc")) ;

}

TEST (Library_Core_Types_String, StringConstructor)
{

    using library::core::types::String ;

    EXPECT_NO_THROW(String(std::string(""))) ;
    EXPECT_NO_THROW(String(std::string("abc"))) ;

}

TEST (Library_Core_Types_String, StringOperator)
{

    using library::core::types::String ;

    {

        String A = "abc" ;

        std::string B = A ;

        EXPECT_EQ("abc", B) ;

    }

}

TEST (Library_Core_Types_String, IsEmpty)
{

    using library::core::types::String ;

    EXPECT_TRUE(String().isEmpty()) ;
    EXPECT_TRUE(String("").isEmpty()) ;

    EXPECT_FALSE(String("abc").isEmpty()) ;
    EXPECT_FALSE(String("\n").isEmpty()) ;

}

TEST (Library_Core_Types_String, IsUppercase)
{

    using library::core::types::String ;

    EXPECT_TRUE(String("ABC").isUppercase()) ;
    EXPECT_TRUE(String("A_B_C").isUppercase()) ;
    EXPECT_TRUE(String("A/B/C").isUppercase()) ;
    EXPECT_TRUE(String("A?B?C").isUppercase()) ;

    EXPECT_FALSE(String().isUppercase()) ;
    EXPECT_FALSE(String("").isUppercase()) ;
    EXPECT_FALSE(String("abc").isUppercase()) ;
    EXPECT_FALSE(String("ABCabc").isUppercase()) ;
    EXPECT_FALSE(String("abcABC").isUppercase()) ;

}

TEST (Library_Core_Types_String, IsLowercase)
{

    using library::core::types::String ;

    EXPECT_TRUE(String("abc").isLowercase()) ;
    EXPECT_TRUE(String("a_b_c").isLowercase()) ;
    EXPECT_TRUE(String("a/b/c").isLowercase()) ;
    EXPECT_TRUE(String("a?b?c").isLowercase()) ;

    EXPECT_FALSE(String().isLowercase()) ;
    EXPECT_FALSE(String("").isLowercase()) ;
    EXPECT_FALSE(String("ABC").isLowercase()) ;
    EXPECT_FALSE(String("ABCabc").isLowercase()) ;
    EXPECT_FALSE(String("abcABC").isLowercase()) ;

}

TEST (Library_Core_Types_String, GetLength)
{

    using library::core::types::String ;

    EXPECT_EQ(size_t(0), String().getLength()) ;
    EXPECT_EQ(size_t(0), String("").getLength()) ;

    EXPECT_EQ(size_t(3), String("abc").getLength()) ;
    EXPECT_EQ(size_t(1), String("\n").getLength()) ;

}

TEST (Library_Core_Types_String, GetFirst)
{

    using library::core::types::String ;

    EXPECT_EQ('H', String("Hello World!").getFirst()) ;
    EXPECT_ANY_THROW(String("").getFirst()) ;

}

TEST (Library_Core_Types_String, GetLast)
{

    using library::core::types::String ;

    EXPECT_EQ('!', String("Hello World!").getLast()) ;
    EXPECT_ANY_THROW(String("").getLast()) ;

}

TEST (Library_Core_Types_String, Empty)
{

    using library::core::types::String ;

    EXPECT_TRUE(String::Empty().isEmpty()) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////