################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/types_/test_integer.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.types import Integer, Sign

################################################################################################################################################################

def test_integer_constructors ():

    a = Integer(0)
    b = Integer(1)
    c = Integer(123456789)
    d = Integer(-1)
    u = Integer.undefined()

    assert isinstance(a, Integer)
    assert isinstance(b, Integer)
    assert isinstance(c, Integer)
    assert isinstance(d, Integer)
    assert isinstance(u, Integer)

    with pytest.raises(TypeError):

        e = Integer(1.2)

def test_integer_comparators ():

    a = Integer(5)

    assert a == a
    assert a == 5
    assert a != (a + 1)
    assert (a - 1) < a
    assert (a - 1) <= a
    assert a <= a
    assert (a + 1) > a
    assert (a + 1) >= a
    assert a >= a

def test_integer_operators () :

    a = Integer(15)
    b = Integer(30)
    c = Integer(-45)

    # Addition
    assert a + b == Integer(45)
    a += b
    assert a == Integer(45)

    # Substraction
    assert a - b == Integer(15)
    a -= b
    assert a == Integer(15)

    # Multiplication
    assert a * Integer(2) == Integer(30)
    a *= Integer(1)
    assert a == Integer(15)

    # Division
    assert a / Integer(3) == Integer(5)
    a /= Integer(3)
    assert a == Integer(5)

    # Addition with python native type
    assert a + 2 == Integer(7)
    a += 2
    assert a == Integer(7)

    # Substraction with python native python
    assert a - 10 == Integer(-3)
    a -= 10
    assert a == Integer(-3)

    # Multiplication with python native python
    assert a * 2 == Integer(-6)
    a *= 2
    assert a == Integer(-6)

    # Division with python native python
    assert a / (-3) == Integer(2)
    a /= -3
    assert a == Integer(2)

def test_integer_casting ():

    a = Integer(0)
    b = Integer(5)
    c = Integer(-7)

    assert a == 0
    assert b == 5
    assert c == -7
    assert int(b) == 5
    assert int(a) == 0
    assert int(c) == -7
    assert isinstance(a, Integer)
    assert isinstance(b, Integer)
    assert isinstance(c, Integer)
    assert isinstance(int(a), int)
    assert isinstance(int(b), int)
    assert isinstance(int(c), int)

def test_integer_is_defined ():

    a = Integer(10)
    b = Integer(-1346)
    c = Integer(0)
    u = Integer.undefined()

    assert a.is_defined() is True
    assert b.is_defined() is True
    assert c.is_defined() is True
    assert u.is_defined() is False

def test_integer_zero ():

    a = Integer(4)
    b = Integer(0)
    c = Integer.zero()

    assert a.is_zero() is False
    assert b.is_zero() is True
    assert c.is_zero() is True

def test_integer_is_positive ():

    assert Integer(-3).is_positive() is False
    assert Integer(0).is_positive() is True
    assert Integer(4).is_positive() is True

def test_integer_is_negative ():

    assert Integer(-5).is_negative() is True
    assert Integer(0).is_negative() is True
    assert Integer(7).is_negative() is False

def test_integer_is_strictly_positive ():

    assert Integer(-15).is_strictly_positive() is False
    assert Integer(0).is_strictly_positive() is False
    assert Integer(1).is_strictly_positive() is True
    assert Integer(40).is_strictly_positive() is True

def test_integer_is_strictly_negative ():

    assert Integer(-1).is_strictly_negative() is True
    assert Integer(-18).is_strictly_negative() is True
    assert Integer(0).is_strictly_negative() is False
    assert Integer(2).is_strictly_negative() is False

def test_integer_is_infinity ():

    assert Integer(10).is_infinity() is False
    assert Integer(0).is_infinity() is False
    assert Integer(2000000).is_infinity() is False
    assert Integer(-2400000).is_infinity() is False

    with pytest.raises(TypeError):
        assert Integer(200000000000000000000)
        assert Integer(-200000000000000000000)

# def test_integer_is_positive_infinity ():

# def test_integer_is_negative_infinity ():

def test_integer_is_finite ():

    assert Integer(0).is_finite() is True
    assert Integer(1).is_finite() is True
    assert Integer(-1).is_finite() is True
    assert Integer(2300000).is_finite() is True
    assert Integer(-2300000).is_finite() is True
    # assert Integer(23000000000000000000).is_finite() is False
    # assert Integer(-23000000000000000000).is_finite() is False

def test_integer_is_even ():

    assert Integer(2).is_even() is True
    assert Integer(4).is_even() is True
    assert Integer(6).is_even() is True
    assert Integer(10).is_even() is True
    assert Integer(-4).is_even() is True
    assert Integer(-2).is_even() is True
    assert Integer(-2453856).is_even() is True
    assert Integer(2453856).is_even() is True
    assert Integer(1).is_even() is False
    assert Integer(3).is_even() is False
    assert Integer(0).is_even() is True

def test_integer_is_odd ():

    assert Integer(2).is_odd() is False
    assert Integer(4).is_odd() is False
    assert Integer(6).is_odd() is False
    assert Integer(10).is_odd() is False
    assert Integer(-4).is_odd() is False
    assert Integer(-2).is_odd() is False
    assert Integer(-23257).is_odd() is True
    assert Integer(23257).is_odd() is True
    assert Integer(-2453856).is_odd() is False
    assert Integer(2453856).is_odd() is False
    assert Integer(1).is_odd() is True
    assert Integer(3).is_odd() is True
    assert Integer(0).is_odd() is False

def test_integer_get_sign ():

    assert isinstance(Integer(4).get_sign(), Sign)
    assert Integer(2).get_sign() == Sign.Positive
    assert Integer(-1).get_sign() == Sign.Negative
    assert Integer(232567).get_sign() == Sign.Positive
    assert Integer(0).get_sign() == Sign.NoSign
    assert Integer.undefined().get_sign() == Sign.Undefined

def test_integer_static_methods ():

    a = Integer(34)

    assert Integer.undefined()
    assert Integer.zero() == Integer(0)
    # assert Integer.positive_infinity()
    # assert Integer.negative_infinity()
    assert Integer.int8(a) == a
    assert Integer.int16(a) == a
    assert Integer.int32(a) == a
    assert Integer.uint8(a) == a
    assert Integer.uint16(a) == a
    assert Integer.uint32(a) == a
    assert Integer.uint64(a) == a

    # assert Integer.index()
    # assert Integer.size()

################################################################################################################################################################
