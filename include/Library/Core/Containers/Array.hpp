////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Array.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Containers_Array__
#define __Library_Core_Containers_Array__

#include <Library/Core/Types/Index.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Types/String.hpp>

#include <functional>
#include <vector>
#include <ostream>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

using library::core::types::Index ;
using library::core::types::Size ;
using library::core::types::String ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Array container
///
///                             Sequence containers representing arrays that can change in size.
///                             Arrays use contiguous storage locations for their elements.

template <class T>
class Array : public std::vector<T>
{

    public:

        typedef typename std::vector<T>::const_iterator ConstIterator ;
        typedef typename std::vector<T>::iterator Iterator ;
        typedef std::function<bool(const T&)> Predicate ;

        /// @brief              Default constructor (disabled)

                                // Array                                       ( ) = delete ;
                                Array                                       ( ) = default ;

        /// @brief              Constructs an array from a C++ Standard Library vector
        ///
        /// @code
        ///                     std::vector<Integer> vector = {1, 2, 3} ;
        ///                     Array<Integer> array(vector) ;
        /// @endcode
        ///
        /// @param              [in] aVector A vector

                                Array                                       (   const   std::vector<T>&             aVector                                     ) ;

        /// @brief              Constructs an array of given size populated with a given value
        ///
        /// @code
        ///                     Array<String> array(3, "abc") ; // ["abc", "abc", "abc"]
        /// @endcode
        ///
        /// @param              [in] aSize An array size
        /// @param              [in] aValue A value

                                Array                                       (   const   Size&                       aSize,
                                                                                const   T&                          aValue                                      ) ;

                                template <class InputIterator>
                                Array                                       (           InputIterator               aFirstIterator,
                                                                                        InputIterator               aLastIterator,
                                                                                const   typename std::vector<T>::allocator_type& anAllocator                    =   typename std::vector<T>::allocator_type() ) ;

        /// @brief              Constructs an array using an initializer list
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        /// @endcode
        ///
        /// @param              [in] aList An initializer list

                                Array                                       (           std::initializer_list<T>    aList                                       ) ;

        /// @brief              Concatenate array
        ///
        /// @code
        ///                     Array<Integer> a = {1, 2, 3} ;
        ///                     Array<Integer> b = {4, 5, 6} ;
        ///                     Array<Integer> c = a + b ; // {1, 2, 3, 4, 5, 6}
        /// @endcode
        ///
        /// @param              [in] anArray An array to append
        /// @return             An concatenated array

