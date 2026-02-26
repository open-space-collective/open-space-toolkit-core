/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Object__
#define __OpenSpaceToolkit_Core_Container_Object__

#include <fstream>
#include <ostream>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Container/Pair.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Type/EnumHelper.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Integer.hpp>
#include <OpenSpaceToolkit/Core/Type/Real.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>
#include <OpenSpaceToolkit/Core/Type/Unique.hpp>

namespace ostk
{
namespace core
{
namespace container
{

namespace filesystem = ostk::core::filesystem;

using ostk::core::type::Unique;

class Dictionary;

/// @brief Universal type container
///
/// @note The current implementation uses boost::any internally. This may be replaced soon for
/// portability.
/// @note The current implementation is not efficient, as two new operators are called. This is
/// just temporary, for testing.
class Object
{
   public:
    enum class Type
    {

        Undefined,
        Boolean,
        Integer,
        Real,
        String,
        Dictionary,
        Array

    };

    enum class Format
    {

        Undefined,
        JSON,
        YAML

    };

    /// @brief Default constructor (disabled)
    Object() = delete;

    /// @brief Constructs an object using an initializer list
    ///
    /// @code
    ///     Object object = {{ "Key A": Object::Integer(123) }, { "Key B": Object::String("Hello
    ///     World!") }} ;
    /// @endcode
    ///
    /// @param [in] aList An initializer list
    Object(std::initializer_list<container::Pair<type::String, Object>> aList);

    /// @brief Copy constructor
    ///
    /// @param [in] anObject An object
    Object(const Object& anObject);

    /// @brief Destructor
    ~Object();

    /// @brief Copy assignment operator
    ///
    /// @param [in] anObject An object
    /// @return Reference to object
    Object& operator=(const Object& anObject);

    /// @brief Equal to operator
    ///
    /// @code
    ///     Object firstObject = Object::Integer(123) ;
    ///     Object secondObject = Object::Integer(123) ;
    ///     firstObject == secondObject ; // True
    /// @endcode
    ///
    /// @param [in] anObject An object
    /// @return True if objects are equal
    bool operator==(const Object& anObject) const;

    /// @brief Not equal to operator
    ///
    /// @code
    ///     Object firstObject = Object::Integer(123) ;
    ///     Object secondObject = Object::Integer(456) ;
    ///     firstObject != secondObject ; // True
    /// @endcode
    ///
    /// @param [in] anObject An object
    /// @return True if objects are not equal
    bool operator!=(const Object& anObject) const;

    /// @brief Const key subscript operator
    ///
    /// @code
    ///     const Object& value = object["key"] ;
    /// @endcode
    ///
    /// @param [in] aKey A key
    /// @return Const reference to value
    const Object& operator[](const type::String& aKey) const;

    /// @brief Const index subscript operator
    ///
    /// @code
    ///     const Object& value = object[0] ;
    /// @endcode
    ///
    /// @param [in] anIndex An index
    /// @return Const reference to value
    const Object& operator[](const type::Index& anIndex) const;

    /// @brief Key subscript operator
    ///
    /// @code
    ///     Object& value = object["key"] ;
    /// @endcode
    ///
    /// @param [in] aKey A key
    /// @return Reference to value
    Object& operator[](const type::String& aKey);

    /// @brief Index subscript operator
    ///
    /// @code
    ///     Object& value = object[0] ;
    /// @endcode
    ///
    /// @param [in] anIndex An index
    /// @return Reference to value
    Object& operator[](const type::Index& anIndex);

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] anObject An object
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    /// @brief File output operator
    ///
    /// @param [in] aFile A file
    /// @param [in] anObject An object
    /// @return Reference to file
    friend filesystem::File& operator<<(filesystem::File& aFile, const Object& anObject);

    /// @brief File input operator
    ///
    /// @param [in] aFile A file
    /// @param [in] anObject An object
    /// @return Reference to file
    friend filesystem::File& operator>>(filesystem::File& aFile, Object& anObject);

    /// @brief Check if object is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Check if object is a boolean
    ///
    /// @return True if boolean
    bool isBoolean() const;

    /// @brief Check if object is an integer
    ///
    /// @return True if integer
    bool isInteger() const;

    /// @brief Check if object is a real
    ///
    /// @return True if real
    bool isReal() const;

    /// @brief Check if object is a string
    ///
    /// @return True if string
    bool isString() const;

    /// @brief Check if object is a dictionary
    ///
    /// @return True if dictionary
    bool isDictionary() const;

    /// @brief Check if object is an array
    ///
    /// @return True if array
    bool isArray() const;

    /// @brief Access boolean value (const)
    ///
    /// @return Const reference to boolean value
    const bool& accessBoolean() const;

    /// @brief Access integer value (const)
    ///
    /// @return Const reference to integer value
    const type::Integer& accessInteger() const;

    /// @brief Access real value (const)
    ///
    /// @return Const reference to real value
    const type::Real& accessReal() const;

    /// @brief Access string value (const)
    ///
    /// @return Const reference to string value
    const type::String& accessString() const;

