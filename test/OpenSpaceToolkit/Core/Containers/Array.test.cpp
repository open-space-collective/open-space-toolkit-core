/// Apache License 2.0

#include <OpenSpaceToolkit/Core/Containers/Array.hpp>
#include <OpenSpaceToolkit/Core/Types/Index.hpp>
#include <OpenSpaceToolkit/Core/Types/Integer.hpp>
#include <OpenSpaceToolkit/Core/Types/Real.hpp>
#include <OpenSpaceToolkit/Core/Types/Size.hpp>
#include <OpenSpaceToolkit/Core/Types/String.hpp>

#include <Global.test.hpp>

TEST(OpenSpaceToolkit_Core_Containers_Array, VectorConstructor)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const std::vector<Integer> aVector = {1, 2, 3};

        EXPECT_NO_THROW(Array<Integer> array(aVector); (void)array;);

        const Array<Integer> array(aVector);

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

TEST(OpenSpaceToolkit_Core_Containers_Array, SizeValueConstructor)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Size size = 3;
        const Integer value = 123;

        EXPECT_NO_THROW(Array<Integer> array(size, value); (void)array;);

        const Array<Integer> array(size, value);

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

TEST(OpenSpaceToolkit_Core_Containers_Array, InitializerListConstructor)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        EXPECT_NO_THROW(Array<Integer> array({1, 2, 3}); (void)array;);

        const Array<Integer> array({1, 2, 3});

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

TEST(OpenSpaceToolkit_Core_Containers_Array, AdditionOperator)
{
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> firstArray({-4, -3, -2, -1});
        const Array<Integer> secondArray({+0, +1, +2, +3, +4});

        EXPECT_NO_THROW(firstArray + secondArray);

        EXPECT_EQ(Array<Integer>({-4, -3, -2, -1, +0, +1, +2, +3, +4}), firstArray + secondArray);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, IsEmpty)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Array;

    {
        EXPECT_FALSE(Array<Integer>({1, 2, 3}).isEmpty());
    }

    {
        EXPECT_TRUE(Array<Integer>({}).isEmpty());
        EXPECT_TRUE(Array<Integer>::Empty().isEmpty());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, Contains)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({1, 2, 3});

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

TEST(OpenSpaceToolkit_Core_Containers_Array, IsNear)
{
    using ostk::core::types::Real;
    using ostk::core::ctnr::Array;

    // Tolerance

    {
        const Array<Real> array = {1.0, 2.0, 3.0};

        EXPECT_TRUE(array.isNear(array, 0.0));
    }

    {
        const Array<Real> firstArray = {1.0, 2.0, 3.0};
        const Array<Real> secondArray = {1.0, 2.0, 3.0};

        EXPECT_TRUE(firstArray.isNear(secondArray, 0.0));
    }

    {
        const Array<Real> firstArray = {1.0, 2.0, 3.0};
        const Array<Real> secondArray = {1.0, 2.0, 4.0};

        EXPECT_TRUE(firstArray.isNear(secondArray, 1.0));
    }

    {
        const Array<Real> firstArray = {1.0, 2.0, 3.0};
        const Array<Real> secondArray = {1.0, 2.0, 3.0, 4.0};

        EXPECT_FALSE(firstArray.isNear(secondArray, 1.0));
    }

    // Comparator

    {
        const Array<Real> firstArray = {1.0, 2.0, 3.0};
        const Array<Real> secondArray = {1.0, 2.0, 4.0};

        EXPECT_TRUE(firstArray.isNear(
            secondArray,
            [](const Real& aFirstValue, const Real& aSecondValue) -> bool
            {
                return aFirstValue.isNear(aSecondValue, 1.0);
            }
        ));
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, AccessFirst)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({1, 2, 3});

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

TEST(OpenSpaceToolkit_Core_Containers_Array, AccessLast)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({1, 2, 3});

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

TEST(OpenSpaceToolkit_Core_Containers_Array, GetSize)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    EXPECT_EQ(Size(0), Array<Integer>({}).getSize());
    EXPECT_EQ(Size(0), Array<Integer>::Empty().getSize());

    EXPECT_EQ(Size(3), Array<Integer>({1, 2, 3}).getSize());
    EXPECT_EQ(Size(2), Array<String>({"abc", "def"}).getSize());
}

