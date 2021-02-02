################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/types/test_integer.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.containers import *

################################################################################################################################################################

def test_array_set ():

    # int
    int_array_list = set_int_array([1, 2, 3])
    int_array_tuple = set_int_array((1, 2, 3))

    # double
    double_array_list = set_double_array([1.0, 2.0, 3.0])
    double_array_tuple = set_double_array((1.0, 2.0, 3.0))

    # Integer
    integer_array_list = set_integer_array([1, 2, 3])
    integer_array_tuple = set_integer_array((1, 2, 3))

    # Real
    integer_array_list = set_integer_array([1, 2, 3])
    integer_array_tuple = set_integer_array((1, 2, 3))

    # String
    string_array_list = set_string_array(['abc', 'def', 'ghi'])
    string_array_tuple = set_string_array(('abc', 'def', 'ghi'))

def test_array_get ():

    int_array = [i for i in get_int_array()]
    double_array = [i for i in get_double_array()]
    integer_array = [i for i in get_integer_array()]
    real_array = [i for i in get_real_array()]
    string_array = [i for i in get_string_array()]

################################################################################################################################################################
