/// Apache License 2.0

#include <nanobind/stl/bind_map.h>
#include <nanobind/stl/bind_vector.h>

#include <OpenSpaceToolkit/Core/Container/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

using ostk::core::container::Dictionary;
using ostk::core::container::Object;

Object objectFromPythonHandle(const nanobind::handle& anObject)
{
    using namespace nanobind;

    using ostk::core::container::Array;

    if (isinstance<bool_>(anObject))
    {
        return Object::Boolean(nanobind::cast<bool>(anObject));
    }

    if (isinstance<int_>(anObject))
    {
        return Object::Integer(nanobind::cast<int>(anObject));
    }

    if (isinstance<float_>(anObject))
    {
        return Object::Real(nanobind::cast<double>(anObject));
    }

    if (isinstance<str>(anObject))
    {
        return Object::String(nanobind::cast<std::string>(anObject));
    }

    if (isinstance<list>(anObject))
    {
        Array<Object> array = Array<Object>::Empty();

        for (const auto& item : anObject)
        {
            array.add(objectFromPythonHandle(item));
        }

        return Object::Array(array);
    }

    if (isinstance<dict>(anObject))
    {
        Dictionary dictionary = Dictionary::Empty();

        for (const auto& [key, value] : nanobind::cast<dict>(anObject))
        {
            dictionary[nanobind::cast<std::string>(key)] = objectFromPythonHandle(value);
        }

        return Object::Dictionary(dictionary);
    }

    throw ostk::core::error::RuntimeError("Object type is wrong.");
}

inline void OpenSpaceToolkitCorePy_Container_Dictionary(nanobind::class_<Dictionary>& dictionaryClass)
{
    using namespace nanobind;

    using ostk::core::type::String;

    dictionaryClass

        // https://github.com/pybind/nanobind/blob/e3aa215b020886d648add951186052c619c3cf9d/include/nanobind/stl_bind.h

        // nanobind has no `init(factory)`; a placement-new `__init__` is the equivalent.
        .def(
            "__init__",
            [](Dictionary* aDictionaryPtr, const dict& aDictionary)
            {
                Dictionary dictionary = Dictionary::Empty();

                for (const auto& [key, value] : aDictionary)
                {
                    dictionary[nanobind::cast<std::string>(key)] = objectFromPythonHandle(value);
                }

                new (aDictionaryPtr) Dictionary(dictionary);
            }
        )

        .def(
            "__eq__",
            [](const Dictionary& self, const Dictionary& other)
            {
                return self == other;
            },
            nanobind::is_operator()
        )
        .def(
            "__ne__",
            [](const Dictionary& self, const Dictionary& other)
            {
                return self != other;
            },
            nanobind::is_operator()
        )

        .def(
            "__bool__",
            [](const Dictionary& aDictionary) -> bool
            {
                return !aDictionary.isEmpty();
            }
        )
        .def("__len__", &Dictionary::getSize)

        .def(
            "__iter__",
            [](const Dictionary& aDictionary)
            {
                return make_iterator<rv_policy::reference_internal>(
                    handle(), "DictionaryIterator", aDictionary.begin(), aDictionary.end()
                );
            },
            keep_alive<0, 1>()
        )
        .def("__contains__", &Dictionary::hasValueForKey)
        .def("__getitem__", overload_cast<const String&>(&Dictionary::operator[]))
        // .def("__delitem__", ...)

        // .def("keys", ...)
        // .def("values", ...)
        // .def("items", ...)

        .def(
            "__str__",
            [](const Dictionary& aDictionary) -> std::string
            {
                return Object::Dictionary(aDictionary).toString(Object::Format::JSON);
            }
        )
        .def(
            "__repr__",
            [](const Dictionary& aDictionary) -> std::string
            {
                return Object::Dictionary(aDictionary).toString(Object::Format::JSON);
            }
        )

        .def("is_empty", &Dictionary::isEmpty)
        .def("has_value_for_key", &Dictionary::hasValueForKey, arg("key"))
        .def("get_size", &Dictionary::getSize)
        .def("add_value_for_key", &Dictionary::addValueForKey, arg("value"), arg("key"))

        .def_static("empty", &Dictionary::Empty)
        .def_static("parse", &Dictionary::Parse, arg("string"), arg("format"))

        ;

    class_<Dictionary::ConstIterator>(dictionaryClass, "ConstIterator")

        .def(
            "__eq__",
            [](const Dictionary::ConstIterator& self, const Dictionary::ConstIterator& other)
            {
                return self == other;
            },
            nanobind::is_operator()
        )
        .def(
            "__ne__",
            [](const Dictionary::ConstIterator& self, const Dictionary::ConstIterator& other)
            {
                return self != other;
            },
            nanobind::is_operator()
        )

        .def("access_key", &Dictionary::ConstIterator::accessKey, rv_policy::reference)
        .def("access_value", &Dictionary::ConstIterator::accessValue, rv_policy::reference)

        ;
}
