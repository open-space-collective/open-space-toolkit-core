/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>

#include <OpenSpaceToolkitCorePy/Container/Array.cpp>
#include <OpenSpaceToolkitCorePy/Container/Dictionary.cpp>
#include <OpenSpaceToolkitCorePy/Container/Object.cpp>

inline void OpenSpaceToolkitCorePy_Container(pybind11::module& aModule)
{
    using ostk::core::container::Dictionary;
    using ostk::core::container::Object;

    // Create "container" python submodule
    auto container = aModule.def_submodule("container");

    pybind11::class_<Dictionary> dictionaryClass(container, "Dictionary");
    pybind11::class_<Object> objectClass(container, "Object");

    // Add objects to python "container" submodules
    OpenSpaceToolkitCorePy_Container_Array(container);
    OpenSpaceToolkitCorePy_Container_Object(objectClass);
    OpenSpaceToolkitCorePy_Container_Dictionary(dictionaryClass);
}
