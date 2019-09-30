////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library ▸ Core
/// @file           Library/Core/FileSystem/Path.test.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

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

TEST (Library_Core_FileSystem_Path, AdditionOperator)
{

    using library::core::fs::Path ;

    {

        const Path firstPath = Path::Parse("/abc/def") ;
        const Path secondPath = Path::Parse("/ghi/jkl") ;

        EXPECT_EQ(Path::Parse("/abc/def/ghi/jkl"), firstPath + secondPath) ;

    }

    {

        const Path firstPath = Path::Parse("/abc/def") ;
        const Path secondPath = Path::Parse("./ghi/jkl") ;

        EXPECT_EQ(Path::Parse("/abc/def/./ghi/jkl"), firstPath + secondPath) ;

    }

    {

        const Path firstPath = Path::Parse("/abc/def") ;
        const Path secondPath = Path::Parse("../ghi/jkl") ;

        EXPECT_EQ(Path::Parse("/abc/def/../ghi/jkl"), firstPath + secondPath) ;

    }

    {

        const Path firstPath = Path::Parse("./abc/def") ;
        const Path secondPath = Path::Parse("../ghi/jkl") ;

        EXPECT_EQ(Path::Parse("./abc/def/../ghi/jkl"), firstPath + secondPath) ;

    }

    {

        const Path path = Path::Parse("/abc/def") ;

        EXPECT_ANY_THROW(Path::Undefined() + path) ;
        EXPECT_ANY_THROW(path + Path::Undefined()) ;
        EXPECT_ANY_THROW(Path::Undefined() + Path::Undefined()) ;

    }

}

TEST (Library_Core_FileSystem_Path, AdditionAssignmentOperator)
{

    using library::core::fs::Path ;

    {

        Path firstPath = Path::Parse("/abc/def") ;
        const Path secondPath = Path::Parse("/ghi/jkl") ;

        firstPath += secondPath ;

        EXPECT_EQ(Path::Parse("/abc/def/ghi/jkl"), firstPath) ;

    }

    {

        Path firstPath = Path::Parse("/abc/def") ;
        const Path secondPath = Path::Parse("./ghi/jkl") ;

        firstPath += secondPath ;

        EXPECT_EQ(Path::Parse("/abc/def/./ghi/jkl"), firstPath) ;

    }

    {

        Path firstPath = Path::Parse("/abc/def") ;
        const Path secondPath = Path::Parse("../ghi/jkl") ;

        firstPath += secondPath ;

        EXPECT_EQ(Path::Parse("/abc/def/../ghi/jkl"), firstPath) ;

    }

    {

        Path firstPath = Path::Parse("./abc/def") ;
        const Path secondPath = Path::Parse("../ghi/jkl") ;

        firstPath += secondPath ;

        EXPECT_EQ(Path::Parse("./abc/def/../ghi/jkl"), firstPath) ;

    }

    {

        Path path = Path::Parse("/abc/def") ;

        EXPECT_ANY_THROW(Path::Undefined() += path) ;
        EXPECT_ANY_THROW(path += Path::Undefined()) ;
        EXPECT_ANY_THROW(Path::Undefined() += Path::Undefined()) ;

    }

}

TEST (Library_Core_FileSystem_Path, StreamOperator)
{

    using library::core::fs::Path ;

    {

        const Path path = Path::Parse("/abc/def.ghi") ;

        testing::internal::CaptureStdout() ;

        EXPECT_NO_THROW(std::cout << path << std::endl) ;

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

TEST (Library_Core_FileSystem_Path, IsAbsolute)
{

    using library::core::fs::Path ;

    {

        EXPECT_TRUE(Path::Parse("/").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc/").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc/..").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc/def").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc/def.ghi").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc/./def.ghi").isAbsolute()) ;
        EXPECT_TRUE(Path::Parse("/abc/../def.ghi").isAbsolute()) ;

    }

    {

        EXPECT_FALSE(Path::Parse("./").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("./abc").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("./abc/").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("./abc/def").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("./abc/def.ghi").isAbsolute()) ;

        EXPECT_FALSE(Path::Parse("../").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("../abc").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("../abc/").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("../abc/def").isAbsolute()) ;
        EXPECT_FALSE(Path::Parse("../abc/def.ghi").isAbsolute()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().isAbsolute()) ;

    }

}

TEST (Library_Core_FileSystem_Path, IsRelative)
{

    using library::core::fs::Path ;

    {

        EXPECT_TRUE(Path::Parse("./").isRelative()) ;
        EXPECT_TRUE(Path::Parse("./abc").isRelative()) ;
        EXPECT_TRUE(Path::Parse("./abc/").isRelative()) ;
        EXPECT_TRUE(Path::Parse("./abc/def").isRelative()) ;
        EXPECT_TRUE(Path::Parse("./abc/def.ghi").isRelative()) ;

        EXPECT_TRUE(Path::Parse("../").isRelative()) ;
        EXPECT_TRUE(Path::Parse("../abc").isRelative()) ;
        EXPECT_TRUE(Path::Parse("../abc/").isRelative()) ;
        EXPECT_TRUE(Path::Parse("../abc/def").isRelative()) ;
        EXPECT_TRUE(Path::Parse("../abc/def.ghi").isRelative()) ;

    }

    {

        EXPECT_FALSE(Path::Parse("/").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc/").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc/..").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc/def").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc/def.ghi").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc/./def.ghi").isRelative()) ;
        EXPECT_FALSE(Path::Parse("/abc/../def.ghi").isRelative()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().isRelative()) ;

    }

}

