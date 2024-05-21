/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Sign.hpp>

using ostk::core::type::Sign;

inline void OpenSpaceToolkitCorePy_Type_Sign(pybind11::module& aModule)
{
    using namespace pybind11;

    enum_<Sign>(aModule, "Sign")
        .value("Undefined", Sign::Undefined)
        .value("Positive", Sign::Positive)
        .value("Negative", Sign::Negative)
        .value("NoSign", Sign::None)
        .export_values()

        ;
}
