/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_FileSystem_File, EqualToOperator)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_TRUE(File::Path(Path::Parse("/")) == File::Path(Path::Parse("/")));
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path/to/file")));
    }

    {
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path/to/file/")));
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path/to/file2")));
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Path(Path::Parse("/path2/to/file")));
    }

    {
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) == File::Undefined());
        EXPECT_FALSE(File::Undefined() == File::Path(Path::Parse("/path/to/file")));
        EXPECT_FALSE(File::Undefined() == File::Undefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, NotEqualToOperator)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path/to/file/")));
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path/to/file2")));
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path2/to/file")));
    }

    {
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")) != File::Undefined());
        EXPECT_TRUE(File::Undefined() != File::Path(Path::Parse("/path/to/file")));
        EXPECT_TRUE(File::Undefined() != File::Undefined());
    }

    {
        EXPECT_FALSE(File::Path(Path::Parse("/")) != File::Path(Path::Parse("/")));
        EXPECT_FALSE(File::Path(Path::Parse("/path/to/file")) != File::Path(Path::Parse("/path/to/file")));
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, StreamOperator)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        const File file = File::Path(Path::Parse("/path/to/file"));

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << file << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, FileStreamOperator)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/tmp/file.txt"));

        file.create();

        file.open(File::OpenMode::Truncate);

        file << "Hello World!";

        file.close();

        EXPECT_EQ("Hello World!", file.getContents());

        file.remove();
    }

    {
        EXPECT_ANY_THROW(File::Undefined() << "Hello World!");
        EXPECT_ANY_THROW(File::Path(Path::Parse("/tmp/does-not-exist.txt")) << "Hello World!");
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, IsDefined)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_TRUE(File::Path(Path::Parse("/")).isDefined());
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file")).isDefined());
        EXPECT_TRUE(File::Path(Path::Parse("/path/to/file/")).isDefined());
    }

    {
        EXPECT_FALSE(File::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, Exists)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_TRUE(File::Path(Path::Parse("/")).exists());
        EXPECT_TRUE(File::Path(Path::Parse("/usr")).exists());
        EXPECT_TRUE(File::Path(Path::Parse("/app/CMakeLists.txt")).exists());
    }

    {
        EXPECT_FALSE(File::Path(Path::Parse("/skf47hksdjf")).exists());
        EXPECT_FALSE(File::Path(Path::Parse("/usr/sdfkjdfg")).exists());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().exists());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, IsOpen)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/app/CMakeLists.txt"));

        EXPECT_FALSE(file.isOpen());

        file.open(File::OpenMode::Read);

        EXPECT_TRUE(file.isOpen());

        file.close();

        EXPECT_FALSE(file.isOpen());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().isOpen());
        EXPECT_ANY_THROW(File::Path(Path::Parse("/tmp/does-not-exist.txt")).isOpen());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, GetName)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    // With extension

    {
        EXPECT_EQ("/", File::Path(Path::Parse("/")).getName(true));
        EXPECT_EQ("usr", File::Path(Path::Parse("/usr")).getName(true));
        EXPECT_EQ("CMakeLists.txt", File::Path(Path::Parse("/app/CMakeLists.txt")).getName(true));
        EXPECT_EQ("CMakeLists.txt", File::Path(Path::Parse("./CMakeLists.txt")).getName(true));
        EXPECT_EQ("CMakeLists.txt", File::Path(Path::Parse("../CMakeLists.txt")).getName(true));
    }

    // Without extension

    {
        EXPECT_EQ("/", File::Path(Path::Parse("/")).getName(false));
        EXPECT_EQ("usr", File::Path(Path::Parse("/usr")).getName(false));
        EXPECT_EQ("CMakeLists", File::Path(Path::Parse("/app/CMakeLists.txt")).getName(false));
        EXPECT_EQ("CMakeLists", File::Path(Path::Parse("./CMakeLists.txt")).getName(false));
        EXPECT_EQ("CMakeLists", File::Path(Path::Parse("../CMakeLists.txt")).getName(false));
    }

    {
        EXPECT_ANY_THROW(File::Undefined().getName());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, GetExtension)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_TRUE(File::Path(Path::Parse("/")).exists());
        EXPECT_TRUE(File::Path(Path::Parse("/usr")).exists());
        EXPECT_TRUE(File::Path(Path::Parse("/app/CMakeLists.txt")).exists());
    }

    {
        EXPECT_FALSE(File::Path(Path::Parse("/skf47hksdjf")).exists());
        EXPECT_FALSE(File::Path(Path::Parse("/usr/sdfkjdfg")).exists());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().exists());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, GetPath)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        const Path path = Path::Parse("/path/to/file");

        EXPECT_EQ(path, File::Path(path).getPath());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().getPath());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, GetPermissions)
{
    using ostk::core::fs::PermissionSet;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        const Path path = Path::Parse("/app/build");

        const File file = File::Path(path);

        EXPECT_EQ(PermissionSet::RWX(), file.getPermissions());
    }

    {
        const Path path = Path::Parse("/app/build/Makefile");

        const File file = File::Path(path);

        EXPECT_EQ(PermissionSet::RW(), file.getPermissions());
    }

    {
        const Path path = Path::Parse("/app/bin/open-space-toolkit-core.test");

        const File file = File::Path(path);

        EXPECT_EQ(PermissionSet::RWX(), file.getPermissions());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().getPermissions());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, GetParentDirectory)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;
    using ostk::core::fs::Directory;

    {
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")), File::Path(Path::Parse("/app/CMakeLists.txt")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/path/to")), File::Path(Path::Parse("/path/to/file")).getParentDirectory()
        );
    }

    {
        EXPECT_ANY_THROW(File::Undefined().getParentDirectory());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, ToString)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_EQ("CMakeLists.txt", File::Path(Path::Parse("CMakeLists.txt")).toString());
        EXPECT_EQ("./CMakeLists.txt", File::Path(Path::Parse("./CMakeLists.txt")).toString());
        EXPECT_EQ("/app/CMakeLists.txt", File::Path(Path::Parse("/app/CMakeLists.txt")).toString());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().toString());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, Open)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/app/CMakeLists.txt"));

        EXPECT_FALSE(file.isOpen());

        file.open(File::OpenMode::Read);

        EXPECT_TRUE(file.isOpen());

        EXPECT_ANY_THROW(file.open(File::OpenMode::Read));
    }

    {
        EXPECT_ANY_THROW(File::Undefined().open(File::OpenMode::Read));
        EXPECT_ANY_THROW(File::Path(Path::Parse("/tmp/does-not-exist.txt")).open(File::OpenMode::Read));
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, Close)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/app/CMakeLists.txt"));

        EXPECT_FALSE(file.isOpen());

        file.open(File::OpenMode::Read);

        EXPECT_TRUE(file.isOpen());

        file.close();

        EXPECT_FALSE(file.isOpen());

        EXPECT_ANY_THROW(file.close());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().close());
        EXPECT_ANY_THROW(File::Path(Path::Parse("/tmp/does-not-exist.txt")).close());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, AccessStream)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/tmp/file.txt"));

        file.create();

        file.open(File::OpenMode::Truncate);

        file.accessStream() << "Hello World!";

        file.close();

        EXPECT_EQ("Hello World!", file.getContents());

        file.remove();
    }

    {
        EXPECT_ANY_THROW(File::Undefined().accessStream());
        EXPECT_ANY_THROW(File::Path(Path::Parse("/tmp/does-not-exist.txt")).accessStream());
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_File, RenameTo)
// {

