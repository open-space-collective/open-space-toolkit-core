################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/filesystem/test_file.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.types import String
from ostk.core.filesystem import Directory, Path, PermissionSet, File

################################################################################################################################################################

def test_file_constructors ():

    undefined_file = File.undefined()
    current_file = File.path(Path.parse('./test_file.py'))

    assert isinstance(undefined_file, File)
    assert isinstance(current_file, File)

def test_file_operators ():

    undefined_file = File.undefined()
    current_file = File.path(Path.parse('./test_file.py'))

    assert current_file == current_file
    assert current_file != undefined_file

def test_file_is_defined ():

    undefined_file = File.undefined()
    current_file = File.path(Path.parse('./test_file.py'))

    assert undefined_file.is_defined() is False
    assert current_file.is_defined() is True

def test_file_exists ():

    current_file = File.path(Path.parse('./__init__.py'))
    false_file = File.path(Path.parse('./false_file.py'))

    assert current_file.exists() is True
    assert false_file.exists() is False

def test_file_getter_functions ():

    current_file = File.path(Path.parse('./__init__.py'))
    shared_lib_file = File.path(Path.parse('./shared_library.so.3.3'))
    test_file = File.path(Path.current() + Path.parse('../assets/pythontestfile.txt'))

    # name
    file_name = current_file.get_name()
    so_file_name = shared_lib_file.get_name()

    assert isinstance(file_name, String)
    assert file_name == '__init__.py'
    assert so_file_name == 'shared_library.so.3.3'

    # extension
    file_extension = current_file.get_extension()
    so_file_extension = shared_lib_file.get_extension()

    assert isinstance(file_extension, String)
    assert isinstance(so_file_extension, String)
    assert file_extension == 'py'
    assert so_file_extension == '3' # [TBR]

    # path
    file_path = current_file.get_path()
    so_file_path = shared_lib_file.get_path()

    assert isinstance(file_path, Path)
    assert file_path == Path.parse('./__init__.py')
    assert so_file_path == Path.parse('./shared_library.so.3.3')

    # permissions
    file_permissions = current_file.get_permissions()
    assert isinstance(file_permissions, PermissionSet)

    with pytest.raises(RuntimeError):
        so_file_permissions = shared_lib_file.get_permissions()

    # directory
    file_directory = current_file.get_parent_directory()
    assert isinstance(file_directory, Directory)
    assert file_directory.to_string() == '/usr/local/lib/python3.11/site-packages/ostk/core'

    # content
    # assert test_file.exists() is True
    # test_file_content = test_file.get_contents()
    # assert test_file_content == 'Hello World\n'

# def test_file_move_to_directory ():

#     test_file = File.path(Path.parse('./assets/pythontestfile.txt'))
#     destination_directory = Directory.path((Path.current() + Path.parse('./assets/testdir')).get_normalized_path())

#     assert destination_directory.exists() is True
#     test_file.move_to_directory(destination_directory)
#     assert File.path(Path.parse('./assets/testdir/pythontestfile.txt')).exists() is True
#     assert File.path(Path.parse('./assets/pythontestfile.txt')).exists() is False

# # def test_file_create ():

# def test_file_remove ():

#     test_file = File.path(Path.parse('./assets/testdir/pythontestfile.txt'))
#     destination_directory = Directory.path(Path.parse('./assets/testdir/'))
#     test_file.remove()

#     assert test_file.exists() is False
#     assert File.path(Path.parse('./assets/pythontestfile.txt')) is False

################################################################################################################################################################
