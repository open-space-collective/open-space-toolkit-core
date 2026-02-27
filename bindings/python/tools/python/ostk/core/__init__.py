# Apache License 2.0

from .OpenSpaceToolkitCorePy import *

import math as _math

from .type import Integer as _Integer
from .type import Sign as _Sign


class Real(float):
    """
    Real number type that inherits from float.

    Provides enhanced functionality over standard float including special states
    (undefined, infinity) and utility methods for numerical analysis.
    """

    def __new__(cls, value=0.0):
        return super().__new__(cls, value)

    def __repr__(self):
        if _math.isnan(self):
            return "Undefined"
        if _math.isinf(self):
            return "+Inf" if self > 0 else "-Inf"
        if self == int(self) and _math.isfinite(self):
            return str(float(self))
        return str(float(self))

    def __str__(self):
        return self.__repr__()

    def __hash__(self):
        return float.__hash__(self)

    # Arithmetic operators returning Real

    def __add__(self, other):
        return Real(float.__add__(self, float(other)))

    def __radd__(self, other):
        return Real(float.__add__(float(other), self))

    def __iadd__(self, other):
        return Real(float.__add__(self, float(other)))

    def __sub__(self, other):
        return Real(float.__sub__(self, float(other)))

    def __rsub__(self, other):
        return Real(float.__sub__(float(other), self))

    def __isub__(self, other):
        return Real(float.__sub__(self, float(other)))

    def __mul__(self, other):
        return Real(float.__mul__(self, float(other)))

    def __rmul__(self, other):
        return Real(float.__mul__(float(other), self))

    def __imul__(self, other):
        return Real(float.__mul__(self, float(other)))

    def __truediv__(self, other):
        other_f = float(other)
        if other_f == 0.0:
            return Real(float("nan"))
        return Real(float.__truediv__(self, other_f))

    def __rtruediv__(self, other):
        if float(self) == 0.0:
            return Real(float("nan"))
        return Real(float.__truediv__(float(other), self))

    def __itruediv__(self, other):
        other_f = float(other)
        if other_f == 0.0:
            return Real(float("nan"))
        return Real(float.__truediv__(self, other_f))

    def __neg__(self):
        return Real(float.__neg__(self))

    def __pos__(self):
        return Real(float(self))

    def __abs__(self):
        return Real(float.__abs__(self))

    # Instance methods

    def is_defined(self):
        """
        Check if the Real number is defined (not NaN or uninitialized).
        """
        return not _math.isnan(self)

    def is_zero(self):
        """
        Check if the Real number is exactly zero.
        """
        return _math.isfinite(self) and float(self) == 0.0

    def is_positive(self):
        """
        Check if the Real number is positive (>= 0).
        """
        if _math.isnan(self):
            return False

        return float(self) >= 0.0 or self == float("inf")

    def is_negative(self):
        """
        Check if the Real number is negative (<= 0).
        """
        if _math.isnan(self):
            return False
        return float(self) <= 0.0 or self == float("-inf")

    def is_strictly_positive(self):
        """
        Check if the Real number is strictly positive (> 0).
        """
        if _math.isnan(self):
            return False
        return float(self) > 0.0 or self == float("inf")

    def is_strictly_negative(self):
        """
        Check if the Real number is strictly negative (< 0).
        """
        if _math.isnan(self):
            return False
        return float(self) < 0.0 or self == float("-inf")

    def is_infinity(self):
        """
        Check if the Real number represents infinity (positive or negative).
        """
        return _math.isinf(self)

    def is_positive_infinity(self):
        """
        Check if the Real number represents positive infinity.
        """
        return self == float("inf")

    def is_negative_infinity(self):
        """
        Check if the Real number represents negative infinity.
        """
        return self == float("-inf")

    def is_integer(self):
        """
        Check if the Real number represents an integer value.
        """
        if not _math.isfinite(self):
            return False
        return float(self) == int(float(self))

    def is_finite(self):
        """
        Check if the Real number is finite (not infinity or NaN).
        """
        return _math.isfinite(self)

    def is_near(self, other, tolerance=1e-15):
        """
        Check if the Real number is near another value within a tolerance.
        """
        self_f = float(self)
        other_f = float(other)
        tol_f = float(tolerance)
        if _math.isnan(self_f):
            raise RuntimeError("Real not defined")
        if _math.isnan(other_f):
            raise RuntimeError("Real not defined")
        if _math.isnan(tol_f):
            raise RuntimeError("Tolerance not defined")
        if _math.isinf(self_f) or _math.isinf(other_f):
            return False
        return _math.fabs(self_f - other_f) <= tol_f

    def get_sign(self):
        """
        Get the sign of the Real number.
        """
        if _math.isnan(self):
            return _Sign.Undefined
        if self == float("inf"):
            return _Sign.Positive
        if self == float("-inf"):
            return _Sign.Negative
        if float(self) > 0.0:
            return _Sign.Positive
        if float(self) < 0.0:
            return _Sign.Negative
        return _Sign.NoSign

    def to_integer(self):
        """
        Convert the Real number to an Integer.
        """
        if not self.is_integer():
            raise RuntimeError("Real is not integer.")
        return _Integer(int(float(self)))

    def abs(self):
        """
        Get the absolute value of the Real number.
        """
        if _math.isnan(self):
            return Real(float("nan"))
        if _math.isinf(self):
            return Real(float("inf"))
        return Real(_math.fabs(float(self)))

    def floor(self):
        """
        Get the floor (largest integer <= value) of the Real number.
        """
        if not _math.isfinite(self):
            return _Integer.undefined()
        return _Integer(int(_math.floor(float(self))))

    def sqrt(self):
        """
        Get the square root of the Real number.
        """
        if _math.isnan(self):
            return Real(float("nan"))
        if self == float("-inf"):
            return Real(float("nan"))
        if self == float("inf"):
            return Real(float("inf"))
        if float(self) < 0.0:
            return Real(float("nan"))
        return Real(_math.sqrt(float(self)))

    # Static methods

    @staticmethod
    def undefined():
        """
        Create an undefined Real number.
        """
        return Real(float("nan"))

    @staticmethod
    def zero():
        """
        Create a Real number representing zero.
        """
        return Real(0.0)

    @staticmethod
    def pi():
        """
        Create a Real number representing pi.
        """
        return Real(_math.pi)

    @staticmethod
    def half_pi():
        """
        Create a Real number representing pi/2.
        """
        return Real(_math.pi / 2.0)

    @staticmethod
    def two_pi():
        """
        Create a Real number representing 2*pi.
        """
        return Real(2.0 * _math.pi)

    @staticmethod
    def epsilon():
        """
        Create a Real number representing machine epsilon.
        """
        return Real(1e-15)

    @staticmethod
    def positive_infinity():
        """
        Create a Real number representing positive infinity.
        """
        return Real(float("inf"))

    @staticmethod
    def negative_infinity():
        """
        Create a Real number representing negative infinity.
        """
        return Real(float("-inf"))

    @staticmethod
    def integer(an_integer):
        """
        Create a Real number from an Integer.
        """
        return Real(float(int(an_integer)))

    @staticmethod
    def can_parse(a_string):
        """
        Check if a string can be parsed as a Real number.
        """
        if not a_string:
            return False
        if a_string in ("Undefined", "NaN", "Inf", "+Inf", "-Inf"):
            return True
        try:
            float(a_string)
            return True
        except ValueError:
            return False

    @staticmethod
    def parse(a_string):
        """
        Parse a string as a Real number.
        """
        if not a_string:
            raise RuntimeError("String is undefined")
        if a_string in ("Undefined", "NaN"):
            return Real(float("nan"))
        if a_string in ("Inf", "+Inf"):
            return Real(float("inf"))
        if a_string == "-Inf":
            return Real(float("-inf"))
        try:
            return Real(float(a_string))
        except ValueError:
            raise RuntimeError(f"Cannot cast string [{a_string}] to Real.")


# Inject the Real class into the type submodule
from . import type as _type_module

_type_module.Real = Real
