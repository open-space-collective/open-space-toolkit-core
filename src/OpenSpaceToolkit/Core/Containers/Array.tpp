////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           OpenSpaceToolkit/Core/Containers/Array.tpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <OpenSpaceToolkit/Core/Error.hpp>
#include <OpenSpaceToolkit/Core/Utilities.hpp>

#include <algorithm>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                template <class T>
                                Array<T>::Array                             (   const   Size&                       aSize,
                                                                                const   T&                          anElement                                   )
                                :    std::vector<T>(aSize, anElement)
{

}

                                template <class T>
                                Array<T>::Array                             (   const   std::vector<T>&             aVector                                     )
                                :    std::vector<T>(aVector)
{

}

                                template <class T>
                                Array<T>::Array                             (           std::initializer_list<T>    aList                                       )
                                :    std::vector<T>(aList)
{

}

                                template <class T>
                                Array<T>::Array                             (           std::vector<T>&&            aVector                                     )
                                :    std::vector<T>(std::move(aVector))
{

}

                                template <class T>
                                template <class InputIterator>
                                Array<T>::Array                             (           InputIterator               aFirstIterator,
                                                                                        InputIterator               aLastIterator,
                                                                                const   typename std::vector<T>::allocator_type& anAllocator                    )
                                :    std::vector<T>(aFirstIterator, aLastIterator, anAllocator)
{

}

                                template <class T>
Array<T>                        Array<T>::operator +                        (   const   Array<T>&                   anArray                                     ) const
{

    Array<T> array(*this) ;

    array.mergeWith(anArray) ;

    return array ;

}

                                template <class U>
