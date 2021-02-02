################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/filesystem/test_path.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.filesystem import Path
from ostk.core.types import String

################################################################################################################################################################

def test_path_parse ():

    # create path from String parsing
    path_1 = Path.parse("/path/to/file.txt")
    path_2 = Path.parse('/path/to/file.txt')
    path_3 = Path.parse(String('/path/to/file.txt'))

    assert isinstance(path_1, Path)
    assert isinstance(path_2, Path)
    assert isinstance(path_3, Path)

def test_path_undefined ():

    # create undefined path
    undefined_path = Path.undefined()
    assert isinstance(undefined_path, Path)

def test_path_root ():

    # create root path
    root_path = Path.root()
    assert isinstance(root_path, Path)

def test_path_current ():

    # create current path
    current_path = Path.current()
    assert isinstance(current_path, Path)

def test_path_operators ():

    path_1 = Path.parse("/path/to/dir_1")
    path_2 = Path.parse("/dir_1/to/file.txt")
    path_3 = path_1 + path_2

    assert path_1 == path_1
    assert path_2 != path_1

    path_1 += path_2

    assert isinstance(path_1, Path)
    assert isinstance(path_2, Path)
    assert isinstance(path_3, Path)

def test_path_is_defined ():

    path_1 = Path.undefined()
    path_2 = Path.current()

    assert path_1.is_defined() is False
    assert path_2.is_defined() is True

def test_path_is_absolute ():

    path_1 = Path.current()
    path_2 = Path.parse('../path/to/file.txt')
    path_3 = Path.parse('./path/to/file.txt')

    assert path_1.is_absolute() is True
    assert path_2.is_absolute() is False
    assert path_3.is_absolute() is False

def test_path_is_relative ():

    path_1 = Path.current()
    path_2 = Path.parse('../path/to/file.txt')
    path_3 = Path.parse('./path/to/file.txt')

    assert path_1.is_relative() is False
    assert path_2.is_relative() is True
    assert path_3.is_relative() is True

def test_path_get_parent_path ():

    path = Path.parse('./path/to/file.txt')
    parent_path = path.get_parent_path()

    assert parent_path.to_string() == './path/to'

def test_path_get_last_element ():

    path_1 = Path.parse('./path/to/file.txt')
    path_2 = Path.parse('/path/to/dir_1')

    assert path_1.get_last_element() == 'file.txt'
    assert path_2.get_last_element() == 'dir_1'

def test_path_get_normalized_path ():

    current_path = Path.current()
    path_1 = Path.parse('/path/to/file.txt')
    path_2 = Path.parse('./path/to/file.txt')
    path_3 = Path.parse('/path/to/../to/./file.txt')
    path_4 = Path.parse('/path/../to/./file.txt')
    norm_path_1 = path_1.get_normalized_path()
    norm_path_2 = path_2.get_normalized_path()
    norm_path_3 = path_3.get_normalized_path()
    norm_path_4 = path_4.get_normalized_path()

    assert path_1.is_absolute() is True
    assert path_1 == norm_path_1

    assert path_2.is_relative() is True
    assert norm_path_2 == current_path + path_1

    assert norm_path_3 == Path.parse('/path/to/file.txt')
    assert norm_path_3.to_string() == '/path/to/file.txt'

    assert norm_path_4 == Path.parse('/to/file.txt')
    assert norm_path_4.to_string() == '/to/file.txt'

def test_path_get_absolute_path ():

    current_path = Path.current()
    path_1 = Path.parse('/path/to/file.txt')
    path_2 = Path.parse('./path/to/file.txt')
    abs_path_1 = path_1.get_absolute_path()
    abs_path_2 = path_2.get_absolute_path()

    assert path_1.is_absolute() is True
    assert path_1 == abs_path_1

    assert path_2.is_relative() is True
    assert abs_path_2 == current_path + path_2
    assert abs_path_2.get_normalized_path() == current_path + path_1

def test_path_to_string ():

    path_1 = Path.undefined()
    with pytest.raises(RuntimeError):

        path_1.to_string()

    path_2 = Path.parse('/path/to/file.txt')
    path_2_string = path_2.to_string()
    assert isinstance(path_2_string, String)
    assert path_2_string == String('/path/to/file.txt')
    assert path_2_string == '/path/to/file.txt'


################################################################################################################################################################
