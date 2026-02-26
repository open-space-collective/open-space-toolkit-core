/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_Type_String__
#define __OpenSpaceToolkit_Core_Type_String__

#if __cplusplus >= 202002L
#define CPP20
#endif

#ifdef CPP20
#include <format>
#else
#define FMT_HEADER_ONLY
#include <fmt/format.h>
#endif
#include <ostream>
#include <regex>
#include <string>
#include <type_traits>

#include <boost/regex.hpp>

#include <OpenSpaceToolkit/Core/Type/Index.hpp>
#include <OpenSpaceToolkit/Core/Type/Size.hpp>

namespace ostk
{
namespace core
{

// Forward declare Array to avoid circular dependency
namespace container
{
template <typename T>
class Array;
}

namespace type
{

using ostk::core::container::Array;
using ostk::core::type::Index;
using ostk::core::type::Size;

class Real;
class Integer;

/// @brief A sequence of characters
///
/// @note The current implementation (derived for std::string) is temporary, as this type of
/// inheritance this is not recommended.
class String : public std::string
{
   public:
    using std::string::string;

    /// @brief Default constructor
    ///
    /// @code
    ///     String string ;
    /// @endcode
    String();

    /// @brief Constructor from std::string
    ///
    /// @code
    ///     String string("Hello") ;
    /// @endcode
    ///
    /// @param [in] aString A standard string
    String(const std::string& aString);

    /// @brief Destructor
    ~String();

    /// @brief Check if string is empty
    ///
    /// @code
    ///     String("Hello").isEmpty() ; // False
    ///     String("").isEmpty() ; // True
    /// @endcode
    ///
    /// @return True if empty
    bool isEmpty() const;

    /// @brief Check if all characters are uppercase
    ///
    /// @code
    ///     String("ABC").isUppercase() ; // True
    ///     String("Abc").isUppercase() ; // False
    /// @endcode
    ///
    /// @return True if all characters are uppercase
    bool isUppercase() const;

    /// @brief Check if all characters are lowercase
    ///
    /// @code
    ///     String("abc").isLowercase() ; // True
    ///     String("Abc").isLowercase() ; // False
    /// @endcode
    ///
    /// @return True if all characters are lowercase
    bool isLowercase() const;

    /// @brief Returns whether the string matches a regular expression
    ///
    /// @code
    ///     String("abc").match(std::regex("^[a-z]{3}$")) ; // True
    /// @endcode
    ///
    /// @param [in] aRegularExpression A regular expression
    /// @return True if matches regular expression
    bool match(const std::regex& aRegularExpression) const;

    /// @brief Returns whether the string matches a regular expression (boost::regex overload)
    ///
    /// @code
    ///     String("abc").match(boost::regex("^[a-z]{3}$")) ; // True
    /// @endcode
    ///
    /// @param [in] aRegularExpression A boost regular expression
    /// @return True if matches regular expression
    bool match(const boost::regex& aRegularExpression) const;

    /// @brief Get length of string
    ///
    /// @code
    ///     String("Hello").getLength() ; // 5
    /// @endcode
    ///
    /// @return Length of string
    Size getLength() const;

    /// @brief Get first character
    ///
    /// @code
    ///     String("Hello").getFirst() ; // 'H'
    /// @endcode
    ///
    /// @return First character
    char getFirst() const;

    /// @brief Get last character
    ///
    /// @code
    ///     String("Hello").getLast() ; // 'o'
    /// @endcode
    ///
    /// @return Last character
    char getLast() const;

    /// @brief Get head of string (first N characters)
    ///
    /// @code
    ///     String("Hello").getHead(3) ; // "Hel"
    /// @endcode
    ///
    /// @param [in] aLength Number of characters
    /// @return Head substring
    String getHead(const Size& aLength) const;

    /// @brief Get tail of string (last N characters)
    ///
    /// @code
    ///     String("Hello").getTail(3) ; // "llo"
    /// @endcode
    ///
    /// @param [in] aLength Number of characters
    /// @return Tail substring
    String getTail(const Size& aLength) const;

    /// @brief Get substring starting at position with given length
    ///
    /// @code
    ///     String("Hello").getSubstring(1, 3) ; // "ell"
    /// @endcode
    ///
    /// @param [in] aStartPosition A start position
    /// @param [in] aLength A length
    /// @return Substring
    String getSubstring(const Index& aStartPosition, const Size& aLength) const;

    /// @brief Split the String into tokens separated by the given delimeter.
    /// E.X. String("1sat2satredsatbluesat").split("sat") -> ["1", "2", "red", "blue", ""]
    ///
    /// @return Array of String tokens
    Array<String> split(const String& aDelimiter) const;

    /// @brief Removes whitespace from both ends
    ///
    /// @return Reference to string
    String& trim();

    /// @brief Replace all occurences of character by other character
    ///
    /// @param [in] aCharacter A character
    /// @param [in] aNewCharacter A replacement character
    /// @return Reference to string
    String& replace(const char aCharacter, const char aNewCharacter);

    /// @brief Replace all occurences of string by other string
    ///
    /// @param [in] aCharacter A string
    /// @param [in] aNewCharacter A replacement string
    /// @return Reference to string
    String& replace(const String& aString, const String& aNewString);

