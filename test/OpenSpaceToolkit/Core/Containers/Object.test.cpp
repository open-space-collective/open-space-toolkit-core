/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/FileSystem/File.hpp>
#include <OpenSpaceToolkit/Core/Logger.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Containers_Object, InitializerListConstructor)
{
    using ostk::core::ctnr::Object;

    {
        Object object = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_TRUE(object.isDefined());
        EXPECT_TRUE(object.isDictionary());

        EXPECT_FALSE(object["Undefined"].isDefined());
        EXPECT_TRUE(object["Boolean"].isBoolean());
        EXPECT_TRUE(object["Integer"].isInteger());
        EXPECT_TRUE(object["Real"].isReal());
        EXPECT_TRUE(object["String"].isString());

        EXPECT_EQ(true, object["Boolean"].getBoolean());
        EXPECT_EQ(123, object["Integer"].getInteger());
        EXPECT_EQ(123.456, object["Real"].getReal());
        EXPECT_EQ("Hello World!", object["String"].getString());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, CopyConstructor)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        Object firstObject = Object::Integer(123);

        EXPECT_NO_THROW(Object secondObject(firstObject); (void)secondObject;);

        Object secondObject(firstObject);

        EXPECT_EQ(firstObject, secondObject);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AssignmentOperator)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        Object firstObject = Object::Integer(123);

        EXPECT_NO_THROW(Object secondObject = firstObject; (void)secondObject;);

        Object secondObject = firstObject;

        EXPECT_EQ(firstObject, secondObject);
    }

    {
        Object firstObject = Object::Integer(123);
        Object secondObject = Object::Real(123.456);

        EXPECT_NO_THROW(secondObject = firstObject);

        EXPECT_EQ(firstObject, secondObject);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, EqualToOperator)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        EXPECT_TRUE(Object::Integer(123) == Object::Integer(123));
        EXPECT_TRUE(Object::Real(123.456) == Object::Real(123.456));
        EXPECT_TRUE(Object::String("abc") == Object::String("abc"));
    }

    {
        EXPECT_FALSE(Object::Integer(123) == Object::Integer(456));
        EXPECT_FALSE(Object::Real(123.456) == Object::Real(123.000));
        EXPECT_FALSE(Object::String("abc") == Object::String("def"));

        EXPECT_FALSE(Object::Integer(123) == Object::Real(123));
        EXPECT_FALSE(Object::Integer(123) == Object::String("123"));
        EXPECT_FALSE(Object::Real(123.456) == Object::String("123.456"));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, NotEqualToOperator)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        EXPECT_FALSE(Object::Integer(123) != Object::Integer(123));
        EXPECT_FALSE(Object::Real(123.456) != Object::Real(123.456));
        EXPECT_FALSE(Object::String("abc") != Object::String("abc"));
    }

    {
        EXPECT_TRUE(Object::Integer(123) != Object::Integer(456));
        EXPECT_TRUE(Object::Real(123.456) != Object::Real(123.000));
        EXPECT_TRUE(Object::String("abc") != Object::String("def"));

        EXPECT_TRUE(Object::Integer(123) != Object::Real(123));
        EXPECT_TRUE(Object::Integer(123) != Object::String("123"));
        EXPECT_TRUE(Object::Real(123.456) != Object::String("123.456"));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, KeySubscriptOperator)
{
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Object;

    {
        Dictionary dictionary = {{"Key", Object::String("Value")}};

        Object object = Object::Dictionary(dictionary);

        EXPECT_EQ("Value", object["Key"].getString());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IndexSubscriptOperator)
{
    using ostk::core::types::Size;
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Array();
        EXPECT_EQ(Size(0), object.accessArray().getSize());

        EXPECT_TRUE(object.isArray());

        object[0] = Object::Boolean(true);
        object[1] = Object::Integer(123);
        object[2] = Object::Real(123.456);
        object[3] = Object::String("abc");

        EXPECT_TRUE(object.isArray());
        EXPECT_EQ(Size(4), object.accessArray().getSize());

        EXPECT_EQ(true, object[0].getBoolean());
        EXPECT_EQ(123, object[1].getInteger());
        EXPECT_EQ(123.456, object[2].getReal());
        EXPECT_EQ("abc", object[3].getString());
    }

    {
        Object object = Object::Undefined();

        EXPECT_FALSE(object.isArray());

        object[3] = Object::String("abc");

        EXPECT_TRUE(object.isArray());
        EXPECT_EQ(Size(4), object.accessArray().getSize());

        EXPECT_FALSE(object[0].isDefined());
        EXPECT_FALSE(object[1].isDefined());
        EXPECT_FALSE(object[2].isDefined());
        EXPECT_EQ("abc", object[3].getString());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, StreamOperator)
{
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Undefined();

        object["Integer"] = Object::Integer(123);
        object["Real"] = Object::Real(123.456);
        object["String"] = Object::String("Hello World!");

        testing::internal::CaptureStdout();

        EXPECT_NO_THROW(std::cout << object << std::endl);

        EXPECT_FALSE(testing::internal::GetCapturedStdout().empty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, OutputFileStreamOperator)
{
    using ostk::core::ctnr::Object;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        Object object = Object::Undefined();

        object["Integer"] = Object::Integer(123);
        object["Real"] = Object::Real(123.456);
        object["String"] = Object::String("Hello World!");

        File file = File::Path(Path::Parse("/tmp/test.json"));

        file.create();

        file.open(File::OpenMode::Truncate);

        file << object;

        file.close();

        EXPECT_TRUE(file.exists());
        EXPECT_EQ("{\"Integer\":123,\"Real\":123.456,\"String\":\"Hello World!\"}", file.getContents());

        file.remove();
    }

    {
        Object object = Object::Undefined();

        object["Integer"] = Object::Integer(123);
        object["Real"] = Object::Real(123.456);
        object["String"] = Object::String("Hello World!");

        File file = File::Undefined();

        EXPECT_ANY_THROW(file << object);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, InputFileStreamOperator)
{
    using ostk::core::ctnr::Object;
    using ostk::core::fs::Path;
    using ostk::core::fs::File;

    {
        Object object = Object::Undefined();

        object["Integer"] = Object::Integer(123);
        object["Real"] = Object::Real(123.456);
        object["String"] = Object::String("Hello World!");

        File file = File::Path(Path::Parse("/tmp/test.json"));

        file.create();

        file.open(File::OpenMode::Truncate);

        file << object;

        file.close();

        Object loadedObject = Object::Undefined();

        file.open(File::OpenMode::Read);

        file >> loadedObject;

        file.close();

        EXPECT_EQ(object, loadedObject);

        file.remove();
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsDefined)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    {
        EXPECT_TRUE(Object::Integer(123).isDefined());
        EXPECT_TRUE(Object::Real(123.456).isDefined());
        EXPECT_TRUE(Object::String("abc").isDefined());
        EXPECT_TRUE(Object::Dictionary(Dictionary::Empty()).isDefined());
        EXPECT_TRUE(Object::Array().isDefined());
    }

    {
        EXPECT_FALSE(Object::Undefined().isDefined());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsBoolean)
{
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    EXPECT_TRUE(Object::Boolean(true).isBoolean());
    EXPECT_TRUE(Object::Boolean(false).isBoolean());

    EXPECT_FALSE(Object::Undefined().isBoolean());
    EXPECT_FALSE(Object::Integer(123).isBoolean());
    EXPECT_FALSE(Object::Real(123).isBoolean());
    EXPECT_FALSE(Object::String("123").isBoolean());
    EXPECT_FALSE(Object::Dictionary(Dictionary::Empty()).isBoolean());
    EXPECT_FALSE(Object::Array().isBoolean());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsInteger)
{
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    EXPECT_TRUE(Object::Integer(123).isInteger());

    EXPECT_FALSE(Object::Undefined().isInteger());
    EXPECT_FALSE(Object::Boolean(true).isInteger());
    EXPECT_FALSE(Object::Real(123).isInteger());
    EXPECT_FALSE(Object::String("123").isInteger());
    EXPECT_FALSE(Object::Dictionary(Dictionary::Empty()).isInteger());
    EXPECT_FALSE(Object::Array().isInteger());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsReal)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    EXPECT_TRUE(Object::Real(123.456).isReal());

    EXPECT_FALSE(Object::Undefined().isReal());
    EXPECT_FALSE(Object::Boolean(true).isReal());
    EXPECT_FALSE(Object::Integer(123).isReal());
    EXPECT_FALSE(Object::String("123").isReal());
    EXPECT_FALSE(Object::Dictionary(Dictionary::Empty()).isReal());
    EXPECT_FALSE(Object::Array().isReal());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsString)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    EXPECT_TRUE(Object::String("abc").isString());
    EXPECT_TRUE(Object::String("123").isString());

    EXPECT_FALSE(Object::Undefined().isString());
    EXPECT_FALSE(Object::Boolean(true).isString());
    EXPECT_FALSE(Object::Integer(123).isString());
    EXPECT_FALSE(Object::Real(123.456).isString());
    EXPECT_FALSE(Object::Dictionary(Dictionary::Empty()).isString());
    EXPECT_FALSE(Object::Array().isString());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsDictionary)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    {
        EXPECT_TRUE(Object::Dictionary(Dictionary::Empty()).isDictionary());

        EXPECT_FALSE(Object::Undefined().isDictionary());
        EXPECT_FALSE(Object::Boolean(true).isDictionary());
        EXPECT_FALSE(Object::Integer(123).isDictionary());
        EXPECT_FALSE(Object::Real(123.456).isDictionary());
        EXPECT_FALSE(Object::String("abc").isDictionary());
        EXPECT_FALSE(Object::Array().isDictionary());
    }

    {
        Dictionary dictionary = Dictionary::Empty();

        dictionary["Key"] = Object::String("Value");

        Object object = Object::Dictionary(dictionary);

        EXPECT_TRUE(object.isDictionary());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, IsArray)
{
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    {
        EXPECT_TRUE(Object::Array().isArray());
        EXPECT_TRUE(Object::Array({Object::Boolean(true), Object::Integer(123), Object::Real(123.456)}).isArray());

        EXPECT_FALSE(Object::Undefined().isArray());
        EXPECT_FALSE(Object::Boolean(true).isArray());
        EXPECT_FALSE(Object::Integer(123).isArray());
        EXPECT_FALSE(Object::Real(123.456).isArray());
        EXPECT_FALSE(Object::String("abc").isArray());
        EXPECT_FALSE(Object::Dictionary(Dictionary::Empty()).isArray());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AccessBoolean)
{
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Boolean(true);

        EXPECT_EQ(true, object.accessBoolean());

        object.accessBoolean() = false;

        EXPECT_EQ(false, object.accessBoolean());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AccessInteger)
{
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Integer(123);

        EXPECT_EQ(123, object.accessInteger());

        object.accessInteger() = 456;

        EXPECT_EQ(456, object.accessInteger());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AccessReal)
{
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Real(123.456);

        EXPECT_EQ(123.456, object.accessReal());

        object.accessReal() = 456.789;

        EXPECT_EQ(456.789, object.accessReal());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AccessString)
{
    using ostk::core::ctnr::Object;

    {
        Object object = Object::String("abc");

        EXPECT_EQ("abc", object.accessString());

        object.accessString() = "def";

        EXPECT_EQ("def", object.accessString());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AccessDictionary)
{
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Dictionary({{"Key", Object::String("Value")}});

        EXPECT_EQ(Dictionary({{"Key", Object::String("Value")}}), object.accessDictionary());

        object.accessDictionary() = Dictionary({{"Key 2", Object::String("Value 2")}});

        EXPECT_EQ(Dictionary({{"Key 2", Object::String("Value 2")}}), object.accessDictionary());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, AccessArray)
{
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Array({Object::Integer(123), Object::Real(123.456), Object::String("Value")});

        EXPECT_EQ(
            Array<Object>({Object::Integer(123), Object::Real(123.456), Object::String("Value")}), object.accessArray()
        );

        object.accessArray()[0] = Object::String("Hello");
        object.accessArray()[1] = Object::Real(456.789);
        object.accessArray()[2] = Object::Integer(456);

        object.accessArray().add(Object::Undefined());
        object.accessArray().add(Object::Boolean(true));

        EXPECT_EQ(
            Array<Object>(
                {Object::String("Hello"),
                 Object::Real(456.789),
                 Object::Integer(456),
                 Object::Undefined(),
                 Object::Boolean(true)}
            ),
            object.accessArray()
        );
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, GetType)
{
    using ostk::core::types::Integer;
    using ostk::core::types::Real;
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        EXPECT_EQ(Object::Type::Undefined, Object::Undefined().getType());
        EXPECT_EQ(Object::Type::Integer, Object::Integer(Integer(123)).getType());
        EXPECT_EQ(Object::Type::Real, Object::Real(Real(123.456)).getType());
        EXPECT_EQ(Object::Type::String, Object::String(String("abc")).getType());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, GetBoolean)
{
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Boolean(true);

        EXPECT_EQ(true, object.getBoolean());
    }

    {
        Object object = Object::Boolean(true);

        EXPECT_EQ(true, object.getBoolean());
    }

    {
        EXPECT_ANY_THROW(Object::Undefined().getBoolean());
        EXPECT_ANY_THROW(Object::Real(123).getBoolean());
        EXPECT_ANY_THROW(Object::String("123").getBoolean());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, GetInteger)
{
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Integer(123);

        EXPECT_EQ(123, object.getInteger());
    }

    {
        Object object = Object::Integer(-123);

        EXPECT_EQ(-123, object.getInteger());
    }

    {
        EXPECT_ANY_THROW(Object::Undefined().getInteger());
        EXPECT_ANY_THROW(Object::Real(123).getInteger());
        EXPECT_ANY_THROW(Object::String("123").getInteger());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, GetReal)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Object;

    {
        Object object = Object::Real(123.456);

        EXPECT_EQ(123.456, object.getReal());
    }

    {
        Object object = Object::Real(-123.456);

        EXPECT_EQ(-123.456, object.getReal());
    }

    {
        EXPECT_ANY_THROW(Object::Undefined().getReal());
        EXPECT_ANY_THROW(Object::Integer(123).getReal());
        EXPECT_ANY_THROW(Object::String("123").getReal());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, GetString)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        Object object = Object::String("abc");

        EXPECT_EQ("abc", object.getString());
    }

    {
        Object object = Object::String("");

        EXPECT_EQ("", object.getString());
    }

    {
        EXPECT_ANY_THROW(Object::Undefined().getString());
        EXPECT_ANY_THROW(Object::Integer(123).getString());
        EXPECT_ANY_THROW(Object::Real(123.456).getString());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, GetDictionary)
{
    using ostk::core::ctnr::Dictionary;
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    {
        Dictionary dictionary = Dictionary::Empty();

        dictionary["Undefined"] = Object::Undefined();
        dictionary["Boolean"] = Object::Boolean(false);
        dictionary["Integer"] = Object::Integer(123);
        dictionary["Real"] = Object::Real(123.456);
        dictionary["String"] = Object::String("Value");
        dictionary["Dictionary"]["A"] = Object::Integer(456);
        dictionary["Dictionary"]["B"] = Object::Real(456.789);
        dictionary["Dictionary"]["C"] = Object::String("Value");

        Object object = Object::Dictionary(dictionary);

        EXPECT_EQ(dictionary, object.getDictionary());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, Undefined)
{
    using ostk::core::ctnr::Object;

    EXPECT_FALSE(Object::Undefined().isDefined());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, Integer)
{
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Object;

    EXPECT_NO_THROW(Object::Integer(123));

    Object object = Object::Integer(123);

    EXPECT_TRUE(object.isDefined());
    EXPECT_EQ(123, object.getInteger());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, Real)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Object;

    EXPECT_NO_THROW(Object::Real(123.456));

    Object object = Object::Real(123.456);

    EXPECT_TRUE(object.isDefined());
    EXPECT_EQ(123.456, object.getReal());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, String)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;

    EXPECT_NO_THROW(Object::String("abc"));

    Object object = Object::String("abc");

    EXPECT_TRUE(object.isDefined());
    EXPECT_EQ("abc", object.getString());
}

TEST(OpenSpaceToolkit_Core_Containers_Object, Dictionary)
{
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Object;

    {
        EXPECT_NO_THROW(Object::Dictionary({{"Key", Object::String("Value")}}));

        Object object = Object::Dictionary({{"Key", Object::String("Value")}});

        EXPECT_TRUE(object.isDefined());
        EXPECT_EQ(Dictionary({{"Key", Object::String("Value")}}), object.getDictionary());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, Array)
{
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    {
        EXPECT_NO_THROW(Object::Array({Object::Integer(123), Object::Real(123.456), Object::String("Value")}));

        Object object = Object::Array({{Object::Integer(123), Object::Real(123.456), Object::String("Value")}});

        EXPECT_TRUE(object.isDefined());
        EXPECT_EQ(
            Array<Object>({Object::Integer(123), Object::Real(123.456), Object::String("Value")}), object.getArray()
        );
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Object, Parse)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Dictionary;
    using ostk::core::ctnr::Array;
    using ostk::core::ctnr::Object;

    // JSON

    {

        {

            const String jsonString = "";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Undefined, object.getType());
}

{
    const String jsonString = "false";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Boolean, object.getType());

    EXPECT_EQ(false, object.getBoolean());
}

{
    const String jsonString = "true";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Boolean, object.getType());

    EXPECT_EQ(true, object.getBoolean());
}

{
    const String jsonString = "0";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Integer, object.getType());

    EXPECT_EQ(0, object.getInteger());
}

