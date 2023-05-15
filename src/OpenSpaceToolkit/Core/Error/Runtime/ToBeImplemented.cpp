/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error/Runtime/ToBeImplemented.hpp>

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

ToBeImplemented::ToBeImplemented()
    : RuntimeError("This is not yet implemented.")
{
}

ToBeImplemented::ToBeImplemented(const String& aFunctionName)
    : RuntimeError("{" + aFunctionName + "} is not yet implemented.")
{
}

//                                 ToBeImplemented::ToBeImplemented            (   const   String& aScope,
//                                                                                 const   String& aFunctionName )
//                                 :   RuntimeError(aScope, "{" + aFunctionName + "} is not yet implemented.")
// {

// }

ToBeImplemented::~ToBeImplemented() {}

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk
