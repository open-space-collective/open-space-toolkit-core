// cxx exception hook for every ostk-* shim: passes "<kind>\x1f<message>\x1f<stack trace>"
// to Rust, decoded by ostk_core::Error.
#pragma once

#include <exception>
#include <string>

#include <OpenSpaceToolkit/Core/Error/Runtime/ToBeImplemented.hpp>
#include <OpenSpaceToolkit/Core/Error/Runtime/Undefined.hpp>
#include <OpenSpaceToolkit/Core/Error/Runtime/Wrong.hpp>
#include <OpenSpaceToolkit/Core/Error/RuntimeError.hpp>

namespace ostk_rs
{

inline std::string encodeError(const char* aKind, const std::string& aMessage, const std::string& aStackTrace = "")
{
    return std::string(aKind) + '\x1f' + aMessage + '\x1f' + aStackTrace;
}

}  // namespace ostk_rs

namespace rust
{
namespace behavior
{

template <typename Try, typename Fail>
static void trycatch(Try&& func, Fail&& fail) noexcept
try
{
    func();
}
// Most derived first. Kinds must match ErrorKind::from_tag (src/error.rs).
catch (const ostk::core::error::runtime::Undefined& error)
{
    fail(ostk_rs::encodeError("undefined", error.getMessage(), error.getStackTrace()).c_str());
}
catch (const ostk::core::error::runtime::Wrong& error)
{
    fail(ostk_rs::encodeError("wrong", error.getMessage(), error.getStackTrace()).c_str());
}
catch (const ostk::core::error::runtime::ToBeImplemented& error)
{
    fail(ostk_rs::encodeError("to_be_implemented", error.getMessage(), error.getStackTrace()).c_str());
}
catch (const ostk::core::error::RuntimeError& error)
{
    fail(ostk_rs::encodeError("runtime", error.getMessage(), error.getStackTrace()).c_str());
}
catch (const std::exception& error)
{
    fail(ostk_rs::encodeError("std", error.what()).c_str());
}
catch (...)
{
    fail(ostk_rs::encodeError("unknown", "unknown C++ exception").c_str());
}

}  // namespace behavior
}  // namespace rust
