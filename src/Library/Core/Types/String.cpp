////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Types/String.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Types/String.hpp>
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

String                          String::Empty                               ( )

{
    return String("") ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////