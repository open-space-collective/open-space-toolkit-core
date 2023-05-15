/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Types/Sign.hpp>

inline void OpenSpaceToolkitCorePy_Types_Sign(pybind11::module& aModule)
{
    using namespace pybind11;

    using ostk::core::types::Sign;

    enum_<Sign>(aModule, "Sign")
        .value("Undefined", Sign::Undefined)
        .value("Positive", Sign::Positive)
        .value("Negative", Sign::Negative)
        .value("NoSign", Sign::None)
        .export_values()

        ;
}
