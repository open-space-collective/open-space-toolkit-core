////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           LibraryCorePy/Containers/Array.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Array.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline void                     LibraryCorePy_Containers_Array              ( )
{

    using namespace boost::python ;

    using library::core::types::Integer ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::core::ctnr::Array ;

    class_<Array<int>>("ArrayInt", no_init)

        .def(vector_indexing_suite<Array<int>>())

    ;

    class_<Array<double>>("ArrayDouble", no_init)

        .def(vector_indexing_suite<Array<double>>())

    ;

    class_<Array<Integer>>("ArrayInteger", no_init)

        .def(vector_indexing_suite<Array<Integer>>())

    ;

    class_<Array<Real>>("ArrayReal", no_init)

        .def(vector_indexing_suite<Array<Real>>())

    ;

    class_<Array<String>>("ArrayString", no_init)

        .def(vector_indexing_suite<Array<String>>())

    ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////