{
    const String jsonString = "-123";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Integer, object.getType());

    EXPECT_EQ(-123, object.getInteger());
}

{
    const String jsonString = "123";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Integer, object.getType());

    EXPECT_EQ(123, object.getInteger());
}

{
    const String jsonString = "0.0";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Real, object.getType());

    EXPECT_EQ(0.0, object.getReal());
}

{
    const String jsonString = "-123.456";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Real, object.getType());

    EXPECT_EQ(-123.456, object.getReal());
}

{
    const String jsonString = "123.456";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Real, object.getType());

    EXPECT_EQ(123.456, object.getReal());
}

{
    const String jsonString = "\"abc\"";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::String, object.getType());

    EXPECT_EQ("abc", object.getString());
}

{
    const String jsonString = "\"abcdef,./<>?;:[]{}|-=!@#$%^&*()_+\"";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::String, object.getType());

    EXPECT_EQ("abcdef,./<>?;:[]{}|-=!@#$%^&*()_+", object.getString());
}

{
    const String jsonString = "\"abc\\\"'def\"";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::String, object.getType());

    EXPECT_EQ("abc\"'def", object.getString());
}

{
    const String jsonString = "{\"Key\": \"Value\"}";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Dictionary, object.getType());

    EXPECT_EQ(Dictionary({{"Key", Object::String("Value")}}), object.getDictionary());
}

