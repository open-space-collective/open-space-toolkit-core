/// Apache License 2.0

#include <OpenSpaceToolkitCorePy/Container/Array.cpp>
#include <OpenSpaceToolkitCorePy/Container/Dictionary.cpp>
#include <OpenSpaceToolkitCorePy/Container/Object.cpp>

inline void OpenSpaceToolkitCorePy_Container(pybind11::module& aModule)
{
    // Create "container" python submodule
    auto container = aModule.def_submodule("container");


    // Add objects to python "container" submodules
    OpenSpaceToolkitCorePy_Container_Array(container);
    OpenSpaceToolkitCorePy_Container_Object(container);
    OpenSpaceToolkitCorePy_Container_Dictionary(container);
}
