////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/// @project        Open Space Toolkit ▸ Core
/// @file           Library/Core/Containers/Object.cpp
/// @author         Lucas Brémond <lucas@loftorbital.com>
/// @license        Apache License 2.0

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Library/Core/Containers/Object.hpp>
#include <Library/Core/Containers/Array.hpp>
#include <Library/Core/Containers/Dictionary.hpp>
#include <Library/Core/Logger.hpp>
#include <Library/Core/Utilities.hpp>

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/filereadstream.h>
#include <rapidjson/filewritestream.h>

#include <boost/any.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace ostk
{
namespace core
{
namespace ctnr
{

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Object::Impl
{

    public:

                                Impl                                        ( ) = delete ;

                                Impl                                        (   const   boost::any&                 anyValue                                    ) ;

        Object::Impl*           clone                                       ( ) const ;

        bool                    operator ==                                 (   const   Object::Impl&               anObject                                    ) const ;
        bool                    operator !=                                 (   const   Object::Impl&               anObject                                    ) const ;

        bool                    isBoolean                                   ( ) const ;
        bool                    isInteger                                   ( ) const ;
        bool                    isReal                                      ( ) const ;
        bool                    isString                                    ( ) const ;
        bool                    isDictionary                                ( ) const ;
        bool                    isArray                                     ( ) const ;

        const bool&             accessBoolean                               ( ) const ;
        const types::Integer&   accessInteger                               ( ) const ;
        const types::Real&      accessReal                                  ( ) const ;
        const types::String&    accessString                                ( ) const ;
        const ctnr::Dictionary& accessDictionary                            ( ) const ;
        const ctnr::Array<Object>& accessArray                              ( ) const ;

        Object::Type            getType                                     ( ) const ;

        bool&                   accessBoolean                               ( ) ;
        types::Integer&         accessInteger                               ( ) ;
        types::Real&            accessReal                                  ( ) ;
        types::String&          accessString                                ( ) ;
        ctnr::Dictionary&       accessDictionary                            ( ) ;
        ctnr::Array<Object>&    accessArray                                 ( ) ;

    private:

        boost::any              value_ ;

} ;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::Impl::Impl                          (   const   boost::any&                 anyValue                                    )
                                :   value_(anyValue)
{
}

Object::Impl*                   Object::Impl::clone                         ( ) const
{
    return new Object::Impl(*this) ;
}

bool                            Object::Impl::operator ==                   (   const   Object::Impl&               anObject                                    ) const
{

    if (value_.type() != anObject.value_.type())
    {
        return false ;
    }

    if (value_.type() == typeid(bool))
    {
        return boost::any_cast<bool>(value_) == boost::any_cast<bool>(anObject.value_) ;
    }

    if (value_.type() == typeid(types::Integer))
    {
        return boost::any_cast<types::Integer>(value_) == boost::any_cast<types::Integer>(anObject.value_) ;
    }

    if (value_.type() == typeid(types::Real))
    {
        return boost::any_cast<types::Real>(value_) == boost::any_cast<types::Real>(anObject.value_) ;
    }

    if (value_.type() == typeid(types::String))
    {
        return boost::any_cast<types::String>(value_) == boost::any_cast<types::String>(anObject.value_) ;
    }

    if (value_.type() == typeid(ctnr::Array<ctnr::Object>))
    {
        return boost::any_cast<ctnr::Array<ctnr::Object>>(value_) == boost::any_cast<ctnr::Array<ctnr::Object>>(anObject.value_) ;
    }

    if (value_.type() == typeid(ctnr::Dictionary))
    {
        return boost::any_cast<ctnr::Dictionary>(value_) == boost::any_cast<ctnr::Dictionary>(anObject.value_) ;
    }

    throw ostk::core::error::runtime::Wrong("Type") ;

    return false ;

}

bool                            Object::Impl::operator !=                   (   const   Object::Impl&               anObject                                    ) const
{
    return !((*this) == anObject) ;
}

bool                            Object::Impl::isBoolean                     ( ) const
{
    return value_.type() == typeid(bool) ;
}

bool                            Object::Impl::isInteger                     ( ) const
{
    return value_.type() == typeid(types::Integer) ;
}

bool                            Object::Impl::isReal                        ( ) const
{
    return value_.type() == typeid(types::Real) ;
}

bool                            Object::Impl::isString                      ( ) const
{
    return value_.type() == typeid(types::String) ;
}

bool                            Object::Impl::isDictionary                  ( ) const
{
    return value_.type() == typeid(ctnr::Dictionary) ;
}

bool                            Object::Impl::isArray                       ( ) const
{
    return value_.type() == typeid(ctnr::Array<ctnr::Object>) ;
}

const bool&                     Object::Impl::accessBoolean                 ( ) const
{

    if (this->isBoolean())
    {
        return boost::any_cast<const bool&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Boolean].") ;

}

const types::Integer&           Object::Impl::accessInteger                 ( ) const
{

    if (this->isInteger())
    {
        return boost::any_cast<const types::Integer&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Integer].") ;

}

const types::Real&              Object::Impl::accessReal                    ( ) const
{

    if (this->isReal())
    {
        return boost::any_cast<const types::Real&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Real].") ;

}

const types::String&            Object::Impl::accessString                  ( ) const
{

    if (this->isString())
    {
        return boost::any_cast<const types::String&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [String].") ;

}

const ctnr::Dictionary&         Object::Impl::accessDictionary              ( ) const
{

    if (this->isDictionary())
    {
        return boost::any_cast<const ctnr::Dictionary&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Dictionary].") ;

}

const ctnr::Array<Object>&      Object::Impl::accessArray                   ( ) const
{

    if (this->isArray())
    {
        return boost::any_cast<const ctnr::Array<Object>&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Array].") ;

}

Object::Type                    Object::Impl::getType                       ( ) const
{

    if (this->isBoolean())
    {
        return Object::Type::Boolean ;
    }

    if (this->isInteger())
    {
        return Object::Type::Integer ;
    }

    if (this->isReal())
    {
        return Object::Type::Real ;
    }

    if (this->isString())
    {
        return Object::Type::String ;
    }

    if (this->isDictionary())
    {
        return Object::Type::Dictionary ;
    }

    if (this->isArray())
    {
        return Object::Type::Array ;
    }

    return Object::Type::Undefined ;

}

bool&                           Object::Impl::accessBoolean                 ( )
{

    if (this->isBoolean())
    {
        return boost::any_cast<bool&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Boolean].") ;

}

types::Integer&                 Object::Impl::accessInteger                 ( )
{

    if (this->isInteger())
    {
        return boost::any_cast<types::Integer&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Integer].") ;

}

types::Real&                    Object::Impl::accessReal                    ( )
{

    if (this->isReal())
    {
        return boost::any_cast<types::Real&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Real].") ;

}

types::String&                  Object::Impl::accessString                  ( )
{

    if (this->isString())
    {
        return boost::any_cast<types::String&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [String].") ;

}

ctnr::Dictionary&               Object::Impl::accessDictionary              ( )
{

    if (this->isDictionary())
    {
        return boost::any_cast<ctnr::Dictionary&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Dictionary].") ;

}

ctnr::Array<Object>&            Object::Impl::accessArray                   ( )
{

    if (this->isArray())
    {
        return boost::any_cast<ctnr::Array<Object>&>(value_) ;
    }

    throw ostk::core::error::RuntimeError("Object is not of type [Array].") ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::Object                              (           std::initializer_list<ctnr::Pair<types::String, Object>> aList          )
                                :   objectImplUPtr_(std::make_unique<Object::Impl>(boost::any(ctnr::Dictionary(aList))))
{

}

                                Object::Object                              (   const   Object&                     anObject                                    )
                                :   objectImplUPtr_((anObject.objectImplUPtr_ != nullptr) ? anObject.objectImplUPtr_->clone() : nullptr)
{
}

                                Object::~Object                             ( )
{
}

Object&                         Object::operator =                          (   const   Object&                     anObject                                    )
{

    if (this != &anObject)
    {
        objectImplUPtr_.reset((anObject.objectImplUPtr_ != nullptr) ? anObject.objectImplUPtr_->clone() : nullptr) ;
    }

    return *this ;

}

bool                            Object::operator ==                         (   const   Object&                     anObject                                    ) const
{
    return ((objectImplUPtr_ == nullptr) && (anObject.objectImplUPtr_ == nullptr)) || ((objectImplUPtr_ != nullptr) && (anObject.objectImplUPtr_ != nullptr) && ((*objectImplUPtr_) == (*anObject.objectImplUPtr_))) ;
}

bool                            Object::operator !=                         (   const   Object&                     anObject                                    ) const
{
    return !((*this) == anObject) ;
}

const Object&                   Object::operator []                         (   const   types::String&              aKey                                        ) const
{

    LOG_SCOPE("Object", "operator [String]") ;

    if (!this->isDictionary())
    {
        throw ostk::core::error::RuntimeError("Object is not a dictionary.") ;
    }

    return this->accessDictionary()[aKey] ;

}

const Object&                   Object::operator []                         (   const   types::Index&               anIndex                                     ) const
{

    LOG_SCOPE("Object", "operator [Index]") ;

    if (!this->isArray())
    {
        throw ostk::core::error::RuntimeError("Object is not an array.") ;
    }

    return this->accessArray()[anIndex] ;

}

Object&                         Object::operator []                         (   const   types::String&              aKey                                        )
{

    LOG_SCOPE("Object", "operator [String]") ;

    if (!this->isDictionary())
    {
        objectImplUPtr_ = std::make_unique<Object::Impl>(boost::any(Dictionary::Empty())) ;
    }

    return this->accessDictionary()[aKey] ;

}

Object&                         Object::operator []                         (   const   types::Index&               anIndex                                     )
{

    LOG_SCOPE("Object", "operator [Index]") ;

    if (!this->isArray())
    {
        objectImplUPtr_ = std::make_unique<Object::Impl>(boost::any(ctnr::Array<Object>::Empty())) ;
    }

    ctnr::Array<Object>& array = this->accessArray() ;

    if (anIndex >= array.getSize())
    {

        ctnr::Array<Object> undefinedObjectArray = ctnr::Array<Object>((anIndex - array.getSize() + 1), Object::Undefined()) ;

        array.insert(array.end(), undefinedObjectArray.begin(), undefinedObjectArray.end()) ;

    }

    return array[anIndex] ;

}

std::ostream&                   operator <<                                 (           std::ostream&               anOutputStream,
                                                                                const   Object&                     anObject                                    )
{

    ostk::core::utils::Print::Header(anOutputStream, "Object") ;

    ostk::core::utils::Print::Line(anOutputStream) << "Type:" << Object::StringFromType(anObject.getType()) ;

    if (anObject.isDefined())
    {
        ostk::core::utils::Print::Separator(anOutputStream) ;
    }

    switch (anObject.getType())
    {

        case Object::Type::Undefined:
            break ;

        case Object::Type::Boolean:
            ostk::core::utils::Print::Line(anOutputStream) << anObject.accessBoolean() ;
            break ;

        case Object::Type::Integer:
            ostk::core::utils::Print::Line(anOutputStream) << anObject.accessInteger() ;
            break ;

        case Object::Type::Real:
            ostk::core::utils::Print::Line(anOutputStream) << anObject.accessReal() ;
            break ;

        case Object::Type::String:
            ostk::core::utils::Print::Line(anOutputStream) << anObject.accessString() ;
            break ;

        case Object::Type::Dictionary:
            ostk::core::utils::Print::Line(anOutputStream) << anObject.accessDictionary() ;
            break ;

        case Object::Type::Array:
        {

            Integer index = 0 ;

            for (const auto& arrayElement: anObject.accessArray())
            {

                ostk::core::utils::Print::Line(anOutputStream) << ("- [" + index.toString() + "]: ") << arrayElement.toString(Object::Format::JSON) ;

                index++ ;

            }

            break ;

        }

        default:
            throw ostk::core::error::runtime::Wrong("Type") ;
            break ;

    }

    ostk::core::utils::Print::Footer(anOutputStream) ;

    return anOutputStream ;

}

fs::File&                       operator <<                                 (           fs::File&                   aFile,
                                                                                const   Object&                     anObject                                    )
{

    // [TBM] This should be improved, supporting format manipulators and iterative string generation

    aFile.accessStream() << anObject.toString(Object::Format::JSON) ;

    return aFile ;

}

fs::File&                       operator >>                                 (           fs::File&                   aFile,
                                                                                        Object&                     anObject                                    )
{

    // [TBM] This should be improved, supporting format manipulators

    anObject = Object::Load(aFile, Object::Format::JSON) ;

    return aFile ;

}

bool                            Object::isDefined                           ( ) const
{
    return objectImplUPtr_ != nullptr ;
}

bool                            Object::isBoolean                           ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->isBoolean() : false ;
}

bool                            Object::isInteger                           ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->isInteger() : false ;
}

bool                            Object::isReal                              ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->isReal() : false ;
}

bool                            Object::isString                            ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->isString() : false ;
}

bool                            Object::isDictionary                        ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->isDictionary() : false ;
}

bool                            Object::isArray                             ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->isArray() : false ;
}

