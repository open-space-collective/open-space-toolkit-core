////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           LibraryCorePy/Containers/Array.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Array.hpp>

#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Real.hpp>
#include <Library/Core/Types/Integer.hpp>

#include <boost/python/stl_iterator.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// https://wiki.python.org/moin/boost.python/HowTo#Dynamic_template_to-python_converters
// https://stackoverflow.com/questions/15842126/feeding-a-python-list-into-a-function-taking-in-a-vector-with-boost-python
// https://misspent.wordpress.com/2009/09/27/how-to-write-boost-python-converters/
// https://www.boost.org/doc/libs/1_66_0/libs/python/doc/html/faq/how_can_i_automatically_convert_.html

template <typename Container>
struct ToListConverter
{

	static PyObject*            convert                                     (   const   Container&                  aContainer                                  )
    {
		
        boost::python::list list ;

        for (const auto& element : aContainer)
        {
            list.append(element) ;
        }
		
        return boost::python::incref(list.ptr()) ;

	}

} ;

struct IterableConverter
{

    /// @brief                  Registers converter from a python interable type to the provided type
  
                                template <typename Container>
    IterableConverter&          from_python                                 ( )
    {

        boost::python::converter::registry::push_back
        (
            &IterableConverter::convertible,
            &IterableConverter::construct<Container>,
            boost::python::type_id<Container>()
        ) ;

        return *this ;

    }

    /// @brief                  Registers converter from the provided type to a python interable type
  
                                template <typename Container>
    IterableConverter&          to_python                                   ( )
    {

        boost::python::to_python_converter<Container, ToListConverter<Container>>() ;

        return *this ;

    }

    /// @brief                  Check if PyObject is iterable

    static void*                convertible                                 (           PyObject*                   anObject                                    )
    {
    return PyObject_GetIter(anObject) ? anObject : nullptr ;
    }

    /// @brief Convert iterable PyObject to C++ container type.
    ///
    /// Container Concept requirements:
    ///
    ///   * Container::value_type is CopyConstructable.
    ///   * Container can be constructed and populated with two iterators.
    ///     I.e. Container(begin, end)

                                template <typename Container>
    static void                 construct                                   (           PyObject*                   object,
                                                                                        boost::python::converter::rvalue_from_python_stage1_data* data          )
    {

        namespace python = boost::python ;

        // Object is a borrowed reference, so create a handle indicting it is borrowed for proper reference counting

        python::handle<> handle(python::borrowed(object)) ;

        // Obtain a handle to the memory block that the converter has allocated for the C++ type

        typedef python::converter::rvalue_from_python_storage<Container> storage_type ;
        
        void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes ;

        typedef python::stl_input_iterator<typename Container::value_type> iterator ;

        // Allocate the C++ type into the converter's memory block, and assign
        // its handle to the converter's convertible variable.  The C++
        // container is populated by passing the begin and end iterators of
        // the python object to the container's constructor.

        new (storage) Container
        (
            iterator(python::object(handle)), // begin
            iterator() // end
        ) ;
        
        data->convertible = storage ;

    }

} ;

inline void                     LibraryCorePy_Containers_Array              ( )
{

    using namespace boost::python ;

    using library::core::types::Integer ;
    using library::core::types::Real ;
    using library::core::types::String ;

    using library::core::ctnr::Array ;

    IterableConverter()

        .from_python<Array<int>>()
        .from_python<Array<double>>()
        .from_python<Array<std::string>>()

        .from_python<Array<Integer>>()
        .from_python<Array<Real>>()
        .from_python<Array<String>>()

        .from_python<Array<Array<Integer>>>()
        .from_python<Array<Array<Real>>>()
        .from_python<Array<Array<String>>>()

        .to_python<Array<int>>()
        .to_python<Array<double>>()
        .to_python<Array<std::string>>()

        .to_python<Array<Integer>>()
        .to_python<Array<Real>>()
        .to_python<Array<String>>()
        
    ;

    def("GetIntArray", +[] () -> Array<int> { Array<int> vector = { 1, 2, 3 } ; return vector ; }) ;
    def("GetDoubleArray", +[] () -> Array<double> { Array<double> vector = { 1.0, 2.0, 3.0 } ; return vector ; }) ;
    def("GetIntegerArray", +[] () -> Array<Integer> { Array<Integer> vector = { 1, 2, 3 } ; return vector ; }) ;
    def("GetRealArray", +[] () -> Array<Real> { Array<Real> vector = { 1.0, 2.0, 3.0 } ; return vector ; }) ;
    def("GetStringArray", +[] () -> Array<String> { Array<String> vector = { "abc", "def", "ghi" } ; return vector ; }) ;

    def("SetIntArray", +[] (const Array<int>& anArray) -> void { (void) anArray ; }) ;
    def("SetDoubleArray", +[] (const Array<double>& anArray) -> void { (void) anArray ; }) ;
    def("SetIntegerArray", +[] (const Array<Integer>& anArray) -> void { (void) anArray ; }) ;
    def("SetRealArray", +[] (const Array<Real>& anArray) -> void { (void) anArray ; }) ;
    def("SetStringArray", +[] (const Array<String>& anArray) -> void { (void) anArray ; ; }) ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////