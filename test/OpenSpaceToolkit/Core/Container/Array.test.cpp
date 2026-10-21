/// Apache License 2.0

#include <cmath>
#include <limits>

#include <OpenSpaceToolkit/Core/Container/Array.hpp>
#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>
#include <OpenSpaceToolkit/Core/Type/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Container_Array, VectorConstructor)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        const std::vector<int> aVector = {1, 2, 3};

        EXPECT_NO_THROW(Array<int> array(aVector); (void)array;);

        const Array<int> array(aVector);

        EXPECT_EQ(Size(3), array.getSize());

        EXPECT_EQ(1, array[0]);
        EXPECT_EQ(2, array[1]);
        EXPECT_EQ(3, array[2]);
    }

    {
        const std::vector<String> vector = {"abc", "def", "ghi"};

        EXPECT_NO_THROW(Array<String> array(vector); (void)array;);

        const Array<String> array(vector);

        EXPECT_EQ(Size(3), array.getSize());

        EXPECT_EQ("abc", array[0]);
        EXPECT_EQ("def", array[1]);
        EXPECT_EQ("ghi", array[2]);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, SizeValueConstructor)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        const Size size = 3;
        const int value = 123;

        EXPECT_NO_THROW(Array<int> array(size, value); (void)array;);

        const Array<int> array(size, value);

        EXPECT_EQ(Size(3), array.getSize());

        EXPECT_EQ(123, array[0]);
        EXPECT_EQ(123, array[1]);
        EXPECT_EQ(123, array[2]);
    }

    {
        const Size size = 3;
        const String value = "abc";

        EXPECT_NO_THROW(Array<String> array(size, value); (void)array;);

        const Array<String> array(size, value);

        EXPECT_EQ(Size(3), array.getSize());

        EXPECT_EQ("abc", array[0]);
        EXPECT_EQ("abc", array[1]);
        EXPECT_EQ("abc", array[2]);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, InitializerListConstructor)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        EXPECT_NO_THROW(Array<int> array({1, 2, 3}); (void)array;);

        const Array<int> array({1, 2, 3});

        EXPECT_EQ(Size(3), array.getSize());

        EXPECT_EQ(1, array[0]);
        EXPECT_EQ(2, array[1]);
        EXPECT_EQ(3, array[2]);
    }

    {
        EXPECT_NO_THROW(Array<String> array({"abc", "def", "ghi"}); (void)array;);

        const Array<String> array({"abc", "def", "ghi"});

        EXPECT_EQ(Size(3), array.getSize());

        EXPECT_EQ("abc", array[0]);
        EXPECT_EQ("def", array[1]);
        EXPECT_EQ("ghi", array[2]);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, AdditionOperator)
{
    using ostk::core::container::Array;

    {
        const Array<int> firstArray({-4, -3, -2, -1});
        const Array<int> secondArray({+0, +1, +2, +3, +4});

        EXPECT_NO_THROW(firstArray + secondArray);

        EXPECT_EQ(Array<int>({-4, -3, -2, -1, +0, +1, +2, +3, +4}), firstArray + secondArray);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, IsEmpty)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;

    {
        EXPECT_FALSE(Array<int>({1, 2, 3}).isEmpty());
    }

    {
        EXPECT_TRUE(Array<int>({}).isEmpty());
        EXPECT_TRUE(Array<int>::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Contains)
{
    using ostk::core::container::Array;
    using ostk::core::type::String;

    {
        const Array<int> array({1, 2, 3});

        EXPECT_TRUE(array.contains(1));
        EXPECT_TRUE(array.contains(2));
        EXPECT_TRUE(array.contains(3));

        EXPECT_FALSE(array.contains(0));
        EXPECT_FALSE(array.contains(4));
    }

    {
        const Array<String> array({"abc", "def"});

        EXPECT_TRUE(array.contains("abc"));
        EXPECT_TRUE(array.contains("def"));

        EXPECT_FALSE(array.contains(""));
        EXPECT_FALSE(array.contains("ghi"));
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, IsNear)
{
    using ostk::core::container::Array;

    // Tolerance

    {
        const Array<double> array = {1.0, 2.0, 3.0};

        EXPECT_TRUE(array.isNear(array, 0.0));
    }

    {
        const Array<double> firstArray = {1.0, 2.0, 3.0};
        const Array<double> secondArray = {1.0, 2.0, 4.0};

        EXPECT_FALSE(firstArray.isNear(secondArray, 0.5));
    }

    {
        const Array<double> firstArray = {1.0, std::numeric_limits<double>::quiet_NaN()};

        EXPECT_FALSE(firstArray.isNear(firstArray, 1.0));
    }

    {
        const Array<int> firstArray = {1, 2, 3};
        const Array<int> secondArray = {1, 2, 4};

        EXPECT_TRUE(firstArray.isNear(secondArray, 1));
        EXPECT_FALSE(firstArray.isNear(secondArray, 0));
    }

    {
        const Array<double> firstArray = {1.0, 2.0, 3.0};
        const Array<double> secondArray = {1.0, 2.0, 3.0};

        EXPECT_TRUE(firstArray.isNear(secondArray, 0.0));
    }

    {
        const Array<double> firstArray = {1.0, 2.0, 3.0};
        const Array<double> secondArray = {1.0, 2.0, 4.0};

        EXPECT_TRUE(firstArray.isNear(secondArray, 1.0));
    }

    {
        const Array<double> firstArray = {1.0, 2.0, 3.0};
        const Array<double> secondArray = {1.0, 2.0, 3.0, 4.0};

        EXPECT_FALSE(firstArray.isNear(secondArray, 1.0));
    }

    // Comparator

    {
        const Array<double> firstArray = {1.0, 2.0, 3.0};
        const Array<double> secondArray = {1.0, 2.0, 4.0};

        EXPECT_TRUE(firstArray.isNear(
            secondArray,
            [](const double& aFirstValue, const double& aSecondValue) -> bool
            {
                return std::abs(aFirstValue - aSecondValue) <= 1.0;
            }
        ));
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, AccessFirst)
{
    using ostk::core::container::Array;
    using ostk::core::type::String;

    {
        const Array<int> array({1, 2, 3});

        EXPECT_NO_THROW(array.accessFirst());

        EXPECT_EQ(1, array.accessFirst());
    }

    {
        const Array<String> array({"abc", "def"});

        EXPECT_NO_THROW(array.accessFirst());

        EXPECT_EQ("abc", array.accessFirst());
    }

    {
        const Array<String> array({});

        EXPECT_ANY_THROW(array.accessFirst());
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, AccessLast)
{
    using ostk::core::container::Array;
    using ostk::core::type::String;

    {
        const Array<int> array({1, 2, 3});

        EXPECT_NO_THROW(array.accessLast());

        EXPECT_EQ(3, array.accessLast());
    }

    {
        const Array<String> array({"abc", "def"});

        EXPECT_NO_THROW(array.accessLast());

        EXPECT_EQ("def", array.accessLast());
    }

    {
        const Array<String> array({});

        EXPECT_ANY_THROW(array.accessLast());
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, GetSize)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    EXPECT_EQ(Size(0), Array<int>({}).getSize());
    EXPECT_EQ(Size(0), Array<int>::Empty().getSize());

    EXPECT_EQ(Size(3), Array<int>({1, 2, 3}).getSize());
    EXPECT_EQ(Size(2), Array<String>({"abc", "def"}).getSize());
}

TEST(OpenSpaceToolkit_Core_Container_Array, GetIndexOf)
{
    using ostk::core::container::Array;
    using ostk::core::type::Index;
    using ostk::core::type::String;

    {
        const Array<int> array({1, 2, 3});

        EXPECT_EQ(Index(0), array.getIndexOf(1));
        EXPECT_EQ(Index(1), array.getIndexOf(2));
        EXPECT_EQ(Index(2), array.getIndexOf(3));

        EXPECT_ANY_THROW(array.getIndexOf(0));
        EXPECT_ANY_THROW(array.getIndexOf(4));
    }

    {
        const Array<String> array({"abc", "def"});

        EXPECT_EQ(Index(0), array.getIndexOf("abc"));
        EXPECT_EQ(Index(1), array.getIndexOf("def"));

        EXPECT_ANY_THROW(array.getIndexOf(""));
        EXPECT_ANY_THROW(array.getIndexOf("ghi"));
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, ToString)
{
    using ostk::core::container::Array;
    using ostk::core::type::String;

    {
        const Array<int> array({1, 2, 3});

        EXPECT_EQ("[1, 2, 3]", array.toString());
    }

    {
        const Array<double> array({1.0, 2.5, -3.0});

        EXPECT_EQ("[1.0, 2.5, -3.0]", array.toString());
    }

    {
        const Array<double> array({std::numeric_limits<double>::quiet_NaN(), std::numeric_limits<double>::infinity()});

        EXPECT_EQ("[Undefined, +Inf]", array.toString());
    }

    {
        const Array<String> array({"abc", "def"});

        EXPECT_EQ("[\"abc\", \"def\"]", array.toString());
    }

    {
        EXPECT_EQ("[]", Array<int>::Empty().toString());
        EXPECT_EQ("[]", Array<String>::Empty().toString());
    }
}

// TEST (OpenSpaceToolkit_Core_Container_Array, GetObject)
// {

//     using ostk::core::container::Array ;

//     FAIL() ;

// }

TEST(OpenSpaceToolkit_Core_Container_Array, AccessWhere)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        const Array<int> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        const Array<int>::Predicate predicate = [](const int& anInteger) -> bool
        {
            return (anInteger % 2) == 0;
        };

        EXPECT_NO_THROW(array.accessWhere(predicate));

        const Array<const int*> filteredArray = array.accessWhere(predicate);

        EXPECT_EQ(Size(5), filteredArray.getSize());

        EXPECT_TRUE(&array[0] == filteredArray[0]);
        EXPECT_TRUE(&array[2] == filteredArray[1]);
        EXPECT_TRUE(&array[4] == filteredArray[2]);
        EXPECT_TRUE(&array[6] == filteredArray[3]);
        EXPECT_TRUE(&array[8] == filteredArray[4]);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, GetWhere)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        const Array<int> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        const Array<int>::Predicate predicate = [](const int& anInteger) -> bool
        {
            return (anInteger % 2) == 0;
        };

        EXPECT_NO_THROW(array.getWhere(predicate));

        const Array<int> filteredArray = array.getWhere(predicate);

        EXPECT_EQ(Size(5), filteredArray.getSize());

        EXPECT_EQ(Array<int>({-4, -2, +0, +2, +4}), filteredArray);

        EXPECT_TRUE(&array[0] != &filteredArray[0]);
        EXPECT_TRUE(&array[2] != &filteredArray[1]);
        EXPECT_TRUE(&array[4] != &filteredArray[2]);
        EXPECT_TRUE(&array[6] != &filteredArray[3]);
        EXPECT_TRUE(&array[8] != &filteredArray[4]);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Find)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;

    {
        const Array<int> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        EXPECT_NO_THROW(array.find(+1));

        const Array<int>::ConstIterator arrayIt = array.find(+1);

        EXPECT_EQ(+1, (*arrayIt));
    }

    {
        Array<int> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        EXPECT_NO_THROW(array.find(+1));

        const Array<int>::Iterator arrayIt = array.find(+1);

        EXPECT_EQ(+1, (*arrayIt));

        (*arrayIt) = +123;

        EXPECT_EQ(+123, (*arrayIt));

        EXPECT_EQ(Array<int>({-4, -3, -2, -1, +0, +123, +2, +3, +4}), array);
    }

    {
        Array<int> array({123, 456, 123});

        EXPECT_NO_THROW(array.find(123));

        const Array<int>::Iterator arrayIt = array.find(123);

        EXPECT_EQ(123, (*arrayIt));

        (*arrayIt) = 999;

        EXPECT_EQ(999, (*arrayIt));

        EXPECT_EQ(Array<int>({999, 456, 123}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Map)
{
    using ostk::core::container::Array;
    using ostk::core::type::String;

    {
        const Array<String> strings = {"1", "2", "3"};

        const Array<int> integers = strings.map<int>(
            [](const String& aString) -> int
            {
                return std::stoi(aString);
            }
        );

        ASSERT_EQ(3, integers.getSize());

        EXPECT_EQ(1, integers.at(0));
        EXPECT_EQ(2, integers.at(1));
        EXPECT_EQ(3, integers.at(2));
    }

    {
        EXPECT_TRUE(Array<String>::Empty()
                        .map<String>(
                            [](const String& aString) -> String
                            {
                                return aString;
                            }
                        )
                        .isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Reduce)
{
    using ostk::core::container::Array;

    {
        const Array<int> integers = {1, 2, 3};

        const int reducedInteger = integers.reduce(std::plus<int>());

        EXPECT_EQ(6, reducedInteger);
    }

    {
        const Array<int> integers = {1, 2, 3};

        const int reducedInteger = integers.reduce(
            [](const int& anAccumulator, const int& aValue) -> int
            {
                return anAccumulator + aValue;
            }
        );

        EXPECT_EQ(6, reducedInteger);
    }

    {
        // EXPECT_ANY_THROW(Array<Integer>::Empty().reduce([] () -> ddd { return aaa ; })) ;
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Add)
{
    using ostk::core::container::Array;
    using ostk::core::type::Index;
    using ostk::core::type::String;

    {
        Array<int> array({1, 2, 3});

        EXPECT_EQ(Array<int>({1, 2, 3}), array);

        array.add(4);

        EXPECT_EQ(Array<int>({1, 2, 3, 4}), array);

        array.add(4);

        EXPECT_EQ(Array<int>({1, 2, 3, 4, 4}), array);
    }

    {
        Array<int> array({1, 2, 3});

        EXPECT_EQ(Array<int>({1, 2, 3}), array);

        array.add({4, 5, 6});

        EXPECT_EQ(Array<int>({1, 2, 3, 4, 5, 6}), array);

        array.add({4, 5, 6});

        EXPECT_EQ(Array<int>({1, 2, 3, 4, 5, 6, 4, 5, 6}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Remove)
{
    using ostk::core::container::Array;
    using ostk::core::type::Index;
    using ostk::core::type::String;

    {
        Array<int> array({1, 2, 3});

        EXPECT_EQ(Array<int>({1, 2, 3}), array);

        array.remove(3);

        EXPECT_EQ(Array<int>({1, 2}), array);

        EXPECT_NO_THROW(array.remove(3));

        array.remove(1);

        EXPECT_EQ(Array<int>({2}), array);
    }

    {
        Array<int> array({1, 3, 2, 3});

        EXPECT_EQ(Array<int>({1, 3, 2, 3}), array);

        array.remove(3);

        EXPECT_EQ(Array<int>({1, 2}), array);

        EXPECT_NO_THROW(array.remove(3));
    }

    {
        Array<int> array({1, 3, 2, 3});

        EXPECT_EQ(Array<int>({1, 3, 2, 3}), array);

        array.remove({2, 3});

        EXPECT_EQ(Array<int>({1}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, MergeWith)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        Array<int> firstArray({-4, -3, -2, -1});
        const Array<int> secondArray({+0, +1, +2, +3, +4});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<int>({-4, -3, -2, -1, +0, +1, +2, +3, +4}), firstArray);
    }

    {
        Array<int> firstArray({});
        const Array<int> secondArray({+0, +1, +2, +3, +4});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<int>({+0, +1, +2, +3, +4}), firstArray);
    }

    {
        Array<int> firstArray({-4, -3, -2, -1});
        const Array<int> secondArray({});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<int>({-4, -3, -2, -1}), firstArray);
    }

    {
        Array<int> firstArray({});
        const Array<int> secondArray({});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<int>({}), firstArray);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, RemoveWhere)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;
    using ostk::core::type::String;

    {
        Array<int> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        const Array<int>::Predicate predicate = [](const int& anInteger) -> bool
        {
            return (anInteger % 2) != 0;
        };

        EXPECT_NO_THROW(array.removeWhere(predicate));

        EXPECT_EQ(Array<int>({-4, -2, +0, +2, +4}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Empty)
{
    using ostk::core::container::Array;
    using ostk::core::type::Size;

    {
        EXPECT_NO_THROW(Array<int> array = Array<int>::Empty(); (void)array;);

        EXPECT_EQ(Size(0), Array<int>::Empty().getSize());
    }
}

TEST(OpenSpaceToolkit_Core_Container_Array, Zip)
{
    using ostk::core::container::Array;
    using ostk::core::type::Index;

    {
        const Array<int> firstArray = {{-4, -3, -2, -1, +0, +1, +2, +3, +4}};
        const Array<int> secondArray = {{-8, -6, -4, -2, +0, +2, +4, +6, +8}};

        Index index = 0;

        for (const auto tuple : ostk::core::container::iterator::Zip(firstArray, secondArray))
        {
            EXPECT_EQ(std::get<0>(tuple) * 2, std::get<1>(tuple));

            index++;
        }

        EXPECT_EQ(9, index);
    }
}
