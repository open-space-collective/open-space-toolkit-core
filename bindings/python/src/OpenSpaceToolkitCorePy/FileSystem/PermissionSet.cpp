/// Apache License 2.0

#include <OpenSpaceToolkit/Core/FileSystem/PermissionSet.hpp>

using ostk::core::filesystem::PermissionSet;

inline void OpenSpaceToolkitCorePy_FileSystem_PermissionSet(nanobind::class_<PermissionSet>& permissionSet)
{
    using namespace nanobind;

    permissionSet

        // Define init method using nanobind "init" convenience method
        .def(
            init<const bool, const bool, const bool>(),
            R"doc(
                Construct a PermissionSet with specific read, write, and execute permissions.

                Args:
                    can_read (bool): Whether read permission is granted.
                    can_write (bool): Whether write permission is granted.
                    can_execute (bool): Whether execute permission is granted.

                Example:
                    >>> perm = PermissionSet(True, False, True)  # read and execute only
                    >>> perm.can_read()  # True
                    >>> perm.can_write()  # False
            )doc",
            arg("can_read"),
            arg("can_write"),
            arg("can_execute")
        )

        // Define methods
        .def(
            "__eq__",
            [](const PermissionSet& self, const PermissionSet& other)
            {
                return self == other;
            },
            nanobind::is_operator(),
            R"doc(Check if two PermissionSets are equal.)doc"
        )
        .def(
            "__ne__",
            [](const PermissionSet& self, const PermissionSet& other)
            {
                return self != other;
            },
            nanobind::is_operator(),
            R"doc(Check if two PermissionSets are not equal.)doc"
        )

        .def(
            "__add__",
            [](const PermissionSet& self, const PermissionSet& other)
            {
                return self + other;
            },
            nanobind::is_operator(),
            R"doc(Combine two PermissionSets (union of permissions).)doc"
        )
        .def(
            "__sub__",
            [](const PermissionSet& self, const PermissionSet& other)
            {
                return self - other;
            },
            nanobind::is_operator(),
            R"doc(Remove permissions (subtract permissions).)doc"
        )

        .def("__str__", &(shiftToString<PermissionSet>), R"doc(Return string representation of the PermissionSet.)doc")
        .def(
            "__repr__",
            &(shiftToString<PermissionSet>),
            R"doc(Return string representation of the PermissionSet for debugging.)doc"
        )

        .def(
            "is_none",
            &PermissionSet::isNone,
            R"doc(
                Check if no permissions are granted.

                Returns:
                    bool: True if no permissions (read, write, execute) are granted.

                Example:
                    >>> perm = PermissionSet.none()
                    >>> perm.is_none()  # True
            )doc"
        )
        .def(
            "is_all",
            &PermissionSet::isAll,
            R"doc(
                Check if all permissions are granted.

                Returns:
                    bool: True if all permissions (read, write, execute) are granted.

                Example:
                    >>> perm = PermissionSet.rwx()
                    >>> perm.is_all()  # True
            )doc"
        )
        .def(
            "can_read",
            &PermissionSet::canRead,
            R"doc(
                Check if read permission is granted.

                Returns:
                    bool: True if read permission is granted.

                Example:
                    >>> perm = PermissionSet.r()
                    >>> perm.can_read()  # True
            )doc"
        )
        .def(
            "can_write",
            &PermissionSet::canWrite,
            R"doc(
                Check if write permission is granted.

                Returns:
                    bool: True if write permission is granted.

                Example:
                    >>> perm = PermissionSet.w()
                    >>> perm.can_write()  # True
            )doc"
        )
        .def(
            "can_execute",
            &PermissionSet::canExecute,
            R"doc(
                Check if execute permission is granted.

                Returns:
                    bool: True if execute permission is granted.

                Example:
                    >>> perm = PermissionSet.x()
                    >>> perm.can_execute()  # True
            )doc"
        )

        // Define static methods
        .def_static(
            "none",
            &PermissionSet::None,
            R"doc(
                Create a PermissionSet with no permissions.

                Returns:
                    PermissionSet: A permission set with no permissions granted.

                Example:
                    >>> perm = PermissionSet.none()
                    >>> perm.is_none()  # True
            )doc"
        )
        .def_static(
            "r",
            &PermissionSet::R,
            R"doc(
                Create a PermissionSet with read permission only.

                Returns:
                    PermissionSet: A permission set with read permission.

                Example:
                    >>> perm = PermissionSet.r()
                    >>> perm.can_read()  # True
                    >>> perm.can_write()  # False
            )doc"
        )
        .def_static(
            "w",
            &PermissionSet::W,
            R"doc(
                Create a PermissionSet with write permission only.

                Returns:
                    PermissionSet: A permission set with write permission.

                Example:
                    >>> perm = PermissionSet.w()
                    >>> perm.can_write()  # True
            )doc"
        )
        .def_static(
            "x",
            &PermissionSet::X,
            R"doc(
                Create a PermissionSet with execute permission only.

                Returns:
                    PermissionSet: A permission set with execute permission.

                Example:
                    >>> perm = PermissionSet.x()
                    >>> perm.can_execute()  # True
            )doc"
        )
        .def_static(
            "rw",
            &PermissionSet::RW,
            R"doc(
                Create a PermissionSet with read and write permissions.

                Returns:
                    PermissionSet: A permission set with read and write permissions.

                Example:
                    >>> perm = PermissionSet.rw()
                    >>> perm.can_read()  # True
                    >>> perm.can_write()  # True
                    >>> perm.can_execute()  # False
            )doc"
        )
        .def_static(
            "rx",
            &PermissionSet::RX,
            R"doc(
                Create a PermissionSet with read and execute permissions.

                Returns:
                    PermissionSet: A permission set with read and execute permissions.

                Example:
                    >>> perm = PermissionSet.rx()
                    >>> perm.can_read()  # True
                    >>> perm.can_execute()  # True
                    >>> perm.can_write()  # False
            )doc"
        )
        .def_static(
            "rwx",
            &PermissionSet::RWX,
            R"doc(
                Create a PermissionSet with all permissions (read, write, execute).

                Returns:
                    PermissionSet: A permission set with all permissions.

                Example:
                    >>> perm = PermissionSet.rwx()
                    >>> perm.is_all()  # True
            )doc"
        )

        ;
}
