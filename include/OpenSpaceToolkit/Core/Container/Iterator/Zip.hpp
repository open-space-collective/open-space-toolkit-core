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

/// @brief Zip iterator
///
/// Allows iterating over multiple sequences simultaneously.
///
/// @code
///     Array<int> a = {1, 2, 3} ;
///     Array<String> b = {"a", "b", "c"} ;
///     for (const auto& [x, y] : Zip(a, b))
///     {
///     // x = 1, y = "a" ; x = 2, y = "b" ; ...
///     }
/// @endcode
///
/// @ref https://gist.github.com/mortehu/373069390c75b02f98b655e3f7dbef9a
template <typename... T>
class ZipIterator
{
   public:
    /// @brief Inner iterator over zipped elements
    class Iterator : std::iterator<std::forward_iterator_tag, std::tuple<decltype(*std::declval<T>().begin())...>>
    {
       public:
        std::tuple<decltype(std::declval<T>().begin())...> iterators_;

        /// @brief Constructor
        ///
        /// @param [in] anIteratorList A tuple of iterators
        explicit Iterator(decltype(iterators_) anIteratorList)
            : iterators_ {std::move(anIteratorList)}
        {
        }

        /// @brief Pre-increment operator
        ///
        /// @return Reference to iterator
        Iterator& operator++()
        {
            increment(std::index_sequence_for<T...> {});

            return *this;
        }

        /// @brief Post-increment operator
        ///
        /// @return Iterator before increment
        Iterator operator++(int)
        {
            auto saved {*this};

            increment(std::index_sequence_for<T...> {});

            return saved;
        }

        /// @brief Not equal to operator
        ///
        /// @param [in] anIterator An iterator
        /// @return True if iterators are not equal
        bool operator!=(const Iterator& anIterator) const
        {
            return iterators_ != anIterator.iterators_;
        }

        /// @brief Dereference operator
        ///
        /// @return Tuple of dereferenced values
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

    /// @brief Constructor
    ///
    /// @param [in] aSequence Sequences to zip together
    ZipIterator(T&... aSequence)
        : begin_ {std::make_tuple(aSequence.begin()...)},
          end_ {std::make_tuple(aSequence.end()...)}
    {
    }

    /// @brief Returns an iterator pointing to the first zipped element
    ///
    /// @return Iterator to the first element
    ZipIterator::Iterator begin() const
    {
        return begin_;
    }

    /// @brief Returns an iterator pointing past the last zipped element
    ///
    /// @return Iterator past the last element
    ZipIterator::Iterator end() const
    {
        return end_;
    }

   private:
    ZipIterator::Iterator begin_;
    ZipIterator::Iterator end_;
};

/// @brief Zip multiple sequences together for parallel iteration
///
/// @code
///     Array<int> a = {1, 2, 3} ;
///     Array<String> b = {"a", "b", "c"} ;
///     for (const auto& [x, y] : Zip(a, b))
///     {
///     // ...
///     }
/// @endcode
///
/// @note Sequences must be the same length
///
/// @param [in] seqs Sequences to zip
/// @return ZipIterator over the zipped sequences
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
