/// Apache License 2.0

#include <OpenSpaceToolkitCorePy/Containers/Array.cpp>
#include <OpenSpaceToolkitCorePy/Containers/Dictionary.cpp>
#include <OpenSpaceToolkitCorePy/Containers/Object.cpp>

inline void OpenSpaceToolkitCorePy_Containers(pybind11::module& aModule)
{
    // Create "containers" python submodule
    auto containers = aModule.def_submodule("containers");

    // Add __path__ attribute for "containers" submodule
    containers.attr("__path__") = "ostk.core.containers";

    // Add objects to python "containers" submodules
    OpenSpaceToolkitCorePy_Containers_Array(containers);
    OpenSpaceToolkitCorePy_Containers_Object(containers);
    OpenSpaceToolkitCorePy_Containers_Dictionary(containers);
}
