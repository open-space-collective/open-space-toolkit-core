////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Utilities/Print.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Utilities/Print.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
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
    stream_ << std::left << types::String(indentation_, ' ') << types::String(indentation_, ' ') << types::String(indentation_, ' ') << types::String(indentation_, ' ') ;
    // stream_ << std::left << types::String(indentation_, '\t') ;
}

                                Print::LineBuffer::~LineBuffer              ( )
{
    stream_ << std::endl ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void                            Print::Header                               (           std::ostream&               anOutputStream,
                                                                                const   types::String&              aName                                       )
{
    anOutputStream << "-- " << aName << " " << types::String((aName.getLength() < 60) ? (60 - aName.getLength() - 1) : 0, '-') << std::endl ;
}

Print::LineBuffer               Print::Line                                 (           std::ostream&               anOutputStream,
                                                                                        uint                        anIndentation                               )
{
    return Print::LineBuffer(anOutputStream, anIndentation) ;
}

void                            Print::Separator                            (           std::ostream&               anOutputStream                              )
{
    anOutputStream << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << std::endl ;
}

void                            Print::Footer                               (           std::ostream&               anOutputStream                              )
{
    anOutputStream << "---------------------------------------------------------------" << std::endl ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////