{
    const String jsonString = "[null, true, 123, 456.789, \"abc\"]";

    EXPECT_NO_THROW(Object::Parse(jsonString, Object::Format::JSON));

    const Object object = Object::Parse(jsonString, Object::Format::JSON);

    EXPECT_EQ(Object::Type::Array, object.getType());

    EXPECT_TRUE(object.isArray());

    EXPECT_FALSE(object[0].isDefined());
    EXPECT_TRUE(object[1].isBoolean());
    EXPECT_TRUE(object[2].isInteger());
    EXPECT_TRUE(object[3].isReal());
    EXPECT_TRUE(object[4].isString());

    EXPECT_EQ(true, object[1].getBoolean());
    EXPECT_EQ(123, object[2].getInteger());
    EXPECT_EQ(456.789, object[3].getReal());
    EXPECT_EQ("abc", object[4].getString());
}
}

// YAML

{
    {
        const String yamlString = "";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Undefined, object.getType());
    }

    {
        const String yamlString = "false";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Boolean, object.getType());

        EXPECT_EQ(false, object.getBoolean());
    }

    {
        const String yamlString = "true";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Boolean, object.getType());

        EXPECT_EQ(true, object.getBoolean());
    }

    {
        const String yamlString = "0";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Integer, object.getType());

        EXPECT_EQ(0, object.getInteger());
    }

    {
        const String yamlString = "-123";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Integer, object.getType());

        EXPECT_EQ(-123, object.getInteger());
    }

    {
        const String yamlString = "123";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Integer, object.getType());

        EXPECT_EQ(123, object.getInteger());
    }

    {
        const String yamlString = "0.0";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Real, object.getType());

        EXPECT_EQ(0.0, object.getReal());
    }

    {
        const String yamlString = "-123.456";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Real, object.getType());

        EXPECT_EQ(-123.456, object.getReal());
    }

    {
        const String yamlString = "123.456";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Real, object.getType());

        EXPECT_EQ(123.456, object.getReal());
    }

    {
        const String yamlString = "abc";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::String, object.getType());

        EXPECT_EQ("abc", object.getString());
    }

    {
        const String yamlString = "\"abc\"";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::String, object.getType());

        EXPECT_EQ("abc", object.getString());
    }

    {
        const String yamlString = "\"abcdef,./<>?;:[]{}|-=!@#$%^&*()_+\"";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::String, object.getType());

        EXPECT_EQ("abcdef,./<>?;:[]{}|-=!@#$%^&*()_+", object.getString());
    }

    {
        const String yamlString = "\"abc\\\"'def\"";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::String, object.getType());

        EXPECT_EQ("abc\"'def", object.getString());
    }

    {
        const String yamlString = "Key: Value";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Dictionary, object.getType());

        EXPECT_EQ(Dictionary({{"Key", Object::String("Value")}}), object.getDictionary());
    }

    {
        const String yamlString = "{\"Key\": \"Value\"}";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Dictionary, object.getType());

        EXPECT_EQ(Dictionary({{"Key", Object::String("Value")}}), object.getDictionary());
    }

    // {

    //     const String yamlString = "- true\n false" ;

    //     EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML)) ;

    //     const Object object = Object::Parse(yamlString, Object::Format::YAML) ;

    //     EXPECT_EQ(Object::Type::Array, object.getType()) ;

    //     EXPECT_TRUE(object.isArray()) ;

    //     EXPECT_FALSE(object[0].isDefined()) ;

    //     EXPECT_EQ(true, object[0].getBoolean()) ;

    // }

    {
        const String yamlString = "[null, true, 123, 456.789, \"abc\"]";

        EXPECT_NO_THROW(Object::Parse(yamlString, Object::Format::YAML));

        const Object object = Object::Parse(yamlString, Object::Format::YAML);

        EXPECT_EQ(Object::Type::Array, object.getType());

        EXPECT_TRUE(object.isArray());

        EXPECT_FALSE(object[0].isDefined());
        EXPECT_TRUE(object[1].isBoolean());
        EXPECT_TRUE(object[2].isInteger());
        EXPECT_TRUE(object[3].isReal());
        EXPECT_TRUE(object[4].isString());

        EXPECT_EQ(true, object[1].getBoolean());
        EXPECT_EQ(123, object[2].getInteger());
        EXPECT_EQ(456.789, object[3].getReal());
        EXPECT_EQ("abc", object[4].getString());
    }
}
}

