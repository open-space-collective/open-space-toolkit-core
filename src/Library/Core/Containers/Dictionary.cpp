////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Dictionary.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        TBD

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Dictionary.hpp>
#include <Library/Core/Logger.hpp>
#include <Library/Core/Utilities.hpp>

#include <tsl/ordered_map.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Dictionary::Iterator::Iterator              ( )
{
}

                                Dictionary::Iterator::Iterator              (   const   Iterator::MapIterator&      anOrderedMapIt                              )
                                :   mapIt_(anOrderedMapIt)
{
}

                                Dictionary::Iterator::Iterator              (   const   Dictionary::Iterator&       anIterator                                  )
                                :   mapIt_(anIterator.mapIt_)
{
}

Dictionary::Iterator&           Dictionary::Iterator::operator =            (   const   Dictionary::Iterator&       anIterator                                  )
{

    if (this != &anIterator)
    {
        mapIt_ = anIterator.mapIt_ ;
    }

    return (*this) ;

}

bool                            Dictionary::Iterator::operator ==           (   const   Dictionary::Iterator&       anIterator                                  ) const
{
    return mapIt_ == anIterator.mapIt_ ;
}

bool                            Dictionary::Iterator::operator !=           (   const   Dictionary::Iterator&       anIterator                                  ) const
{
    return mapIt_ != anIterator.mapIt_ ;
}

const Dictionary::Iterator&     Dictionary::Iterator::operator *            ( ) const
{
    return (*this) ;
}

const Dictionary::Iterator*     Dictionary::Iterator::operator ->           ( ) const
{
    return this ;
}

Dictionary::Iterator&           Dictionary::Iterator::operator *            ( )
{
    return (*this) ;
}

Dictionary::Iterator*           Dictionary::Iterator::operator ->           ( )
{
    return this ;
}

Dictionary::Value&              Dictionary::Iterator::operator []           (   const   Dictionary::Key&            aKey                                        )
{
    return mapIt_.value()[aKey] ;
}

Dictionary::Iterator&           Dictionary::Iterator::operator ++           ( )
{

    ++mapIt_ ;

    return (*this) ;

}

Dictionary::Iterator            Dictionary::Iterator::operator ++           (           int                                                                     )
{
    return Dictionary::Iterator(mapIt_++) ;
}

Dictionary::Iterator&           Dictionary::Iterator::operator --           ( )
{

    --mapIt_ ;

    return (*this) ;

}

Dictionary::Iterator            Dictionary::Iterator::operator --           (           int                                                                     )
{
    return Dictionary::Iterator(mapIt_--) ;
}

const Dictionary::Key&          Dictionary::Iterator::accessKey             ( ) const
{
    return mapIt_.key() ;
}

const Dictionary::Value&        Dictionary::Iterator::accessValue           ( ) const
{
    return const_cast<Iterator::MapIterator&>(mapIt_).value() ; // const_cast used due to a bug with tsl::ordered_map
}

Dictionary::Value&              Dictionary::Iterator::accessValue           ( )
{
    return mapIt_.value() ;
}

const Dictionary::Iterator::MapIterator& Dictionary::Iterator::accessMapIterator  ( ) const
{
    return mapIt_ ;
}

