////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/FileSystem/PermissionSet.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, Constructor)
{

    using ostk::core::fs::PermissionSet ;

    {

        const bool canRead = false ;
        const bool canWrite = false ;
        const bool canExecute = false ;

        EXPECT_NO_THROW(PermissionSet(canRead, canWrite, canExecute)) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, EqualToOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_TRUE(PermissionSet(false, false, false) == PermissionSet(false, false, false)) ;
        EXPECT_TRUE(PermissionSet(true, false, false) == PermissionSet(true, false, false)) ;
        EXPECT_TRUE(PermissionSet(false, true, false) == PermissionSet(false, true, false)) ;
        EXPECT_TRUE(PermissionSet(false, false, true) == PermissionSet(false, false, true)) ;
        EXPECT_TRUE(PermissionSet(true, true, false) == PermissionSet(true, true, false)) ;
        EXPECT_TRUE(PermissionSet(true, false, true) == PermissionSet(true, false, true)) ;
        EXPECT_TRUE(PermissionSet(false, false, true) == PermissionSet(false, false, true)) ;
        EXPECT_TRUE(PermissionSet(false, true, true) == PermissionSet(false, true, true)) ;
        EXPECT_TRUE(PermissionSet(true, true, true) == PermissionSet(true, true, true)) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, NotEqualToOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_FALSE(PermissionSet(false, false, false) != PermissionSet(false, false, false)) ;
        EXPECT_FALSE(PermissionSet(true, false, false) != PermissionSet(true, false, false)) ;
        EXPECT_FALSE(PermissionSet(false, true, false) != PermissionSet(false, true, false)) ;
        EXPECT_FALSE(PermissionSet(false, false, true) != PermissionSet(false, false, true)) ;
        EXPECT_FALSE(PermissionSet(true, true, false) != PermissionSet(true, true, false)) ;
        EXPECT_FALSE(PermissionSet(true, false, true) != PermissionSet(true, false, true)) ;
        EXPECT_FALSE(PermissionSet(false, false, true) != PermissionSet(false, false, true)) ;
        EXPECT_FALSE(PermissionSet(false, true, true) != PermissionSet(false, true, true)) ;
        EXPECT_FALSE(PermissionSet(true, true, true) != PermissionSet(true, true, true)) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, AdditionOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_EQ(PermissionSet::RWX(), PermissionSet::RW() + PermissionSet::X()) ;
        EXPECT_EQ(PermissionSet::RWX(), PermissionSet::RW() + PermissionSet::RWX()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, SubtractionOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_EQ(PermissionSet::RW(), PermissionSet::RWX() - PermissionSet::X()) ;
        EXPECT_EQ(PermissionSet::None(), PermissionSet::RW() - PermissionSet::RWX()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, LogicalAndOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_EQ(PermissionSet::R(), PermissionSet::RW() && PermissionSet::RX()) ;
        EXPECT_EQ(PermissionSet::RX(), PermissionSet::RWX() && PermissionSet::RX()) ;
        EXPECT_EQ(PermissionSet::RWX(), PermissionSet::RWX() && PermissionSet::RWX()) ;
        EXPECT_EQ(PermissionSet::None(), PermissionSet::RWX() && PermissionSet::None()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, LogicalOOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_EQ(PermissionSet::RWX(), PermissionSet::RW() || PermissionSet::RX()) ;
        EXPECT_EQ(PermissionSet::RWX(), PermissionSet::RWX() || PermissionSet::RWX()) ;
        EXPECT_EQ(PermissionSet::RW(), PermissionSet::RW() || PermissionSet::None()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, StreamOperator)
{

    using ostk::core::fs::PermissionSet ;

    {

        const PermissionSet permissionSet = { true, true, true } ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << permissionSet << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, IsNone)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_TRUE(PermissionSet(false, false, false).isNone()) ;
        EXPECT_FALSE(PermissionSet(true, false, false).isNone()) ;
        EXPECT_FALSE(PermissionSet(false, true, false).isNone()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).isNone()) ;
        EXPECT_FALSE(PermissionSet(true, true, false).isNone()) ;
        EXPECT_FALSE(PermissionSet(true, false, true).isNone()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).isNone()) ;
        EXPECT_FALSE(PermissionSet(false, true, true).isNone()) ;
        EXPECT_FALSE(PermissionSet(true, true, true).isNone()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, IsAll)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_FALSE(PermissionSet(false, false, false).isAll()) ;
        EXPECT_FALSE(PermissionSet(true, false, false).isAll()) ;
        EXPECT_FALSE(PermissionSet(false, true, false).isAll()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).isAll()) ;
        EXPECT_FALSE(PermissionSet(true, true, false).isAll()) ;
        EXPECT_FALSE(PermissionSet(true, false, true).isAll()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).isAll()) ;
        EXPECT_FALSE(PermissionSet(false, true, true).isAll()) ;
        EXPECT_TRUE(PermissionSet(true, true, true).isAll()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, CanRead)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_FALSE(PermissionSet(false, false, false).canRead()) ;
        EXPECT_TRUE(PermissionSet(true, false, false).canRead()) ;
        EXPECT_FALSE(PermissionSet(false, true, false).canRead()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).canRead()) ;
        EXPECT_TRUE(PermissionSet(true, true, false).canRead()) ;
        EXPECT_TRUE(PermissionSet(true, false, true).canRead()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).canRead()) ;
        EXPECT_FALSE(PermissionSet(false, true, true).canRead()) ;
        EXPECT_TRUE(PermissionSet(true, true, true).canRead()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, CanWrite)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_FALSE(PermissionSet(false, false, false).canWrite()) ;
        EXPECT_FALSE(PermissionSet(true, false, false).canWrite()) ;
        EXPECT_TRUE(PermissionSet(false, true, false).canWrite()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).canWrite()) ;
        EXPECT_TRUE(PermissionSet(true, true, false).canWrite()) ;
        EXPECT_FALSE(PermissionSet(true, false, true).canWrite()) ;
        EXPECT_FALSE(PermissionSet(false, false, true).canWrite()) ;
        EXPECT_TRUE(PermissionSet(false, true, true).canWrite()) ;
        EXPECT_TRUE(PermissionSet(true, true, true).canWrite()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, CanExecute)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_FALSE(PermissionSet(false, false, false).canExecute()) ;
        EXPECT_FALSE(PermissionSet(true, false, false).canExecute()) ;
        EXPECT_FALSE(PermissionSet(false, true, false).canExecute()) ;
        EXPECT_TRUE(PermissionSet(false, false, true).canExecute()) ;
        EXPECT_FALSE(PermissionSet(true, true, false).canExecute()) ;
        EXPECT_TRUE(PermissionSet(true, false, true).canExecute()) ;
        EXPECT_TRUE(PermissionSet(false, false, true).canExecute()) ;
        EXPECT_TRUE(PermissionSet(false, true, true).canExecute()) ;
        EXPECT_TRUE(PermissionSet(true, true, true).canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, None)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::None()) ;

        const PermissionSet permissionSet = PermissionSet::None() ;

        EXPECT_FALSE(permissionSet.canRead()) ;
        EXPECT_FALSE(permissionSet.canWrite()) ;
        EXPECT_FALSE(permissionSet.canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, R)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::R()) ;

        const PermissionSet permissionSet = PermissionSet::R() ;

        EXPECT_TRUE(permissionSet.canRead()) ;
        EXPECT_FALSE(permissionSet.canWrite()) ;
        EXPECT_FALSE(permissionSet.canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, W)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::W()) ;

        const PermissionSet permissionSet = PermissionSet::W() ;

        EXPECT_FALSE(permissionSet.canRead()) ;
        EXPECT_TRUE(permissionSet.canWrite()) ;
        EXPECT_FALSE(permissionSet.canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, X)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::X()) ;

        const PermissionSet permissionSet = PermissionSet::X() ;

        EXPECT_FALSE(permissionSet.canRead()) ;
        EXPECT_FALSE(permissionSet.canWrite()) ;
        EXPECT_TRUE(permissionSet.canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, RW)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::RW()) ;

        const PermissionSet permissionSet = PermissionSet::RW() ;

        EXPECT_TRUE(permissionSet.canRead()) ;
        EXPECT_TRUE(permissionSet.canWrite()) ;
        EXPECT_FALSE(permissionSet.canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, RX)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::RX()) ;

        const PermissionSet permissionSet = PermissionSet::RX() ;

        EXPECT_TRUE(permissionSet.canRead()) ;
        EXPECT_FALSE(permissionSet.canWrite()) ;
        EXPECT_TRUE(permissionSet.canExecute()) ;

    }

}

TEST (OpenSpaceToolkit_Core_FileSystem_PermissionSet, RWX)
{

    using ostk::core::fs::PermissionSet ;

    {

        EXPECT_NO_THROW(PermissionSet::RWX()) ;

        const PermissionSet permissionSet = PermissionSet::RWX() ;

        EXPECT_TRUE(permissionSet.canRead()) ;
        EXPECT_TRUE(permissionSet.canWrite()) ;
        EXPECT_TRUE(permissionSet.canExecute()) ;

    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
