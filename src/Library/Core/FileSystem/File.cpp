////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/File.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/Error.hpp>
#include <Library/Core/Utilities.hpp>

#include <boost/filesystem.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                File::File                                  (   const   File&                       aFile                                       )
                                :   path_(aFile.path_)
{
    
}

File&                           File::operator =                            (   const   File&                       aFile                                       )
{

    if (this != &aFile)
    {
        path_ = aFile.path_ ;
    }

    return *this ;

}

bool                            File::operator ==                           (   const   File&                       aFile                                       ) const
{

    if ((!this->isDefined()) || (!aFile.isDefined()))
    {
        return false ;
    }

    return path_ == aFile.path_ ;

}

bool                            File::operator !=                           (   const   File&                       aFile                                       ) const
{
    return !((*this) == aFile) ;
}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   File&                       aFile                                       )
{

    library::core::utils::Print::Header(anOutputStream, "File") ;

    library::core::utils::Print::Line(anOutputStream) << "Name:" << (aFile.isDefined() ? aFile.getName() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Extension:" << (aFile.isDefined() ? aFile.getExtension() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Path:" << (aFile.isDefined() ? aFile.path_.toString() : "Undefined") ;
    library::core::utils::Print::Line(anOutputStream) << "Exists:" << (aFile.isDefined() ? String::Boolean(aFile.exists()) : "Undefined") ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            File::isDefined                             ( ) const
{
    return path_.isDefined() ;
}

bool                            File::exists                                ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("File") ;
    }

    try
    {
        return boost::filesystem::exists(path_.toString()) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw library::core::error::RuntimeError(e.what()) ;
    }

    return false ;

}

String                          File::getName                               (           bool                        withExtension                               ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("File") ;
    }

    try
	{

		if (!withExtension)
        {
            return boost::filesystem::path(path_.toString()).stem().string() ;
        }

        return boost::filesystem::path(path_.toString()).filename().string() ;

	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		throw library::core::error::RuntimeError(e.what()) ;
	}

    return String::Empty() ;

}

String                          File::getExtension                          ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("File") ;
    }

    try
	{

		const String fullExtension = boost::filesystem::path(path_.toString()).extension().string() ;

		if (fullExtension.getLength() > 1)
		{
			return fullExtension.getTail(fullExtension.getLength() - 1) ;
		}

        return fullExtension ;

	}
	catch (const boost::filesystem::filesystem_error& e)
	{
		throw library::core::error::RuntimeError(e.what()) ;
	}

    return String::Empty() ;

}

fs::Path                        File::getPath                               ( ) const
{

    if (!this->isDefined())
    {
        throw library::core::error::runtime::Undefined("File") ;
    }
    
    return path_ ;

}

// fs::PermissionSet               File::getPermissions                        ( ) const
// {

// }

// fs::Directory                   File::getParentDirectory                    ( ) const
// {

// }

// void                            File::renameTo                              (   const   String&              aName                                       )
// {

// }

// File                            File::copyToDirectory                       (   const   fs::Directory&              aDestination,
//                                                                                 const   String&              aNewFileName                                ) const
// {

// }

// void                            File::moveToDirectory                       (   const   fs::Directory&              aDestination                                )
// {

// }

// void                            File::create                                (   const   fs::PermissionSet&          anOwnerPermissionsSet,
//                                                                                 const   fs::PermissionSet&          aGroupPermissionsSet,
//                                                                                 const   fs::PermissionSet&          anOtherPermissionsSet                       )
// {

// }

// void                            File::clear                                 ( )
// {

// }

// void                            File::remove                                ( )
// {

// }

File                            File::Undefined                             ( )
{
    return File(Path::Undefined()) ;
}

File                            File::Path                                  (   const   fs::Path&                   aPath                                       )
{

    if (!aPath.isDefined())
    {
        throw library::core::error::runtime::Undefined("Path") ;
    }

    return File(aPath) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                File::File                                  (   const   fs::Path&                   aPath                                       )
                                :   path_(aPath)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////