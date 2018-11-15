////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Library/Core
/// @file           Library/Core/Containers/Dictionary.hpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __Library_Core_Containers_Dictionary__
#define __Library_Core_Containers_Dictionary__

#include <Library/Core/FileSystem/File.hpp>
#include <Library/Core/Containers/List.hpp>
#include <Library/Core/Containers/OrderedMap.hpp>
#include <Library/Core/Types/String.hpp>
#include <Library/Core/Types/Size.hpp>
#include <Library/Core/Containers/Object.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace library
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace fs = library::core::fs ;

using library::core::types::Size ;
using library::core::types::String ;
using library::core::ctnr::OrderedMap ;
using library::core::ctnr::Object ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @brief                      Key-value pairs container
///
///                             Each entry consists of one string that represents the key and an object that is that key’s value.
///                             Within a dictionary, keys are unique.
///                             Dictionaries preserve the order of insertion.

class Dictionary
{

    public:

        typedef types::String Key ;
        typedef ctnr::List<Dictionary::Key> Path ;
        typedef Object Value ;

        class Iterator
        {

            public:

                typedef OrderedMap<Dictionary::Key, Dictionary::Value>::iterator MapIterator ;

                                Iterator                                    ( ) ;

                                Iterator                                    (   const   Iterator::MapIterator&      anOrderedMapIt                              ) ;
                                
                                Iterator                                    (   const   Iterator&                   aIterator                                   ) ;

                Iterator&       operator =                                  (   const   Iterator&                   aIterator                                   ) ;

                bool            operator ==                                 (   const   Iterator&                   aIterator                                   ) const ;
                bool            operator !=                                 (   const   Iterator&                   aIterator                                   ) const ;

                const Iterator& operator *                                  ( ) const ;
                const Iterator* operator ->                                 ( ) const ;

                Iterator&       operator *                                  ( ) ;
                Iterator*       operator ->                                 ( ) ;

                Dictionary::Value& operator []                              (   const   Dictionary::Key&            aKey                                        ) ;

                Iterator&       operator ++                                 ( ) ;
                Iterator        operator ++                                 (           int                                                                     ) ;

                Iterator&       operator --                                 ( ) ;
                Iterator        operator --                                 (           int                                                                     ) ;

                const Dictionary::Key& accessKey                            ( ) const ;
                const Dictionary::Value& accessValue                        ( ) const ;

                Dictionary::Value& accessValue                              ( ) ;

                const Iterator::MapIterator& accessMapIterator              ( ) const ;

                Iterator::MapIterator& accessMapIterator                    ( ) ;

            private:

                Iterator::MapIterator mapIt_ ;

        } ;

        class ConstIterator
        {

            public:

                typedef OrderedMap<Dictionary::Key, Dictionary::Value>::const_iterator MapConstIterator ;

                                ConstIterator                               ( ) ;

                                ConstIterator                               (   const   ConstIterator::MapConstIterator& anOrderedMapIt                         ) ;
                                
                                ConstIterator                               (   const   ConstIterator&              aConstIterator                              ) ;
                                ConstIterator                               (   const   Iterator&                   anIterator                                  ) ;

                ConstIterator&  operator =                                  (   const   ConstIterator&              aConstIterator                              ) ;

                bool            operator ==                                 (   const   ConstIterator&              aConstIterator                              ) const ;
                bool            operator !=                                 (   const   ConstIterator&              aConstIterator                              ) const ;

                const ConstIterator& operator *                             ( ) const ;
                const ConstIterator* operator ->                            ( ) const ;

                const Dictionary::Value& operator []                        (   const   Dictionary::Key&            aKey                                        ) const ;

                ConstIterator&  operator ++                                 ( ) ;
                ConstIterator   operator ++                                 (           int                                                                     ) ;

                ConstIterator&  operator --                                 ( ) ;
                ConstIterator   operator --                                 (           int                                                                     ) ;

                const Dictionary::Key& accessKey                            ( ) const ;
                const Dictionary::Value& accessValue                        ( ) const ;

                ConstIterator::MapConstIterator& accessMapConstIterator     ( ) ;

            private:

                ConstIterator::MapConstIterator mapIt_ ;

        } ;

