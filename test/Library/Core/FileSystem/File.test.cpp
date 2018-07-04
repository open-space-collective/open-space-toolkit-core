////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/File.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/File.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_FileSystem_File, CopyConstructor)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        const File file = File::Path(Path::Parse("/path/to/file")) ;

        const File newFile(file) ;

        EXPECT_EQ(file, newFile) ;

    }

}

TEST (Library_Core_FileSystem_File, AssignmentOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        const File file = File::Path(Path::Parse("/path/to/file")) ;

        const File newFile = file ;

        EXPECT_EQ(file, newFile) ;

    }

}

TEST (Library_Core_FileSystem_File, EqualToOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        EXPECT_TRUE(File::Path(Path::Parse("/")) == File::Path(Path::Parse("/"))) ;
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path/to/file"))) ;

    }

    {

        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path/to/file/"))) ;
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path/to/file2"))) ;
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path2/to/file"))) ;

    }

    {

        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Undefined()) ;
        EXPECT_FALSE(File::Undefined() == File::Path(Path::Parse("/path/to/file"))) ;
        EXPECT_FALSE(File::Undefined() == File::Undefined()) ;

    }

}

TEST (Library_Core_FileSystem_File, NotEqualToOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path/to/file/"))) ;
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path/to/file2"))) ;
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path2/to/file"))) ;

    }

    {

        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Undefined()) ;
        EXPECT_TRUE(File::Undefined() != File::Path(Path::Parse("/path/to/file"))) ;
        EXPECT_TRUE(File::Undefined() != File::Undefined()) ;

    }

    {

        EXPECT_FALSE(File::Path(Path::Parse("/")) != File::Path(Path::Parse("/"))) ;
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path/to/file"))) ;

    }

}

TEST (Library_Core_FileSystem_File, StreamOperator)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << File::Path(Path::Parse("/path/to/file")) << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }
    
}

TEST (Library_Core_FileSystem_File, IsDefined)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        EXPECT_TRUE(File::Path(Path::Parse("/")).isDefined()) ;
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")).isDefined()) ;
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file/")).isDefined()) ;

    }

    {

        EXPECT_FALSE(File::Undefined().isDefined()) ;

    }
    
}

TEST (Library_Core_FileSystem_File, Exists)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        EXPECT_TRUE(File::Path(Path::Parse("/")).exists()) ;
        EXPECT_TRUE(File::Path(Path::Parse("/usr")).exists()) ;
        EXPECT_TRUE(File::Path(Path::Parse("/app/CMakeLists.txt")).exists()) ;

    }

    {

        EXPECT_FALSE(File::Path(Path::Parse("/skf47hksdjf")).exists()) ;
        EXPECT_FALSE(File::Path(Path::Parse("/usr/sdfkjdfg")).exists()) ;

    }

    {

        EXPECT_ANY_THROW(File::Undefined().exists()) ;

    }
    
}

TEST (Library_Core_FileSystem_File, GetName)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    // With extension

    {

        EXPECT_EQ("/", File::Path(Path::Parse("/")).getName(true)) ;
        EXPECT_EQ("usr", File::Path(Path::Parse("/usr")).getName(true)) ;
        EXPECT_EQ("CMakeLists.txt", File::Path(Path::Parse("/app/CMakeLists.txt")).getName(true)) ;

    }

    // Without extension

    {

        EXPECT_EQ("/", File::Path(Path::Parse("/")).getName(false)) ;
        EXPECT_EQ("usr", File::Path(Path::Parse("/usr")).getName(false)) ;
        EXPECT_EQ("CMakeLists", File::Path(Path::Parse("/app/CMakeLists.txt")).getName(false)) ;

    }

    {

        EXPECT_ANY_THROW(File::Undefined().getName()) ;

    }
    
}

TEST (Library_Core_FileSystem_File, GetExtension)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        EXPECT_TRUE(File::Path(Path::Parse("/")).exists()) ;
        EXPECT_TRUE(File::Path(Path::Parse("/usr")).exists()) ;
        EXPECT_TRUE(File::Path(Path::Parse("/app/CMakeLists.txt")).exists()) ;

    }

    {

        EXPECT_FALSE(File::Path(Path::Parse("/skf47hksdjf")).exists()) ;
        EXPECT_FALSE(File::Path(Path::Parse("/usr/sdfkjdfg")).exists()) ;

    }

    {

        EXPECT_ANY_THROW(File::Undefined().exists()) ;

    }
    
}

TEST (Library_Core_FileSystem_File, GetPath)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        const Path path = Path::Parse("/path/to/file") ;

        EXPECT_EQ(path, File::Path(path).getPath()) ;

    }
    
    {

        EXPECT_ANY_THROW(File::Undefined().getPath()) ;

    }
    
}

// TEST (Library_Core_FileSystem_File, GetPermissions)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, GetParentDirectory)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, RenameTo)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, CopyToDirectory)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, MoveToDirectory)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, Create)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, Clear)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_File, Remove)
// {

//     using library::core::fs::Path ;
//     using library::core::fs::File ;

//     {

//         FAIL() ;

//     }
    
// }

TEST (Library_Core_FileSystem_File, Undefined)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        EXPECT_NO_THROW(File::Undefined()) ;
        EXPECT_FALSE(File::Undefined().isDefined()) ;

    }
    
}

TEST (Library_Core_FileSystem_File, Path)
{

    using library::core::fs::Path ;
    using library::core::fs::File ;

    {

        const Path path = Path::Parse("/path/to/file") ;

        EXPECT_TRUE(File::Path(path).isDefined()) ;

        EXPECT_EQ(path, File::Path(path).getPath()) ;

    }

    {

        const Path path = Path::Parse("/path/to/file/") ;

        EXPECT_TRUE(File::Path(path).isDefined()) ;

        EXPECT_EQ(path, File::Path(path).getPath()) ;

    }

    {

        EXPECT_ANY_THROW(File::Path(Path::Parse(""))) ;
        EXPECT_ANY_THROW(File::Path(Path::Undefined())) ;

    }
    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////