const bool&                     Object::accessBoolean                       ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessBoolean() ;

}

const types::Integer&           Object::accessInteger                       ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessInteger() ;

}

const types::Real&              Object::accessReal                          ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessReal() ;

}

const types::String&            Object::accessString                        ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessString() ;

}

const ctnr::Dictionary&         Object::accessDictionary                    ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessDictionary() ;

}

const ctnr::Array<Object>&      Object::accessArray                         ( ) const
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessArray() ;

}

Object::Type                    Object::getType                             ( ) const
{
    return (objectImplUPtr_ != nullptr) ? objectImplUPtr_->getType() : Object::Type::Undefined ;
}

bool                            Object::getBoolean                          ( ) const
{
    return this->accessBoolean() ;
}

types::Integer                  Object::getInteger                          ( ) const
{
    return this->accessInteger() ;
}

types::Real                     Object::getReal                             ( ) const
{
    return this->accessReal() ;
}

types::String                   Object::getString                           ( ) const
{
    return this->accessString() ;
}

ctnr::Dictionary                Object::getDictionary                       ( ) const
{
    return this->accessDictionary() ;
}

ctnr::Array<Object>             Object::getArray                            ( ) const
{
    return this->accessArray() ;
}

types::String                   Object::toString                            (   const   Object::Format&             aFormat                                     ) const
{

    LOG_SCOPE("Object", "toString") ;

    switch (aFormat)
    {

        case Object::Format::Undefined:
            break ;

        case Object::Format::JSON:
            return this->getJsonString() ;

        // case Object::Format::XML:
        //     break ;

        default:
            break ;

    }

    throw ostk::core::error::runtime::Wrong("Format") ;

    return types::String::Empty() ;

}

