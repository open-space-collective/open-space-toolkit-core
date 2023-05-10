/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Dictionary.hpp>
#include <OpenSpaceToolkit/Core/Containers/Object.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, InitializerListConstructor)
{
    using ostk::core::types::Size;
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary dictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")},
            {"Dictionary",
             {{"Undefined", Object::Undefined()},
              {"Boolean", Object::Boolean(false)},
              {"Integer", Object::Integer(456)},
              {"Real", Object::Real(456.789)}}},
            {"Array",
             Object::Array(
                 {Object::Undefined(),
                  Object::Boolean(true),
                  Object::Integer(123),
                  Object::Real(123.456),
                  Object::String("Hello World!"),
                  {{"Undefined", Object::Undefined()},
                   {"Boolean", Object::Boolean(false)},
                   {"Integer", Object::Integer(456)},
                   {"Real", Object::Real(456.789)}},
                  Object::Array({Object::Integer(123), Object::Integer(456), Object::Integer(789)})}
             )}};

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_FALSE(dictionary["Undefined"].isDefined());
        EXPECT_TRUE(dictionary["Boolean"].isBoolean());
        EXPECT_TRUE(dictionary["Integer"].isInteger());
        EXPECT_TRUE(dictionary["Real"].isReal());
        EXPECT_TRUE(dictionary["String"].isString());
        EXPECT_TRUE(dictionary["Dictionary"].isDictionary());
        EXPECT_FALSE(dictionary["Dictionary"]["Undefined"].isDefined());
        EXPECT_TRUE(dictionary["Dictionary"]["Boolean"].isBoolean());
        EXPECT_TRUE(dictionary["Dictionary"]["Integer"].isInteger());
        EXPECT_TRUE(dictionary["Dictionary"]["Real"].isReal());
        EXPECT_TRUE(dictionary["Array"].isArray());
        EXPECT_EQ(Size(7), dictionary["Array"].getArray().getSize());
        EXPECT_FALSE(dictionary["Array"][0].isDefined());
        EXPECT_TRUE(dictionary["Array"][1].isBoolean());
        EXPECT_TRUE(dictionary["Array"][2].isInteger());
        EXPECT_TRUE(dictionary["Array"][3].isReal());
        EXPECT_TRUE(dictionary["Array"][4].isString());
        EXPECT_TRUE(dictionary["Array"][5].isDictionary());
        EXPECT_FALSE(dictionary["Array"][5]["Undefined"].isDefined());
        EXPECT_TRUE(dictionary["Array"][5]["Boolean"].isBoolean());
        EXPECT_TRUE(dictionary["Array"][5]["Integer"].isInteger());
        EXPECT_TRUE(dictionary["Array"][5]["Real"].isReal());
        EXPECT_TRUE(dictionary["Array"][6].isArray());
        EXPECT_TRUE(dictionary["Array"][6][0].isInteger());
        EXPECT_TRUE(dictionary["Array"][6][1].isInteger());
        EXPECT_TRUE(dictionary["Array"][6][2].isInteger());

        EXPECT_EQ(true, dictionary["Boolean"].getBoolean());
        EXPECT_EQ(123, dictionary["Integer"].getInteger());
        EXPECT_EQ(123.456, dictionary["Real"].getReal());
        EXPECT_EQ("Hello World!", dictionary["String"].getString());
        EXPECT_EQ(false, dictionary["Dictionary"]["Boolean"].getBoolean());
        EXPECT_EQ(456, dictionary["Dictionary"]["Integer"].getInteger());
        EXPECT_EQ(456.789, dictionary["Dictionary"]["Real"].getReal());
        EXPECT_EQ(true, dictionary["Array"][1].getBoolean());
        EXPECT_EQ(123, dictionary["Array"][2].getInteger());
        EXPECT_EQ(123.456, dictionary["Array"][3].getReal());
        EXPECT_EQ("Hello World!", dictionary["Array"][4].getString());
        EXPECT_EQ(false, dictionary["Array"][5]["Boolean"].getBoolean());
        EXPECT_EQ(456, dictionary["Array"][5]["Integer"].getInteger());
        EXPECT_EQ(456.789, dictionary["Array"][5]["Real"].getReal());
        EXPECT_EQ(123, dictionary["Array"][6][0].getInteger());
        EXPECT_EQ(456, dictionary["Array"][6][1].getInteger());
        EXPECT_EQ(789, dictionary["Array"][6][2].getInteger());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, CopyConstructor)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        const Dictionary secondDictionary(firstDictionary);

        EXPECT_EQ(firstDictionary, secondDictionary);

        EXPECT_NE(&firstDictionary, &secondDictionary);
        EXPECT_NE(&firstDictionary["Undefined"], &secondDictionary["Undefined"]);
        EXPECT_NE(&firstDictionary["Boolean"], &secondDictionary["Boolean"]);
        EXPECT_NE(&firstDictionary["Integer"], &secondDictionary["Integer"]);
        EXPECT_NE(&firstDictionary["Real"], &secondDictionary["Real"]);
        EXPECT_NE(&firstDictionary["String"], &secondDictionary["String"]);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, AssignmentOperator)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        const Dictionary secondDictionary = firstDictionary;

        EXPECT_EQ(firstDictionary, secondDictionary);

        EXPECT_NE(&firstDictionary, &secondDictionary);
        EXPECT_NE(&firstDictionary["Undefined"], &secondDictionary["Undefined"]);
        EXPECT_NE(&firstDictionary["Boolean"], &secondDictionary["Boolean"]);
        EXPECT_NE(&firstDictionary["Integer"], &secondDictionary["Integer"]);
        EXPECT_NE(&firstDictionary["Real"], &secondDictionary["Real"]);
        EXPECT_NE(&firstDictionary["String"], &secondDictionary["String"]);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, EqualToOperator)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_TRUE(firstDictionary == firstDictionary);
    }

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        const Dictionary secondDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_TRUE(firstDictionary == secondDictionary);
    }

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        const Dictionary secondDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(false)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_FALSE(firstDictionary == secondDictionary);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, NotEqualToOperator)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_FALSE(firstDictionary != firstDictionary);
    }

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        const Dictionary secondDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_FALSE(firstDictionary != secondDictionary);
    }

    {
        const Dictionary firstDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        const Dictionary secondDictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(false)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        EXPECT_TRUE(firstDictionary != secondDictionary);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, KeySubscriptOperator)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary dictionary = {
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")},
            {"Dictionary",
             {{"Boolean", Object::Boolean(false)},
              {"Integer", Object::Integer(456)},
              {"Real", Object::Real(456.789)},
              {"Dictionary",
               {{"Boolean", Object::Boolean(true)},
                {"Integer", Object::Integer(789)},
                {"Real", Object::Real(789.123)}}}}}};

        EXPECT_EQ(true, dictionary["Boolean"].getBoolean());
        EXPECT_EQ(123, dictionary["Integer"].getInteger());
        EXPECT_EQ(123.456, dictionary["Real"].getReal());
        EXPECT_EQ("Hello World!", dictionary["String"].getString());

        EXPECT_EQ(false, dictionary["Dictionary"]["Boolean"].getBoolean());
        EXPECT_EQ(456, dictionary["Dictionary"]["Integer"].getInteger());
        EXPECT_EQ(456.789, dictionary["Dictionary"]["Real"].getReal());

        EXPECT_EQ(true, dictionary["Dictionary"]["Dictionary"]["Boolean"].getBoolean());
        EXPECT_EQ(789, dictionary["Dictionary"]["Dictionary"]["Integer"].getInteger());
        EXPECT_EQ(789.123, dictionary["Dictionary"]["Dictionary"]["Real"].getReal());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, Iterators)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        const Dictionary dictionary = {
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        uint idx = 0;

        for (const auto& dictIt : dictionary)
        {
            const Dictionary::Key& key = dictIt.accessKey();
            const Dictionary::Value& value = dictIt.accessValue();

            switch (idx)
            {
                case 0:
                    EXPECT_EQ("Boolean", key);
                    EXPECT_TRUE(value.isBoolean());
                    EXPECT_EQ(true, value.getBoolean());
                    break;

                case 1:
                    EXPECT_EQ("Integer", key);
                    EXPECT_TRUE(value.isInteger());
                    EXPECT_EQ(123, value.getInteger());
                    break;

                case 2:
                    EXPECT_EQ("Real", key);
                    EXPECT_TRUE(value.isReal());
                    EXPECT_EQ(123.456, value.getReal());
                    break;

                case 3:
                    EXPECT_EQ("String", key);
                    EXPECT_TRUE(value.isString());
                    EXPECT_EQ("Hello World!", value.getString());
                    break;

                default:
                    FAIL();
                    break;
            }

            idx++;
        }
    }

    {
        Dictionary dictionary = {
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")}};

        {
            uint idx = 0;

            for (auto& dictIt : dictionary)
            {
                const Dictionary::Key& key = dictIt.accessKey();
                Dictionary::Value& value = dictIt.accessValue();

                switch (idx)
                {
                    case 0:
                        EXPECT_EQ("Boolean", key);
                        EXPECT_TRUE(value.isBoolean());
                        EXPECT_EQ(true, value.getBoolean());
                        value = Object::Boolean(false);
                        break;

                    case 1:
                        EXPECT_EQ("Integer", key);
                        EXPECT_TRUE(value.isInteger());
                        EXPECT_EQ(123, value.getInteger());
                        value = Object::Integer(456);
                        break;

                    case 2:
                        EXPECT_EQ("Real", key);
                        EXPECT_TRUE(value.isReal());
                        EXPECT_EQ(123.456, value.getReal());
                        value = Object::Real(456.789);
                        break;

                    case 3:
                        EXPECT_EQ("String", key);
                        EXPECT_TRUE(value.isString());
                        EXPECT_EQ("Hello World!", value.getString());
                        value = Object::String("What's up?");
                        break;

                    default:
                        FAIL();
                        break;
                }

                idx++;
            }
        }

        {
            uint idx = 0;

            for (const auto& dictIt : dictionary)
            {
                const Dictionary::Key& key = dictIt.accessKey();
                const Dictionary::Value& value = dictIt.accessValue();

                switch (idx)
                {
                    case 0:
                        EXPECT_EQ("Boolean", key);
                        EXPECT_TRUE(value.isBoolean());
                        EXPECT_EQ(false, value.getBoolean());
                        break;

                    case 1:
                        EXPECT_EQ("Integer", key);
                        EXPECT_TRUE(value.isInteger());
                        EXPECT_EQ(456, value.getInteger());
                        break;

                    case 2:
                        EXPECT_EQ("Real", key);
                        EXPECT_TRUE(value.isReal());
                        EXPECT_EQ(456.789, value.getReal());
                        break;

                    case 3:
                        EXPECT_EQ("String", key);
                        EXPECT_TRUE(value.isString());
                        EXPECT_EQ("What's up?", value.getString());
                        break;

                    default:
                        FAIL();
                        break;
                }

                idx++;
            }
        }
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, IsEmpty)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        EXPECT_FALSE(Dictionary({{"Key", Object::String("Value")}}).isEmpty());
    }

    {
        EXPECT_TRUE(Dictionary::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, HasValueForKey)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        Dictionary dictionary = Dictionary::Empty();

        EXPECT_FALSE(dictionary.hasValueForKey("Key"));

        EXPECT_NO_THROW(dictionary.addValueForKey(Object::String("Value"), "Key"));

        EXPECT_TRUE(dictionary.hasValueForKey("Key"));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, GetSize)
{
    using ostk::core::types::Size;
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        EXPECT_EQ(Size(0), Dictionary::Empty().getSize());
    }

    {
        const Dictionary dictionary = {
            {"Undefined", Object::Undefined()},
            {"Boolean", Object::Boolean(true)},
            {"Integer", Object::Integer(123)},
            {"Real", Object::Real(123.456)},
            {"String", Object::String("Hello World!")},
            {"Dictionary",
             {{"Undefined", Object::Undefined()},
              {"Boolean", Object::Boolean(false)},
              {"Integer", Object::Integer(456)},
              {"Real", Object::Real(456.789)}}},
            {"Array",
             Object::Array(
                 {Object::Undefined(),
                  Object::Boolean(true),
                  Object::Integer(123),
                  Object::Real(123.456),
                  Object::String("Hello World!"),
                  {{"Undefined", Object::Undefined()},
                   {"Boolean", Object::Boolean(false)},
                   {"Integer", Object::Integer(456)},
                   {"Real", Object::Real(456.789)}},
                  Object::Array({Object::Integer(123), Object::Integer(456), Object::Integer(789)})}
             )}};

        EXPECT_EQ(Size(7), dictionary.getSize());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, AddValueForKey)
{
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        Dictionary dictionary = Dictionary::Empty();

        EXPECT_FALSE(dictionary.hasValueForKey("Key"));

        EXPECT_NO_THROW(dictionary.addValueForKey(Object::String("Value"), "Key"));

        EXPECT_TRUE(dictionary.hasValueForKey("Key"));

        EXPECT_ANY_THROW(dictionary.addValueForKey(Object::String("Value"), "Key"));

        EXPECT_TRUE(dictionary.hasValueForKey("Key"));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, Empty)
{
    using ostk::core::ctnr::Dictionary;

    {
        EXPECT_TRUE(Dictionary::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Dictionary, Parse)
{
    using ostk::core::types::String;
    using ostk::core::ctnr::Object;
    using ostk::core::ctnr::Dictionary;

    {
        String jsonString = "{}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_TRUE(dictionary.isEmpty());
    }

    {
        String jsonString = "{\"Key\": true}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_TRUE(dictionary["Key"].isBoolean());
        EXPECT_EQ(true, dictionary["Key"].getBoolean());
    }

    {
        String jsonString = "{\"Key\": 123}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_TRUE(dictionary["Key"].isInteger());
        EXPECT_EQ(123, dictionary["Key"].getInteger());
    }

    {
        String jsonString = "{\"Key\": 123.456}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_TRUE(dictionary["Key"].isReal());
        EXPECT_EQ(123.456, dictionary["Key"].getReal());
    }

    {
        String jsonString = "{\"Key\": \"Value\"}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_TRUE(dictionary["Key"].isString());
        EXPECT_EQ("Value", dictionary["Key"].getString());
    }

    {
        String jsonString = "{\"Key\": {\"Key\": \"Value\"}}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_TRUE(dictionary["Key"].isDictionary());
        EXPECT_TRUE(dictionary["Key"]["Key"].isString());
        EXPECT_EQ("Value", dictionary["Key"]["Key"].getString());
    }

    {
        String jsonString = "{\"Key\": [true, 123, 456.789, \"abc\"]}";

        EXPECT_NO_THROW(Dictionary::Parse(jsonString, Object::Format::JSON));

        Dictionary dictionary = Dictionary::Parse(jsonString, Object::Format::JSON);

        EXPECT_FALSE(dictionary.isEmpty());

        EXPECT_TRUE(dictionary["Key"].isArray());
        EXPECT_TRUE(dictionary["Key"][0].isBoolean());
        EXPECT_TRUE(dictionary["Key"][1].isInteger());
        EXPECT_TRUE(dictionary["Key"][2].isReal());
        EXPECT_TRUE(dictionary["Key"][3].isString());
        EXPECT_EQ(true, dictionary["Key"][0].getBoolean());
        EXPECT_EQ(123, dictionary["Key"][1].getInteger());
        EXPECT_EQ(456.789, dictionary["Key"][2].getReal());
        EXPECT_EQ("abc", dictionary["Key"][3].getString());
    }

    {
        EXPECT_ANY_THROW(Dictionary::Parse(""));
        EXPECT_ANY_THROW(Dictionary::Parse("true"));
        EXPECT_ANY_THROW(Dictionary::Parse("123"));
        EXPECT_ANY_THROW(Dictionary::Parse("123.456"));
        EXPECT_ANY_THROW(Dictionary::Parse("abc"));
        EXPECT_ANY_THROW(Dictionary::Parse("{{}}"));
    }
}