std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Array<U>&                   anArray                                     )
{

    ostk::core::utils::Print::Header(anOutputStream, "Array") ;

    for (const auto& element : anArray)
    {
        anOutputStream << element << std::endl ;
    }

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

                                template <class T>
const T&                        Array<T>::accessFirst                       ( ) const
{

    if (this->isEmpty())
    {
        throw ostk::core::error::RuntimeError("Array is empty.") ;
    }

    return this->front() ;

}

                                template <class T>
const T&                        Array<T>::accessLast                        ( ) const
{

    if (this->isEmpty())
    {
        throw ostk::core::error::RuntimeError("Array is empty.") ;
    }

    return this->back() ;

}

                                template <class T>
bool                            Array<T>::isEmpty                           ( ) const
{
    return this->empty() ;
}

                                template <class T>
bool                            Array<T>::contains                          (   const   T&                          anElement                                   ) const
{
    return std::find(this->begin(), this->end(), anElement) != this->end() ;
}

                                template <class T>
bool                            Array<T>::isNear                            (   const   Array<T>&                   anArray,
                                                                                const   T&                          aTolerance                                  ) const
{

    if (this->getSize() != anArray.getSize())
    {
        return false ;
    }

    for (const auto elementTuple : ostk::core::ctnr::iterators::Zip(*this, anArray))
    {

        if (!std::get<0>(elementTuple).isNear(std::get<1>(elementTuple), aTolerance))
        {
            return false ;
        }

    }

    return true ;

}

                                template <class T>
bool                            Array<T>::isNear                            (   const   Array<T>&                   anArray,
                                                                                const   std::function<bool (const T&, const T&)>& aComparator                   ) const
{

    if (this->getSize() != anArray.getSize())
    {
        return false ;
    }

    for (const auto elementTuple : ostk::core::ctnr::iterators::Zip(*this, anArray))
    {

        if (!aComparator(std::get<0>(elementTuple), std::get<1>(elementTuple)))
        {
            return false ;
        }

    }

    return true ;

}

                                template <class T>
Size                            Array<T>::getSize                           ( ) const
{
    return this->size() ;
}

                                template <class T>
Index                           Array<T>::getIndexOf                        (   const   T&                          anElement                                   ) const
{

    typename Array<T>::const_iterator arrayIt = std::find(this->begin(), this->end(), anElement) ;

    if (arrayIt == this->end())
    {
        throw ostk::core::error::RuntimeError("Array does not contain element.") ;
    }

    return std::distance(this->begin(), arrayIt) ;

}

template <typename T>
typename std::enable_if<ostk::core::types::HasToString<T>::value, types::String>::type extractString (const T& aType)
{
    return aType.toString() ;
}

template <typename T>
typename std::enable_if<std::is_same<T, types::String>::value, types::String>::type extractString (const T& aType)
{
    return "\"" + aType + "\"" ;
}

// template <typename T>
// typename std::enable_if<!ostk::core::types::HasToString<T>::value, types::String>::type extractString (const T& aType)
// {
//     return aType ;
// }

                                template <class T>
types::String                   Array<T>::toString                         ( ) const
{

    types::String string = "[" ;

    for (const auto& item : (*this))
    {

        // string += item.toString() ;
        string += extractString(item) ;

        if (&item != &(this->back()))
        {
            string += ", " ;
        }

    }

    string += "]" ;

    return string ;

}

                                template <class T>
typename Array<T>::ConstIterator Array<T>::find                             (   const   T&                          anElement                                   ) const
{
    return std::find(this->begin(), this->end(), anElement) ;
}

template <typename T, typename U>
U                               foldLeft                                    (   const   std::vector<T>&             data,
                                                                                const   U&                          initialValue,
                                                                                const   std::function<U (U, T)>&    aFoldFunction                               )
{

    U accumulator = initialValue ;

    const typename Array<T>::ConstIterator end = data.cend() ;

    for (typename Array<T>::ConstIterator it = data.cbegin(); it != end; ++it)
    {
        accumulator = aFoldFunction(accumulator, *it) ;
    }

    return accumulator ;

}

                                template <class T>
                                template <class U>
Array<U>                        Array<T>::map                               (   const   std::function<U (T)>        aMappingFunction                            ) const
{

    Array<U> result = Array<U>::Empty() ;

    result.reserve(this->getSize()) ;

    foldLeft<T, Array<U>&>
    (
        (*this), result, [aMappingFunction] (Array<U>& anArray, T aValue) -> Array<U>&
        {

            anArray.add(aMappingFunction(aValue)) ;

            return anArray;

        }
    ) ;

    return result ;

}

                                template <class T>
T                               Array<T>::reduce                            (   const   std::function<T (T, T)>&    aReduceFunction                             ) const
{

    if (this->isEmpty())
    {
        throw ostk::core::error::RuntimeError("Array is empty.") ;
    }

    typename Array<T>::ConstIterator it = this->cbegin() ;
    const typename Array<T>::ConstIterator end = this->cend() ;

    T accumulator = *it ;

    ++it ;

    for (; it != end; ++it)
    {
        accumulator = aReduceFunction(accumulator, *it) ;
    }

    return accumulator ;

}

                                template <class T>
Array<const T*>                 Array<T>::accessWhere                       (   const   std::function<bool(const T&)>& aPredicate                               ) const
{

    Array<const T*> array = Array<const T*>::Empty() ;

    for (const auto& item : (*this))
    {

        if (aPredicate(item))
        {
            array.add(&item) ;
        }

    }

    return array ;

}

                                template <class T>
Array<T>                        Array<T>::getWhere                          (   const    std::function<bool(const T&)>& aPredicate                              ) const
{

    Array<T> array = Array<T>::Empty() ;

    std::copy_if
    (
        this->begin(),
        this->end(),
        std::back_inserter(array),
        aPredicate
    ) ;

    return array ;

}

                                template <class T>
T&                              Array<T>::accessFirst                       ( )
{

    if (this->isEmpty())
    {
        throw ostk::core::error::RuntimeError("Array is empty.") ;
    }

    return this->front() ;

}

                                template <class T>
T&                              Array<T>::accessLast                        ( )
{

    if (this->isEmpty())
    {
        throw ostk::core::error::RuntimeError("Array is empty.") ;
    }

    return this->back() ;

}

                                template <class T>
void                            Array<T>::add                               (   const   T&                          anElement                                   )
{
    this->emplace_back(anElement) ;
}

                                template <class T>
void                            Array<T>::remove                            (   const   T&                          anElement                                   )
{
    this->erase(std::remove(this->begin(), this->end(), anElement), this->end()) ;
}

                                template <class T>
void                            Array<T>::add                               (   const   Array<T>&                   anArray                                     )
{
    this->insert(this->end(), anArray.begin(), anArray.end()) ;
}

                                template <class T>
void                            Array<T>::remove                            (   const   Array<T>&                   anArray                                     )
{

    for (const auto& element: anArray)
    {
        this->erase(std::remove(this->begin(), this->end(), element), this->end()) ;
    }

}

                                template <class T>
void                            Array<T>::mergeWith                         (   const   Array<T>&                   anArray                                     )
{
    this->insert(this->end(), anArray.begin(), anArray.end()) ;
}

                                template <class T>
void                            Array<T>::removeWhere                       (   const    std::function<bool(const T&)>& aPredicate                              )
{

    this->erase
    (
        std::remove_if
        (
            this->begin(),
            this->end(),
            aPredicate
        ),
        this->end()
    ) ;

}

                                template <class T>
typename Array<T>::Iterator     Array<T>::find                              (   const   T&                          anElement                                   )
{
    return std::find(this->begin(), this->end(), anElement) ;
}

                                template <class T>
Array<T>                        Array<T>::Empty                             ( )
{
    return std::move(std::vector<T>()) ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