types::String                   Object::getJsonString                       ( ) const
{

    LOG_SCOPE("Object", "getJsonString") ;

    rapidjson::Document jsonDocument ;

    std::function<rapidjson::Value(const Object&)> ValueFromObject =
    [&jsonDocument, &ValueFromObject]
    (const Object& anObject) -> rapidjson::Value
    {

        rapidjson::Value value ;

        switch (anObject.getType())
        {

            case Object::Type::Undefined:
                value.SetNull() ;
                break ;

            case Object::Type::Boolean:
                value.SetBool(anObject.accessBoolean()) ;
                break ;

            case Object::Type::Integer:
            {

                const types::Integer& integer = anObject.accessInteger() ;

                if (integer.isDefined() && integer.isFinite())
                {
                    value.SetInt(integer) ;
                }
                else
                {

                    const types::String string = integer.toString() ;

                    value.SetString(string.data(), string.length()) ;

                }

                break ;

            }

            case Object::Type::Real:
                value.SetDouble(anObject.accessReal()) ;
                break ;

            case Object::Type::String:
                value.SetString(anObject.accessString().data(), anObject.accessString().length()) ;
                break ;

            case Object::Type::Dictionary:
            {

                value.SetObject() ;

                for (const auto& dictIt : anObject.accessDictionary())
                {
                    value.AddMember(rapidjson::Value(dictIt.accessKey().data(), dictIt.accessKey().length()).Move(), ValueFromObject(dictIt.accessValue()), jsonDocument.GetAllocator()) ;
                }

                break ;

            }

            case Object::Type::Array:
            {

                value.SetArray() ;

                rapidjson::Document::AllocatorType& allocator = jsonDocument.GetAllocator() ;

                for (const auto& object : anObject.accessArray())
                {
                    value.PushBack(ValueFromObject(object), allocator) ;
                }

                break ;

            }

            default:
                throw ostk::core::error::runtime::Wrong("Type") ;
                break ;

        }

        return value ;

    } ;

    jsonDocument.CopyFrom(ValueFromObject(*this), jsonDocument.GetAllocator()) ;

    rapidjson::StringBuffer buffer ;

    rapidjson::Writer<rapidjson::StringBuffer, rapidjson::UTF8<>, rapidjson::UTF8<>, rapidjson::CrtAllocator, rapidjson::kWriteNanAndInfFlag> writer(buffer) ;

    jsonDocument.Accept(writer) ;

    return buffer.GetString() ;

}