TEST(OpenSpaceToolkit_Core_Containers_Array, GetIndexOf)
{
    using ostk::core::types::Index;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({1, 2, 3});

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

TEST(OpenSpaceToolkit_Core_Containers_Array, ToString)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({1, 2, 3});

        EXPECT_EQ("[1, 2, 3]", array.toString());
    }

    {
        const Array<String> array({"abc", "def"});

        EXPECT_EQ("[\"abc\", \"def\"]", array.toString());
    }

    {
        EXPECT_EQ("[]", Array<Integer>::Empty().toString());
        EXPECT_EQ("[]", Array<String>::Empty().toString());
    }
}

// TEST (OpenSpaceToolkit_Core_Containers_Array, GetObject)
// {

//     using ostk::core::ctnr::Array ;

//     FAIL() ;

// }

TEST(OpenSpaceToolkit_Core_Containers_Array, AccessWhere)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        const Array<Integer>::Predicate predicate = [](const Integer& anInteger) -> bool
        {
            return anInteger.isEven();
        };

        EXPECT_NO_THROW(array.accessWhere(predicate));

        const Array<const Integer*> filteredArray = array.accessWhere(predicate);

        EXPECT_EQ(Size(5), filteredArray.getSize());

        EXPECT_TRUE(&array[0] == filteredArray[0]);
        EXPECT_TRUE(&array[2] == filteredArray[1]);
        EXPECT_TRUE(&array[4] == filteredArray[2]);
        EXPECT_TRUE(&array[6] == filteredArray[3]);
        EXPECT_TRUE(&array[8] == filteredArray[4]);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, GetWhere)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        const Array<Integer>::Predicate predicate = [](const Integer& anInteger) -> bool
        {
            return anInteger.isEven();
        };

        EXPECT_NO_THROW(array.getWhere(predicate));

        const Array<Integer> filteredArray = array.getWhere(predicate);

        EXPECT_EQ(Size(5), filteredArray.getSize());

        EXPECT_EQ(Array<Integer>({-4, -2, +0, +2, +4}), filteredArray);

        EXPECT_TRUE(&array[0] != &filteredArray[0]);
        EXPECT_TRUE(&array[2] != &filteredArray[1]);
        EXPECT_TRUE(&array[4] != &filteredArray[2]);
        EXPECT_TRUE(&array[6] != &filteredArray[3]);
        EXPECT_TRUE(&array[8] != &filteredArray[4]);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, Find)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        EXPECT_NO_THROW(array.find(+1));

        const Array<Integer>::ConstIterator arrayIt = array.find(+1);

        EXPECT_EQ(+1, (*arrayIt));
    }

    {
        Array<Integer> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        EXPECT_NO_THROW(array.find(+1));

        const Array<Integer>::Iterator arrayIt = array.find(+1);

        EXPECT_EQ(+1, (*arrayIt));

        (*arrayIt) = +123;

        EXPECT_EQ(+123, (*arrayIt));

        EXPECT_EQ(Array<Integer>({-4, -3, -2, -1, +0, +123, +2, +3, +4}), array);
    }

    {
        Array<Integer> array({123, 456, 123});

        EXPECT_NO_THROW(array.find(123));

        const Array<Integer>::Iterator arrayIt = array.find(123);

        EXPECT_EQ(123, (*arrayIt));

        (*arrayIt) = 999;

        EXPECT_EQ(999, (*arrayIt));

        EXPECT_EQ(Array<Integer>({999, 456, 123}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, Map)
{
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        const Array<String> strings = {"1", "2", "3"};

        const Array<Integer> integers = strings.map<Integer>(
            [](const String& aString) -> Integer
            {
                return Integer::Parse(aString);
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

TEST(OpenSpaceToolkit_Core_Containers_Array, Reduce)
{
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> integers = {1, 2, 3};

        const Integer reducedInteger = integers.reduce(std::plus<Integer>());

        EXPECT_EQ(6, reducedInteger);
    }

    {
        const Array<Integer> integers = {1, 2, 3};

        const Integer reducedInteger = integers.reduce(
            [](const Integer& anAccumulator, const Integer& aValue) -> Integer
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

TEST(OpenSpaceToolkit_Core_Containers_Array, Add)
{
    using ostk::core::types::Index;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        Array<Integer> array({1, 2, 3});

        EXPECT_EQ(Array<Integer>({1, 2, 3}), array);

        array.add(4);

        EXPECT_EQ(Array<Integer>({1, 2, 3, 4}), array);

        array.add(4);

        EXPECT_EQ(Array<Integer>({1, 2, 3, 4, 4}), array);
    }

    {
        Array<Integer> array({1, 2, 3});

        EXPECT_EQ(Array<Integer>({1, 2, 3}), array);

        array.add({4, 5, 6});

        EXPECT_EQ(Array<Integer>({1, 2, 3, 4, 5, 6}), array);

        array.add({4, 5, 6});

        EXPECT_EQ(Array<Integer>({1, 2, 3, 4, 5, 6, 4, 5, 6}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, Remove)
{
    using ostk::core::types::Index;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        Array<Integer> array({1, 2, 3});

        EXPECT_EQ(Array<Integer>({1, 2, 3}), array);

        array.remove(3);

        EXPECT_EQ(Array<Integer>({1, 2}), array);

        EXPECT_NO_THROW(array.remove(3));

        array.remove(1);

        EXPECT_EQ(Array<Integer>({2}), array);
    }

    {
        Array<Integer> array({1, 3, 2, 3});

        EXPECT_EQ(Array<Integer>({1, 3, 2, 3}), array);

        array.remove(3);

        EXPECT_EQ(Array<Integer>({1, 2}), array);

        EXPECT_NO_THROW(array.remove(3));
    }

    {
        Array<Integer> array({1, 3, 2, 3});

        EXPECT_EQ(Array<Integer>({1, 3, 2, 3}), array);

        array.remove({2, 3});

        EXPECT_EQ(Array<Integer>({1}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, MergeWith)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        Array<Integer> firstArray({-4, -3, -2, -1});
        const Array<Integer> secondArray({+0, +1, +2, +3, +4});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<Integer>({-4, -3, -2, -1, +0, +1, +2, +3, +4}), firstArray);
    }

    {
        Array<Integer> firstArray({});
        const Array<Integer> secondArray({+0, +1, +2, +3, +4});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<Integer>({+0, +1, +2, +3, +4}), firstArray);
    }

    {
        Array<Integer> firstArray({-4, -3, -2, -1});
        const Array<Integer> secondArray({});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<Integer>({-4, -3, -2, -1}), firstArray);
    }

    {
        Array<Integer> firstArray({});
        const Array<Integer> secondArray({});

        EXPECT_NO_THROW(firstArray.mergeWith(secondArray));

        EXPECT_EQ(Array<Integer>({}), firstArray);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, RemoveWhere)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::types::String;
    using ostk::core::ctnr::Array;

    {
        Array<Integer> array({-4, -3, -2, -1, +0, +1, +2, +3, +4});

        const Array<Integer>::Predicate predicate = [](const Integer& anInteger) -> bool
        {
            return anInteger.isOdd();
        };

        EXPECT_NO_THROW(array.removeWhere(predicate));

        EXPECT_EQ(Array<Integer>({-4, -2, +0, +2, +4}), array);
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, Empty)
{
    using ostk::core::types::Size;
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Array;

    {
        EXPECT_NO_THROW(Array<Integer> array = Array<Integer>::Empty(); (void)array;);

        EXPECT_EQ(Size(0), Array<Integer>::Empty().getSize());
    }
}

TEST(OpenSpaceToolkit_Core_Containers_Array, Zip)
{
    using ostk::core::types::Index;
    using ostk::core::types::Integer;
    using ostk::core::ctnr::Array;

    {
        const Array<Integer> firstArray = {{-4, -3, -2, -1, +0, +1, +2, +3, +4}};
        const Array<Integer> secondArray = {{-8, -6, -4, -2, +0, +2, +4, +6, +8}};

        Index index = 0;

        for (const auto tuple : ostk::core::ctnr::iterators::Zip(firstArray, secondArray))
        {
            EXPECT_EQ(std::get<0>(tuple) * 2, std::get<1>(tuple));

            index++;
        }

        EXPECT_EQ(9, index);
    }
}
