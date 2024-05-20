/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/Sign.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <OpenSpaceToolkitCorePy/Type/Integer.cpp>
#include <OpenSpaceToolkitCorePy/Type/Real.cpp>
#include <OpenSpaceToolkitCorePy/Type/Sign.cpp>
#include <OpenSpaceToolkitCorePy/Type/String.cpp>

inline void OpenSpaceToolkitCorePy_Type(pybind11::module& aModule)
{
    using ostk::core::type::Integer;
    using ostk::core::type::Real;
    using ostk::core::type::Sign;
    using ostk::core::type::String;

    // Create "type" python submodule
    auto type = aModule.def_submodule("type");

    pybind11::class_<Integer> integerClass(type, "Integer");
    pybind11::class_<Real> realClass(type, "Real");
    pybind11::class_<String> stringClass(type, "String");

    // Add custom type to python "type" submodule
    OpenSpaceToolkitCorePy_Type_Sign(aModule);
    OpenSpaceToolkitCorePy_Type_Integer(integerClass);
    OpenSpaceToolkitCorePy_Type_Real(realClass);
    OpenSpaceToolkitCorePy_Type_String(stringClass);
}
