/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_System_User__
#define __OpenSpaceToolkit_Core_System_User__

#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace system
{

using ostk::core::types::String;

/// @brief                      User
///
///                             POSIX compliant
///
/// @ref                        https://en.wikipedia.org/wiki/User_identifier

class User
{
   public:
    User(const uint& aUID, const String& aName);

    User(const uint& aUID, const uint& aEUID, const String& aName);

    bool operator==(const User& aUser) const;

    bool operator!=(const User& aUser) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const User& aUser);

    bool isDefined() const;

    int getUID() const;

    int getEUID() const;

    String getName() const;

    static User Undefined();

    static User Process();

    static User UID(const uint& aUID);

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