    /// @brief Access dictionary value (const)
    ///
    /// @return Const reference to dictionary value
    const container::Dictionary& accessDictionary() const;

    /// @brief Access array value (const)
    ///
    /// @return Const reference to array value
    const container::Array<Object>& accessArray() const;

    /// @brief Get object type
    ///
    /// @return Object type
    Object::Type getType() const;

    /// @brief Get boolean value (copy)
    ///
    /// @return Boolean value
    bool getBoolean() const;

    /// @brief Get integer value (copy)
    ///
    /// @return Integer value
    type::Integer getInteger() const;

    /// @brief Get real value (copy)
    ///
    /// @return Real value
    type::Real getReal() const;

    /// @brief Get string value (copy)
    ///
    /// @return String value
    type::String getString() const;

    /// @brief Get dictionary value (copy)
    ///
    /// @return Dictionary value
    container::Dictionary getDictionary() const;

    /// @brief Get array value (copy)
    ///
    /// @return Array value
    container::Array<Object> getArray() const;

    /// @brief Convert object to string representation
    ///
    /// @param [in] aFormat A serialization format (default: Undefined)
    /// @return String representation
    type::String toString(const Object::Format& aFormat = Object::Format::Undefined) const;

    /// @brief Convert object to JSON string
    ///
    /// @return JSON string representation
    type::String getJsonString() const;

    /// @brief Access boolean value (mutable)
    ///
    /// @return Reference to boolean value
    bool& accessBoolean();

    /// @brief Access integer value (mutable)
    ///
    /// @return Reference to integer value
    type::Integer& accessInteger();

    /// @brief Access real value (mutable)
    ///
    /// @return Reference to real value
    type::Real& accessReal();

    /// @brief Access string value (mutable)
    ///
    /// @return Reference to string value
    type::String& accessString();

    /// @brief Access dictionary value (mutable)
    ///
    /// @return Reference to dictionary value
    container::Dictionary& accessDictionary();

    /// @brief Access array value (mutable)
    ///
    /// @return Reference to array value
    container::Array<Object>& accessArray();

    /// @brief Construct an undefined object
    ///
    /// @code
    ///     Object object = Object::Undefined() ;
    /// @endcode
    ///
    /// @return Undefined object
    static Object Undefined();

    /// @brief Construct a boolean object
    ///
    /// @code
    ///     Object object = Object::Boolean(true) ;
    /// @endcode
    ///
    /// @param [in] aBoolean A boolean
    /// @return Boolean object
    static Object Boolean(const bool& aBoolean);

    /// @brief Construct an integer object
    ///
    /// @code
    ///     Object object = Object::Integer(123) ;
    /// @endcode
    ///
    /// @param [in] anInteger An integer (default: Undefined)
    /// @return Integer object
    static Object Integer(const type::Integer& anInteger = type::Integer::Undefined());

    /// @brief Construct a real object
    ///
    /// @code
    ///     Object object = Object::Real(1.23) ;
    /// @endcode
    ///
    /// @param [in] aReal A real (default: Undefined)
    /// @return Real object
    static Object Real(const type::Real& aReal = type::Real::Undefined());

    /// @brief Construct a string object
    ///
    /// @code
    ///     Object object = Object::String("Hello World!") ;
    /// @endcode
    ///
    /// @param [in] aString A string (default: Empty)
    /// @return String object
    static Object String(const type::String& aString = type::String::Empty());

    /// @brief Construct a dictionary object
    ///
    /// @code
    ///     Object object = Object::Dictionary(Dictionary::Empty()) ;
    /// @endcode
    ///
    /// @param [in] aDictionary A dictionary
    /// @return Dictionary object
    static Object Dictionary(const container::Dictionary& aDictionary);

    /// @brief Construct an array object
    ///
    /// @code
    ///     Object object = Object::Array() ;
    /// @endcode
    ///
    /// @param [in] anArray An array (default: Empty)
    /// @return Array object
    static Object Array(const container::Array<Object>& anArray = container::Array<Object>::Empty());

    /// @brief Construct an object by parsing a string
    ///
    /// @code
    ///     Object object = Object::Parse("{\"key\": 123}") ;
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @param [in] aFormat A serialization format (default: Undefined)
    /// @return Object
    static Object Parse(const type::String& aString, const Object::Format& aFormat = Object::Format::Undefined);

    /// @brief Construct an object by loading from a file
    ///
    /// @code
    ///     Object object = Object::Load(File::Path(Path::Parse("/path/to/file.json"))) ;
    /// @endcode
    ///
    /// @param [in] aFile A file
    /// @param [in] aFormat A serialization format (default: Undefined)
    /// @return Object
    static Object Load(const filesystem::File& aFile, const Object::Format& aFormat = Object::Format::Undefined);

    OSTK_CORE_DECLARE_ENUM_STRING_CONVERSION(Object::Type, Type, Object)

   private:
    class Impl;

    Unique<Object::Impl> objectImplUPtr_;

    Object(const Unique<Object::Impl>& anObjectImpl);

    static Object ParseJson(const type::String& aString);

    static Object ParseYaml(const type::String& aString);
};

}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
