/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error/Runtime/Undefined.hpp>

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

Undefined::Undefined(const String& aVariableName)
    : RuntimeError("{" + aVariableName + "} is undefined.")
{
}

//                                 Undefined::Undefined                        (   const   String& aScope,
//                                                                                 const   String& aVariableName )
//                                 :   RuntimeError(aScope, "{" + aVariableName + "} is undefined.")
// {

// }

Undefined::~Undefined() {}

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk
