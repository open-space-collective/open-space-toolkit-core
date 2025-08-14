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

/// @brief                      Universal type container
///
/// @note                       The current implementation uses boost::any internally. This may be replaced soon for
/// portability.
/// @note                       The current implementation is not efficient, as two new operators are called. This is
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

    /// @brief              Default constructor (disabled)

    Object() = delete;

    /// @brief              Constructs an object using an initializer list
    ///
    /// @code
    ///                     Object object = {{ "Key A": Object::Integer(123) }, { "Key B": Object::String("Hello
    ///                     World!") }} ;
    /// @endcode
    ///
    /// @param              [in] aList An initializer list

    Object(std::initializer_list<container::Pair<type::String, Object>> aList);

    /// @brief              Copy constructor
    ///
    /// @param              [in] anObject An object

    Object(const Object& anObject);

    /// @brief              Destructor

    ~Object();

    /// @brief              Copy assignment operator
    ///
    /// @param              [in] anObject An object
    /// @return             Reference to object

    Object& operator=(const Object& anObject);

    /// @brief              Equal to operator
    ///
    /// @code
    ///                     Object firstObject = Object::Integer(123) ;
    ///                     Object secondObject = Object::Integer(123) ;
    ///                     firstObject == secondObject ; // True
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are equal

    bool operator==(const Object& anObject) const;

    /// @brief              Not equal to operator
    ///
    /// @code
    ///                     Object firstObject = Object::Integer(123) ;
    ///                     Object secondObject = Object::Integer(456) ;
    ///                     firstObject != secondObject ; // True
    /// @endcode
    ///
    /// @param              [in] anObject An object
    /// @return             True if objects are not equal

    bool operator!=(const Object& anObject) const;

    const Object& operator[](const type::String& aKey) const;
    const Object& operator[](const type::Index& anIndex) const;

    Object& operator[](const type::String& aKey);
    Object& operator[](const type::Index& anIndex);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    friend filesystem::File& operator<<(filesystem::File& aFile, const Object& anObject);

    friend filesystem::File& operator>>(filesystem::File& aFile, Object& anObject);

    bool isDefined() const;
    bool isBoolean() const;
    bool isInteger() const;
    bool isReal() const;
    bool isString() const;
    bool isDictionary() const;
    bool isArray() const;

    const bool& accessBoolean() const;
    const type::Integer& accessInteger() const;
    const type::Real& accessReal() const;
    const type::String& accessString() const;
    const container::Dictionary& accessDictionary() const;
    const container::Array<Object>& accessArray() const;

    Object::Type getType() const;

    bool getBoolean() const;
    type::Integer getInteger() const;
    type::Real getReal() const;
    type::String getString() const;
    container::Dictionary getDictionary() const;
    container::Array<Object> getArray() const;

    type::String toString(const Object::Format& aFormat = Object::Format::Undefined) const;
    type::String getJsonString() const;

    bool& accessBoolean();
    type::Integer& accessInteger();
    type::Real& accessReal();
    type::String& accessString();
    container::Dictionary& accessDictionary();
    container::Array<Object>& accessArray();

    static Object Undefined();

    static Object Boolean(const bool& aBoolean);

    static Object Integer(const type::Integer& anInteger = type::Integer::Undefined());

    static Object Real(const type::Real& aReal = type::Real::Undefined());

    static Object String(const type::String& aString = type::String::Empty());

    static Object Dictionary(const container::Dictionary& aDictionary);

    static Object Array(const container::Array<Object>& anArray = container::Array<Object>::Empty());

    static Object Parse(const type::String& aString, const Object::Format& aFormat = Object::Format::Undefined);

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
