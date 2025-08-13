/// Apache License 2.0

#include <stdexcept>  // Required for py::value_error (often through pybind11.h)
#include <string>     // Required for std::string

#include <magic_enum/magic_enum.hpp>

#include <OpenSpaceToolkit/Core/Type/Sign.hpp>

// It's good practice to include pybind11.h directly if using its specific exceptions
#include <pybind11/pybind11.h>  // For py::value_error

namespace py = pybind11;

using ostk::core::type::Sign;

inline void OpenSpaceToolkitCorePy_Type_Sign(pybind11::module& aModule)
{
    py::enum_<Sign>(aModule, "Sign")
        .value("Undefined", Sign::Undefined)
        .value("Positive", Sign::Positive)
        .value("Negative", Sign::Negative)
        .value("NoSign", Sign::None)
        .export_values()
        .def(
            "__str__",
            [](const Sign& aSign)
            {
                return std::string(magic_enum::enum_name(aSign));
            }
        )
        .def_static(
            "from_string",
            [](const std::string& enumString)
            {
                auto result = magic_enum::enum_cast<Sign>(enumString);
                if (result.has_value())
                {
                    return result.value();
                }
                throw py::value_error("Invalid string for Sign enum: " + enumString);
            }
        );
}
