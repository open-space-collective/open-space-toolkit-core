////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Logger/Sinks/Sink.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __OpenSpaceToolkit_Core_Logger_Sinks_Sink__
#define __OpenSpaceToolkit_Core_Logger_Sinks_Sink__

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Logger/Severity.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace logger
{
namespace sinks
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::types::String ;
using ostk::core::ctnr::Array ;
using ostk::core::logger::Severity ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Log sink base

class Sink
{

    public:

                                Sink                                        (   const   Severity&                   aSeverity                                   ) ;

        virtual                 ~Sink                                       ( ) = 0 ;

        virtual Sink*           clone                                       ( ) const = 0 ;

        bool                    isEnabled                                   ( ) const ;

        bool                    isLineIdLogged                              ( ) const ;
        bool                    isSeverityLogged                            ( ) const ;
        bool                    isTimestampLogged                           ( ) const ;
        bool                    isThreadLogged                              ( ) const ;
        bool                    isScopeLogged                               ( ) const ;
        bool                    isFileLogged                                ( ) const ;
        bool                    isLineLogged                                ( ) const ;
        bool                    isFunctionLogged                            ( ) const ;
        bool                    isChannelLogged                             ( ) const ;

        virtual void            enable                                      ( ) = 0 ;
        virtual void            disable                                     ( ) = 0 ;

        void                    addChannel                                  (   const   String&                     aChannel                                    ) ;
        void                    removeChannel                               (   const   String&                     aChannel                                    ) ;

    protected:

        // String                  name_ ;

        bool                    enabled_ ;

        Severity                severity_ ;

        bool                    lineIdEnabled_ ;
        bool                    severityEnabled_ ;
        bool                    timestampEnabled_ ;
        bool                    threadEnabled_ ;
        bool                    scopeEnabled_ ;
        bool                    fileEnabled_ ;
        bool                    lineEnabled_ ;
        bool                    functionEnabled_ ;
        bool                    channelEnabled_ ;

        Array<String>           channels_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
