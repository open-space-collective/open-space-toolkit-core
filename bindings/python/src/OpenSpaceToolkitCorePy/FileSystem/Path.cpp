/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/Path.hpp>

using ostk::core::filesystem::Path;

inline void OpenSpaceToolkitCorePy_FileSystem_Path(pybind11::class_<Path>& pathClass)
{
    using namespace pybind11;

    pathClass

        // Define init method using pybind11 "init" convenience method
        // No init here

        // Define methods
        .def(self == self)
        .def(self != self)

        .def(self + self)
        .def(self += self)

        // .def("__str__", +[] (const ostk::core::filesystem::Path& aPath) -> str { return aPath.toString() ; })
        // .def("__repr__", +[] (const ostk::core::filesystem::Path& aPath) -> str { return aPath.toString() ; })
        .def("__str__", &(shiftToString<Path>))
        .def("__repr__", &(shiftToString<Path>))

        .def("is_defined", &Path::isDefined)
        .def("is_absolute", &Path::isAbsolute)
        .def("is_relative", &Path::isRelative)
        .def("get_parent_path", &Path::getParentPath)
        .def("get_last_element", &Path::getLastElement)
        .def("get_normalized_path", &Path::getNormalizedPath)
        .def("get_absolute_path", &Path::getAbsolutePath, arg_v("base_path", Path::Current(), "Path.current()"))
        // .def("get_relative_path_to", &Path::getRelativePathTo)
        .def("to_string", &Path::toString)

        // Define static methods
        .def_static("undefined", &Path::Undefined)
        .def_static("root", &Path::Root)
        .def_static("current", &Path::Current)
        .def_static("parse", &Path::Parse)
        // .def_static("strings", &Path::Strings)

        ;
}
