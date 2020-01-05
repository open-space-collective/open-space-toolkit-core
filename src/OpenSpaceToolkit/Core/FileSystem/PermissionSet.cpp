////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/FileSystem/PermissionSet.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                PermissionSet::PermissionSet                (   const   bool                        canRead,
                                                                                const   bool                        canWrite,
                                                                                const   bool                        canExecute                                  )
                                :   read_(canRead),
                                    write_(canWrite),
                                    execute_(canExecute)
{

}

bool                            PermissionSet::operator ==                  (   const   PermissionSet&              aPermissionSet                              ) const
{
    return (read_ == aPermissionSet.read_) && (write_ == aPermissionSet.write_) && (execute_ == aPermissionSet.execute_) ;
}

bool                            PermissionSet::operator !=                  (   const   PermissionSet&              aPermissionSet                              ) const
{
    return (read_ != aPermissionSet.read_) || (write_ != aPermissionSet.write_) || (execute_ != aPermissionSet.execute_) ;
}

PermissionSet                   PermissionSet::operator +                   (   const   PermissionSet&              aPermissionSet                              ) const
{
    return { read_ || aPermissionSet.read_, write_ || aPermissionSet.write_, execute_ || aPermissionSet.execute_ } ;
}

PermissionSet                   PermissionSet::operator -                   (   const   PermissionSet&              aPermissionSet                              ) const
{

    PermissionSet permissionSet = { *this } ;

    if (aPermissionSet.read_)
    {
        permissionSet.read_ = false ;
    }

    if (aPermissionSet.write_)
    {
        permissionSet.write_ = false ;
    }

    if (aPermissionSet.execute_)
    {
        permissionSet.execute_ = false ;
    }

    return permissionSet ;

}

PermissionSet                   PermissionSet::operator &&                  (   const   PermissionSet&              aPermissionSet                              ) const
{
    return { read_ && aPermissionSet.read_, write_ && aPermissionSet.write_, execute_ && aPermissionSet.execute_ } ;
}

PermissionSet                   PermissionSet::operator ||                  (   const   PermissionSet&              aPermissionSet                              ) const
{
    return { read_ || aPermissionSet.read_, write_ || aPermissionSet.write_, execute_ || aPermissionSet.execute_ } ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   PermissionSet&              aPermissionSet                              )
{

    ostk::core::utils::Print::Header(anOutputStream, "Permission Set") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Read:"                << aPermissionSet.read_ ;
    ostk::core::utils::Print::Line(anOutputStream) << "Write:"               << aPermissionSet.write_ ;
    ostk::core::utils::Print::Line(anOutputStream) << "Execute:"             << aPermissionSet.execute_ ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            PermissionSet::isNone                       ( ) const
{
    return (!read_) && (!write_) && (!execute_) ;
}

bool                            PermissionSet::isAll                        ( ) const
{
    return read_ && write_ && execute_ ;
}

bool                            PermissionSet::canRead                      ( ) const
{
    return read_ ;
}

bool                            PermissionSet::canWrite                     ( ) const
{
    return write_ ;
}

bool                            PermissionSet::canExecute                   ( ) const
{
    return execute_ ;
}

PermissionSet                   PermissionSet::None                         ( )
{
    return { false, false, false } ;
}

PermissionSet                   PermissionSet::R                            ( )
{
    return { true, false, false } ;
}

PermissionSet                   PermissionSet::W                            ( )
{
    return { false, true, false } ;
}

PermissionSet                   PermissionSet::X                            ( )
{
    return { false, false, true } ;
}

PermissionSet                   PermissionSet::RW                           ( )
{
    return { true, true, false } ;
}

PermissionSet                   PermissionSet::RX                           ( )
{
    return { true, false, true } ;
}

PermissionSet                   PermissionSet::RWX                          ( )
{
    return { true, true, true } ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
