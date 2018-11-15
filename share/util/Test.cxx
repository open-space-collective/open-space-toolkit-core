////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Test.cxx
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Logger.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class TestClass
{

    public:

                                TestClass                                   ( ) ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   TestClass&                  aTestClass                          ) ;

    private:

        int integer_ ;
        double double_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                TestClass::TestClass                        ( )
                                :   integer_(123),
                                    double_(456.789)
{

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   TestClass&                  aTestClass                          )
{

    anOutputStream << "Class ▸ " << aTestClass.integer_ << " " << aTestClass.double_ ;

    return anOutputStream ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int                             main                                        ( )
{

    LOG_SCOPE("Test") ;

    using library::core::types::Integer ;
    using library::core::Logger ;
    using library::core::logger::Severity ;

    Logger logger = Logger::Console(Severity::Info) ;

    logger << 1 ;
    logger << 123.456 ;
    logger << 'a' ;
    logger << "Hello World!" ;
    logger << "Hello" << " " << "World!" ;
    logger << TestClass() ;

    LOG_TRACE(logger) << TestClass() << " !!!" ;
    LOG_DEBUG(logger) << TestClass() << " !!!" ;
    LOG_INFO(logger) << TestClass() << " !!!" ;
    LOG_WARNING(logger) << TestClass() << " !!!" ;
    LOG_ERROR(logger) << TestClass() << " !!!" ;

    GLOBAL_LOG_TRACE << "Hello " << " " << "World!" ;
    GLOBAL_LOG_DEBUG << "Hello " << " " << "World!" ;
    GLOBAL_LOG_INFO << "Hello " << " " << "World!" ;
    GLOBAL_LOG_WARNING << "Hello " << " " << "World!" ;
    GLOBAL_LOG_ERROR << "Hello " << " " << "World!" ;
    GLOBAL_LOG_FATAL << "Hello " << " " << "World!" ;

    Integer a = 6 ;

    if (a < 5)
    {
        
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////