        /// @brief              Constructs a dictionary using an initializer list
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123), "Key B": Object::String("Hello World!") }} ;
        /// @endcode
        ///
        /// @param              [in] aList An initializer list

                                Dictionary                                  (           std::initializer_list<std::pair<Dictionary::Key, Dictionary::Value>> aList ) ;

        /// @brief              Copy constructor
        ///
        /// @param              [in] aDictionary A dictionary

                                Dictionary                                  (   const   Dictionary&                 aDictionary                                 ) ;

        /// @brief              Destructor

                                ~Dictionary                                 ( ) ;

        /// @brief              Copy assignment operator
        ///
        /// @param              [in] aDictionary A dictionary
        /// @return             Reference to dictionary

        Dictionary&             operator =                                  (   const   Dictionary&                 aDictionary                                 ) ;

        /// @brief              Equal to operator
        ///
        /// @code
        ///                     Dictionary firstDictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     Dictionary secondDictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     firstDictionary == secondDictionary ; // True
        /// @endcode
        ///
        /// @param              [in] aDictionary A dictionary
        /// @return             True if dictionaries are equal

        bool                    operator ==                                 (   const   Dictionary&                 aDictionary                                 ) const ;

        /// @brief              Not equal to operator
        ///
        /// @code
        ///                     Dictionary firstDictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     Dictionary secondDictionary = {{ "Key A": Object::Integer(456) }} ;
        ///                     firstDictionary != secondDictionary ; // True
        /// @endcode
        ///
        /// @param              [in] aDictionary A dictionary
        /// @return             True if dictionaries are not equal

        bool                    operator !=                                 (   const   Dictionary&                 aDictionary                                 ) const ;

        /// @brief              Key subscript operator
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     const Object& object = dictionary["Key A"] ; // &123
        /// @endcode
        ///
        /// @param              [in] aKey A key
        /// @return             A const reference to value

        const Dictionary::Value& operator []                                (   const   Dictionary::Key&            aKey                                        ) const ;

        /// @brief              Key subscript operator
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     Object& object = dictionary["Key A"] ; // &123
        /// @endcode
        ///
        /// @param              [in] aKey A key
        /// @return             A reference to value
        
        Dictionary::Value&      operator []                                 (   const   Dictionary::Key&            aKey                                        ) ;

        /// @brief              Output stream operator
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     std::cout << dictionary ;
        /// @endcode
        ///
        /// @param              [in] anOutputStream An output stream
        /// @param              [in] aDictionary An dictionary
        /// @return             A reference to output stream

        friend std::ostream&    operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Dictionary&                 aDictionary                                 ) ;

        /// @brief              Check if dictionary is empty
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     dictionary.isEmpty() ; // False
        /// @endcode
        ///
        /// @return             True if dictionary is empty

        bool                    isEmpty                                     ( ) const ;

        /// @brief              Check if dictionary has value for a given key
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     dictionary.hasValueForKey("Key A") ; // True
        /// @endcode
        ///
        /// @param              [in] aKey A key
        /// @return             True if dictionary has value for a given key

        bool                    hasValueForKey                              (   const   Dictionary::Key&            aKey                                        ) const ;

        /// @brief              Get size of dictionary
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     dictionary.getSize() ; // 1
        /// @endcode
        ///
        /// @return             Dictionary size

        Size                    getSize                                     ( ) const ;

        /// @brief              Add entry to dictionary
        ///
        /// @code
        ///                     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
        ///                     dictionary.addValueForKey(Object::Integer(456), "Key B") ;
        /// @endcode
        ///
        /// @param              [in] aValue A value
        /// @param              [in] aKey A key

        void                    addValueForKey                              (   const   Dictionary::Value&          aValue,
                                                                                const   Dictionary::Key&            aKey                                        ) ;

        /// @brief              Returns an iterator pointing to the first element
        ///
        /// @return             Iterator pointing to the first element

        Dictionary::ConstIterator begin                                     ( ) const ;

        /// @brief              Returns an iterator pointing to the last element
        ///
        /// @return             Iterator pointing to the last element

        Dictionary::ConstIterator end                                       ( ) const ;

        /// @brief              Returns an iterator pointing to the first element
        ///
        /// @return             Iterator pointing to the first element
        
        Dictionary::Iterator    begin                                       ( ) ;

        /// @brief              Returns an iterator pointing to the last element
        ///
        /// @return             Iterator pointing to the last element

        Dictionary::Iterator    end                                         ( ) ;

        /// @brief              Constructs an empty dictionary
        ///
        /// @code
        ///                     Dictionary dictionary = Dictionary::Empty() ; // {}
        /// @endcode
        ///
        /// @return             Empty dictionary

        static Dictionary       Empty                                       ( ) ;

        /// @brief              Constructs a dictionary from a string
        ///
        /// @code
        ///                     String jsonString = "{\"Key\": 123}" ;
        ///                     Dictionary dictionary = Dictionary::Parse(jsonString) ;
        /// @endcode
        ///
        /// @param              [in] aString A string
        /// @param              [in] (optional) aFormat Serialization format
        /// @return             Dictionary

        static Dictionary       Parse                                       (   const   types::String&              aString,
                                                                                const   Object::Format&             aFormat                                     =   Object::Format::Undefined ) ;

    private:

        OrderedMap<Dictionary::Key, Dictionary::Value> map_ ;

                                Dictionary                                  ( ) ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////