////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/File.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_FileSystem_File__
#define __Library_Core_FileSystem_File__

#include <Library/Core/FileSystem/Path.hpp>
#include <Library/Core/FileSystem/PermissionSet.hpp>
#include <Library/Core/Types/String.hpp>

#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Directory ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Computer resource for recording data discretely in a computer storage device.

class File
{

    public:

        /// @brief              Copy constructor
        ///
        /// @param              [in] aFile A file

                                File                                        (   const   File&                       aFile                                       ) ;

        /// @brief              Assignment operator
        ///
        /// @param              [in] aFile A file
        /// @return             File

        File&                   operator =                                  (   const   File&                       aFile                                       ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     File firstFile = File::Path(Path::Parse("/path/to/file")) ;
        ///                     File secondFile = File::Path(Path::Parse("/path/to/file")) ;
        ///                     firstFile == secondFile ; // True
        /// @endcode
        ///
        /// @param              [in] aFile A file
        /// @return             True if files are equal

        bool                    operator ==                                 (   const   File&                       aFile                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     File firstFile = File::Path(Path::Parse("/path/to/first/file")) ;
        ///                     File secondFile = File::Path(Path::Parse("/path/to/second/file")) ;
        ///                     firstFile != secondFile ; // True
        /// @endcode
        ///
        /// @param              [in] aFile A file
        /// @return             True if files are not equal

        bool                    operator !=                                 (   const   File&                       aFile                                       ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file")) ;
        ///                     std::cout << file ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aFile A file
        /// @return             An output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   File&                       aFile                                       ) ;

        /// @brief              Check if file is defined
        ///
        /// @code
        ///                     File file = File::Undefined() ;
        ///                     file.isDefined() ; // False
        /// @endcode
        ///
        /// @return             True if file is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Check if file exists
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/nonexistent/file")) ;
        ///                     file.exists() ; // False
        /// @endcode
        ///
        /// @return             True if file exists

        bool                    exists                                      ( ) const ;

        /// @brief              Get file name
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.getName() ; // file.txt
        ///                     file.getName(false) ; // file
        /// @endcode
        ///
        /// @param              [in] (optional) withExtension If true, add extension to filename
        /// @return             File name

        String                  getName                                     (           bool                        withExtension                               =   true) const ;

        /// @brief              Get file extension
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.getExtension() ; // txt
        /// @endcode
        ///
        /// @return             File extension

        String                  getExtension                                ( ) const ;

        /// @brief              Get file path
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     Path path = file.getPath() ; // /path/to/file.txt
        /// @endcode
        ///
        /// @return             File path

        fs::Path                getPath                                     ( ) const ;

        /// @brief              Get file permissions
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     Permissions permissions = file.getPermissions() ; // rw-
        /// @endcode
        ///
        /// @return             File permissions

        fs::PermissionSet       getPermissions                              ( ) const ;

        /// @brief              Get file's parent directory
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     Directory directory = file.getParentDirectory() ; // /path/to
        /// @endcode
        ///
        /// @return             File's parent directory

        fs::Directory           getParentDirectory                          ( ) const ;

        /// @brief              Get serialized file
        ///
        /// @code
        ///                     File::Path(Path::Parse("/path/to/file")).toString() ; // "/path/to/file"
        /// @endcode
        ///
        /// @return             Serialized file

        String                  toString                                    ( ) const ;

        /// @brief              Rename file
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.renameTo("cat.jpg") ; // /path/to/cat.jpg
        /// @endcode
        ///
        /// @param              [in] aName A file name

        void                    renameTo                                    (   const   String&                     aName                                       ) ;

        /// @brief              Copy file to directory
        ///
        /// @code
        ///                     File original = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     Directory destination = Directory::Path(Path::Parse("/new/path/to")) ;
        ///                     File copy = original.copyToDirectory(destination) ; // /new/path/to/file.txt
        /// @endcode
        ///
        /// @param              [in] aDestination A destination directory
        /// @param              [in] (optional) aNewFileName A copied file name
        /// @return             Copied file

        File                    copyToDirectory                             (   const   fs::Directory&              aDestination,
                                                                                const   String&                     aNewFileName                                =   "" ) const ;

        /// @brief              Move file to directory
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     Directory destination = Directory::Path(Path::Parse("/new/path/to")) ;
        ///                     file.moveToDirectory(destination) ; // /new/path/to/file.txt
        /// @endcode
        ///
        /// @param              [in] aDestination A destination directory

        void                    moveToDirectory                             (   const   fs::Directory&              aDestination                                ) ;

        /// @brief              Create empty file
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.exists() ; // False
        ///                     file.create() ;
        ///                     file.exists() ; // True
        /// @endcode
        ///
        /// @param              [in] (optional) anOwnerPermissionsSet An owner permissions set
        /// @param              [in] (optional) aGroupPermissionsSet A group permissions set
        /// @param              [in] (optional) anOtherPermissionsSet An other permissions set

        void                    create                                      (   const   fs::PermissionSet&          anOwnerPermissionsSet                       =   fs::PermissionSet::RW(),
                                                                                const   fs::PermissionSet&          aGroupPermissionsSet                        =   fs::PermissionSet::R(),
                                                                                const   fs::PermissionSet&          anOtherPermissionsSet                       =   fs::PermissionSet::R() ) ;

        /// @brief              Clear file contents
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.exists() ; // True
        ///                     file.clear() ;
        ///                     file.exists() ; // True
        /// @endcode

        void                    clear                                       ( ) ;

        /// @brief              Delete file
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.exists() ; // True
        ///                     file.delete() ;
        ///                     file.exists() ; // False
        /// @endcode

        void                    remove                                      ( ) ;

        /// @brief              Constructs an undefined file
        ///
        /// @code
        ///                     File file = File::Undefined() ;
        ///                     file.isDefined() ; // False
        /// @endcode
        ///
        /// @return             Undefined file

        static File             Undefined                                   ( ) ;

        /// @brief              Constructs a file from a given path
        ///
        /// @code
        ///                     File file = File::Path(Path::Parse("/path/to/file.txt")) ;
        ///                     file.isDefined() ; // True
        /// @endcode
        ///
        /// @param              [in] aPath Path to file
        /// @return             File

        static File             Path                                        (   const   fs::Path&                   aPath                                       ) ;

    private:

        fs::Path                path_ ;

                                File                                        (   const   fs::Path&                   aPath                                       ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////