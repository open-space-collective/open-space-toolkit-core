////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/FileSystem/File.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <boost/filesystem.hpp>

#include <fstream>
#include <errno.h>
#include <unistd.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                File::File                                  (   const   File&                       aFile                                       )
                                :   path_(aFile.path_),
                                    fileStreamUPtr_(nullptr)
{

}

File&                           File::operator =                            (   const   File&                       aFile                                       )
{

    if (this != &aFile)
    {

        path_ = aFile.path_ ;

        fileStreamUPtr_.reset(nullptr) ;

    }

    return *this ;

}

                                File::~File                                 ( )
{

    if (this->isDefined() && this->exists() && this->isOpen())
    {
        this->close() ;
    }

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

    ostk::core::utils::Print::Header(anOutputStream, "File") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Name:"                << (aFile.isDefined() ? aFile.getName() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Extension:"           << (aFile.isDefined() ? aFile.getExtension() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Path:"                << (aFile.isDefined() ? aFile.path_.toString() : "Undefined") ;
    ostk::core::utils::Print::Line(anOutputStream) << "Exists:"              << (aFile.isDefined() ? String::Boolean(aFile.exists()) : "Undefined") ;

    ostk::core::utils::Print::Footer(anOutputStream) ;

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
        throw ostk::core::error::runtime::Undefined("File") ;
    }

    try
    {
        return boost::filesystem::exists(path_.toString()) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what()) ;
    }

    return false ;

}

bool                            File::isOpen                                ( ) const
{

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    return (fileStreamUPtr_ != nullptr) && fileStreamUPtr_->is_open() ;

}

String                          File::getName                               (   const   bool                        withExtension                               ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
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
        throw ostk::core::error::RuntimeError(e.what()) ;
    }

    return String::Empty() ;

}

String                          File::getExtension                          ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
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
        throw ostk::core::error::RuntimeError(e.what()) ;
    }

    return String::Empty() ;

}

fs::Path                        File::getPath                               ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
    }

    return path_ ;

}

fs::PermissionSet               File::getPermissions                        ( ) const
{

    // https://linux.die.net/man/2/access

    const auto handleErrorForPath = [] (const fs::Path& aPath) -> void
    {

        switch (errno)
        {

            case EACCES:
                throw ostk::core::error::RuntimeError("[EACCES] The requested access would be denied to the file, or search permission is denied for one of the directories in the path prefix of [{}].", aPath.toString()) ;

            case ELOOP:
                throw ostk::core::error::RuntimeError("[ELOOP] Too many symbolic links were encountered in resolving [{}].", aPath.toString()) ;

            case ENAMETOOLONG:
                throw ostk::core::error::RuntimeError("[ENAMETOOLONG] [{}] is too long.", aPath.toString()) ;

            case ENOENT:
                throw ostk::core::error::RuntimeError("[ENOENT] A component of [{}] does not exist or is a dangling symbolic link.", aPath.toString()) ;

            case ENOTDIR:
                throw ostk::core::error::RuntimeError("[ENOTDIR] A component used as a directory in [{}] is not, in fact, a directory.", aPath.toString()) ;

            case EROFS:
                throw ostk::core::error::RuntimeError("[EROFS] Write permission was requested for a file on a read-only file system [{}].", aPath.toString()) ;

            case EFAULT:
                throw ostk::core::error::RuntimeError("[EFAULT] Path [{}] points outside your accessible address space [{}].", aPath.toString()) ;

            case EINVAL:
                throw ostk::core::error::RuntimeError("[EINVAL] Mode was incorrectly specified [{}].", aPath.toString()) ;

            case EIO:
                throw ostk::core::error::RuntimeError("[EIO] An I/O error occurred [{}].", aPath.toString()) ;

            case ENOMEM:
                throw ostk::core::error::RuntimeError("[ENOMEM] Insufficient kernel memory was available [{}].", aPath.toString()) ;

            case ETXTBSY:
                throw ostk::core::error::RuntimeError("[ETXTBSY] Write access was requested to an executable which is being executed [{}].", aPath.toString()) ;

            default:
                throw ostk::core::error::RuntimeError("Unknown error for path [{}].", aPath.toString()) ;

        }

    } ;

    const auto canRead = [&handleErrorForPath] (const fs::Path& aPath) -> bool
    {

        const int result = access(aPath.toString().data(), R_OK) ;

        if ((result != 0) && (errno != EACCES))
        {
            handleErrorForPath(aPath) ;
        }

        return result == 0 ;

    } ;

    const auto canWrite = [&handleErrorForPath] (const fs::Path& aPath) -> bool
    {

        const int result = access(aPath.toString().data(), W_OK) ;

        if ((result != 0) && (errno != EACCES) && (errno != EROFS))
        {
            handleErrorForPath(aPath) ;
        }

        return result == 0 ;

    } ;

    const auto canExecute = [&handleErrorForPath] (const fs::Path& aPath) -> bool
    {

        const int result = access(aPath.toString().data(), X_OK) ;

        if ((result != 0) && (errno != EACCES))
        {
            handleErrorForPath(aPath) ;
        }

        return result == 0 ;

    } ;

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    return { canRead(path_), canWrite(path_), canExecute(path_) } ;

}

fs::Directory                   File::getParentDirectory                    ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
    }

    String filePathString = path_.getNormalizedPath().toString() ;

    // Below is a hacky solution to trim trailing slashes

    while ((filePathString.getLength() > 1) && (filePathString.getLast() == '/'))
    {
        filePathString = filePathString.getHead(filePathString.getLength() - 1) ;
    }

    if ((filePathString.getLength() > 2) && (filePathString.getTail(2) == "/."))
    {
        filePathString = filePathString.getHead(filePathString.getLength() - 2) ;
    }

    if (filePathString == "/")
    {
        return fs::Directory::Root() ;
    }

    return fs::Directory::Path(Path::Parse(filePathString).getParentPath()) ;

}

