################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/types_/test_string.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.types import String

################################################################################################################################################################

def test_string_constructors ():

    a = String('Hello')
    b = String('World')
    c = String("OSTK")

    assert isinstance(a, String)
    assert isinstance(b, String)
    assert isinstance(c, String)

def test_string_comparators ():

    a = String('Hello')

    assert a == a
    assert a == "Hello"
    assert a == 'Hello'
    assert a != (a + ' !')

def test_string_operators ():

    a = String('Hello')
    b = String('World')
    c = String('OSTK')

    assert a + b == String('HelloWorld')

def test_string_casting ():

    a = String('Ostk')
    b = str(a)

    assert isinstance(a, String)
    assert isinstance(b, str)
    assert a == b

def test_string_is_empty ():

    a = String('')
    b = String('a')
    c = String('abcdefg')

    assert a.is_empty() is True
    assert b.is_empty() is False
    assert c.is_empty() is False

def test_string_is_uppercase ():

    a = String('Hello World')
    b = String('OSTK')
    c = String('ostk')

    assert a.is_uppercase() is False
    assert b.is_uppercase() is True
    assert c.is_uppercase() is False

def test_string_is_lowercase ():

    a = String('Hello World')
    b = String('OSTK')
    c = String('ostk')

    assert a.is_lowercase() is False
    assert b.is_lowercase() is False
    assert c.is_lowercase() is True

# def test_string_match ():

#     a = String('Hello World')

#     assert a.match(r'World') is True
#     assert a.match(r'Word') is False
#     assert a.match(r'.*d') is True
#     assert a.match(r'+.d') is True

def test_string_getters ():

    a = String('Hello World')
    b = String('')
    c = String('Ostk')

    # length
    assert a.get_length() == 11
    assert b.get_length() == 0

    # first
    assert a.get_first() == String('H')
    assert a.get_first() == 'H'

    with pytest.raises(RuntimeError):

        b.get_first()

    # last
    assert a.get_last() == String('d')
    assert a.get_last() == 'd'

    with pytest.raises(RuntimeError):

        assert b.get_last()

    # head
    assert c.get_head(0) == String('')
    assert c.get_head(0).is_empty() is True
    assert c.get_head(1) == String('O')
    assert c.get_head(1) == 'O'
    assert c.get_head(1) != 'o'
    assert isinstance(c.get_head(1), String)
    assert c.get_head(2) == String('Os')
    assert c.get_head(2) == 'Os'
    assert isinstance(c.get_head(3), String)

    with pytest.raises(RuntimeError):

        assert b.get_head(1)

    # tail
    assert c.get_tail(0) == String('')
    assert c.get_tail(0).is_empty() is True
    assert c.get_tail(1) == String('k')
    assert c.get_tail(1) == 'k'
    assert c.get_tail(1) != 'K'
    assert isinstance(c.get_tail(1), String)
    assert c.get_tail(3) == String('stk')
    assert c.get_tail(3) == 'stk'
    assert isinstance(c.get_head(3), String)

    with pytest.raises(RuntimeError):

        assert b.get_tail(2)

    # substring
    assert c.get_substring(0, 4)

    with pytest.raises(RuntimeError):

        assert c.get_substring(0, 0)

    # with pytest.raises(RuntimeError):

    #     assert c.get_substring(1, 1)

    assert c.get_substring(0, 1) == String('O')
    assert c.get_substring(0, 1) == 'O'
    assert c.get_substring(0, 2) == 'Os'
    assert c.get_substring(0, 3) == 'Ost'
    assert c.get_substring(0, 4) == 'Ostk'

    with pytest.raises(RuntimeError):

        assert c.get_substring(0, 5)

    with pytest.raises(RuntimeError):

        assert c.get_substring(1, 0)

    assert c.get_substring(1, 2) == 'st'
    assert c.get_substring(1, 3) == 'stk'

    with pytest.raises(RuntimeError):
        assert b.get_substring(0, 1)

def test_string_static_methods ():

    # empty
    assert String.empty() == String('')
    assert String.empty() == ''
    assert String.empty().is_empty() is True
    assert isinstance(String.empty(), String)
    assert str(String.empty()) == ''
    assert str(String.empty()) == String('')
    assert isinstance(str(String.empty()), str)

    # boolean
    assert String.boolean(True) == String('True')
    assert String.boolean(False) == String('False')
    assert isinstance(String.boolean(True), String)

    with pytest.raises(TypeError):

        assert String.boolean('string')

    # char
    assert String.char('e') == String('e')
    assert isinstance(String.char('e'), String)

    with pytest.raises(ValueError):

        assert String.char('')

    with pytest.raises(ValueError):

        assert String.char('st')

    # replicate
    assert String.replicate('a', 3) == String('aaa')
    assert isinstance(String.replicate('a', 3), String)
    assert String.replicate('ab', 4) == String('abababab')
    assert String.replicate('hello', 1) == String('hello')
    assert String.replicate('hello', 2) == String('hellohello')
    assert String.replicate('hello', 2) == 'hellohello'

    # format

################################################################################################################################################################
