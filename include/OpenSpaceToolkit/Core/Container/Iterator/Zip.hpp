/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Container_Iterator_Zip__
#define __OpenSpaceToolkit_Core_Container_Iterator_Zip__

#include <iterator>
#include <tuple>
#include <utility>

namespace ostk
{
namespace core
{
namespace container
{
namespace iterator
{

/// @brief                      Zip iterator
///
/// @ref                        https://gist.github.com/mortehu/373069390c75b02f98b655e3f7dbef9a

template <typename... T>
class ZipIterator
{
   public:
    class Iterator : std::iterator<std::forward_iterator_tag, std::tuple<decltype(*std::declval<T>().begin())...>>
    {
       public:
        std::tuple<decltype(std::declval<T>().begin())...> iterators_;

        explicit Iterator(decltype(iterators_) anIteratorList)
            : iterators_ {std::move(anIteratorList)}
        {
        }

        Iterator& operator++()
        {
            increment(std::index_sequence_for<T...> {});

            return *this;
        }

        Iterator operator++(int)
        {
            auto saved {*this};

            increment(std::index_sequence_for<T...> {});

            return saved;
        }

        bool operator!=(const Iterator& anIterator) const
        {
            return iterators_ != anIterator.iterators_;
        }

        auto operator*() const
        {
            return deref(std::index_sequence_for<T...> {});
        }

       private:
        template <std::size_t... I>
        auto deref(std::index_sequence<I...>) const
        {
            return typename Iterator::value_type {*std::get<I>(iterators_)...};
        }

        template <std::size_t... I>
        void increment(std::index_sequence<I...>)
        {
            auto l = {(++std::get<I>(iterators_), 0)...};

            (void)l;
        }
    };

    ZipIterator(T&... aSequence)
        : begin_ {std::make_tuple(aSequence.begin()...)},
          end_ {std::make_tuple(aSequence.end()...)}
    {
    }

    ZipIterator::Iterator begin() const
    {
        return begin_;
    }

    ZipIterator::Iterator end() const
    {
        return end_;
    }

   private:
    ZipIterator::Iterator begin_;
    ZipIterator::Iterator end_;
};

/// @note                       Sequences must be the same length

template <typename... T>
auto Zip(T&&... seqs)
{
    return ZipIterator<T...> {seqs...};
}

}  // namespace iterator
}  // namespace container
}  // namespace core
}  // namespace ostk

#endif
