/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Dictionary__
#define __OpenSpaceToolkit_Core_Container_Dictionary__

#include <OpenSpaceToolkit/Core/Container/List.hpp>
#include <OpenSpaceToolkit/Core/Container/Object.hpp>
#include <OpenSpaceToolkit/Core/Container/OrderedMap.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace container
{

namespace filesystem = ostk::core::filesystem;

using ostk::core::container::Object;
using ostk::core::container::OrderedMap;
using ostk::core::type::Size;
using ostk::core::type::String;

/// @brief Key-value pairs container
///
/// Each entry consists of one string that represents the key and an object that is that
/// key's value. Within a dictionary, keys are unique. Dictionaries preserve the order of
/// insertion.
class Dictionary
{
   public:
    typedef type::String Key;
    typedef container::List<Dictionary::Key> Path;
    typedef Object Value;

    /// @brief Mutable iterator for dictionary entries
    class Iterator
    {
       public:
        typedef OrderedMap<Dictionary::Key, Dictionary::Value>::iterator MapIterator;

        /// @brief Default constructor
        Iterator();

        /// @brief Constructor from map iterator
        ///
        /// @param [in] anOrderedMapIt An ordered map iterator
        Iterator(const Iterator::MapIterator& anOrderedMapIt);

        /// @brief Copy constructor
        ///
        /// @param [in] aIterator An iterator
        Iterator(const Iterator& aIterator);

        /// @brief Copy assignment operator
        ///
        /// @param [in] aIterator An iterator
        /// @return Reference to iterator
        Iterator& operator=(const Iterator& aIterator);

        /// @brief Equal to operator
        ///
        /// @param [in] aIterator An iterator
        /// @return True if iterators are equal
        bool operator==(const Iterator& aIterator) const;

        /// @brief Not equal to operator
        ///
        /// @param [in] aIterator An iterator
        /// @return True if iterators are not equal
        bool operator!=(const Iterator& aIterator) const;

        /// @brief Const dereference operator
        ///
        /// @return Const reference to iterator
        const Iterator& operator*() const;

        /// @brief Const member access operator
        ///
        /// @return Const pointer to iterator
        const Iterator* operator->() const;

        /// @brief Dereference operator
        ///
        /// @return Reference to iterator
        Iterator& operator*();

        /// @brief Member access operator
        ///
        /// @return Pointer to iterator
        Iterator* operator->();

        /// @brief Key subscript operator
        ///
        /// @param [in] aKey A key
        /// @return Reference to value
        Dictionary::Value& operator[](const Dictionary::Key& aKey);

        /// @brief Pre-increment operator
        ///
        /// @return Reference to incremented iterator
        Iterator& operator++();

        /// @brief Post-increment operator
        ///
        /// @return Iterator before increment
        Iterator operator++(int);

        /// @brief Pre-decrement operator
        ///
        /// @return Reference to decremented iterator
        Iterator& operator--();

        /// @brief Post-decrement operator
        ///
        /// @return Iterator before decrement
        Iterator operator--(int);

        /// @brief Access key (const)
        ///
        /// @return Const reference to key
        const Dictionary::Key& accessKey() const;

        /// @brief Access value (const)
        ///
        /// @return Const reference to value
        const Dictionary::Value& accessValue() const;

        /// @brief Access value (mutable)
        ///
        /// @return Reference to value
        Dictionary::Value& accessValue();

        /// @brief Access underlying map iterator (const)
        ///
        /// @return Const reference to map iterator
        const Iterator::MapIterator& accessMapIterator() const;

        /// @brief Access underlying map iterator (mutable)
        ///
        /// @return Reference to map iterator
        Iterator::MapIterator& accessMapIterator();

       private:
        Iterator::MapIterator mapIt_;
    };

    /// @brief Const iterator for dictionary entries
    class ConstIterator
    {
       public:
        typedef OrderedMap<Dictionary::Key, Dictionary::Value>::const_iterator MapConstIterator;

        /// @brief Default constructor
        ConstIterator();

        /// @brief Constructor from map const iterator
        ///
        /// @param [in] anOrderedMapIt An ordered map const iterator
        ConstIterator(const ConstIterator::MapConstIterator& anOrderedMapIt);

        /// @brief Copy constructor
        ///
        /// @param [in] aConstIterator A const iterator
        ConstIterator(const ConstIterator& aConstIterator);

        /// @brief Constructor from mutable iterator
        ///
        /// @param [in] anIterator A mutable iterator
        ConstIterator(const Iterator& anIterator);

        /// @brief Copy assignment operator
        ///
        /// @param [in] aConstIterator A const iterator
        /// @return Reference to const iterator
        ConstIterator& operator=(const ConstIterator& aConstIterator);

        /// @brief Equal to operator
        ///
        /// @param [in] aConstIterator A const iterator
        /// @return True if const iterators are equal
        bool operator==(const ConstIterator& aConstIterator) const;

        /// @brief Not equal to operator
        ///
        /// @param [in] aConstIterator A const iterator
        /// @return True if const iterators are not equal
        bool operator!=(const ConstIterator& aConstIterator) const;

        /// @brief Const dereference operator
        ///
        /// @return Const reference to const iterator
        const ConstIterator& operator*() const;

        /// @brief Const member access operator
        ///
        /// @return Const pointer to const iterator
        const ConstIterator* operator->() const;

        /// @brief Const key subscript operator
        ///
        /// @param [in] aKey A key
        /// @return Const reference to value
        const Dictionary::Value& operator[](const Dictionary::Key& aKey) const;

        /// @brief Pre-increment operator
        ///
        /// @return Reference to incremented const iterator
        ConstIterator& operator++();

        /// @brief Post-increment operator
        ///
        /// @return Const iterator before increment
        ConstIterator operator++(int);

        /// @brief Pre-decrement operator
        ///
        /// @return Reference to decremented const iterator
        ConstIterator& operator--();

        /// @brief Post-decrement operator
        ///
        /// @return Const iterator before decrement
        ConstIterator operator--(int);

        /// @brief Access key (const)
        ///
        /// @return Const reference to key
        const Dictionary::Key& accessKey() const;

        /// @brief Access value (const)
        ///
        /// @return Const reference to value
        const Dictionary::Value& accessValue() const;

        /// @brief Access underlying map const iterator (mutable)
        ///
        /// @return Reference to map const iterator
        ConstIterator::MapConstIterator& accessMapConstIterator();

       private:
        ConstIterator::MapConstIterator mapIt_;
    };

    /// @brief Constructs a dictionary using an initializer list
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123), "Key B": Object::String("Hello
    ///     World!") }} ;
    /// @endcode
    ///
    /// @param [in] aList An initializer list
    Dictionary(std::initializer_list<std::pair<Dictionary::Key, Dictionary::Value>> aList);

    /// @brief Copy constructor
    ///
    /// @param [in] aDictionary A dictionary
    Dictionary(const Dictionary& aDictionary);

    /// @brief Destructor
    ~Dictionary();

    /// @brief Copy assignment operator
    ///
    /// @param [in] aDictionary A dictionary
    /// @return Reference to dictionary
    Dictionary& operator=(const Dictionary& aDictionary);

    /// @brief Equal to operator
    ///
    /// @code
    ///     Dictionary firstDictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     Dictionary secondDictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     firstDictionary == secondDictionary ; // True
    /// @endcode
    ///
    /// @param [in] aDictionary A dictionary
    /// @return True if dictionaries are equal
    bool operator==(const Dictionary& aDictionary) const;

    /// @brief Not equal to operator
    ///
    /// @code
    ///     Dictionary firstDictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     Dictionary secondDictionary = {{ "Key A": Object::Integer(456) }} ;
    ///     firstDictionary != secondDictionary ; // True
    /// @endcode
    ///
    /// @param [in] aDictionary A dictionary
    /// @return True if dictionaries are not equal
    bool operator!=(const Dictionary& aDictionary) const;

    /// @brief Key subscript operator
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     const Object& object = dictionary["Key A"] ; // &123
    /// @endcode
    ///
    /// @param [in] aKey A key
    /// @return A const reference to value
    const Dictionary::Value& operator[](const Dictionary::Key& aKey) const;

    /// @brief Key subscript operator
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     Object& object = dictionary["Key A"] ; // &123
    /// @endcode
    ///
    /// @param [in] aKey A key
    /// @return A reference to value
    Dictionary::Value& operator[](const Dictionary::Key& aKey);

    /// @brief Output stream operator
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     std::cout << dictionary ;
    /// @endcode
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aDictionary An dictionary
    /// @return A reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Dictionary& aDictionary);

    /// @brief Check if dictionary is empty
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     dictionary.isEmpty() ; // False
    /// @endcode
    ///
    /// @return True if dictionary is empty
    bool isEmpty() const;

    /// @brief Check if dictionary has value for a given key
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     dictionary.hasValueForKey("Key A") ; // True
    /// @endcode
    ///
    /// @param [in] aKey A key
    /// @return True if dictionary has value for a given key
    bool hasValueForKey(const Dictionary::Key& aKey) const;

    /// @brief Get size of dictionary
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     dictionary.getSize() ; // 1
    /// @endcode
    ///
    /// @return Dictionary size
    Size getSize() const;

    /// @brief Add entry to dictionary
    ///
    /// @code
    ///     Dictionary dictionary = {{ "Key A": Object::Integer(123) }} ;
    ///     dictionary.addValueForKey(Object::Integer(456), "Key B") ;
    /// @endcode
    ///
    /// @param [in] aValue A value
    /// @param [in] aKey A key
    void addValueForKey(const Dictionary::Value& aValue, const Dictionary::Key& aKey);

    /// @brief Returns an iterator pointing to the first element
    ///
    /// @return Iterator pointing to the first element
    Dictionary::ConstIterator begin() const;

    /// @brief Returns an iterator pointing to the last element
    ///
    /// @return Iterator pointing to the last element
    Dictionary::ConstIterator end() const;

    /// @brief Returns an iterator pointing to the first element
    ///
    /// @return Iterator pointing to the first element
    Dictionary::Iterator begin();

    /// @brief Returns an iterator pointing to the last element
    ///
    /// @return Iterator pointing to the last element
    Dictionary::Iterator end();

    /// @brief Constructs an empty dictionary
    ///
    /// @code
    ///     Dictionary dictionary = Dictionary::Empty() ; // {}
    /// @endcode
    ///
    /// @return Empty dictionary
    static Dictionary Empty();

    /// @brief Constructs a dictionary from a string
    ///
    /// @code
    ///     String jsonString = "{\"Key\": 123}" ;
    ///     Dictionary dictionary = Dictionary::Parse(jsonString) ;
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @param [in] (optional) aFormat Serialization format
    /// @return Dictionary
    static Dictionary Parse(const type::String& aString, const Object::Format& aFormat = Object::Format::Undefined);

   private:
    OrderedMap<Dictionary::Key, Dictionary::Value> map_;

    Dictionary();
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
