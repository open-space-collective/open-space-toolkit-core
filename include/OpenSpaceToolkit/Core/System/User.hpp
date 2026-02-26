/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_System_User__
#define __OpenSpaceToolkit_Core_System_User__

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace system
{

using ostk::core::type::String;

/// @brief User
///
/// POSIX compliant
///
/// @ref https://en.wikipedia.org/wiki/User_identifier
class User
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aUID A user ID
    /// @param [in] aName A user name
    User(const uint& aUID, const String& aName);

    /// @brief Constructor with effective user ID
    ///
    /// @param [in] aUID A user ID
    /// @param [in] aEUID An effective user ID
    /// @param [in] aName A user name
    User(const uint& aUID, const uint& aEUID, const String& aName);

    /// @brief Equal to operator
    ///
    /// @param [in] aUser A user
    /// @return True if users are equal
    bool operator==(const User& aUser) const;

    /// @brief Not equal to operator
    ///
    /// @param [in] aUser A user
    /// @return True if users are not equal
    bool operator!=(const User& aUser) const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aUser A user
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const User& aUser);

    /// @brief Check if user is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Get user ID
    ///
    /// @return User ID
    int getUID() const;

    /// @brief Get effective user ID
    ///
    /// @return Effective user ID
    int getEUID() const;

    /// @brief Get user name
    ///
    /// @return User name
    String getName() const;

    /// @brief Construct an undefined user
    ///
    /// @return Undefined user
    static User Undefined();

    /// @brief Construct a user from the current process
    ///
    /// @return Current process user
    static User Process();

    /// @brief Construct a user from a user ID
    ///
    /// @param [in] aUID A user ID
    /// @return User
    static User UID(const uint& aUID);

    /// @brief Construct a user from a user name
    ///
    /// @param [in] aName A user name
    /// @return User
    static User Name(const String& aName);

   private:
    int uid_;
    int euid_;
    String name_;
};

}  // namespace system
}  // namespace core
}  // namespace ostk

#endif