bool&                           Object::accessBoolean                       ( )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessBoolean() ;

}

types::Integer&                 Object::accessInteger                       ( )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessInteger() ;

}

types::Real&                    Object::accessReal                          ( )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessReal() ;

}

types::String&                  Object::accessString                        ( )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessString() ;

}

ctnr::Dictionary&               Object::accessDictionary                    ( )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessDictionary() ;

}

ctnr::Array<Object>&            Object::accessArray                         ( )
{

    if (!this->isDefined())
    {
        throw ostk::core::error::runtime::Undefined("Object") ;
    }

    return objectImplUPtr_->accessArray() ;

}

Object                          Object::Undefined                           ( )
{
    return Object(nullptr) ;
}

Object                          Object::Boolean                             (   const   bool&                       aBoolean                                    )
{
    return Object(std::make_unique<Object::Impl>(boost::any(aBoolean))) ;
}

Object                          Object::Integer                             (   const   types::Integer&             anInteger                                   )
{
    return Object(std::make_unique<Object::Impl>(boost::any(anInteger))) ;
}

Object                          Object::Real                                (   const   types::Real&                aReal                                       )
{
    return Object(std::make_unique<Object::Impl>(boost::any(aReal))) ;
}

Object                          Object::String                              (   const   types::String&              aString                                     )
{
    return Object(std::make_unique<Object::Impl>(boost::any(aString))) ;
}