// TEST (OpenSpaceToolkit_Core_Containers_Object, Load)
// {

//     using ostk::core::ctnr::Object ;

//     {

//         FAIL() ;

//     }

// }

TEST(OpenSpaceToolkit_Core_Containers_Object, StringFromType)
{
    using ostk::core::ctnr::Object;

    EXPECT_EQ("Undefined", Object::StringFromType(Object::Type::Undefined));
    EXPECT_EQ("Boolean", Object::StringFromType(Object::Type::Boolean));
    EXPECT_EQ("Integer", Object::StringFromType(Object::Type::Integer));
    EXPECT_EQ("Real", Object::StringFromType(Object::Type::Real));
    EXPECT_EQ("String", Object::StringFromType(Object::Type::String));
    EXPECT_EQ("Dictionary", Object::StringFromType(Object::Type::Dictionary));
    EXPECT_EQ("Array", Object::StringFromType(Object::Type::Array));
}

TEST(OpenSpaceToolkit_Core_Containers_Object, TypeFromString)
{
    using ostk::core::ctnr::Object;

    EXPECT_EQ(Object::Type::Undefined, Object::TypeFromString("Undefined"));
    EXPECT_EQ(Object::Type::Boolean, Object::TypeFromString("Boolean"));
    EXPECT_EQ(Object::Type::Integer, Object::TypeFromString("Integer"));
    EXPECT_EQ(Object::Type::Real, Object::TypeFromString("Real"));
    EXPECT_EQ(Object::Type::String, Object::TypeFromString("String"));
    EXPECT_EQ(Object::Type::Dictionary, Object::TypeFromString("Dictionary"));
    EXPECT_EQ(Object::Type::Array, Object::TypeFromString("Array"));
}
