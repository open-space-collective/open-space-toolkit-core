/// Apache License 2.0

#include <boost/filesystem.hpp>

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

namespace ostk
{
namespace core
{
namespace filesystem
{

bool Directory::operator==(const Directory& aDirectory) const
{
    if ((!this->isDefined()) || (!aDirectory.isDefined()))
    {
        return false;
    }

    return path_ == aDirectory.path_;
}

bool Directory::operator!=(const Directory& aDirectory) const
{
    return !((*this) == aDirectory);
}

std::ostream& operator<<(std::ostream& anOutputStream, const Directory& aDirectory)
{
    ostk::core::utils::Print::Header(anOutputStream, "Directory");

    ostk::core::utils::Print::Line(anOutputStream)
        << "Name:" << (aDirectory.isDefined() ? aDirectory.getName() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Path:" << (aDirectory.isDefined() ? aDirectory.path_.toString() : "Undefined");
    ostk::core::utils::Print::Line(anOutputStream)
        << "Exists:" << (aDirectory.isDefined() ? String::Boolean(aDirectory.exists()) : "Undefined");

    ostk::core::utils::Print::Footer(anOutputStream);

    return anOutputStream;
}

bool Directory::isDefined() const
{
    return path_.isDefined();
}

bool Directory::exists() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory");
    }

    try
    {
        return boost::filesystem::is_directory(path_.toString() + "/");
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return false;
}

bool Directory::isEmpty() const
{
    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("Directory [{}] does not exist.", this->toString());
    }

    try
    {
        return boost::filesystem::is_empty(boost::filesystem::path(path_.toString()));
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return false;
}

bool Directory::containsFileWithName(const String& aFileName) const
{
    if (aFileName.isEmpty())
    {
        throw ostk::core::error::runtime::Undefined("File name");
    }

    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("Directory [{}] does not exist.", this->toString());
    }

    try
    {
        const boost::filesystem::path directoryPath = {path_.toString()};

        for (boost::filesystem::directory_iterator directoryIterator {directoryPath};
             directoryIterator != boost::filesystem::directory_iterator();
             ++directoryIterator)
        {
            const boost::filesystem::path subFilePath = directoryIterator->path();

            if (!boost::filesystem::is_directory(subFilePath))
            {
                if (subFilePath.filename().string() == aFileName)
                {
                    return true;
                }
            }
        }
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return false;
}

// bool                            Directory::containsDirectoryWithName        (   const   String& aDirectoryName )
// const
// {
// }

String Directory::getName() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File");
    }

    try
    {
        String directoryPathString = path_.toString();

        while ((directoryPathString.getLength() > 1) && (directoryPathString.getLast() == '/'))
        {
            directoryPathString = directoryPathString.getHead(directoryPathString.getLength() - 1);
        }

        return boost::filesystem::path(directoryPathString).filename().string();
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    return String::Empty();
}

filesystem::Path Directory::getPath() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File");
    }

    return path_;
}

// filesystem::PermissionSet               Directory::getPermissions                   ( ) const
// {
//     return File::Path(path_).getPermissions() ;
// }

Directory Directory::getParentDirectory() const
{
    return File::Path(path_).getParentDirectory();
}

// containers::Array<filesystem::File>           Directory::getFiles                         ( ) const
// {

// }

containers::Array<Directory> Directory::getDirectories() const
{
    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("Directory [{}] does not exist.", this->toString());
    }

    containers::Array<Directory> subDirectories = containers::Array<Directory>::Empty();

    try
    {
        const boost::filesystem::path directoryPath = {path_.toString()};

        for (boost::filesystem::directory_iterator directoryIterator {directoryPath};
             directoryIterator != boost::filesystem::directory_iterator();
             ++directoryIterator)
        {
            const boost::filesystem::path subDirectoryPath = directoryIterator->path();

            if (boost::filesystem::is_directory(subDirectoryPath))
            {
                subDirectories.add(Directory::Path(Path::Parse(subDirectoryPath.string())));
            }
        }
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    std::sort(
        subDirectories.begin(),
        subDirectories.end(),
        [](const Directory& aFirstDirectory, const Directory& aSecondDirectory) -> bool
        {
            return aFirstDirectory.getName() < aSecondDirectory.getName();
        }
    );

    return subDirectories;
}

String Directory::toString() const
{
    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Directory");
    }

    return path_.toString();
}

// void                            Directory::renameTo                         (   const   String& aName )
// {
// }

// Directory                       Directory::copyToDirectory                  (   const   Directory& aDestination,
//                                                                                 const   String& aNewDirectoryName )
//                                                                                 const
// {
// }

// void                            Directory::moveToDirectory                  (   const   Directory& aDestination )
// {
// }

void Directory::create(
    const filesystem::PermissionSet& anOwnerPermissionSet,
    const filesystem::PermissionSet& aGroupPermissionSet,
    const filesystem::PermissionSet& anOtherPermissionSet
)
{
    if (this->exists())
    {
        throw ostk::core::error::RuntimeError("Directory [{}] already exists.", this->toString());
    }

    try
    {
        String directoryPathString = path_.toString();

        if ((directoryPathString.getLength() > 1) && (directoryPathString.getLast() != '/'))
        {
            directoryPathString += "/";
        }

        if (!boost::filesystem::create_directories(boost::filesystem::path(directoryPathString).parent_path()))
        {
            throw ostk::core::error::RuntimeError("Cannot create directory [{}].", this->toString());
        }
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }

    (void)anOwnerPermissionSet;
    (void)aGroupPermissionSet;
    (void)anOtherPermissionSet;

    // [TBI] this->applyOwnership(...)

    // [TBI] this->applyPermissions(...)
}

void Directory::remove()
{
    if (!this->exists())
    {
        throw ostk::core::error::RuntimeError("Directory [{}] does not exist.", this->toString());
    }

    try
    {
        boost::filesystem::remove_all(path_.toString());
    }
    catch (const boost::filesystem::filesystem_error& e)
    {
        throw ostk::core::error::RuntimeError(e.what());
    }
}

Directory Directory::Undefined()
{
    return {Path::Undefined()};
}

Directory Directory::Root()
{
    return {Path::Parse("/")};
}

Directory Directory::Path(const filesystem::Path& aPath)
{
    if (!aPath.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Path");
    }

    return {aPath};
}

Directory::Directory(const filesystem::Path& aPath)
    : path_(aPath)
{
}

}  // namespace filesystem
}  // namespace core
}  // namespace ostk