Object                          Object::Dictionary                          (   const   ctnr::Dictionary&           aDictionary                                 )
{
    return Object(std::make_unique<Object::Impl>(boost::any(aDictionary))) ;
}

Object                          Object::Array                               (   const   ctnr::Array<Object>&        anArray                                     )
{
    return Object(std::make_unique<Object::Impl>(boost::any(anArray))) ;
}

Object                          Object::Parse                               (   const   types::String&              aString,
                                                                                const   Object::Format&             aFormat                                     )
{

    switch (aFormat)
    {

        case Object::Format::Undefined:
        {

            // Automatically detect format

            if ((!aString.isEmpty()) && (aString.getFirst() == '{') && (aString.getLast() == '}'))
            {
                return Object::ParseJson(aString) ;
            }
            else
            {
                throw ostk::core::error::RuntimeError("Cannot detect format.") ;
            }

            break ;

        }

        case Object::Format::JSON:
            return Object::ParseJson(aString) ;

        default:
            break ;
    }

    throw ostk::core::error::runtime::Wrong("Format") ;

    return Object::Undefined() ;

}

Object                          Object::ParseJson                           (   const   types::String&              aString                                     )
{

    LOG_SCOPE("Object", "ParseJson") ;

    if (aString.isEmpty())
    {
        return Object::Undefined() ;
    }

    std::function<Object (const rapidjson::Value&)> parseJson =
    [&parseJson]
    (const rapidjson::Value& aJsonValue) -> Object
    {

        if (aJsonValue.IsNull()) // Value is Null
        {
            return Object::Undefined() ;
        }
        else if (aJsonValue.IsBool()) // Value is Boolean
        {
            return Object::Boolean(aJsonValue.GetBool()) ;
        }
        else if (aJsonValue.IsNumber()) // Value is Number
        {

            if (aJsonValue.IsInt() || aJsonValue.IsUint() || aJsonValue.IsInt64() || aJsonValue.IsUint64())
            {
                return Object::Integer(aJsonValue.GetInt()) ;
            }
            else if (aJsonValue.IsDouble())
            {
                return Object::Real(aJsonValue.GetDouble()) ;
            }
            else
            {
                throw ostk::core::error::runtime::Wrong("Number") ;
            }

        }
        else if (aJsonValue.IsString()) // Object is String
        {

            const types::String jsonValueString = aJsonValue.GetString() ;

            return Object::String(jsonValueString) ;

        }
        else if (aJsonValue.IsObject()) // Object is Object
        {

            ctnr::Dictionary dictionary = ctnr::Dictionary::Empty() ;

            for (const auto& objectIt : aJsonValue.GetObject())
            {
                dictionary[objectIt.name.GetString()] = parseJson(objectIt.value) ;
            }

            return Object::Dictionary(dictionary) ;

        }
        else if (aJsonValue.IsArray()) // Object is [Array]
        {

            if (aJsonValue.Empty())
            {
                return Object::Array() ;
            }

            ctnr::Array<Object> array = ctnr::Array<Object>::Empty() ;

            for (const auto& arrayElement : aJsonValue.GetArray())
            {
                array.add(parseJson(arrayElement)) ;
            }

            return Object::Array(array) ;

        }
        else
        {
            throw ostk::core::error::runtime::Wrong("Value") ;
        }

        return Object::Undefined() ;

    } ;

    rapidjson::StringStream jsonStream(aString.data()) ;

    rapidjson::Document jsonDocument ;

    if (jsonDocument.ParseStream<rapidjson::kParseNanAndInfFlag | rapidjson::kParseCommentsFlag>(jsonStream).HasParseError())
    {
        throw ostk::core::error::RuntimeError("Cannot parse JSON string [" + aString + "].") ;
    }

    const Object object = parseJson(jsonDocument) ;

    return object ;

}

