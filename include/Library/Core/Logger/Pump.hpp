////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Logger/Pump.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Logger_Pump__
#define __Library_Core_Logger_Pump__

#include <Library/Core/Types/Unique.hpp>
#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Logger/Severity.hpp>
#include <Library/Core/Logger/Source.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace logger
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Integer ;
using library::core::types::String ;
using library::core::logger::Severity ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Log pump

class Pump
{

    public:

        using StreamManipulator = std::ostream&(std::ostream&) ;

                                Pump                                        (   const   Severity&                   aSeverity,
                                                                                const   Integer&                    aLine,
                                                                                const   String&                     aFile,
                                                                                const   String&                     aFunction,
                                                                                        Source*                     aSource                                     ) ;

                                Pump                                        (   const   Pump&                       aPump                                       ) = delete ;

                                Pump                                        (           Pump&&                      aPump                                       ) ;

                                ~Pump                                       ( ) ;

        Pump&                   operator =                                  (   const   Pump&                       aPump                                       ) = delete ;

        template <class T>
        Pump&                   operator <<                                 (   const   T&                          anObject                                    )
        {

            if (this->canAccessStream())
            {
                this->accessStream() << anObject ;
            }

            return *this ;

        }

        Pump&                   operator <<                                 (           StreamManipulator           aStreamManipulator                          )
        {

            if (this->canAccessStream())
            {
                this->accessStream() << aStreamManipulator ;
            }

            return *this ;

        }

    private:

        class Impl ;

        Unique<Pump::Impl>      implPtr_ ;

        bool                    canAccessStream                             ( ) const ;

        std::ostream&           accessStream                                ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
