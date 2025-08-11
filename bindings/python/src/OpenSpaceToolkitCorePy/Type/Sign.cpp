/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Type/Sign.hpp>

#include <magic_enum.hpp>

#include <string> // Required for std::string
#include <stdexcept> // Required for py::value_error (often through pybind11.h)

// It's good practice to include pybind11.h directly if using its specific exceptions
#include <pybind11/pybind11.h> // For py::value_error

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
        .def("__str__", [](const Sign& aSign) { return std::string(magic_enum::enum_name(aSign)); })
        .def_static("from_string", [](const std::string& enumString) {
            auto result = magic_enum::enum_cast<Sign>(enumString);
            if (result.has_value())
            {
                return result.value();
            }
            throw py::value_error("Invalid string for Sign enum: " + enumString);
        });
}
