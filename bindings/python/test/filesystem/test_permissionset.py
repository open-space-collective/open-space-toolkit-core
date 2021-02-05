################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/filesystem/test_permissionset.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import itertools

import pytest

from ostk.core.filesystem import Path, Directory, File, PermissionSet

################################################################################################################################################################

def test_permissionset_constructors ():

    # Test all combinations of permissions wit default constructor
    l = [False, True]
    permission_sets = list(itertools.product(l, repeat=3))
    for permission_set in permission_sets:
        permissionset = PermissionSet(*permission_set)
        assert isinstance(permissionset, PermissionSet)

    # Static constructors
    permissionset = PermissionSet.none()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset.can_read() is False
    assert permissionset.can_write() is False
    assert permissionset.can_execute() is False
    assert permissionset.is_none() is True

    permissionset = PermissionSet.r()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset == PermissionSet(True, False, False)
    assert permissionset.can_read() is True
    assert permissionset.can_write() is False
    assert permissionset.can_execute() is False

    permissionset = PermissionSet.w()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset == PermissionSet(False, True, False)
    assert permissionset.can_read() is False
    assert permissionset.can_write() is True
    assert permissionset.can_execute() is False

    permissionset = PermissionSet.x()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset == PermissionSet(False, False, True)
    assert permissionset.can_read() is False
    assert permissionset.can_write() is False
    assert permissionset.can_execute() is True

    permissionset = PermissionSet.rw()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset == PermissionSet(True, True, False)
    assert permissionset.can_read() is True
    assert permissionset.can_write() is True
    assert permissionset.can_execute() is False

    permissionset = PermissionSet.rx()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset == PermissionSet(True, False, True)
    assert permissionset.can_read() is True
    assert permissionset.can_write() is False
    assert permissionset.can_execute() is True

    permissionset = PermissionSet.rwx()
    assert isinstance(permissionset, PermissionSet)
    assert permissionset == PermissionSet(True, True, True)
    assert permissionset.can_read() is True
    assert permissionset.can_write() is True
    assert permissionset.can_execute() is True
    assert permissionset.is_all() is True

def test_permissionset_operators ():

    permissionset_1 = PermissionSet.r()
    permissionset_2 = PermissionSet(False, True, True)
    permissionset_3 = PermissionSet(True, False, False)

    permissionset_4 = permissionset_1 + permissionset_2
    permissionset_5 = permissionset_3 - permissionset_2

    assert permissionset_1 == permissionset_1
    assert permissionset_1 != permissionset_2
    assert permissionset_3 == permissionset_1

    assert isinstance(permissionset_4, PermissionSet)
    assert isinstance(permissionset_5, PermissionSet)
    assert permissionset_4.is_all() is True
    assert permissionset_5 == permissionset_3

################################################################################################################################################################
