#include "ostk-core/src/test_support.h"

#include "ostk_rs/core/array.hpp"
#include "ostk_rs/core/filesystem.hpp"
#include "ostk_rs/core/string.hpp"

#include "ostk-core/src/test_support.rs.h"

namespace ostk_rs
{
namespace core
{
namespace test_support
{

rust::String path_round_trip(rust::Str path)
{
    return toRustPath(toPath(path));
}

rust::String file_round_trip(rust::Str path)
{
    return toRustPath(toFile(path));
}

rust::String directory_round_trip(rust::Str path)
{
    return toRustPath(toDirectory(path));
}

rust::Vec<double> f64_array_round_trip(rust::Slice<const double> values)
{
    return toVec(toArray(values));
}

rust::Vec<size_t> string_array_lengths(rust::Slice<const rust::String> values)
{
    const auto strings = toArray<ostk::core::type::String>(
        values,
        [](const rust::String& value)
        {
            return toOstkString(value);
        }
    );
    return toVec<size_t>(
        strings,
        [](const ostk::core::type::String& value)
        {
            return value.size();
        }
    );
}

}  // namespace test_support
}  // namespace core
}  // namespace ostk_rs