Object                          Object::Load                                (   const   fs::File&                   aFile,
                                                                                const   Object::Format&             aFormat                                     )
{

    LOG_SCOPE("Object", "Load") ;

    if (!aFile.isDefined())
    {
        throw ostk::core::error::runtime::Undefined("File") ;
    }

    if (!aFile.exists())
    {
        throw ostk::core::error::RuntimeError("File [{}] does not exist.", aFile.toString()) ;
    }

    return Object::Parse(aFile.getContents(), aFormat) ;

}

types::String                   Object::StringFromType                      (   const   Object::Type&               aType                                       )
{

    LOG_SCOPE("Object", "StringFromType") ;

    switch (aType)
    {

        case Object::Type::Undefined:
            return "Undefined" ;

        case Object::Type::Boolean:
            return "Boolean" ;

        case Object::Type::Integer:
            return "Integer" ;

        case Object::Type::Real:
            return "Real" ;

        case Object::Type::String:
            return "String" ;

        case Object::Type::Dictionary:
            return "Dictionary" ;

        case Object::Type::Array:
            return "Array" ;

        default:
            throw ostk::core::error::runtime::Wrong("Type") ;
            break ;

    }

    return types::String::Empty() ;

}

Object::Type                    Object::TypeFromString                      (   const   types::String&              aString                                     )
{

    LOG_SCOPE("Object", "TypeFromString") ;

    if (aString == "Undefined")
    {
        return Object::Type::Undefined ;
    }

    if (aString == "Boolean")
    {
        return Object::Type::Boolean ;
    }

    if (aString == "Integer")
    {
        return Object::Type::Integer ;
    }

    if (aString == "Real")
    {
        return Object::Type::Real ;
    }

    if (aString == "String")
    {
        return Object::Type::String ;
    }

    if (aString == "Dictionary")
    {
        return Object::Type::Dictionary ;
    }

    if (aString == "Array")
    {
        return Object::Type::Array ;
    }

    throw ostk::core::error::runtime::Wrong("Type", aString) ;

    return Object::Type::Undefined ;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                Object::Object                              (   const   Unique<Object::Impl>&       anObjectImpl                                )
                                :   objectImplUPtr_((anObjectImpl != nullptr) ? anObjectImpl->clone() : nullptr)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

}
}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
