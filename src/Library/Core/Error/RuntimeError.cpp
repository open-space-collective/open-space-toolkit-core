////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Error/RuntimeError.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace error
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                RuntimeError::RuntimeError                  (   const   String&                     aMessage                            )
                                :   Exception(String::Empty()),
                                    message_(aMessage)
{

}

//                                 RuntimeError::RuntimeError                  (   const   String&                     aScope,
//                                                                                 const   String&                     aMessage                            )
//                                 :   Exception(aScope),
//                                     message_(aMessage)
// {

// }

                                RuntimeError::~RuntimeError                 ( )
{

}

const char*                     RuntimeError::what                          ( ) const noexcept
{
    return message_.data() ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