        Array<T>                operator +                                  (   const   Array<T>&                   anArray                                     ) const ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     std::cout << array ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] anArray An array
        /// @return             An output stream

        template <class U>
        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Array<U>&                   anArray                                     ) ;

        /// @brief              Check if array is empty
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     array.isEmpty() ; // False
        /// @endcode
        ///
        /// @return             True if array is empty

        bool                    isEmpty                                     ( ) const ;

        /// @brief              Check if array contains element (by value)
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     array.contains(2) ; // True
        /// @endcode
        ///
        /// @param              [in] anElement An element
        /// @return             True if array contains element (by value)

        bool                    contains                                    (   const   T&                          anElement                                   ) const ;

        /// @brief              Access first element
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     const Integer& element = array.accessFirst() ; // 1
        /// @endcode
        ///
        /// @return             Reference to the first element of array

        const T&                accessFirst                                 ( ) const ;

        /// @brief              Access last element
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     const Integer& element = array.accessLast() ; // 3
        /// @endcode
        ///
        /// @return             Reference to the last element of array

        const T&                accessLast                                  ( ) const ;

        /// @brief              Get array size
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     Size size = array.getSize() ; // 3
        /// @endcode
        ///
        /// @return             Array size

        Size                    getSize                                     ( ) const ;

        /// @brief              Get index of element (by value)
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     Index index = array.getIndexOf(2) ; // 1
        /// @endcode
        ///
        /// @param              [in] anElement An element
        /// @return             Index of element (by value)

        Index                   getIndexOf                                  (   const   T&                          anElement                                   ) const ;

        /// @brief              Get string representation of array
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     String string = array.toString() ; // "[1, 2, 3]"
        /// @endcode
        ///
        /// @return             String representation of array

        types::String           toString                                    ( ) const ;

        /// @brief              Get array of pointers to element based on condition
        ///
        /// @code
        ///                     Array<Integer> array = {0, 1, 2, 3, 4} ;
        ///                     Array<const Integer*> elements = array.accessWhere([] (const Integer& anInteger) -> bool { return anInteger.isEven() ; }) ; // [&0, &2, &4]
        /// @endcode
        ///
        /// @param              [in] aPredicate A predicate
        /// @return             Array of pointers to element

        Array<const T*>         accessWhere                                 (   const   Array<T>::Predicate&        aPredicate                                  ) const ;

        /// @brief              Get array of elements based on condition
        ///
        /// @code
        ///                     Array<Integer> array = {0, 1, 2, 3, 4} ;
        ///                     Array<const Integer*> elements = array.accessWhere([] (const Integer& anInteger) -> bool { return anInteger.isEven() ; }) ; // [0, 2, 4]
        /// @endcode
        ///
        /// @param              [in] aPredicate A predicate
        /// @return             Array of elements

        Array<T>                getWhere                                    (   const   Array<T>::Predicate&        aPredicate                                  ) const ;

        /// @brief              Get iterator to element, finding by by value
        ///
        /// @code
        ///                     Array<Integer> array = {0, 1, 2, 3, 4} ;
        ///                     auto elementIt = array.find(2) ;
        /// @endcode
        ///
        /// @param              [in] anElement An element
        /// @return             Iterator to element

        typename Array<T>::ConstIterator find                               (   const   T&                          anElement                                   ) const ;

        /// @brief              Access first element
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     Integer& element = array.accessFirst() ; // 1
        /// @endcode
        ///
        /// @return             Reference to the first element of array

        T&                      accessFirst                                 ( ) ;

        /// @brief              Access last element
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     Integer& element = array.accessLast() ; // 3
        /// @endcode
        ///
        /// @return             Reference to the last element of array

        T&                      accessLast                                  ( ) ;

        /// @brief              Add element to array
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     array.add(4) ; // [1, 2, 3, 4]
        /// @endcode
        ///
        /// @param              [in] anElement An element

        void                    add                                         (   const   T&                          anElement                                   ) ;

        /// @brief              Remove element from array (by value)
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     array.remove(2) ; // [1, 3]
        /// @endcode
        ///
        /// @param              [in] anElement An element
        
        void                    remove                                      (   const   T&                          anElement                                   ) ;

        /// @brief              Add elements to array
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3} ;
        ///                     array.add({4, 5}) ; // [1, 2, 3, 4, 5]
        /// @endcode
        ///
        /// @param              [in] anArray An array of elements

        void                    add                                         (   const   Array<T>&                   anArray                                     ) ;

        /// @brief              Remove elements from array (by value)
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3, 4, 5} ;
        ///                     array.remove({2, 4}) ; // [1, 3, 5]
        /// @endcode
        ///
        /// @param              [in] anArray An array of elements

        void                    remove                                      (   const   Array<T>&                   anArray                                     ) ;

        /// @brief              Merge array with another array
        ///
        /// @code
        ///                     Array<Integer> firstArray = {1, 2, 3} ;
        ///                     Array<Integer> secondArray = {4, 5} ;
        ///                     firstArray.merge(secondArray) ; // [1, 2, 3, 4, 5]
        /// @endcode
        ///
        /// @param              [in] anArray An array

        void                    mergeWith                                   (   const   Array<T>&                   anArray                                     ) ;

        /// @brief              Remove elements based on condition
        ///
        /// @code
        ///                     Array<Integer> array = {1, 2, 3, 4, 5} ;
        ///                     array.removeWhere([] (const Integer& anInteger) -> bool { return anInteger.isEven() ; }) ; // [1, 3, 5]
        /// @endcode
        ///
        /// @param              [in] aPredicate A predicate

        void                    removeWhere                                 (   const   Array<T>::Predicate&        aPredicate                                  ) ;

        /// @brief              Get iterator to element, finding by by value
        ///
        /// @code
        ///                     Array<Integer> array = {0, 1, 2, 3, 4} ;
        ///                     auto elementIt = array.find(2) ;
        /// @endcode
        ///
        /// @param              [in] anElement An element
        /// @return             Iterator to element

        typename Array<T>::Iterator find                                    (   const   T&                          anElement                                   ) ;

        /// @brief              Constructs an empty array
        ///
        /// @code
        ///                     Array<Integer> array = Array<Integer>::Empty() ;
        /// @endcode
        ///
        /// @return             Empty array
        
        static Array<T>         Empty                                       ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Array.tpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////