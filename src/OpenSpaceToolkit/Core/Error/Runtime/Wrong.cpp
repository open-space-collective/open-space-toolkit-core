/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Error/Runtime/Wrong.hpp>

namespace ostk
{
namespace core
{
namespace error
{
namespace runtime
{

Wrong::Wrong(const String& aVariableName)
    : RuntimeError("{" + aVariableName + "} is wrong.")
{
}

//                                 Wrong::Wrong                                (   const   String& aScope,
//                                                                                 const   String& aVariableName )
//                                 :   RuntimeError(aScope, "{" + aVariableName + "} is wrong.")
// {

// }

Wrong::~Wrong() {}

}  // namespace runtime
}  // namespace error
}  // namespace core
}  // namespace ostk