//     using ostk::core::fs::Path ;
//     using ostk::core::fs::File ;

//     {

//         FAIL() ;

//     }

// }

// TEST (OpenSpaceToolkit_Core_FileSystem_File, CopyToDirectory)
// {

//     using ostk::core::fs::Path ;
//     using ostk::core::fs::File ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_File, MoveToDirectory)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;
    using ostk::core::fs::Directory;

    {
        File file = File::Path(Path::Parse("/tmp/file"));
        Directory directory = Directory::Path(Path::Parse("/tmp/destination"));

        file.create();
        directory.create();

        file.moveToDirectory(directory);

        EXPECT_EQ("/tmp/destination/file", file.getPath().toString());

        file.remove();
        directory.remove();
    }

    {
        File file = File::Path(Path::Parse("/tmp/file"));
        Directory directory = Directory::Path(Path::Parse("/tmp/destination"));

        file.create();
        directory.create();

        EXPECT_ANY_THROW(file.moveToDirectory(Directory::Undefined()));
        EXPECT_ANY_THROW(File::Undefined().moveToDirectory(directory));
        EXPECT_ANY_THROW(File::Undefined().moveToDirectory(Directory::Undefined()));

        file.remove();
        directory.remove();
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, Create)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/tmp/file"));

        EXPECT_FALSE(file.exists());

        file.create();

        EXPECT_TRUE(file.exists());

        EXPECT_ANY_THROW(file.create());

        file.remove();
    }

    {
        EXPECT_ANY_THROW(File::Undefined().create());
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_File, Clear)
// {

//     using ostk::core::fs::Path ;
//     using ostk::core::fs::File ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_File, Remove)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        File file = File::Path(Path::Parse("/tmp/open-space-toolkit-core-filesystem-file-remove"));

        file.create();

        EXPECT_TRUE(file.exists());

        file.remove();

        EXPECT_FALSE(file.exists());

        EXPECT_ANY_THROW(file.remove());
    }

    {
        EXPECT_ANY_THROW(File::Undefined().remove());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, Undefined)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        EXPECT_NO_THROW(File::Undefined());
        EXPECT_FALSE(File::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_File, Path)
{
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        const Path path = Path::Parse("/path/to/file");

        EXPECT_TRUE(File::Path(path).isDefined());

        EXPECT_EQ(path, File::Path(path).getPath());
    }

    {
        const Path path = Path::Parse("/path/to/file/");

        EXPECT_TRUE(File::Path(path).isDefined());

        EXPECT_EQ(path, File::Path(path).getPath());
    }

    {
        EXPECT_ANY_THROW(File::Path(Path::Parse("")));
        EXPECT_ANY_THROW(File::Path(Path::Undefined()));
    }
}
