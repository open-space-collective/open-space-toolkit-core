/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, EqualToOperator)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_TRUE(Directory::Path(Path::Parse("/")) == Directory::Path(Path::Parse("/")));
        EXPECT_TRUE(
            Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path/to/directory"))
        );
    }

    {
        EXPECT_FALSE(
            Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path/to/directory/"))
        );
        EXPECT_FALSE(
            Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path/to/directory2"))
        );
        EXPECT_FALSE(
            Directory::Path(Path::Parse("/path/to/directory")) == Directory::Path(Path::Parse("/path2/to/file"))
        );
    }

    {
        EXPECT_FALSE(Directory::Path(Path::Parse("/path/to/directory")) == Directory::Undefined());
        EXPECT_FALSE(Directory::Undefined() == Directory::Path(Path::Parse("/path/to/directory")));
        EXPECT_FALSE(Directory::Undefined() == Directory::Undefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, NotEqualToOperator)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_TRUE(
            Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path/to/directory/"))
        );
        EXPECT_TRUE(
            Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path/to/directory2"))
        );
        EXPECT_TRUE(
            Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path2/to/file"))
        );
    }

    {
        EXPECT_FALSE(Directory::Path(Path::Parse("/")) != Directory::Path(Path::Parse("/")));
        EXPECT_FALSE(
            Directory::Path(Path::Parse("/path/to/directory")) != Directory::Path(Path::Parse("/path/to/directory"))
        );
    }

    {
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")) != Directory::Undefined());
        EXPECT_TRUE(Directory::Undefined() != Directory::Path(Path::Parse("/path/to/directory")));
        EXPECT_TRUE(Directory::Undefined() != Directory::Undefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, StreamOperator)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        const Directory directory = Directory::Path(Path::Parse("/path/to/directory"));

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << directory << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, IsDefined)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_TRUE(Directory::Path(Path::Parse("/")).isDefined());
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory")).isDefined());
        EXPECT_TRUE(Directory::Path(Path::Parse("/path/to/directory/")).isDefined());
    }

    {
        EXPECT_FALSE(Directory::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, Exists)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_TRUE(Directory::Path(Path::Parse("/")).exists());
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr")).exists());
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr/bin")).exists());
    }

    {
        EXPECT_FALSE(Directory::Path(Path::Parse("/skf47hksdjf")).exists());
        EXPECT_FALSE(Directory::Path(Path::Parse("/usr/sdfkjdfg")).exists());
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().exists());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, IsEmpty)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr/games")).isEmpty());
        EXPECT_TRUE(Directory::Path(Path::Parse("/usr/games/")).isEmpty());
    }

    {
        EXPECT_FALSE(Directory::Path(Path::Parse("/")).isEmpty());
        EXPECT_FALSE(Directory::Path(Path::Parse("/usr")).isEmpty());
        EXPECT_FALSE(Directory::Path(Path::Parse("/usr/")).isEmpty());
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().isEmpty());
        EXPECT_ANY_THROW(Directory::Path(Path::Parse("/abc")).isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, ContainsFileWithName)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        const Directory directory = Directory::Path(Path::Parse("/app/include/OpenSpaceToolkit/Core"));

        EXPECT_TRUE(directory.containsFileWithName("Error.hpp"));
        EXPECT_TRUE(directory.containsFileWithName("Utilities.hpp"));

        EXPECT_FALSE(directory.containsFileWithName("Error"));
        EXPECT_FALSE(directory.containsFileWithName("Utilities"));
        EXPECT_FALSE(directory.containsFileWithName("abc"));
    }

    {
        const Directory directory = Directory::Path(Path::Parse("/app/tools/development"));

        EXPECT_ANY_THROW(Directory::Undefined().containsFileWithName("abc"));
        EXPECT_ANY_THROW(directory.containsFileWithName(""));
        EXPECT_ANY_THROW(Directory::Undefined().containsFileWithName("abc"));
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_Directory, ContainsDirectoryWithName)
// {

//     using ostk::core::filesystem::Path ;
//     using ostk::core::filesystem::Directory ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, GetName)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_EQ("/", Directory::Path(Path::Parse("/")).getName());
        EXPECT_EQ("usr", Directory::Path(Path::Parse("/usr")).getName());
        EXPECT_EQ("usr", Directory::Path(Path::Parse("/usr/")).getName());
        EXPECT_EQ("games", Directory::Path(Path::Parse("/usr/games")).getName());
        EXPECT_EQ("games", Directory::Path(Path::Parse("/usr/games/")).getName());
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().getName());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, GetPath)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_EQ(Path::Parse("/"), Directory::Path(Path::Parse("/")).getPath());
        EXPECT_EQ(Path::Parse("/usr"), Directory::Path(Path::Parse("/usr")).getPath());
        EXPECT_EQ(Path::Parse("/usr/"), Directory::Path(Path::Parse("/usr/")).getPath());
        EXPECT_EQ(Path::Parse("/usr/games"), Directory::Path(Path::Parse("/usr/games")).getPath());
        EXPECT_EQ(Path::Parse("/usr/games/"), Directory::Path(Path::Parse("/usr/games/")).getPath());
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().getPath());
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_Directory, GetPermissions)
// {

//     using ostk::core::filesystem::PermissionSet ;
//     using ostk::core::filesystem::Path ;
//     using ostk::core::filesystem::Directory ;

//     {

//         const Path path = Path::Parse("/app/build") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RWX(), directory.getPermissions()) ;

//     }

//     {

