////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/PermissionSet.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_FileSystem_PermissionSet__
#define __Library_Core_FileSystem_PermissionSet__

#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Permissions control the ability of the users to view, change, navigate, and execute the contents of the file system.
///
///                             This class is modeled after the Traditional Unix permissions.
///
/// @ref                        https://en.wikipedia.org/wiki/File_system_permissions

class PermissionSet
{

    public:

        /// @brief              Default constructor (disabled)
    
                                PermissionSet                               ( ) = delete ;

        /// @brief              Full constructor
        ///
        /// @param              [in] canRead Can read if set to true
        /// @param              [in] canWrite Can write if set to true
        /// @param              [in] canExecute Can execute if set to true

                                PermissionSet                               (   const   bool&                       canRead,
                                                                                const   bool&                       canWrite,
                                                                                const   bool&                       canExecute                                  ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     PermissionSet::RWX() == PermissionSet::RWX() ; // True
        /// @endcode
        ///
        /// @param              [in] aPermissionSet A permission set
        /// @return             True if permissions are equal

        bool                    operator ==                                 (   const   PermissionSet&              aPermissionSet                              ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     PermissionSet::RW() != PermissionSet::RWX() ; // True
        /// @endcode
        ///
        /// @param              [in] aPermissionSet A permission set
        /// @return             True if permissions are not equal

        bool                    operator !=                                 (   const   PermissionSet&              aPermissionSet                              ) const ;

        /// @brief              Addition operator
        ///
        ///                     Add permissions
        ///
        /// @code
        ///                     PermissionSet rw = PermissionSet::RW() ;
        ///                     PermissionSet x = PermissionSet::X() ;
        ///                     PermissionSet rwx = rw + x ;
        /// @endcode
        ///
        /// @param              [in] aPermissionSet A permission set
        /// @return             Permission set

        PermissionSet           operator +                                  (   const   PermissionSet&              aPermissionSet                              ) const ;

        /// @brief              Subtraction operator
        ///
        ///                     Remove permissions
        ///
        /// @code
        ///                     PermissionSet rwx = PermissionSet::RWX() ;
        ///                     PermissionSet x = PermissionSet::X() ;
        ///                     PermissionSet rw = rwx - x ;
        /// @endcode
        ///
        /// @param              [in] aPermissionSet A permission set
        /// @return             Permission set

        PermissionSet           operator -                                  (   const   PermissionSet&              aPermissionSet                              ) const ;

        /// @brief              Logical AND operator
        ///
        ///                     AND permissions
        ///
        /// @code
        ///                     PermissionSet rw = PermissionSet::RW() ;
        ///                     PermissionSet rx = PermissionSet::RX() ;
        ///                     PermissionSet r = rw && rx ;
        /// @endcode
        ///
        /// @param              [in] aPermissionSet A permission set
        /// @return             Permission set

        PermissionSet           operator &&                                 (   const   PermissionSet&              aPermissionSet                              ) const ;

        /// @brief              Logical OR operator
        ///
        ///                     OR permissions
        ///
        /// @code
        ///                     PermissionSet rw = PermissionSet::RW() ;
        ///                     PermissionSet rx = PermissionSet::RX() ;
        ///                     PermissionSet rwx = rw || rx ;
        /// @endcode
        ///
        /// @param              [in] aPermissionSet A permission set
        /// @return             Permission set

        PermissionSet           operator ||                                 (   const   PermissionSet&              aPermissionSet                              ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::RWX()
        ///                     std::cout << permissions ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPermissionSet A permission set
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   PermissionSet&              aPermissionSet                              ) ;

        /// @brief              Check if permission set is none
        ///
        /// @code
        ///                     PermissionSet::None().isNone() ; // True
        /// @endcode
        ///
        /// @return             True if permission set is none

        bool                    isNone                                      ( ) const ;

        /// @brief              Check if permission set is all
        ///
        /// @code
        ///                     PermissionSet::RWX().isAll() ; // True
        /// @endcode
        ///
        /// @return             True if permission set is all

        bool                    isAll                                       ( ) const ;

        /// @brief              Check if permission set can read
        ///
        /// @code
        ///                     PermissionSet::R().canRead() ; // True
        ///                     PermissionSet::RW().canRead() ; // True
        ///                     PermissionSet::RWX().canRead() ; // True
        /// @endcode
        ///
        /// @return             True if permission set can read

        bool                    canRead                                     ( ) const ;

        /// @brief              Check if permission set can write
        ///
        /// @code
        ///                     PermissionSet::R().canWrite() ; // False
        ///                     PermissionSet::RW().canWrite() ; // True
        ///                     PermissionSet::RWX().canWrite() ; // True
        /// @endcode
        ///
        /// @return             True if permission set can write

        bool                    canWrite                                    ( ) const ;

        /// @brief              Check if permission set can execute
        ///
        /// @code
        ///                     PermissionSet::R().canExecute() ; // False
        ///                     PermissionSet::RW().canExecute() ; // False
        ///                     PermissionSet::RWX().canExecute() ; // True
        /// @endcode
        ///
        /// @return             True if permission set can execute

        bool                    canExecute                                  ( ) const ;

        /// @brief              Constructs a none permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::None() ; // ---
        /// @endcode
        ///
        /// @return             None permissions

        static PermissionSet    None                                        ( ) ;

        /// @brief              Constructs a read permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::R() ; // r--
        /// @endcode
        ///
        /// @return             Read permissions

        static PermissionSet    R                                           ( ) ;

        /// @brief              Constructs a write permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::W() ; // -w-
        /// @endcode
        ///
        /// @return             Write permissions

        static PermissionSet    W                                           ( ) ;

        /// @brief              Constructs an execute permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::X() ; // --x
        /// @endcode
        ///
        /// @return             Execute permissions

        static PermissionSet    X                                           ( ) ;

        /// @brief              Constructs a read-write permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::RW() ; // rw-
        /// @endcode
        ///
        /// @return             Read-Write permissions
        
        static PermissionSet    RW                                          ( ) ;

        /// @brief              Constructs a read-execute permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::RX() ; // r-x
        /// @endcode
        ///
        /// @return             Read-Execute permissions

        static PermissionSet    RX                                          ( ) ;

        /// @brief              Constructs a read-write-execute permission set
        ///
        /// @code
        ///                     PermissionSet permissions = PermissionSet::RWX() ; // rwx
        /// @endcode
        ///
        /// @return             Read-Write-Execute permissions

        static PermissionSet    RWX                                         ( ) ;

    private:

        uint8_t permissions_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////