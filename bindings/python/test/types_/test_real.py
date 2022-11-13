################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/types_/test_real.py
# @author         Remy Derollez <remy@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

import math

from ostk.core.types import Real, Sign

################################################################################################################################################################

def test_real_constructors ():

    a = Real(0)
    b = Real(1)
    c = Real(123456789)
    d = Real(-1)

    e = Real(0.0)
    f = Real(1.5)
    g = Real(123456789.6)
    h = Real(-3.21)
    i = Real(1 / 3)

    assert isinstance(a, Real)
    assert isinstance(b, Real)
    assert isinstance(c, Real)
    assert isinstance(d, Real)
    assert isinstance(e, Real)
    assert isinstance(f, Real)
    assert isinstance(g, Real)
    assert isinstance(h, Real)
    assert isinstance(i, Real)

def test_real_comparators ():

    a = Real(5.54)

    assert a == a
    assert a == 5.54
    assert a != (a + 14.5)
    assert (a - 1.43) < a
    assert (a - 1.23) <= a
    assert a <= a
    assert (a + 1.0) > a
    assert (a + 1.34) >= a
    assert a >= a

def test_real_operators () :

    a = Real(15.34)
    b = Real(30.46)

    # Addition
    assert a + b == Real(45.80)
    a += b
    assert a == Real(45.80)

    # Substraction
    assert a - b == Real(15.339999999999996)
    a -= b
    assert a == Real(15.339999999999996)

    # Multiplication
    assert a * Real(2.5) == Real(38.349999999999994)
    a *= Real(2.5)
    assert a == Real(38.349999999999994)

    # Division
    assert a / Real(1.6) == Real(23.968749999999996)
    a /= Real(1.6)
    assert a == Real(23.968749999999996)

    # Addition with python native type
    assert a + 4.78 == Real(28.748749999999998)
    a += 4.78
    assert a == Real(28.748749999999998)
    assert isinstance(a, Real)

    # Substraction with python native python
    assert a - 30.98 == Real(-2.231250000000003)
    a -= 30.98
    assert a == Real(-2.231250000000003)
    assert isinstance(a, Real)

    # Multiplication with python native python
    assert a * 2.1 == Real(-4.685625000000006)
    a *= 2.1
    assert a == Real(-4.685625000000006)
    assert isinstance(a, Real)

    # Division with python native python
    assert a / (-3.67) == Real(1.2767370572207102)
    a /= -3.67
    assert a == Real(1.2767370572207102)
    assert isinstance(a, Real)

def test_real_casting ():

    a = Real(0.0)
    b = Real(5.2)
    c = Real(-7.65)

    assert a == 0.0
    assert b == 5.2
    assert c == -7.65
    assert float(b) == 5.2
    assert float(a) == 0.0
    assert float(c) == -7.65
    assert isinstance(a, Real)
    assert isinstance(b, Real)
    assert isinstance(c, Real)
    assert isinstance(float(a), float)
    assert isinstance(float(b), float)
    assert isinstance(float(c), float)

def test_real_is_defined ():

    a = Real(10.0)
    b = Real(-1346.67)
    c = Real(0.0)
    d = Real(5 / 3)
    e = Real.undefined()

    assert a.is_defined() is True
    assert b.is_defined() is True
    assert c.is_defined() is True
    assert d.is_defined() is True
    assert e.is_defined() is False

def test_real_is_zero ():

    a = Real(4.0)
    b = Real(0)
    c = Real.zero()
    d = Real(0.0)

    assert a.is_zero() is False
    assert b.is_zero() is True
    assert c.is_zero() is True
    assert d.is_zero() is True

def test_real_is_positive ():

    assert Real(-3.0).is_positive() is False
    assert Real(0.0).is_positive() is True
    assert Real(4.0).is_positive() is True

def test_real_is_negative ():

    assert Real(-5.2).is_negative() is True
    assert Real(0.0).is_negative() is True
    assert Real(7.45687).is_negative() is False

