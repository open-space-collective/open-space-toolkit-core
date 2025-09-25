/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Sign.hpp>

using ostk::core::type::Sign;

inline void OpenSpaceToolkitCorePy_Type_Sign(pybind11::module& aModule)
{
    using namespace pybind11;

    enum_<Sign>(aModule, "Sign", R"doc(
        Enumeration representing the sign of a number.

        The Sign enum indicates whether a value is positive, negative, or has no sign (zero).
    )doc")
        .value("Undefined", Sign::Undefined, R"doc(
            Undefined sign state.

            Example:
                >>> sign = Sign.Undefined
        )doc")
        .value("Positive", Sign::Positive, R"doc(
            Positive sign (> 0).

            Example:
                >>> sign = Sign.Positive
        )doc")
        .value("Negative", Sign::Negative, R"doc(
            Negative sign (< 0).

            Example:
                >>> sign = Sign.Negative
        )doc")
        .value("NoSign", Sign::None, R"doc(
            No sign (= 0).

            Example:
                >>> sign = Sign.NoSign
        )doc")
        .export_values()

        ;
}
