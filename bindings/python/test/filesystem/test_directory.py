################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/filesystem/test_directory.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import os

import pytest

from ostk.core.filesystem import Path, Directory
from ostk.core.types import String

################################################################################################################################################################

def test_directory_constructors ():

    directory = Directory.undefined()
    assert isinstance(directory, Directory)

    directory = Directory.path(Path.current())
    assert isinstance(directory, Directory)
    assert os.getcwd() == directory.to_string()

    directory = Directory.path(Path.parse('/path/to/dir_1'))
    assert isinstance(directory, Directory)

    directory = Directory.root()
    assert isinstance(directory, Directory)
    assert directory.to_string() == '/'
    assert directory.to_string() == String('/')

def test_directory_operators ():

    directory_1 = Directory.path(Path.parse('/path/to/dir_1'))
    directory_2 = Directory.path(Path.current())

    assert directory_1 == directory_1
    assert directory_1 != directory_2

def test_directory_to_string ():

    directory = Directory.path(Path.parse('/path/to/dir_1'))
    dir_string = directory.to_string()

    assert dir_string == String('/path/to/dir_1')
    assert dir_string == '/path/to/dir_1'
    assert isinstance(dir_string, String)

def test_directory_getter_functions ():

    directory = Directory.path(Path.parse('/path/to/dir_1'))
    dir_name = directory.get_name()
    dir_path = directory.get_path()

    assert dir_name == 'dir_1'
    assert isinstance(dir_name, String)
    assert dir_path == Path.parse('/path/to/dir_1')
    assert isinstance(dir_path, Path)

def test_directory_is_defined ():

    directory = Directory.undefined()
    assert directory.is_defined() is False

    directory = Directory.path(Path.current())
    assert directory.is_defined() is True

def test_directory_exists ():

    directory = Directory.undefined()

    with pytest.raises(RuntimeError):

        directory.exists() is False

    directory = Directory.root()
    assert directory.exists() is True

    directory = Directory.path(Path.current())
    assert directory.exists() is True

    directory = Directory.path(Path.parse('/path/to/false_dir_1'))
    assert directory.exists() is False

def test_directory_get_parent_directory ():

    directory = Directory.path(Path.parse('/path/to/false_dir_1'))
    parent_dir = directory.get_parent_directory()

    assert isinstance(parent_dir, Directory)
    assert parent_dir.get_name() == 'to'
    assert parent_dir.get_path() == Path.parse('/path/to')
    assert parent_dir.exists() is False

def test_directory_get_directories ():

    true_directory = Directory.path(Path.current())
    assert true_directory.exists() is True
    directories = true_directory.get_directories()
    assert isinstance(directories, list)
    if len(directories) > 0:
        assert isinstance(directories[0], Directory)

    false_directory = Directory.path(Path.parse('/path/to/false_dir_1'))
    assert false_directory.exists() is False

    with pytest.raises(RuntimeError):
        directories = false_directory.get_directories()

    root_directory = Directory.root()
    assert root_directory.exists() is True
    directories = root_directory.get_directories()
    assert len(directories) > 0
    assert isinstance(directories[0], Directory)

def test_directory_is_empty ():

    root_directory = Directory.root()
    assert root_directory.is_empty() is False

    false_directory = Directory.path(Path.parse('/path/to/false_dir_1'))
    assert false_directory.exists() is False

    with pytest.raises(RuntimeError):
        false_directory.is_empty()

# def test_directory_contains_file_with_name ():

################################################################################################################################################################