//         const Path path = Path::Parse("/app/build/") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RWX(), directory.getPermissions()) ;

//     }

//     {

//         const Path path = Path::Parse("/boot") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RX(), directory.getPermissions()) ;

//     }

//     {

//         const Path path = Path::Parse("/boot/") ;

//         const Directory directory = Directory::Path(path) ;

//         EXPECT_EQ(PermissionSet::RX(), directory.getPermissions()) ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().getPermissions()) ;
//         EXPECT_ANY_THROW(Directory::Path(Path::Parse("/abc")).getPermissions()) ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, GetParentDirectory)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/build")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")), Directory::Path(Path::Parse("/app/build/")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")),
            Directory::Path(Path::Parse("/app/does-not-exist")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")),
            Directory::Path(Path::Parse("/app/does-not-exist/")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")),
            Directory::Path(Path::Parse("/app/does-not-exist/.")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")),
            Directory::Path(Path::Parse("/app//does-not-exist")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")),
            Directory::Path(Path::Parse("/app//does-not-exist/")).getParentDirectory()
        );
        EXPECT_EQ(
            Directory::Path(Path::Parse("/app")),
            Directory::Path(Path::Parse("/app//does-not-exist/.")).getParentDirectory()
        );
        EXPECT_EQ(Directory::Path(Path::Parse("/")), Directory::Path(Path::Parse("/")).getParentDirectory());
        EXPECT_EQ(
            Directory::Path(Path::Parse("/")), Directory::Path(Path::Parse("/app/build/..")).getParentDirectory()
        );
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().getParentDirectory());
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_Directory, GetFiles)
// {

//     using ostk::core::filesystem::Path ;
//     using ostk::core::filesystem::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().getFiles()) ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, GetDirectories)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        const Directory directory = Directory::Path(Path::Parse("/app/tools"));

        const Array<Directory> subDirectories = directory.getDirectories();

        EXPECT_EQ(1, subDirectories.getSize());

        const Array<String> subDirectoryNames = subDirectories.map<String>(
            [](const Directory& aDirectory) -> String
            {
                return aDirectory.getName();
            }
        );

        const Array<String> referenceSubDirectoryNames = {"cmake"};

        EXPECT_EQ(referenceSubDirectoryNames, subDirectoryNames);
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().getDirectories());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, ToString)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_EQ("/app/build", Directory::Path(Path::Parse("/app/build")).toString());
        EXPECT_EQ("/app/build/", Directory::Path(Path::Parse("/app/build/")).toString());
        EXPECT_EQ("/app//does-not-exist", Directory::Path(Path::Parse("/app//does-not-exist")).toString());
        EXPECT_EQ("/", Directory::Path(Path::Parse("/")).toString());
        EXPECT_EQ("/app/build/..", Directory::Path(Path::Parse("/app/build/..")).toString());
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().toString());
    }
}

// TEST (OpenSpaceToolkit_Core_FileSystem_Directory, RenameTo)
// {

//     using ostk::core::filesystem::Path ;
//     using ostk::core::filesystem::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().renameTo()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Core_FileSystem_Directory, CopyToDirectory)
// {

//     using ostk::core::filesystem::Path ;
//     using ostk::core::filesystem::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().copyToDirectory()) ;

//     }

// }

// TEST (OpenSpaceToolkit_Core_FileSystem_Directory, MoveToDirectory)
// {

//     using ostk::core::filesystem::Path ;
//     using ostk::core::filesystem::Directory ;

//     {

//         FAIL() ;

//     }

//     {

//         EXPECT_ANY_THROW(Directory::Undefined().moveToDirectory()) ;

//     }

// }

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, Create)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        Directory directory = Directory::Path(Path::Parse("/tmp/open-space-toolkit-core-filesystem-directory-create"));

        EXPECT_FALSE(directory.exists());

        directory.create();

        EXPECT_TRUE(directory.exists());

        EXPECT_ANY_THROW(directory.create());

        directory.remove();
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().create());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, Remove)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        Directory directory = Directory::Path(Path::Parse("/tmp/open-space-toolkit-core-filesystem-directory-remove"));

        directory.create();

        EXPECT_TRUE(directory.exists());

        directory.remove();

        EXPECT_FALSE(directory.exists());

        EXPECT_ANY_THROW(directory.remove());
    }

    {
        EXPECT_ANY_THROW(Directory::Undefined().remove());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, Undefined)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_NO_THROW(Directory::Undefined());
        EXPECT_FALSE(Directory::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, Root)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        EXPECT_NO_THROW(Directory::Root());
        EXPECT_TRUE(Directory::Root().isDefined());
        EXPECT_EQ(Path::Parse("/"), Directory::Root().getPath());
    }
}

TEST(OpenSpaceToolkit_Core_FileSystem_Directory, Path)
{
    using ostk::core::filesystem::Path;
    using ostk::core::filesystem::Directory;

    {
        const Path path = Path::Parse("/path/to/directory");

        EXPECT_TRUE(Directory::Path(path).isDefined());

        EXPECT_EQ(path, Directory::Path(path).getPath());
    }

    {
        const Path path = Path::Parse("/path/to/directory/");

        EXPECT_TRUE(Directory::Path(path).isDefined());

        EXPECT_EQ(path, Directory::Path(path).getPath());
    }

    {
        EXPECT_ANY_THROW(Directory::Path(Path::Parse("")));
        EXPECT_ANY_THROW(Directory::Path(Path::Undefined()));
    }
}
