////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/System/Group.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_System_Group__
#define __Library_Core_System_Group__

#include <Library/Core/Types/String.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace system
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Group
///
///                             POSIX compliant
///
/// @ref                        https://en.wikipedia.org/wiki/Group_identifier

class Group
{

    public:

                                Group                                       (   const   uint&                       aGID,
                                                                                const   String&                     aName                                       ) ;

                                Group                                       (   const   uint&                       aGID,
                                                                                const   uint&                       aEGID,
                                                                                const   String&                     aName                                       ) ;

        bool                    operator ==                                 (   const   Group&                      aGroup                                      ) const ;

        bool                    operator !=                                 (   const   Group&                      aGroup                                      ) const ;

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Group&                      aGroup                                      ) ;

        bool                    isDefined                                   ( ) const ;

        int                     getGID                                      ( ) const ;

        int                     getEGID                                     ( ) const ;

        int                     getSGID                                     ( ) const ;

        String                  getName                                     ( ) const ;

        static Group            Undefined                                   ( ) ;

        static Group            Process                                     ( ) ;

        static Group            GID                                         (   const   uint&                       aGID                                        ) ;

        static Group            Name                                        (   const   String&                     aName                                       ) ;

    private:

        int gid_ ;
        int egid_ ;
        String name_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////