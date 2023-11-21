/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Containers_Object__
#define __OpenSpaceToolkit_Core_Containers_Object__

#include <fstream>
#include <ostream>

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Pair.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>
#include <OpenSpaceToolkit/Core/Types/Unique.hpp>

namespace ostk
{
namespace core
{
namespace ctnr
{

namespace fs = ostk::core::fs;

using ostk::core::types::Unique;

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

    Object(std::initializer_list<ctnr::Pair<types::String, Object>> aList);

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

    const Object& operator[](const types::String& aKey) const;
    const Object& operator[](const types::Index& anIndex) const;

    Object& operator[](const types::String& aKey);
    Object& operator[](const types::Index& anIndex);

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Object& anObject);

    friend fs::File& operator<<(fs::File& aFile, const Object& anObject);

    friend fs::File& operator>>(fs::File& aFile, Object& anObject);

    bool isDefined() const;
    bool isBoolean() const;
    bool isInteger() const;
    bool isReal() const;
    bool isString() const;
    bool isDictionary() const;
    bool isArray() const;

    const bool& accessBoolean() const;
    const types::Integer& accessInteger() const;
    const types::Real& accessReal() const;
    const types::String& accessString() const;
    const ctnr::Dictionary& accessDictionary() const;
    const ctnr::Array<Object>& accessArray() const;

    Object::Type getType() const;

    bool getBoolean() const;
    types::Integer getInteger() const;
    types::Real getReal() const;
    types::String getString() const;
    ctnr::Dictionary getDictionary() const;
    ctnr::Array<Object> getArray() const;

    types::String toString(const Object::Format& aFormat = Object::Format::Undefined) const;
    types::String getJsonString() const;

    bool& accessBoolean();
    types::Integer& accessInteger();
    types::Real& accessReal();
    types::String& accessString();
    ctnr::Dictionary& accessDictionary();
    ctnr::Array<Object>& accessArray();

    static Object Undefined();

    static Object Boolean(const bool& aBoolean);

    static Object Integer(const types::Integer& anInteger = types::Integer::Undefined());

    static Object Real(const types::Real& aReal = types::Real::Undefined());

    static Object String(const types::String& aString = types::String::Empty());

    static Object Dictionary(const ctnr::Dictionary& aDictionary);

    static Object Array(const ctnr::Array<Object>& anArray = ctnr::Array<Object>::Empty());

    static Object Parse(const types::String& aString, const Object::Format& aFormat = Object::Format::Undefined);

    static Object Load(const fs::File& aFile, const Object::Format& aFormat = Object::Format::Undefined);

    static types::String StringFromType(const Object::Type& aType);

    static Object::Type TypeFromString(const types::String& aString);

   private:
    class Impl;

    Unique<Object::Impl> objectImplUPtr_;

    Object(const Unique<Object::Impl>& anObjectImpl);

    static Object ParseJson(const types::String& aString);

    static Object ParseYaml(const types::String& aString);
};

}  // namespace ctnr
}  // namespace core
}  // namespace ostk

#endif