Dictionary::Iterator::MapIterator& Dictionary::Iterator::accessMapIterator  ( )
{
    return mapIt_ ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Dictionary::ConstIterator::ConstIterator    ( )
{

}

                                Dictionary::ConstIterator::ConstIterator    (   const   ConstIterator::MapConstIterator& anOrderedMapIt                         )
                                :   mapIt_(anOrderedMapIt)
{

}

                                Dictionary::ConstIterator::ConstIterator    (   const   Dictionary::ConstIterator&  aConstIterator                              )
                                :   mapIt_(aConstIterator.mapIt_)
{

}

                                Dictionary::ConstIterator::ConstIterator    (   const   Dictionary::Iterator&       anIterator                                  )
                                :   mapIt_(anIterator.accessMapIterator())
{

}

Dictionary::ConstIterator&      Dictionary::ConstIterator::operator =       (   const   Dictionary::ConstIterator&  aConstIterator                              )
{

    if (this != &aConstIterator)
    {
        mapIt_ = aConstIterator.mapIt_ ;
    }

    return (*this) ;

}

bool                            Dictionary::ConstIterator::operator ==      (   const   Dictionary::ConstIterator&  aConstIterator                              ) const
{
    return mapIt_ == aConstIterator.mapIt_ ;
}

bool                            Dictionary::ConstIterator::operator !=      (   const   Dictionary::ConstIterator&  aConstIterator                              ) const
{
    return mapIt_ != aConstIterator.mapIt_ ;
}

const Dictionary::ConstIterator& Dictionary::ConstIterator::operator *      ( ) const
{
    return (*this) ;
}

const Dictionary::ConstIterator* Dictionary::ConstIterator::operator ->     ( ) const
{
    return this ;
}

const Dictionary::Value&        Dictionary::ConstIterator::operator []      (   const   Dictionary::Key&            aKey                                        ) const
{
    return mapIt_.value()[aKey] ;
}

Dictionary::ConstIterator&      Dictionary::ConstIterator::operator ++      ( )
{

    ++mapIt_ ;

    return (*this) ;

}

Dictionary::ConstIterator       Dictionary::ConstIterator::operator ++      (           int                                                                     )
{
    return Dictionary::ConstIterator(mapIt_++) ;
}

Dictionary::ConstIterator&      Dictionary::ConstIterator::operator --      ( )
{

    --mapIt_ ;

    return (*this) ;

}

Dictionary::ConstIterator       Dictionary::ConstIterator::operator --      (           int                                                                     )
{
    return Dictionary::ConstIterator(mapIt_--) ;
}

const Dictionary::Key&          Dictionary::ConstIterator::accessKey        ( ) const
{
    return mapIt_.key() ;
}

const Dictionary::Value&        Dictionary::ConstIterator::accessValue      ( ) const
{
    return mapIt_.value() ;
}

Dictionary::ConstIterator::MapConstIterator& Dictionary::ConstIterator::accessMapConstIterator ( )
{
    return mapIt_ ;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Dictionary::Dictionary                      (           std::initializer_list<std::pair<Dictionary::Key, Dictionary::Value>> aList )
                                :   map_(aList)
{

}

                                Dictionary::Dictionary                      (   const   Dictionary&                 aDictionary                                 )
                                :   map_(aDictionary.map_)
{

}

                                Dictionary::~Dictionary                     ( )
{

}

Dictionary&                     Dictionary::operator =                      (   const   Dictionary&                 aDictionary                                 )
{

    if (this != &aDictionary)
    {
        map_ = aDictionary.map_ ;
    }

    return (*this) ;

}

bool                            Dictionary::operator ==                     (   const   Dictionary&                 aDictionary                                 ) const
{
    return map_ == aDictionary.map_ ;
}

bool                            Dictionary::operator !=                     (   const   Dictionary&                 aDictionary                                 ) const
{
    return map_ != aDictionary.map_ ;
}

const Dictionary::Value&        Dictionary::operator []                     (   const   Dictionary::Key&            aKey                                        ) const
{

    LOG_SCOPE("Dictionary", "operator [Dictionary::Key]") ;

    if (aKey.isEmpty())
    {
        throw library::core::error::runtime::Undefined("Key") ;
    }

    auto mapIt = map_.find(aKey) ;

    if (mapIt == map_.end())
    {
        throw library::core::error::RuntimeError("No value for key [" + aKey + "].") ;
    }

    return mapIt.value() ;

}

Dictionary::Value&              Dictionary::operator []                     (   const   Dictionary::Key&            aKey                                        )
{

    LOG_SCOPE("Dictionary", "operator [Dictionary::Key]") ;

    if (aKey.isEmpty())
    {
        throw library::core::error::runtime::Undefined("Key") ;
    }

    auto mapIt = map_.find(aKey) ;

    if (mapIt == map_.end())
    {        
        return map_.emplace(aKey, Dictionary::Value::Undefined()).first.value() ;
    }
    
    return mapIt.value() ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Dictionary&                 aDictionary                                 )
{

    std::function<void (const Dictionary&, uint)> printDictionary ;
    std::function<void (const ctnr::Array<Object>&, uint)> printArray ;

    printDictionary =
    [&printDictionary, &printArray, &anOutputStream]
    (const Dictionary& dictionary, uint anIndentation)
    {

        for (const auto& dictIt : dictionary)
        {

            const Dictionary::Key& key = dictIt.accessKey() ;
            const Dictionary::Value& value = dictIt.accessValue() ;

            if (value.isDictionary())
            {

                library::core::utils::Print::Line(anOutputStream, anIndentation) << (key + ": ") ;
                
                printDictionary(value.accessDictionary(), anIndentation + 1) ;

            }
            else if (value.isArray())
            {

                library::core::utils::Print::Line(anOutputStream, anIndentation) << (key + ": ") ;

                printArray(value.accessArray(), anIndentation + 1) ;

            }
            else
            {
                library::core::utils::Print::Line(anOutputStream, anIndentation) << (key + ": ") << value.toString(Object::Format::JSON) ;
            }

        }
        
    } ;

    printArray =
    [&printArray, &printDictionary, &anOutputStream]
    (const ctnr::Array<Object>& array, uint anIndentation)
    {

        types::Integer index = 0 ;

        for (const auto& arrayElement : array)
        {

            if (arrayElement.isDictionary())
            {

                library::core::utils::Print::Line(anOutputStream, anIndentation) << ("- [" + index.toString() + "]: ") ;

                printDictionary(arrayElement.accessDictionary(), anIndentation + 1) ;

            }
            else if (arrayElement.isArray())
            {

                library::core::utils::Print::Line(anOutputStream, anIndentation) << ("- [" + index.toString() + "]: ") ;

                printArray(arrayElement.accessArray(), anIndentation + 1) ;

            }
            else
            {
                library::core::utils::Print::Line(anOutputStream, anIndentation) << ("- [" + index.toString() + "]: ") << arrayElement.toString(Object::Format::JSON) ;
            }

            index++ ;

        }

    } ;

    library::core::utils::Print::Header(anOutputStream, "Dictionary") ;

    library::core::utils::Print::Line(anOutputStream) << "Size:" << aDictionary.map_.size() ;

    library::core::utils::Print::Separator(anOutputStream) ;

    printDictionary(aDictionary, 1) ;

    library::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

bool                            Dictionary::isEmpty                         ( ) const
{
    return map_.empty() ;
}

bool                            Dictionary::hasValueForKey                  (   const   Dictionary::Key&            aKey                                        ) const
{
    return map_.find(aKey) != map_.end() ;
}

Size                            Dictionary::getSize                         ( ) const
{
    return map_.size() ;
}

void                            Dictionary::addValueForKey                  (   const   Dictionary::Value&          aValue,
                                                                                const   Dictionary::Key&            aKey                                        )
{

    LOG_SCOPE("Dictionary", "addValueForKey") ;

    if (aKey.isEmpty())
    {
        throw library::core::error::runtime::Undefined("Key") ;
    }

    if (this->hasValueForKey(aKey))
    {
        throw library::core::error::RuntimeError("Value for key [" + aKey + "] already exists.") ;
    }

    map_.emplace(aKey, aValue) ;

}

Dictionary::ConstIterator       Dictionary::begin                           ( ) const
{
    return Dictionary::ConstIterator(map_.begin()) ;
}

Dictionary::ConstIterator       Dictionary::end                             ( ) const
{
    return Dictionary::ConstIterator(map_.end()) ;
}

Dictionary::Iterator            Dictionary::begin                           ( )
{
    return Dictionary::Iterator(map_.begin()) ;
}

Dictionary::Iterator            Dictionary::end                             ( )
{
    return Dictionary::Iterator(map_.end()) ;
}

Dictionary                      Dictionary::Empty                           ( )
{
    return Dictionary() ;
}

Dictionary                      Dictionary::Parse                           (   const   String&                     aString,
                                                                                const   Object::Format&             aFormat                                     )
{

    LOG_SCOPE("Dictionary", "Parse") ;

    Object object = Object::Parse(aString, aFormat) ;

    if (!object.isDictionary())
    {
        throw library::core::error::runtime::Wrong("String") ;
    }

    return object.accessDictionary() ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Dictionary::Dictionary                      ( )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////