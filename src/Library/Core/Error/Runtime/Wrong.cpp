////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Error/Runtime/Wrong.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Error/Runtime/Wrong.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Wrong::Wrong                                (   const   String&                     aVariableName                               )
                                :   RuntimeError("{" + aVariableName + "} is wrong.")
{

}

//                                 Wrong::Wrong                                (   const   String&                     aScope,
//                                                                                 const   String&                     aVariableName                               )
//                                 :   RuntimeError(aScope, "{" + aVariableName + "} is wrong.")
// {

// }

                                Wrong::~Wrong                               ( )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
