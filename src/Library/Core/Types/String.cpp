////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           Library/Core/Types/String.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Error.hpp>

#include <boost/algorithm/string.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace types
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Integer ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                String::String                              ( )
                                :   std::string()
{

}

                                String::String                              (   const   std::string&                aString                                     )
                                :   std::string(aString)
{

}

                                String::~String                             ( )
{

}

bool                            String::isEmpty                             ( ) const
{
    return this->empty() ;
}

bool                            String::isUppercase                         ( ) const

{
    return (!this->empty()) && !std::any_of(this->begin(), this->end(), [] (char ch) { return ::islower(ch) ; }) ;
}

bool                            String::isLowercase                         ( ) const

{
    return (!this->empty()) && !std::any_of(this->begin(), this->end(), [] (char ch) { return ::isupper(ch) ; }) ;
}

bool                            String::match                               (   const   std::regex&                 aRegularExpression                          ) const
{
    return std::regex_match((*this), aRegularExpression) ;
}

Size                            String::getLength                           ( ) const
{
    return this->length() ;
}

String                          String::getHead                             (   const   Size&                       aLength                                     ) const
{

    if (aLength > this->length())
    {
        throw library::core::error::RuntimeError("Head length [{}] greater than string length [{}].", aLength, this->length()) ;
    }

    return this->substr(0, aLength) ;

}

String                          String::getTail                             (   const   Size&                       aLength                                     ) const
{

    if (aLength > this->length())
    {
        throw library::core::error::RuntimeError("Tail length [{}] greater than string length [{}].", aLength, this->length()) ;
    }

    return this->substr(this->length() - aLength , aLength) ;

}

char                            String::getFirst                            ( ) const
{

    if (this->empty())
    {
        throw library::core::error::RuntimeError("String is empty.") ;
    }

    return (*this)[0] ;

}

char                            String::getLast                             ( ) const
{

    if (this->empty())
    {
        throw library::core::error::RuntimeError("String is empty.") ;
    }

    return (*this)[this->length() - 1] ;

}

String                          String::getSubstring                        (   const   Index&                      aStartPosition,
                                                                                const   Size&                       aLength                                     ) const
{

    if (aLength == 0)
    {
        throw library::core::error::runtime::Wrong("Length") ;
    }

    if (this->empty())
    {
        throw library::core::error::RuntimeError("String is empty.") ;
    }

    if (aStartPosition >= this->length())
    {
        throw library::core::error::RuntimeError("Start position [" + Integer::Index(aStartPosition).toString() + "] out of bounds [" + Integer::Size(this->length() - 1).toString() + "].") ;
    }

    if ((aStartPosition + aLength) > this->length())
    {
        throw library::core::error::RuntimeError("End position [" + Integer::Index(aStartPosition + aLength - 1).toString() + "] out of bounds [" + Integer::Size(this->length() - 1).toString() + "].") ;
    }

    return this->substr(aStartPosition, aLength) ;

}

String&                         String::trim                                ( )
{

    if (!this->empty())
    {
        boost::trim(*this) ;
    }

    return *this ;

}

String&                         String::replace                             (   const   char                        aCharacter,
                                                                                const   char                        aNewCharacter                               )
{

    std::replace(this->begin(), this->end(), aCharacter, aNewCharacter) ;

    return *this ;

}

String&                         String::replace                             (   const   String&                     aString,
                                                                                const   String&                     aNewString                                  )
{

    boost::replace_all(*this, aString, aNewString) ;

    return *this ;

}

String                          String::Empty                               ( )

{
    return String("") ;
}

String                          String::Boolean                             (           bool                        aBoolean                                    )
{
    return aBoolean ? "True" : "False" ;
}

String                          String::Char                                (           char                        aCharacter                                  )
{
    return String(1, aCharacter) ;
}

String                          String::Replicate                           (           char                        aCharacter,
                                                                                        Size                        aCount                                      )
{
    return String(aCount, aCharacter) ;
}

String                          String::Replicate                           (   const   String&                     aString,
                                                                                        Size                        aCount                                      )
{

    std::ostringstream stringStream ;

    for (Index idx = 0; idx < aCount; ++idx)
    {
        stringStream << aString ;
    }

    return stringStream.str() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
