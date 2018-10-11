////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/Path.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_FileSystem_Path__
#define __Library_Core_FileSystem_Path__

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Unique.hpp>

#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace fs
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Unique ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      

class Path
{

    public:

        /// @brief              Copy constructor
        ///
        /// @param              [in] aPath A path

                                Path                                        (   const   Path&                       aPath                                       ) ;

        /// @brief              Destructor

                                ~Path                                       ( ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] aPath A path
        /// @return             Path

        Path&                   operator =                                  (   const   Path&                       aPath                                       ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Path firstPath = Path::Parse("/path/to/file") ;
        ///                     Path secondPath = Path::Parse("/path/to/file") ;
        ///                     firstPath == secondPath ; // True
        /// @endcode
        ///
        /// @param              [in] aPath A path
        /// @return             True if paths are equal

        bool                    operator ==                                 (   const   Path&                       aPath                                       ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Path firstPath = Path::Parse("/path/to/first/file") ;
        ///                     Path secondPath = Path::Parse("/path/to/second/file") ;
        ///                     firstPath != secondPath ; // True
        /// @endcode
        ///
        /// @param              [in] aPath A path
        /// @return             True if paths are not equal

        bool                    operator !=                                 (   const   Path&                       aPath                                       ) const ;

        /// @brief              Addition operator
        ///
        ///                     Append path to path
        ///
        /// @code
        ///                     Path path = Path::Parse("/path") + Path::Parse("./to/file") ; // /path/to/file
        /// @endcode
        ///
        /// @param              [in] aPath A path
        /// @return             Path

        Path                    operator +                                  (   const   Path&                       aPath                                       ) const ;

        /// @brief              Addition assignment operator
        ///
        ///                     Append path to path
        ///
        /// @code
        ///                     Path path = Path::Parse("/path") ;
        ///                     path += Path::Parse("./to/file") ; // /path/to/file
        /// @endcode
        ///
        /// @param              [in] aPath A path
        /// @return             Reference to path

        Path&                   operator +=                                 (   const   Path&                       aPath                                       ) ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/file") ;
        ///                     std::cout << path ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aPath A path
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (            std::ostream&              anOutputStream,
                                                                                const    Path&                      aPath                                       ) ;

        /// @brief              Check if path is defined
        ///
        /// @code
        ///                     Path path = Path::Undefined() ;
        ///                     path.isDefined() ; // False
        /// @endcode
        ///
        /// @return             True if path is defined

        bool                    isDefined                                   ( ) const ;

        /// @brief              Check if path is absolute
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/file") ;
        ///                     path.isAbsolute() ; // True
        /// @endcode
        ///
        /// @return             True if path is absolute

        bool                    isAbsolute                                  ( ) const ;

        /// @brief              Check if path is relative
        ///
        /// @code
        ///                     Path path = Path::Parse("./path/to/file") ;
        ///                     path.isRelative() ; // True
        /// @endcode
        ///
        /// @return             True if path is relative

        bool                    isRelative                                  ( ) const ;

        /// @brief              Get parent path of path
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/file") ;
        ///                     Path parentPath = path.getParentPath() ; // /path/to
        /// @endcode
        ///
        /// @return             Parent path of path

        Path                    getParentPath                               ( ) const ;

        /// @brief              Get last element of path
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/file") ;
        ///                     String element = path.getLastElement() ; // file
        /// @endcode
        ///
        /// @return             Last element of path

        String                  getLastElement                              ( ) const ;

        /// @brief              Get normalized path
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/../to/./file") ;
        ///                     Path normalizedPath = path.getNormalizedPath() ; // /path/to/file
        /// @endcode
        ///
        /// @return             Normalized path

        Path                    getNormalizedPath                           (   const   Path&                       aBasePath                                   =   Path::Current() ) const ;

        /// @brief              Get absolute path
        ///
        /// @code
        ///                     Path path = Path::Parse("./to/file") ;
        ///                     Path absolutePath = path.getAbsolutePath() ; // /path/to/file
        /// @endcode
        ///
        /// @param              [in] (optional) aBasePath A base path
        /// @return             Absolute path

        Path                    getAbsolutePath                             (   const   Path&                       aBasePath                                   =   Path::Current() ) const ;

        /// @brief              Get path relative to path
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/file") ;
        ///                     Path referencePath = Path::Parse("/path") ;
        ///                     Path relativePath = path.getRelativePathTo(referencePath) ; // ./file
        /// @endcode
        ///
        /// @param              [in] aReferencePath A reference path
        /// @return             Absolute path

        Path                    getRelativePathTo                           (   const   Path&                       aReferencePath                              ) const ;

        /// @brief              Get serialized path
        ///
        /// @code
        ///                     Path::Parse("/path/to/file").toString() ; // "/path/to/file"
        /// @endcode
        ///
        /// @return             Serialized path

        String                  toString                                    ( ) const ;

        /// @brief              Constructs an undefined path
        ///
        /// @code
        ///                     Path path = Path::Undefined() ;
        ///                     path.isDefined() ; // False
        /// @endcode
        ///
        /// @return             Undefined path

        static Path             Undefined                                   ( ) ;

        /// @brief              Constructs a root path
        ///
        /// @code
        ///                     Path path = Path::Root() ; // /
        /// @endcode
        ///
        /// @return             Root path

        static Path             Root                                        ( ) ;

        /// @brief              Constructs a current path
        ///
        /// @code
        ///                     Path path = Path::Current() ; // /app/build
        /// @endcode
        ///
        /// @return             Current path

        static Path             Current                                     ( ) ;

        /// @brief              Constructs a path from a given string
        ///
        /// @code
        ///                     Path path = Path::Parse("/path/to/file.txt") ; // /path/to/file.txt
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @return             Path

        static Path             Parse                                       (   const   String&                     aString                                     ) ;

        /// @brief              Constructs a path from a list of string
        ///
        /// @code
        ///                     Path path = Path::Strings({"/", "path", "to", "file.txt"}) ; // /path/to/file.txt
        /// @endcode
        ///
        /// @param              [in] aStringList A list of string
        /// @return             Path

        static Path             Strings                                     (   const   std::initializer_list<String> aStringList                               ) ;

    private:

        class Impl ;

        Unique<Path::Impl>      implUPtr_ ;

                                Path                                        ( ) ;
    
} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////