////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           bindings/python/src/OpenSpaceToolkitCorePy/Containers/Dictionary.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <pybind11/stl_bind.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using ostk::core::ctnr::Object ;
using ostk::core::ctnr::Dictionary ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Object                          objectFromPythonHandle                      (   const   pybind11::handle&           anObject                                    )
{

    using namespace pybind11 ;

    using ostk::core::ctnr::Array ;

    if (isinstance<bool_>(anObject))
    {
        return Object::Boolean(anObject.cast<bool>()) ;
    }

    if (isinstance<int_>(anObject))
    {
        return Object::Integer(anObject.cast<int>()) ;
    }

    if (isinstance<float_>(anObject))
    {
        return Object::Real(anObject.cast<double>()) ;
    }

    if (isinstance<str>(anObject))
    {
        return Object::String(anObject.cast<std::string>()) ;
    }

    if (isinstance<list>(anObject))
    {

        Array<Object> array = Array<Object>::Empty() ;

        for (const auto& item : anObject)
        {
            array.add(objectFromPythonHandle(item)) ;
        }

        return Object::Array(array) ;

    }

    if (isinstance<dict>(anObject))
    {

        Dictionary dictionary = Dictionary::Empty() ;

        for (const auto& [key, value] : anObject.cast<dict>())
        {
            dictionary[key.cast<std::string>()] = objectFromPythonHandle(value) ;
        }

        return Object::Dictionary(dictionary) ;

    }

    throw ostk::core::error::RuntimeError("Object type is wrong.") ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     OpenSpaceToolkitCorePy_Containers_Dictionary (       pybind11::module&              aModule                                     )
{

    using namespace pybind11 ;

    using ostk::core::types::String ;
    using ostk::core::ctnr::Object ;
    using ostk::core::ctnr::Dictionary ;

    class_<Dictionary> dictionary_class(aModule, "Dictionary") ;

    dictionary_class

        // https://github.com/pybind/pybind11/blob/e3aa215b020886d648add951186052c619c3cf9d/include/pybind11/stl_bind.h

        .def
        (
            init
            (
                [] (const dict& aDictionary)
                {

                    Dictionary dictionary = Dictionary::Empty() ;

                    for (const auto& [key, value] : aDictionary)
                    {
                        dictionary[key.cast<std::string>()] = objectFromPythonHandle(value) ;
                    }

                    return dictionary ;

                }
            )
        )

        .def(self == self)
        .def(self != self)

        .def("__bool__", [] (const Dictionary& aDictionary) -> bool { return !aDictionary.isEmpty() ; })
        .def("__len__", &Dictionary::getSize)

        .def("__iter__", [] (const Dictionary &aDictionary) { return make_iterator(aDictionary.begin(), aDictionary.end()) ; })
        .def("__contains__", &Dictionary::hasValueForKey)
        .def("__getitem__", overload_cast<const String&>(&Dictionary::operator[]))
        // .def("__delitem__", ...)

        // .def("keys", ...)
        // .def("values", ...)
        // .def("items", ...)

        .def("__str__", [] (const Dictionary& aDictionary) -> std::string { return Object::Dictionary(aDictionary).toString(Object::Format::JSON) ; })
        .def("__repr__", [] (const Dictionary& aDictionary) -> std::string { return Object::Dictionary(aDictionary).toString(Object::Format::JSON) ; })

        .def("is_empty", &Dictionary::isEmpty)
        .def("has_value_for_key", &Dictionary::hasValueForKey, arg("key"))
        .def("get_size", &Dictionary::getSize)
        .def("add_value_for_key", &Dictionary::addValueForKey, arg("value"), arg("key"))

        .def_static("empty", &Dictionary::Empty)
        .def_static("parse", &Dictionary::Parse, arg("string"), arg("format"))

    ;

    class_<Dictionary::ConstIterator>(dictionary_class, "ConstIterator")

        .def(self == self)
        .def(self != self)

        .def("access_key", &Dictionary::ConstIterator::accessKey, return_value_policy::reference)
        .def("access_value", &Dictionary::ConstIterator::accessValue, return_value_policy::reference)

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