    /// @brief Construct an empty string
    ///
    /// @code
    ///     String string = String::Empty() ; // ""
    /// @endcode
    ///
    /// @return Empty string
    static String Empty();

    /// @brief Construct a string from a boolean value
    ///
    /// @code
    ///     String::Boolean(true) ; // "True"
    ///     String::Boolean(false) ; // "False"
    /// @endcode
    ///
    /// @param [in] aBoolean A boolean
    /// @return String representation of boolean
    static String Boolean(bool aBoolean);

    /// @brief Construct a string from a single character
    ///
    /// @code
    ///     String::Char('A') ; // "A"
    /// @endcode
    ///
    /// @param [in] aCharacter A character
    /// @return String containing the character
    static String Char(char aCharacter);

    /// @brief Construct a string by replicating a character
    ///
    /// @code
    ///     String::Replicate('a', 3) ; // "aaa"
    /// @endcode
    ///
    /// @param [in] aCharacter A character
    /// @param [in] aCount Number of repetitions
    /// @return Replicated string
    static String Replicate(char aCharacter, Size aCount);

    /// @brief Construct a string by replicating a string
    ///
    /// @code
    ///     String::Replicate("ab", 3) ; // "ababab"
    /// @endcode
    ///
    /// @param [in] aString A string
    /// @param [in] aCount Number of repetitions
    /// @return Replicated string
    static String Replicate(const String& aString, Size aCount);

    /// @brief Checks if the string contains any invalid UTF-8 characters
    ///
    /// @param [in] aString A string
    /// @return True if valid UTF-8 string
    static bool IsValidUTF8(const String& aString);

    /// @brief Sanitizes the string by removing any invalid UTF-8 characters
    ///
    /// @param [in] aString A string
    /// @return valid UTF-8 string
    static String SanitizeUTF8(const String& aString);

    /// @brief Create formatted string
    ///
    /// @code
    ///     String::Format("{0}, {1}!", "Hello", "World") ; // "Hello, World!"
    ///     String::Format("Let's operate {0} {1}!", 123, "satellites") ; // "Let's operate 123
    ///     satellites!"
    /// @endcode
    ///
    /// @param [in] aFormat A format
    /// @param [in] anArgumentList A list of arguments
    /// @return Formatted string
#ifdef CPP20
    template <typename... Args>
    static String Format(const std::string_view aFormat, Args&&... anArgumentList)
    {
        return std::vformat(aFormat, std::make_format_args(std::forward<Args>(anArgumentList)...));
    }
#else
    template <typename... Args>
    static String Format(const char* aFormat, Args... anArgumentList)
    {
        return fmt::format(aFormat, anArgumentList...);
    }
#endif
};

/// @ref https://gist.github.com/fenbf/d2cd670704b82e2ce7fd
template <typename T>
class HasToString
{
   private:
    typedef char YesType[1];
    typedef char NoType[2];

    template <typename C>
    static YesType& test(decltype(&C::toString));
    template <typename C>
    static NoType& test(...);

   public:
    enum
    {
        value = sizeof(test<T>(0)) == sizeof(YesType)
    };
};

template <typename T>
typename std::enable_if<HasToString<T>::value, std::string>::type CallToString(T* t)
{
    return t->toString();
}

#ifdef CPP20
// Concept to check if a type is convertible to std::string
template <typename T>
concept StringConvertible = requires(T t) {
    { std::string(t) } -> std::convertible_to<std::string>;
} && !std::is_array_v<T>;  // Exclude array types to avoid ambiguity with const char*
#endif

}  // namespace type
}  // namespace core
}  // namespace ostk

namespace std
{

template <>
struct hash<ostk::core::type::String>
{
    typedef ostk::core::type::String argument_type;
    typedef std::size_t result_type;

    result_type operator()(const argument_type& aString) const
    {
        return std::hash<std::string> {}(aString);
    }
};

#ifdef CPP20
template <>
struct formatter<ostk::core::type::String> : formatter<string>
{
    template <typename FormatContext>
    auto format(const ostk::core::type::String& str, FormatContext& ctx) const
    {
        return formatter<string>::format(static_cast<const string&>(str), ctx);
    }
};

// Generic formatter for StringConvertible types
template <typename T>
    requires ostk::core::type::StringConvertible<T> && (!std::is_same_v<T, ostk::core::type::String>) &&
             (!std::is_same_v<T, std::string>) && (!std::is_same_v<T, const char*>)
struct formatter<T> : formatter<string>
{
    template <typename FormatContext>
    auto format(const T& value, FormatContext& ctx) const
    {
        return formatter<string>::format(string(value), ctx);
    }
};

// Concept to check if a type is an enum
template <typename T>
concept EnumType = is_enum_v<T>;

// Generic formatter for all enum types
template <EnumType T>
struct formatter<T> : formatter<underlying_type_t<T>>
{
    template <typename FormatContext>
    auto format(T value, FormatContext& ctx) const
    {
        return formatter<underlying_type_t<T>>::format(static_cast<underlying_type_t<T>>(value), ctx);
    }
};
#endif

}  // namespace std

#endif