def test_real_is_strictly_positive ():

    assert Real(-15.534).is_strictly_positive() is False
    assert Real(0.0).is_strictly_positive() is False
    assert Real(1.346).is_strictly_positive() is True
    assert Real(5 / 6).is_strictly_positive() is True

def test_real_is_strictly_negative ():

    assert Real(-1.34).is_strictly_negative() is True
    assert Real(-18.54).is_strictly_negative() is True
    assert Real(0.0).is_strictly_negative() is False
    assert Real(2 / 3).is_strictly_negative() is False

def test_real_is_infinity ():

    a = Real.positive_infinity()
    b = Real.negative_infinity()
    c = Real(3467670)
    d = Real(0.0)
    e = Real(-3500678)

    assert a.is_infinity()
    assert b.is_infinity()
    assert c.is_infinity() is False
    assert d.is_infinity() is False
    assert e.is_infinity() is False
    assert a.is_positive_infinity()
    assert b.is_positive_infinity() is False
    assert b.is_negative_infinity()
    assert a.is_negative_infinity() is False
    assert c.is_positive_infinity() is False
    assert c.is_negative_infinity() is False
    assert d.is_positive_infinity() is False
    assert d.is_negative_infinity() is False
    assert e.is_positive_infinity() is False
    assert e.is_negative_infinity() is False

def test_real_is_integer ():

    assert Real(1.2).is_integer() is False
    assert Real(0).is_integer() is True
    assert Real(1.0).is_integer() is True
    assert Real(4976).is_integer() is True
    assert Real(-245.87).is_integer() is False
    assert Real(-35723).is_integer() is True
    assert Real(450.00001).is_integer() is False
    assert Real(458.99999999).is_integer() is False

def test_real_is_finite ():

    assert Real(0).is_finite() is True
    assert Real(1).is_finite() is True
    assert Real(-1).is_finite() is True
    assert Real(45).is_finite() is True

def test_real_is_near ():

    assert Real(0.9999999999999).is_near(Real(1.0), 1e-9) is True
    assert Real(0.999999999999).is_near(1.0, 1e-8) is True
    assert Real(0.95).is_near(Real(1.0), 0.01) is False
    assert Real(0.97).is_near(Real(1.0), 0.05) is True
    assert Real(-0.9999999999999).is_near(Real(-1.0), 1e-9) is True

def test_real_get_sign ():

    assert Real.undefined().get_sign() == Sign.Undefined
    assert Real(456).get_sign() == Sign.Positive
    assert Real(457.3455).get_sign() == Sign.Positive
    assert Real(0.0).get_sign() == Sign.NoSign
    assert Real(-40.54).get_sign() == Sign.Negative

def test_real_abs ():

    assert Real(43.4).abs() == 43.4
    assert Real(-43.43).abs() == 43.43
    assert Real.zero().abs() == 0.0

def test_real_floor ():

    assert Real(43.4).floor() == 43
    assert Real(-3.2).floor() == -4
    assert Real(-23.0).floor() == -23
    assert Real(43.6).floor() == 43
    assert Real(90.999).floor() == 90

def test_real_sqrt ():

    assert Real(64.0).sqrt() == 8.0
    assert Real(16.0).sqrt() == 4.0
    assert Real(45.6).sqrt() == math.sqrt(45.6)
    assert Real(-3.56).sqrt().is_defined() is False

def test_real_pi ():

    assert Real.pi() == math.pi
    assert Real.half_pi() == math.pi / 2
    assert Real.two_pi() == 2 * math.pi

def test_real_epsilon ():

    assert Real.epsilon() == 1e-15
    assert isinstance(Real.epsilon(), Real)

def test_real_integer ():

    assert Real.integer(19) == 19.0
    assert Real.integer(0) == 0.0
    assert Real.integer(-45) == -45.0
    assert Real.integer(76) == Real(76.0)

# def test_real_parse ():

# def test_real_can_parse ():

################################################################################################################################################################
