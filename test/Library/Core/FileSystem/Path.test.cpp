////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/FileSystem/Path.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/FileSystem/Path.hpp>

#include <Global.test.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (Library_Core_FileSystem_Path, CopyConstructor)
{

    using library::core::fs::Path ;

    {

        const Path path = Path::Parse("/abc/def.ghi") ;

        const Path newPath(path) ;

        EXPECT_EQ(path, newPath) ;

    }

}

TEST (Library_Core_FileSystem_Path, AssignmentOperator)
{

    using library::core::fs::Path ;

    {

        const Path path = Path::Parse("/abc/def.ghi") ;

        const Path newPath = path ;

        EXPECT_EQ(path, newPath) ;

    }

}

TEST (Library_Core_FileSystem_Path, EqualToOperator)
{

    using library::core::fs::Path ;

    {

        EXPECT_TRUE(Path::Parse("/") == Path::Parse("/")) ;
        EXPECT_TRUE(Path::Parse("/path/to/file") == Path::Parse("/path/to/file")) ;

    }

    {

        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Parse("/path/to/file/")) ;
        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Parse("/path/to/file2")) ;
        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Parse("/path2/to/file")) ;

    }

    {

        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Undefined()) ;
        EXPECT_FALSE(Path::Undefined() == Path::Parse("/path/to/file")) ;
        EXPECT_FALSE(Path::Undefined() == Path::Undefined()) ;

    }

}

TEST (Library_Core_FileSystem_Path, NotEqualToOperator)
{

    using library::core::fs::Path ;

    {

        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Parse("/path/to/file/")) ;
        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Parse("/path/to/file2")) ;
        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Parse("/path2/to/file")) ;

    }

    {

        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Undefined()) ;
        EXPECT_TRUE(Path::Undefined() != Path::Parse("/path/to/file")) ;
        EXPECT_TRUE(Path::Undefined() != Path::Undefined()) ;

    }

    {

        EXPECT_FALSE(Path::Parse("/") != Path::Parse("/")) ;
        EXPECT_FALSE(Path::Parse("/path/to/file") != Path::Parse("/path/to/file")) ;

    }

}

// TEST (Library_Core_FileSystem_Path, AdditionOperator)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }

// }

// TEST (Library_Core_FileSystem_Path, AdditionAssignmentOperator)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }

// }

TEST (Library_Core_FileSystem_Path, StreamOperator)
{

    using library::core::fs::Path ;

    {

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << Path::Parse("/abc/def.ghi") << std::endl) ;

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty()) ;

    }
    
}

TEST (Library_Core_FileSystem_Path, IsDefined)
{

    using library::core::fs::Path ;

    {

        EXPECT_TRUE(Path::Parse("/").isDefined()) ;
        EXPECT_TRUE(Path::Parse("/abc").isDefined()) ;
        EXPECT_TRUE(Path::Parse("/abc/").isDefined()) ;
        EXPECT_TRUE(Path::Parse("/abc/def").isDefined()) ;
        EXPECT_TRUE(Path::Parse("/abc/def.ghi").isDefined()) ;

    }

    {

        EXPECT_FALSE(Path::Undefined().isDefined()) ;

    }
    
}

// TEST (Library_Core_FileSystem_Path, IsAbsolute)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_Path, IsRelative)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_Path, GetFirstElement)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_Path, GetLastElement)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_Path, GetNormalizedPath)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_Path, GetAbsolutePath)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

// TEST (Library_Core_FileSystem_Path, GetRelativePathTo)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

TEST (Library_Core_FileSystem_Path, ToString)
{

    using library::core::fs::Path ;

    {

        EXPECT_EQ("/", Path::Parse("/").toString()) ;
        EXPECT_EQ("/abc", Path::Parse("/abc").toString()) ;
        EXPECT_EQ("/abc/", Path::Parse("/abc/").toString()) ;
        EXPECT_EQ("/abc/def", Path::Parse("/abc/def").toString()) ;
        EXPECT_EQ("/abc/def.ghi", Path::Parse("/abc/def.ghi").toString()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().toString()) ;

    }
    
}

TEST (Library_Core_FileSystem_Path, Undefined)
{

    using library::core::fs::Path ;

    {

        EXPECT_NO_THROW(Path::Undefined()) ;
        EXPECT_FALSE(Path::Undefined().isDefined()) ;

    }
    
}

TEST (Library_Core_FileSystem_Path, Root)
{

    using library::core::fs::Path ;

    {

        EXPECT_EQ("/", Path::Root().toString()) ;
        EXPECT_TRUE(Path::Root().isDefined()) ;

    }
    
}

TEST (Library_Core_FileSystem_Path, Parse)
{

    using library::core::fs::Path ;

    {

        EXPECT_TRUE(Path::Parse("/").isDefined()) ;
        EXPECT_EQ("/", Path::Parse("/").toString()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Parse("")) ;

    }
    
}

// TEST (Library_Core_FileSystem_Path, Strings)
// {

//     using library::core::fs::Path ;

//     {

//         FAIL() ;

//     }
    
// }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////