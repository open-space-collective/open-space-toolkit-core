////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <iostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main ()
{

    using ostk::core::fs::Path ;
    using ostk::core::fs::Directory ;

    Directory dir = Directory::Path(Path::Parse("/usr/games")) ;

    bool is_empty = dir.isEmpty() ;

    std::cout << "Directory Created is empty: " << is_empty << std::endl ;

    const Directory directory = Directory::Path(Path::Parse("/app/include/OpenSpaceToolkit/Core")) ;

    bool contains1 = directory.containsFileWithName("Error.hpp") ;
    bool contains2 = directory.containsFileWithName("Utilities.hpp") ;

    std::cout << "directory contains file with name Error.hpp " << contains1 << std::endl ;
    std::cout << "directory contains file with name Utilities.hpp " << contains2 << std::endl ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
