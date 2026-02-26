/// Apache License 2.0

#ifndef __OpenSpaceToolkit_Core_System_Group__
#define __OpenSpaceToolkit_Core_System_Group__

#include <OpenSpaceToolkit/Core/Type/String.hpp>

namespace ostk
{
namespace core
{
namespace system
{

using ostk::core::type::String;

/// @brief Group
///
/// POSIX compliant
///
/// @ref https://en.wikipedia.org/wiki/Group_identifier
class Group
{
   public:
    /// @brief Constructor
    ///
    /// @param [in] aGID A group ID
    /// @param [in] aName A group name
    Group(const uint& aGID, const String& aName);

    /// @brief Constructor with effective group ID
    ///
    /// @param [in] aGID A group ID
    /// @param [in] aEGID An effective group ID
    /// @param [in] aName A group name
    Group(const uint& aGID, const uint& aEGID, const String& aName);

    /// @brief Equal to operator
    ///
    /// @param [in] aGroup A group
    /// @return True if groups are equal
    bool operator==(const Group& aGroup) const;

    /// @brief Not equal to operator
    ///
    /// @param [in] aGroup A group
    /// @return True if groups are not equal
    bool operator!=(const Group& aGroup) const;

    /// @brief Output stream operator
    ///
    /// @param [in] anOutputStream An output stream
    /// @param [in] aGroup A group
    /// @return Reference to output stream
    friend std::ostream& operator<<(std::ostream& anOutputStream, const Group& aGroup);

    /// @brief Check if group is defined
    ///
    /// @return True if defined
    bool isDefined() const;

    /// @brief Get group ID
    ///
    /// @return Group ID
    int getGID() const;

    /// @brief Get effective group ID
    ///
    /// @return Effective group ID
    int getEGID() const;

    /// @brief Get saved group ID
    ///
    /// @return Saved group ID
    int getSGID() const;

    /// @brief Get group name
    ///
    /// @return Group name
    String getName() const;

    /// @brief Construct an undefined group
    ///
    /// @return Undefined group
    static Group Undefined();

    /// @brief Construct a group from the current process
    ///
    /// @return Current process group
    static Group Process();

    /// @brief Construct a group from a group ID
    ///
    /// @param [in] aGID A group ID
    /// @return Group
    static Group GID(const uint& aGID);

    /// @brief Construct a group from a group name
    ///
    /// @param [in] aName A group name
    /// @return Group
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
