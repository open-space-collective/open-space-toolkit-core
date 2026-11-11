// See test_support.rs.
#pragma once

#include "ostk_rs/cxx_exceptions.hpp"
#include "rust/cxx.h"

namespace ostk_rs
{
namespace core
{
namespace test_support
{

rust::String path_round_trip(rust::Str path);
rust::String file_round_trip(rust::Str path);
rust::String directory_round_trip(rust::Str path);
rust::Vec<double> f64_array_round_trip(rust::Slice<const double> values);
rust::Vec<size_t> string_array_lengths(rust::Slice<const rust::String> values);

}  // namespace test_support
}  // namespace core
}  // namespace ostk_rs
