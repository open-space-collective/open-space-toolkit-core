////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           Library/Core/Logger.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Logger__
#define __Library_Core_Logger__

#include <Library/Core/Types/Integer.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Logger/Severity.hpp>
#include <Library/Core/Logger/Source.hpp>
#include <Library/Core/Logger/Sink.hpp>
#include <Library/Core/Logger/Pump.hpp>

#include <boost/log/attributes.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::Integer ;
using library::core::types::String ;
using library::core::ctnr::Array ;
using library::core::logger::Severity ;
using library::core::logger::Source ;
using library::core::logger::Sink ;
using library::core::logger::Pump ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Log management

class Logger
{

    public:

                                Logger                                      (   const   String&                     aChannel                            ) ;

        Pump                    operator ()                                 (   const   Severity&                   aSeverity,
                                                                                const   Integer&                    aLine,
                                                                                const   String&                     aFile,
                                                                                const   String&                     aFunction                           ) ;

        template <class T>
        Pump                    operator <<                                    (    const    T&                            anObject                            )
        {

            Pump pump(Severity::Info, Integer::Undefined(), String::Empty(), String::Empty(), &source_) ;

            pump << anObject ;

            return std::move(pump) ;

        }

        String                  getChannel                                  ( ) const ;

        static Logger           Console                                     (   const   Severity&                   aSeverity                           ) ;

        static Logger           Console                                     (   const   String&                     aChannel,
                                                                                const   Severity&                   aSeverity                           ) ;

        static Logger&          Global                                      ( ) ;

    private:

        String                  channel_ ;
        Source                  source_ ;
        Array<Sink>             sinks_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#define                         LOG(aLogger, aSeverity)                         aLogger(aSeverity, __LINE__, __FILE__, __PRETTY_FUNCTION__)

#define                         LOG_TRACE(aLogger)                              LOG(aLogger, library::core::logger::Severity::Trace)
#define                         LOG_DEBUG(aLogger)                              LOG(aLogger, library::core::logger::Severity::Debug)
#define                         LOG_INFO(aLogger)                               LOG(aLogger, library::core::logger::Severity::Info)
#define                         LOG_WARNING(aLogger)                            LOG(aLogger, library::core::logger::Severity::Warning)
#define                         LOG_ERROR(aLogger)                              LOG(aLogger, library::core::logger::Severity::Error)
#define                         LOG_FATAL(aLogger)                              LOG(aLogger, library::core::logger::Severity::Fatal)

#define                         GLOBAL_LOG_TRACE                                LOG_TRACE(library::core::Logger::Global())
#define                         GLOBAL_LOG_DEBUG                                LOG_DEBUG(library::core::Logger::Global())
#define                         GLOBAL_LOG_INFO                                 LOG_INFO(library::core::Logger::Global())
#define                         GLOBAL_LOG_WARNING                              LOG_WARNING(library::core::Logger::Global())
#define                         GLOBAL_LOG_ERROR                                LOG_ERROR(library::core::Logger::Global())
#define                         GLOBAL_LOG_FATAL                                LOG_FATAL(library::core::Logger::Global())

#define                         GET_MACRO(_0, _1, _2, NAME, ...)                NAME

#define                         LOG_SCOPE0()                                    BOOST_LOG_NAMED_SCOPE("?")
#define                         LOG_SCOPE1(aScope)                              BOOST_LOG_NAMED_SCOPE(aScope)
#define                         LOG_SCOPE2(aClass, aMethod)                     BOOST_LOG_NAMED_SCOPE(aClass " ▸ " aMethod)

#define                         LOG_SCOPE(...)                                  GET_MACRO(_0, ##__VA_ARGS__, LOG_SCOPE2, LOG_SCOPE1, LOG_SCOPE0)(__VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
