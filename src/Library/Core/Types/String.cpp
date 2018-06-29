////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/String.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

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

    if (aStartPosition >= this->size())
    {
        throw library::core::error::RuntimeError("Start position [" + Integer::Index(aStartPosition).toString() + "] out of bounds [" + Integer::Size(this->size() - 1).toString() + "].") ;
    }

    if ((aStartPosition + aLength) > this->size())
    {
        throw library::core::error::RuntimeError("End position [" + Integer::Index(aStartPosition + aLength - 1).toString() + "] out of bounds [" + Integer::Size(this->size() - 1).toString() + "].") ;
    }
    
    return this->substr(aStartPosition, aLength) ;

}

String&                         String::trim                                ( )
{

    if (!this->empty())
    {
        boost::trim(*this) ;
    }

    return (*this) ;
    
}

String                          String::Empty                               ( )

{
    return String("") ;
}

String                          String::Char                                (           char                        aCharacter                                  )
{
    return String(1, aCharacter) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////