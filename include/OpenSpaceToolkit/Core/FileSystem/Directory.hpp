/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_FileSystem_Directory__
#define __OpenSpaceToolkit_Core_FileSystem_Directory__

#include <optional>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace filesystem
{

namespace container = ostk::core::container;

using ostk::core::type::String;

/// @brief                      Cataloging structure which contains references to other computer files, and possibly
/// other directories
///
/// @ref                        https://en.wikipedia.org/wiki/Directory_(computing)

class Directory
{
   public:
    /// @brief              Copy constructor
    ///
    /// @param              [in] aDirectory A directory

    Directory(const Directory& aDirectory) = default;

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] aDirectory A directory
    /// @return             Directory

    Directory& operator=(const Directory& aDirectory) = default;

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Directory firstDirectory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Directory secondDirectory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     firstDirectory == secondDirectory ; // True
    /// @endcode
    ///
    /// @param              [in] aDirectory A directory
    /// @return             True if directories are equal

    bool operator==(const Directory& aDirectory) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Directory firstDirectory = Directory::Path(Path::Parse("/path/to/first/directory")) ;
    ///                     Directory secondDirectory = Directory::Path(Path::Parse("/path/to/second/directory")) ;
    ///                     firstDirectory != secondDirectory ; // True
    /// @endcode
    ///
    /// @param              [in] aDirectory A directory
    /// @return             True if directories are not equal

    bool operator!=(const Directory& aDirectory) const;

    /// @brief              Output stream operator
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     std::cout << directory ;
    /// @endcode
    ///
    /// @param              [in] anOutputStream An output stream
    /// @param              [in] aDirectory A directory
    /// @return             A reference to output stream

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Directory& aDirectory);

    /// @brief              Check if directory is defined
    ///
    /// @code
    ///                     Directory directory = Directory::Undefined() ;
    ///                     directory.isDefined() ; // False
    /// @endcode
    ///
    /// @return             True if directory is defined

    bool isDefined() const;

    /// @brief              Check if directory exists
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/nonexistent/directory")) ;
    ///                     directory.exists() ; // False
    /// @endcode
    ///
    /// @return             True if directory exists

    bool exists() const;

    /// @brief              Check if directory is empty
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/empty/directory")) ;
    ///                     directory.isEmpty() ; // True
    /// @endcode
    ///
    /// @return             True if directory is empty

    bool isEmpty() const;

    /// @brief              Check if directory contains file with name
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.containsFileWithName("file.txt") ; // True
    /// @endcode
    ///
    /// @return             True if directory contains file

    bool containsFileWithName(const String& aFileName) const;

    /// @brief              Check if directory contains directory with name
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.containsDirectoryWithName("subdirectory") ; // True
    /// @endcode
    ///
    /// @return             True if directory contains directory

    bool containsDirectoryWithName(const String& aDirectoryName) const;

    /// @brief              Get directory name
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.getName() ; // directory
    /// @endcode
    ///
    /// @return             Directory name

    String getName() const;

    /// @brief              Get directory path
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Path path = directory.getPath() ; // /path/to/directory
    /// @endcode
    ///
    /// @return             Directory path

    filesystem::Path getPath() const;

    /// @brief              Get directory permissions
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Permissions permissions = directory.getPermissions() ; // rwx
    /// @endcode
    ///
    /// @return             Directory permissions

    filesystem::PermissionSet getPermissions() const;

    /// @brief              Get directory's parent directory
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Directory parentDirectory = directory.getParentDirectory() ; // /path/to
    /// @endcode
    ///
    /// @return             Directory's parent directory

    Directory getParentDirectory() const;

    /// @brief              Get files in directory
    ///
    ///                     Files are listed in alphabetical order.
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Array<File> files = directory.getFiles() ;
    /// @endcode
    ///
    /// @return             Array of files in directory

    container::Array<filesystem::File> getFiles() const;

    /// @brief              Get directories in directory
    ///
    ///                     Directories are listed in alphabetical order.
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Array<Directory> directories = directory.getDirectories() ;
    /// @endcode
    ///
    /// @return             Array of directories in directory

    container::Array<Directory> getDirectories() const;

    /// @brief              Get serialized directory
    ///
    /// @code
    ///                     Directory::Path(Path::Parse("/path/to/directory")).toString() ; // "/path/to/directory"
    /// @endcode
    ///
    /// @return             Serialized directory

    String toString() const;

    /// @brief              Rename directory
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.renameTo("folder") ; // /path/to/folder
    /// @endcode
    ///
    /// @param              [in] aName A directory name

    void renameTo(const String& aName);

    /// @brief              Copy directory to directory
    ///
    /// @code
    ///                     Directory original = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Directory destination = Directory::Path(Path::Parse("/path/to/destination")) ;
    ///                     Directory copy = original.copyToDirectory(destination) ; // /path/to/destination/directory
    /// @endcode
    ///
    /// @param              [in] aDestination A destination directory
    /// @param              [in] (optional) aNewDirectoryName A copied directory name
    /// @return             Copied directory

    Directory copyToDirectory(const Directory& aDestination, const String& aNewDirectoryName = "") const;

    /// @brief              Move directory to directory
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     Directory destination = Directory::Path(Path::Parse("/path/to/destination")) ;
    ///                     directory.moveToDirectory(destination) ; // /path/to/destination/directory
    /// @endcode
    ///
    /// @param              [in] aDestination A destination directory

    void moveToDirectory(const Directory& aDestination);

    /// @brief              Create empty directory
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.exists() ; // False
    ///                     directory.create() ;
    ///                     directory.exists() ; // True
    /// @endcode
    ///
    /// @param              [in] (optional) anOwnerPermissionSet An owner permission set
    /// @param              [in] (optional) aGroupPermissionSet A group permission set
    /// @param              [in] (optional) anOtherPermissionSet An other permission set

    void create(
        const filesystem::PermissionSet& anOwnerPermissionSet = filesystem::PermissionSet::RWX(),
        const filesystem::PermissionSet& aGroupPermissionSet = filesystem::PermissionSet::RX(),
        const filesystem::PermissionSet& anOtherPermissionSet = filesystem::PermissionSet::RX()
    );

    /// @brief              Delete directory
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.exists() ; // True
    ///                     directory.delete() ;
    ///                     directory.exists() ; // False
    /// @endcode

    void remove();

    /// @brief              Constructs an undefined directory
    ///
    /// @code
    ///                     Directory directory = Directory::Undefined() ;
    ///                     directory.isDefined() ; // False
    /// @endcode
    ///
    /// @return             Undefined directory

    static Directory Undefined();

    /// @brief              Constructs a root directory
    ///
    /// @code
    ///                     Directory directory = Directory::Root() ; "/"
    /// @endcode
    ///
    /// @return             Root directory

    static Directory Root();

    /// @brief              Constructs a directory from a given path
    ///
    /// @code
    ///                     Directory directory = Directory::Path(Path::Parse("/path/to/directory")) ;
    ///                     directory.isDefined() ; // True
    /// @endcode
    ///
    /// @param              [in] aPath Path to directory
    /// @return             Directory

    static Directory Path(const filesystem::Path& aPath);

   private:
    std::optional<filesystem::Path> path_;

    Directory(const filesystem::Path& aPath);

    Directory();
};

}  // namespace filesystem
}  // namespace core
}  // namespace ostk

#endif
