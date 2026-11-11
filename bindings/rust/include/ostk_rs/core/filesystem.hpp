// Path / File / Directory from the UTF-8 paths that cross the bridge
// (see ostk_core::filesystem::to_utf8).
#pragma once

#include <OpenSpaceToolkit/Core/FileSystem/Directory.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

#include "ostk_rs/core/string.hpp"

#include "rust/cxx.h"

namespace ostk_rs
{
namespace core
{

inline ostk::core::filesystem::Path toPath(rust::Str aPath)
{
    return ostk::core::filesystem::Path::Parse(toOstkString(aPath));
}

inline ostk::core::filesystem::File toFile(rust::Str aPath)
{
    return ostk::core::filesystem::File::Path(toPath(aPath));
}

inline ostk::core::filesystem::Directory toDirectory(rust::Str aPath)
{
    return ostk::core::filesystem::Directory::Path(toPath(aPath));
}

inline rust::String toRustPath(const ostk::core::filesystem::Path& aPath)
{
    return toRustString(aPath.toString());
}

inline rust::String toRustPath(const ostk::core::filesystem::File& aFile)
{
    return toRustPath(aFile.getPath());
}

inline rust::String toRustPath(const ostk::core::filesystem::Directory& aDirectory)
{
    return toRustPath(aDirectory.getPath());
}

}  // namespace core
}  // namespace ostk_rs
