/// Apache License 2.0

#include <OpenSpaceToolkitCorePy/Type/Integer.cpp>
#include <OpenSpaceToolkitCorePy/Type/Real.cpp>
#include <OpenSpaceToolkitCorePy/Type/Sign.cpp>
#include <OpenSpaceToolkitCorePy/Type/String.cpp>

inline void OpenSpaceToolkitCorePy_Type(pybind11::module& aModule)
{
    // Create "type" python submodule
    auto type = aModule.def_submodule("type");


    // Add custom type to python "type" submodule
    OpenSpaceToolkitCorePy_Type_Sign(type);
    OpenSpaceToolkitCorePy_Type_Integer(type);
    OpenSpaceToolkitCorePy_Type_Real(type);
    OpenSpaceToolkitCorePy_Type_String(type);
}
