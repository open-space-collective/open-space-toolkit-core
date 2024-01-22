/// Apache License 2.0

namespace ostk
{
namespace core
{
namespace container
{

template <typename T, typename U, typename V>
Triple<T, U, V> make_triple(const T& aFirstElement, const U& aSecondElement, const V& aThirdElement)
{
    Triple<T, U, V> triple;

    triple.first = aFirstElement;
    triple.second = aSecondElement;
    triple.third = aThirdElement;

    return triple;
}

}  // namespace container
}  // namespace core
}  // namespace ostk
