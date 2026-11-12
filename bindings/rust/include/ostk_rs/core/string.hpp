// String conversions for ostk-* shims.
#pragma once

#include <string>

#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include "rust/cxx.h"

namespace ostk_rs
{
namespace core
{

inline ostk::core::type::String toOstkString(rust::Str aString)
{
    return ostk::core::type::String(std::string(aString));
}

inline rust::String toRustString(const std::string& aString)
{
    return rust::String(aString);
}

}  // namespace core
}  // namespace ostk_rs
