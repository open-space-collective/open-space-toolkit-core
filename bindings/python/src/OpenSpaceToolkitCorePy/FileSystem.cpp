/// Apache License 2.0

// #include <OpenSpaceToolkitCorePy/FileSystem/SymbolicLink.cpp>
#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

#include <OpenSpaceToolkitCorePy/FileSystem/Directory.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/File.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/Path.cpp>
#include <OpenSpaceToolkitCorePy/FileSystem/PermissionSet.cpp>

using ostk::core::filesystem::Directory;
using ostk::core::filesystem::File;
using ostk::core::filesystem::Path;
using ostk::core::filesystem::PermissionSet;

inline void OpenSpaceToolkitCorePy_FileSystem(nanobind::module_& aModule)
{
    // Create "filesystem" python submodule
    auto filesystem = aModule.def_submodule("filesystem", R"doc(
        File system operations and utilities for Open Space Toolkit.

        This submodule provides classes for working with files, directories, paths,
        and permission sets, enabling cross-platform file system operations.
    )doc");

    nanobind::class_<PermissionSet> permissionSetClass(filesystem, "PermissionSet");
    nanobind::class_<Path> pathClass(filesystem, "Path");
    nanobind::class_<File> fileClass(filesystem, "File");
    nanobind::class_<Directory> directoryClass(filesystem, "Directory");

    // Add custom objects to python "filesystem" submodule
    OpenSpaceToolkitCorePy_FileSystem_PermissionSet(permissionSetClass);
    OpenSpaceToolkitCorePy_FileSystem_Path(pathClass);
    OpenSpaceToolkitCorePy_FileSystem_File(fileClass);
    OpenSpaceToolkitCorePy_FileSystem_Directory(directoryClass);
}
