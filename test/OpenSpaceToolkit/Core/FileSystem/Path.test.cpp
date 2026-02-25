/// Apache License 2.0

#include <boost/version.hpp>

#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_FileSystem_Path, CopyConstructor)
{
    using ostk::core::filesystem::Path;

    {
        const Path path = Path::Parse("/abc/def.ghi");

        const Path newPath(path);

        EXPECT_EQ(path, newPath);
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, AssignmentOperator)
{
    using ostk::core::filesystem::Path;

    {
        const Path path = Path::Parse("/abc/def.ghi");

        const Path newPath = path;

        EXPECT_EQ(path, newPath);
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, EqualToOperator)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_TRUE(Path::Parse("/") == Path::Parse("/"));
        EXPECT_TRUE(Path::Parse("/path/to/file") == Path::Parse("/path/to/file"));
    }

    {
        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Parse("/path/to/file/"));
        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Parse("/path/to/file2"));
        EXPECT_FALSE(Path::Parse("/path/to/file") == Path::Parse("/path2/to/file"));
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, NotEqualToOperator)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Parse("/path/to/file/"));
        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Parse("/path/to/file2"));
        EXPECT_TRUE(Path::Parse("/path/to/file") != Path::Parse("/path2/to/file"));
    }

    {
        EXPECT_FALSE(Path::Parse("/") != Path::Parse("/"));
        EXPECT_FALSE(Path::Parse("/path/to/file") != Path::Parse("/path/to/file"));
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, AdditionOperator)
{
    using ostk::core::filesystem::Path;

    {
        const Path firstPath = Path::Parse("/abc/def");
        const Path secondPath = Path::Parse("/ghi/jkl");

        EXPECT_EQ(Path::Parse("/abc/def/ghi/jkl"), firstPath + secondPath);
    }

    {
        const Path firstPath = Path::Parse("/abc/def");
        const Path secondPath = Path::Parse("./ghi/jkl");

        EXPECT_EQ(Path::Parse("/abc/def/./ghi/jkl"), firstPath + secondPath);
    }

    {
        const Path firstPath = Path::Parse("/abc/def");
        const Path secondPath = Path::Parse("../ghi/jkl");

        EXPECT_EQ(Path::Parse("/abc/def/../ghi/jkl"), firstPath + secondPath);
    }

    {
        const Path firstPath = Path::Parse("./abc/def");
        const Path secondPath = Path::Parse("../ghi/jkl");

        EXPECT_EQ(Path::Parse("./abc/def/../ghi/jkl"), firstPath + secondPath);
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, AdditionAssignmentOperator)
{
    using ostk::core::filesystem::Path;

    {
        Path firstPath = Path::Parse("/abc/def");
        const Path secondPath = Path::Parse("/ghi/jkl");

        firstPath += secondPath;

        EXPECT_EQ(Path::Parse("/abc/def/ghi/jkl"), firstPath);
    }

    {
        Path firstPath = Path::Parse("/abc/def");
        const Path secondPath = Path::Parse("./ghi/jkl");

        firstPath += secondPath;

        EXPECT_EQ(Path::Parse("/abc/def/./ghi/jkl"), firstPath);
    }

    {
        Path firstPath = Path::Parse("/abc/def");
        const Path secondPath = Path::Parse("../ghi/jkl");

        firstPath += secondPath;

        EXPECT_EQ(Path::Parse("/abc/def/../ghi/jkl"), firstPath);
    }

    {
        Path firstPath = Path::Parse("./abc/def");
        const Path secondPath = Path::Parse("../ghi/jkl");

        firstPath += secondPath;

        EXPECT_EQ(Path::Parse("./abc/def/../ghi/jkl"), firstPath);
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, StreamOperator)
{
    using ostk::core::filesystem::Path;

    {
        const Path path = Path::Parse("/abc/def.ghi");

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << path << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, IsAbsolute)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_TRUE(Path::Parse("/").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc/").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc/..").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc/def").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc/def.ghi").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc/./def.ghi").isAbsolute());
        EXPECT_TRUE(Path::Parse("/abc/../def.ghi").isAbsolute());
    }

    {
        EXPECT_FALSE(Path::Parse("./").isAbsolute());
        EXPECT_FALSE(Path::Parse("./abc").isAbsolute());
        EXPECT_FALSE(Path::Parse("./abc/").isAbsolute());
        EXPECT_FALSE(Path::Parse("./abc/def").isAbsolute());
        EXPECT_FALSE(Path::Parse("./abc/def.ghi").isAbsolute());

        EXPECT_FALSE(Path::Parse("../").isAbsolute());
        EXPECT_FALSE(Path::Parse("../abc").isAbsolute());
        EXPECT_FALSE(Path::Parse("../abc/").isAbsolute());
        EXPECT_FALSE(Path::Parse("../abc/def").isAbsolute());
        EXPECT_FALSE(Path::Parse("../abc/def.ghi").isAbsolute());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, IsRelative)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_TRUE(Path::Parse("./").isRelative());
        EXPECT_TRUE(Path::Parse("./abc").isRelative());
        EXPECT_TRUE(Path::Parse("./abc/").isRelative());
        EXPECT_TRUE(Path::Parse("./abc/def").isRelative());
        EXPECT_TRUE(Path::Parse("./abc/def.ghi").isRelative());

        EXPECT_TRUE(Path::Parse("../").isRelative());
        EXPECT_TRUE(Path::Parse("../abc").isRelative());
        EXPECT_TRUE(Path::Parse("../abc/").isRelative());
        EXPECT_TRUE(Path::Parse("../abc/def").isRelative());
        EXPECT_TRUE(Path::Parse("../abc/def.ghi").isRelative());
    }

    {
        EXPECT_FALSE(Path::Parse("/").isRelative());
        EXPECT_FALSE(Path::Parse("/abc").isRelative());
        EXPECT_FALSE(Path::Parse("/abc/").isRelative());
        EXPECT_FALSE(Path::Parse("/abc/..").isRelative());
        EXPECT_FALSE(Path::Parse("/abc/def").isRelative());
        EXPECT_FALSE(Path::Parse("/abc/def.ghi").isRelative());
        EXPECT_FALSE(Path::Parse("/abc/./def.ghi").isRelative());
        EXPECT_FALSE(Path::Parse("/abc/../def.ghi").isRelative());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, GetParentPath)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_EQ(Path::Parse("/"), Path::Parse("/abc").getParentPath());
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/").getParentPath());
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/..").getParentPath());
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/def").getParentPath());
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc/def.ghi").getParentPath());
        EXPECT_EQ(Path::Parse("/abc/."), Path::Parse("/abc/./def.ghi").getParentPath());
        EXPECT_EQ(Path::Parse("/abc/.."), Path::Parse("/abc/../def.ghi").getParentPath());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, GetLastElement)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_EQ("/", Path::Parse("/").getLastElement());
        EXPECT_EQ("abc", Path::Parse("/abc").getLastElement());
        EXPECT_EQ(".", Path::Parse("/abc/").getLastElement());
        EXPECT_EQ("..", Path::Parse("/abc/..").getLastElement());
        EXPECT_EQ("def", Path::Parse("/abc/def").getLastElement());
        EXPECT_EQ("def.ghi", Path::Parse("/abc/def.ghi").getLastElement());
        EXPECT_EQ("def.ghi", Path::Parse("/abc/./def.ghi").getLastElement());
        EXPECT_EQ("def.ghi", Path::Parse("/abc/../def.ghi").getLastElement());

        EXPECT_EQ(".", Path::Parse("./").getLastElement());
        EXPECT_EQ("abc", Path::Parse("./abc").getLastElement());
        EXPECT_EQ(".", Path::Parse("./abc/").getLastElement());
        EXPECT_EQ("def", Path::Parse("./abc/def").getLastElement());
        EXPECT_EQ("def.ghi", Path::Parse("./abc/def.ghi").getLastElement());

        EXPECT_EQ(".", Path::Parse("../").getLastElement());
        EXPECT_EQ("abc", Path::Parse("../abc").getLastElement());
        EXPECT_EQ(".", Path::Parse("../abc/").getLastElement());
        EXPECT_EQ("def", Path::Parse("../abc/def").getLastElement());
        EXPECT_EQ("def.ghi", Path::Parse("../abc/def.ghi").getLastElement());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, GetNormalizedPath)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_EQ(Path::Parse("/"), Path::Parse("/").getNormalizedPath());
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc").getNormalizedPath());
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app").getNormalizedPath());

        // Changed behaviour when using Boost >=1.87
        // see https://github.com/open-space-collective/open-space-toolkit-core/pull/177
        if ((BOOST_VERSION / 100) % 1000 >= 87)
        {
            EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app/").getNormalizedPath());
        }
        else
        {
            EXPECT_EQ(Path::Parse("/app/"), Path::Parse("/app/").getNormalizedPath());
        }

        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/build").getNormalizedPath());
        EXPECT_EQ(Path::Parse("/app/build/Makefile"), Path::Parse("/app/build/Makefile").getNormalizedPath());

        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app/.").getNormalizedPath());
        EXPECT_EQ(Path::Parse("/"), Path::Parse("/app/..").getNormalizedPath());
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/./build").getNormalizedPath());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, GetAbsolutePath)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_EQ(Path::Parse("/"), Path::Parse("/").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/app/"), Path::Parse("/app/").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/build").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/app/build/Makefile"), Path::Parse("/app/build/Makefile").getAbsolutePath());

        EXPECT_EQ(Path::Parse("/app/."), Path::Parse("/app/.").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/app/.."), Path::Parse("/app/..").getAbsolutePath());
        EXPECT_EQ(Path::Parse("/app/./build"), Path::Parse("/app/./build").getAbsolutePath());
    }

    {
        EXPECT_EQ(Path::Parse("/"), Path::Parse("/").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(Path::Parse("/abc"), Path::Parse("/abc").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(Path::Parse("/app"), Path::Parse("/app").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(Path::Parse("/app/"), Path::Parse("/app/").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(Path::Parse("/app/build"), Path::Parse("/app/build").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(
            Path::Parse("/app/build/Makefile"),
            Path::Parse("/app/build/Makefile").getAbsolutePath(Path::Parse("/app/build"))
        );

        EXPECT_EQ(Path::Parse("/app/."), Path::Parse("/app/.").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(Path::Parse("/app/.."), Path::Parse("/app/..").getAbsolutePath(Path::Parse("/app/build")));
        EXPECT_EQ(Path::Parse("/app/./build"), Path::Parse("/app/./build").getAbsolutePath(Path::Parse("/app/build")));

        EXPECT_EQ(
            Path::Parse("/app/build/Makefile"), Path::Parse("Makefile").getAbsolutePath(Path::Parse("/app/build"))
        );
        EXPECT_EQ(
            Path::Parse("/app/build/./Makefile"), Path::Parse("./Makefile").getAbsolutePath(Path::Parse("/app/build"))
        );

        EXPECT_EQ(
            Path::Parse("/app/docs/index.html"), Path::Parse("index.html").getAbsolutePath(Path::Parse("/app/docs"))
        );
        EXPECT_EQ(
            Path::Parse("/app/docs/./index.html"), Path::Parse("./index.html").getAbsolutePath(Path::Parse("/app/docs"))
        );
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_Path, GetRelativePathTo)
// {

//     using ostk::core::filesystem::Path ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_Path, ToString)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_EQ("/", Path::Parse("/").toString());
        EXPECT_EQ("/abc", Path::Parse("/abc").toString());
        EXPECT_EQ("/abc/", Path::Parse("/abc/").toString());
        EXPECT_EQ("/abc/def", Path::Parse("/abc/def").toString());
        EXPECT_EQ("/abc/def.ghi", Path::Parse("/abc/def.ghi").toString());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, Root)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_NO_THROW(Path::Root());
        EXPECT_EQ("/", Path::Root().toString());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, Current)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_NO_THROW(Path::Current());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Path, Parse)
{
    using ostk::core::filesystem::Path;

    {
        EXPECT_NO_THROW(Path::Parse("/"));
        EXPECT_EQ("/", Path::Parse("/").toString());
    }

    {
        EXPECT_ANY_THROW(Path::Parse(""));
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_Path, Strings)
// {

//     using ostk::core::filesystem::Path ;

//     {

//         FAIL() ;

//     }

// }
