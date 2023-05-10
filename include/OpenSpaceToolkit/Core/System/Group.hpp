/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_System_Group__
#define __OpenSpaceToolkit_Core_System_Group__

#include <OpenSpaceToolkit/Core/Types/String.hpp>

namespace ostk
{
namespace core
{
namespace system
{

using ostk::core::types::String;

/// @brief                      Group
///
///                             POSIX compliant
///
/// @ref                        https://en.wikipedia.org/wiki/Group_identifier

class Group
{
   public:
    Group(const uint& aGID, const String& aName);

    Group(const uint& aGID, const uint& aEGID, const String& aName);

    bool operator==(const Group& aGroup) const;

    bool operator!=(const Group& aGroup) const;

    friend std::ostream& operator<<(std::ostream& anOutputStream, const Group& aGroup);

    bool isDefined() const;

    int getGID() const;

    int getEGID() const;

    int getSGID() const;

    String getName() const;

    static Group Undefined();

    static Group Process();

    static Group GID(const uint& aGID);

    static Group Name(const String& aName);

   private:
    int gid_;
    int egid_;
    String name_;
};

}  // namespace system
}  // namespace core
}  // namespace ostk

#endif