TEST (Library_Core_FileSystem_Path, GetParentPath)
{

    using library::core::fs::Path ;

    {

        EXPECT_EQ(Path::Parse("/"), Path::Parse("/abc").getParentPath()) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/").getParentPath()) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/..").getParentPath()) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/def").getParentPath()) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/def.ghi").getParentPath()) ;
        EXPECT_EQ(Path::Parse("/abc/."), Path::Parse("/abc/./def.ghi").getParentPath()) ;
        EXPECT_EQ(Path::Parse("/abc/.."), Path::Parse("/abc/../def.ghi").getParentPath()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().getParentPath()) ;

    }

}

TEST (Library_Core_FileSystem_Path, GetLastElement)
{

    using library::core::fs::Path ;

    {

        EXPECT_EQ("/", Path::Parse("/").getLastElement()) ;
        EXPECT_EQ("abc", Path::Parse("/abc").getLastElement()) ;
        EXPECT_EQ(".", Path::Parse("/abc/").getLastElement()) ;
        EXPECT_EQ("..", Path::Parse("/abc/..").getLastElement()) ;
        EXPECT_EQ("def", Path::Parse("/abc/def").getLastElement()) ;
        EXPECT_EQ("def.ghi", Path::Parse("/abc/def.ghi").getLastElement()) ;
        EXPECT_EQ("def.ghi", Path::Parse("/abc/./def.ghi").getLastElement()) ;
        EXPECT_EQ("def.ghi", Path::Parse("/abc/../def.ghi").getLastElement()) ;

        EXPECT_EQ(".", Path::Parse("./").getLastElement()) ;
        EXPECT_EQ("abc", Path::Parse("./abc").getLastElement()) ;
        EXPECT_EQ(".", Path::Parse("./abc/").getLastElement()) ;
        EXPECT_EQ("def", Path::Parse("./abc/def").getLastElement()) ;
        EXPECT_EQ("def.ghi", Path::Parse("./abc/def.ghi").getLastElement()) ;

        EXPECT_EQ(".", Path::Parse("../").getLastElement()) ;
        EXPECT_EQ("abc", Path::Parse("../abc").getLastElement()) ;
        EXPECT_EQ(".", Path::Parse("../abc/").getLastElement()) ;
        EXPECT_EQ("def", Path::Parse("../abc/def").getLastElement()) ;
        EXPECT_EQ("def.ghi", Path::Parse("../abc/def.ghi").getLastElement()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().getLastElement()) ;

    }

}

TEST (Library_Core_FileSystem_Path, GetNormalizedPath)
{

    using library::core::fs::Path ;

    {

        EXPECT_EQ(Path::Parse("/"), Path::Parse("/").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app/").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/build").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/app/build/Makefile"), Path::Parse("/app/build/Makefile").getNormalizedPath()) ;

        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app/.").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/"), Path::Parse("/app/..").getNormalizedPath()) ;
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/./build").getNormalizedPath()) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().getNormalizedPath()) ;

    }

}

TEST (Library_Core_FileSystem_Path, GetAbsolutePath)
{

    using library::core::fs::Path ;

    {

        EXPECT_EQ(Path::Parse("/"), Path::Parse("/").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/app/"), Path::Parse("/app/").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/build").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/app/build/Makefile"), Path::Parse("/app/build/Makefile").getAbsolutePath()) ;

        EXPECT_EQ(Path::Parse("/app/."), Path::Parse("/app/.").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/app/.."), Path::Parse("/app/..").getAbsolutePath()) ;
        EXPECT_EQ(Path::Parse("/app/./build"), Path::Parse("/app/./build").getAbsolutePath()) ;

    }

    {

        EXPECT_EQ(Path::Parse("/"), Path::Parse("/").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app/"), Path::Parse("/app/").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/build").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app/build/Makefile"), Path::Parse("/app/build/Makefile").getAbsolutePath(Path::Parse("/app/build"))) ;

        EXPECT_EQ(Path::Parse("/app/."), Path::Parse("/app/.").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app/.."), Path::Parse("/app/..").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app/./build"), Path::Parse("/app/./build").getAbsolutePath(Path::Parse("/app/build"))) ;

        EXPECT_EQ(Path::Parse("/app/build/Makefile"), Path::Parse("Makefile").getAbsolutePath(Path::Parse("/app/build"))) ;
        EXPECT_EQ(Path::Parse("/app/build/./Makefile"), Path::Parse("./Makefile").getAbsolutePath(Path::Parse("/app/build"))) ;

        EXPECT_EQ(Path::Parse("/app/docs/index.html"), Path::Parse("index.html").getAbsolutePath(Path::Parse("/app/docs"))) ;
        EXPECT_EQ(Path::Parse("/app/docs/./index.html"), Path::Parse("./index.html").getAbsolutePath(Path::Parse("/app/docs"))) ;

    }

    {

        EXPECT_ANY_THROW(Path::Undefined().getAbsolutePath()) ;
        EXPECT_ANY_THROW(Path::Parse("/").getAbsolutePath(Path::Undefined())) ;

    }

}

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

        EXPECT_NO_THROW(Path::Root()) ;
        EXPECT_TRUE(Path::Root().isDefined()) ;
        EXPECT_EQ("/", Path::Root().toString()) ;

    }

}

TEST (Library_Core_FileSystem_Path, Current)
{

    using library::core::fs::Path ;

    {

        EXPECT_NO_THROW(Path::Current()) ;
        EXPECT_TRUE(Path::Current().isDefined()) ;

    }

}

TEST (Library_Core_FileSystem_Path, Parse)
{

    using library::core::fs::Path ;

    {

        EXPECT_NO_THROW(Path::Parse("/")) ;
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
