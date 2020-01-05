////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Utilities/Print.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Utilities_Print__
#define __Library_Core_Utilities_Print__

#include <Library/Core/Types/String.hpp>

#include <iomanip>
#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace utils
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Print
{

    public:

        class LineBuffer
        {

            public:

                                LineBuffer                                  (           std::ostream&               anOutputStream,
                                                                                        uint                        anIndentation                               ) ;

                                LineBuffer                                  (   const   LineBuffer&                 aLineBuffer                                 ) = delete ;

                                LineBuffer                                  (           LineBuffer&&                aLineBuffer                                 ) = default ;

                                ~LineBuffer                                 ( ) ;

                template <class T>
                LineBuffer&     operator <<                                 (   const   T&                          anObject                                    )
                {

                    stream_ << std::setw(40) << std::setfill(' ') << anObject << " " ;

                    return *this ;

                }

            private:

                std::ostream&   stream_ ;
                uint            indentation_ ;

        } ;

                                Print                                       ( ) = delete ;

        static void             Header                                      (           std::ostream&               anOutputStream,
                                                                                const   types::String&              aName                                       ) ;

        static Print::LineBuffer Line                                       (           std::ostream&               anOutputStream,
                                                                                        uint                        anIndentation                               =   1 ) ;

        static void             Separator                                   (           std::ostream&               anOutputStream,
                                                                                const   types::String&              aName                                       =   "") ;

        static void             Footer                                      (           std::ostream&               anOutputStream                              ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
