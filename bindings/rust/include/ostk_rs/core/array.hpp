// Array<T> <-> Rust slice / Vec conversions for ostk-* shims (value types).
#pragma once

#include <OpenSpaceToolkit/Core/Container/Array.hpp>

#include "rust/cxx.h"

namespace ostk_rs
{
namespace core
{

/// Converts each element with `convert`.
template <typename To, typename From, typename Convert>
ostk::core::container::Array<To> toArray(rust::Slice<const From> aSlice, Convert convert)
{
    ostk::core::container::Array<To> array;
    array.reserve(aSlice.size());
    for (const From& element : aSlice)
    {
        array.push_back(convert(element));
    }
    return array;
}

template <typename T>
ostk::core::container::Array<T> toArray(rust::Slice<const T> aSlice)
{
    return toArray<T>(
        aSlice,
        [](const T& element)
        {
            return element;
        }
    );
}

/// Converts each element with `convert`.
template <typename To, typename From, typename Convert>
rust::Vec<To> toVec(const ostk::core::container::Array<From>& anArray, Convert convert)
{
    rust::Vec<To> vec;
    vec.reserve(anArray.size());
    for (const From& element : anArray)
    {
        vec.push_back(convert(element));
    }
    return vec;
}

template <typename T>
rust::Vec<T> toVec(const ostk::core::container::Array<T>& anArray)
{
    return toVec<T>(
        anArray,
        [](const T& element)
        {
            return element;
        }
    );
}

}  // namespace core
}  // namespace ostk_rs