String                          File::getContents                           ( ) const
{

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    std::fstream fileStream { path_.toString(), std::fstream::in } ;

    if (!fileStream.is_open())
    {
        throw ostk::core::error::RuntimeError("Cannot open file [{}].", this->toString()) ;
    }

    String contents ;

    try
    {
        contents = String(std::istreambuf_iterator<char>(fileStream), std::istreambuf_iterator<char>()) ;
    }
    catch (const std::exception& e)
    {

        fileStream.close() ;

        throw ostk::core::error::RuntimeError("Cannot get contents of file [{}].", this->toString()) ;

    }

    fileStream.close() ;

    return contents ;

}

String                          File::toString                              ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
    }

    return path_.toString() ;

}

void                            File::open                                  (   const   File::OpenMode&             anOpenMode                                  )
{

    // https://en.cppreference.com/w/cpp/io/ios_base/openmode

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    if (this->isOpen())
    {
        throw ostk::core::error::RuntimeError("File [{}] is already open.", this->toString()) ;
    }

    std::ios_base::openmode fileOpenMode ;

    switch (anOpenMode)
    {

        case File::OpenMode::Read:
            fileOpenMode = std::ios::in ;
            break ;

        case File::OpenMode::Write:
            fileOpenMode = std::ios::out ;
            break ;

        case File::OpenMode::Binary:
            fileOpenMode = std::ios::out | std::ios::binary ;
            break ;

        case File::OpenMode::Append:
            fileOpenMode = std::ios::out | std::ios::app ;
            break ;

        case File::OpenMode::AtEnd:
            fileOpenMode = std::ios::out | std::ios::ate ;
            break ;

        case File::OpenMode::Truncate:
            fileOpenMode = std::ios::out | std::ios::trunc ;
            break ;

        default:
            throw ostk::core::error::runtime::Wrong("Open mode") ;
            break ;

    }

    fileStreamUPtr_ = std::make_unique<std::fstream>(path_.toString(), fileOpenMode) ;

	if (!fileStreamUPtr_->is_open())
    {
        throw ostk::core::error::RuntimeError("Error when opening file [{}].", this->toString()) ;
    }

}

void                            File::close                                 ( )
{

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    if (!this->isOpen())
    {
        throw ostk::core::error::RuntimeError("File [{}] is not open.", this->toString()) ;
    }

    if (fileStreamUPtr_->is_open())
    {
        fileStreamUPtr_->close() ;
    }

    fileStreamUPtr_.reset(nullptr) ;

}

std::fstream&                   File::accessStream                          ( )
{

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    if (!this->isOpen())
    {
        throw ostk::core::error::RuntimeError("File [{}] is not open.", this->toString()) ;
    }

    return *fileStreamUPtr_ ;

}

// void                            File::renameTo                              (   const   String&              aName                                       )
// {

// }

// File                            File::copyToDirectory                       (   const   fs::Directory&              aDestination,
//                                                                                 const   String&              aNewFileName                                ) const
// {

// }

void                            File::moveToDirectory                       (   const   fs::Directory&              aDestination                                )
{

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", this->toString()) ;
    }

    if (!aDestination.exists())
    {
        throw ostk::core::error::RuntimeError("Destination [{}] does not exist.", aDestination.toString()) ;
    }

    const fs::Path destinationPath = aDestination.getPath() + Path::Parse(this->getName()) ;

    try
    {

        boost::filesystem::rename(path_.toString(), destinationPath.toString()) ;

        path_ = destinationPath ;

    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what()) ;
    }

}

void                            File::create                                (   const   fs::PermissionSet&          anOwnerPermissionSet,
                                                                                const   fs::PermissionSet&          aGroupPermissionSet,
                                                                                const   fs::PermissionSet&          anOtherPermissionSet                        )
{

    if (this->exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] already exists.", this->toString()) ;
    }

    fs::Directory parentDirectory = this->getParentDirectory() ;

    if (!parentDirectory.exists())
    {
        parentDirectory.create() ;
    }

    const fs::Path filePath = path_ ;

    std::fstream fileStream ;

    try
    {

        fileStream.open(filePath.toString(), std::ios::out) ;

        if (fileStream.is_open())
        {
            fileStream.close() ;
        }

    }
    catch (const std::ifstream::failure& e)
    {
        throw ostk::core::error::RuntimeError("Cannot create file [{}].", this->toString()) ;
    }

    (void) anOwnerPermissionSet ;
    (void) aGroupPermissionSet ;
    (void) anOtherPermissionSet ;

    // [TBI] this->applyOwnership(...)

    // [TBI] this->applyPermissions(...)

}

// void                            File::clear                                 ( )
// {

// }

void                            File::remove                                ( )
{

    if (!(this->getPermissions().canWrite()))
    {
        throw ostk::core::error::RuntimeError("Not enough permissions to remove file [{}].", this->toString()) ;
    }

    try
    {
        boost::filesystem::remove(path_.toString()) ;
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what()) ;
    }

}

File                            File::Undefined                             ( )
{
    return { Path::Undefined() } ;
}

File                            File::Path                                  (   const   fs::Path&                   aPath                                       )
{

    if (!aPath.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Path") ;
    }

    return { aPath } ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                File::File                                  (   const   fs::Path&                   aPath                                       )
                                :   path_(aPath),
                                    fileStreamUPtr_(nullptr)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
