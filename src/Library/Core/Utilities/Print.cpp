////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Utilities/Print.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Utilities/Print.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define LENGTH 100

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace utils
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Print::LineBuffer::LineBuffer               (           std::ostream&               anOutputStream,
                                                                                        uint                        anIndentation                               )
                                :   stream_(anOutputStream),
                                    indentation_(anIndentation)
{
    stream_ << std::left << types::String::Replicate("    ", indentation_) ;
}

                                Print::LineBuffer::~LineBuffer              ( )
{
    stream_ << std::endl ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void                            Print::Header                               (           std::ostream&               anOutputStream,
                                                                                const   types::String&              aName                                       )
{
    anOutputStream << "-- " << aName << " " << types::String::Replicate('-', (aName.getLength() < (LENGTH - 3)) ? ((LENGTH - 3) - aName.getLength() - 1) : 0) << std::endl ;
}

Print::LineBuffer               Print::Line                                 (           std::ostream&               anOutputStream,
                                                                                        uint                        anIndentation                               )
{
    return Print::LineBuffer(anOutputStream, anIndentation) ;
}

void                            Print::Separator                            (           std::ostream&               anOutputStream,
                                                                                const   types::String&              aName                                       )
{

    if (aName.isEmpty())
    {
        anOutputStream << types::String::Replicate("- ", LENGTH / 2) << std::endl ;
    }
    else
    {
        anOutputStream << "    " << aName << " " << types::String::Replicate("- ", (aName.getLength() < (LENGTH - 4)) ? ((LENGTH - 4) - aName.getLength() - 1) / 2 : 0) << std::endl ;
    }

}

void                            Print::Footer                               (           std::ostream&               anOutputStream                              )
{
    anOutputStream << types::String::Replicate('-', LENGTH) << std::endl ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
