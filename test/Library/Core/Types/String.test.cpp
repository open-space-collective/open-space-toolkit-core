////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Types/String.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <Global.test.hpp>

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

TEST (Library_Core_Types_String, Match)
{

    using library::core::types::String ;

    {

        EXPECT_TRUE(String("abc").match(std::regex("^[a-z]{3}$"))) ;

    }

    {

        EXPECT_FALSE(String("abc").match(std::regex("^[a-z]{4}$"))) ;

    }

}

TEST (Library_Core_Types_String, GetLength)
{

    using library::core::types::String ;

    EXPECT_EQ(size_t(0), String().getLength()) ;
    EXPECT_EQ(size_t(0), String("").getLength()) ;

    EXPECT_EQ(size_t(3), String("abc").getLength()) ;
    EXPECT_EQ(size_t(1), String("\n").getLength()) ;

}

TEST (Library_Core_Types_String, GetHead)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("abc", String("abcdef").getHead(3)) ;
        EXPECT_EQ("abc", String("abc").getHead(3)) ;
        EXPECT_EQ("", String("abcdef").getHead(0)) ;
        EXPECT_EQ("", String("").getHead(0)) ;

    }

    {

        EXPECT_ANY_THROW(String("abc").getHead(4)) ;

    }

}

TEST (Library_Core_Types_String, GetTail)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("def", String("abcdef").getTail(3)) ;
        EXPECT_EQ("abc", String("abc").getTail(3)) ;
        EXPECT_EQ("", String("abcdef").getTail(0)) ;
        EXPECT_EQ("", String("").getTail(0)) ;

    }

    {

        EXPECT_ANY_THROW(String("abc").getTail(4)) ;

    }

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

TEST (Library_Core_Types_String, GetSubstring)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("abc", String("abcdef").getSubstring(0, 3)) ;
        EXPECT_EQ("def", String("abcdef").getSubstring(3, 3)) ;

    }

    {

        EXPECT_ANY_THROW(String("").getSubstring(0, 1)) ;
        EXPECT_ANY_THROW(String("abc").getSubstring(0, 0)) ;
        EXPECT_ANY_THROW(String("abc").getSubstring(3, 1)) ;
        EXPECT_ANY_THROW(String("abc").getSubstring(0, 4)) ;

    }

}

TEST (Library_Core_Types_String, Trim)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("", String("").trim()) ;
        EXPECT_EQ("abc", String("abc").trim()) ;
        EXPECT_EQ("abc", String("abc\n").trim()) ;
        EXPECT_EQ("abc", String("abc\r").trim()) ;
        EXPECT_EQ("abc", String("abc\r\n").trim()) ;
        EXPECT_EQ("abc", String(" abc").trim()) ;
        EXPECT_EQ("abc", String("   abc").trim()) ;
        EXPECT_EQ("abc", String("abc ").trim()) ;
        EXPECT_EQ("abc", String("abc   ").trim()) ;
        EXPECT_EQ("abc", String(" abc ").trim()) ;
        EXPECT_EQ("abc", String("   abc   ").trim()) ;
        EXPECT_EQ("ab cd", String("   ab cd   ").trim()) ;
        EXPECT_EQ("", String(" ").trim()) ;
        EXPECT_EQ("", String("   ").trim()) ;

    }

}

TEST (Library_Core_Types_String, Replace)
{

    using library::core::types::String ;

    // Char

    {

        EXPECT_EQ("", String("").replace('a', 'a')) ;
        EXPECT_EQ("bbc", String("abc").replace('a', 'b')) ;
        EXPECT_EQ("abc-", String("abc\n").replace('\n', '-')) ;
        EXPECT_EQ("abc-", String("abc\r").replace('\r', '-')) ;
        EXPECT_EQ("abc-\n", String("abc\r\n").replace('\r', '-')) ;
        EXPECT_EQ("-abc", String(" abc").replace(' ', '-')) ;
        EXPECT_EQ("---abc", String("   abc").replace(' ', '-')) ;
        EXPECT_EQ("abc-", String("abc ").replace(' ', '-')) ;
        EXPECT_EQ("abc---", String("abc   ").replace(' ', '-')) ;
        EXPECT_EQ("-abc-", String(" abc ").replace(' ', '-')) ;
        EXPECT_EQ("---abc---", String("   abc   ").replace(' ', '-')) ;
        EXPECT_EQ("---ab-cd---", String("   ab cd   ").replace(' ', '-')) ;

    }

    // String

    {

        EXPECT_EQ("", String("").replace("", "")) ;
        EXPECT_EQ("bbc", String("abc").replace("a", "b")) ;
        EXPECT_EQ("abc", String("abc\n").replace("\n", "")) ;
        EXPECT_EQ("abc", String("abc\r").replace("\r", "")) ;
        EXPECT_EQ("abc", String("abc\r\n").replace("\r\n", "")) ;
        EXPECT_EQ("abc", String(" abc").replace(" ", "")) ;
        EXPECT_EQ("abc", String("   abc").replace("   ", "")) ;
        EXPECT_EQ("abc", String("abc ").replace(" ", "")) ;
        EXPECT_EQ("abc", String("abc   ").replace(" ", "")) ;
        EXPECT_EQ("abc", String(" abc ").replace(" ", "")) ;
        EXPECT_EQ("abc", String("   abc   ").replace(" ", "")) ;
        EXPECT_EQ("ab cd", String("   ab cd   ").replace("   ", "")) ;

    }

}

TEST (Library_Core_Types_String, Empty)
{

    using library::core::types::String ;

    EXPECT_TRUE(String::Empty().isEmpty()) ;

}

TEST (Library_Core_Types_String, Boolean)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("True", String::Boolean(true)) ;
        EXPECT_EQ("False", String::Boolean(false)) ;

    }

}

TEST (Library_Core_Types_String, Char)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("a", String::Char('a')) ;
        EXPECT_EQ("0", String::Char('0')) ;

    }

}

TEST (Library_Core_Types_String, Replicate)
{

    using library::core::types::String ;

    {

        EXPECT_EQ("aaa", String::Replicate('a', 3)) ;
        EXPECT_EQ("", String::Replicate('a', 0)) ;

    }

    {

        EXPECT_EQ("- - - ", String::Replicate("- ", 3)) ;
        EXPECT_EQ("", String::Replicate("- ", 0)) ;
        EXPECT_EQ("", String::Replicate("", 3)) ;

    }

}

TEST (Library_Core_Types_String, Format)
{

    using library::core::types::Integer ;
    using library::core::types::Real ;
    using library::core::types::String ;

    {

        EXPECT_EQ("", String::Format("")) ;
        EXPECT_EQ("123", String::Format("{0}", 123)) ;
        EXPECT_EQ("123.456", String::Format("{0}", 123.456)) ;
        EXPECT_EQ("123", String::Format("{0}", Integer(123))) ;
        EXPECT_EQ("123.456", String::Format("{0}", Real(123.456))) ;
        EXPECT_EQ("123 - 456 - 789 - 123", String::Format("{0} - {1} - {2} - {0}", 123, 456, 789)) ;
        EXPECT_EQ("123 - 456.789", String::Format("{0} - {1}", 123, 456.789)) ;
        EXPECT_EQ("Hello, World!", String::Format("{0}, {1}!", "Hello", "World")) ;
        EXPECT_EQ("123 - 456.789 - Hello, World!", String::Format("{0} - {1} - {2}, {3}!", 123, 456.789, "Hello", "World")) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
