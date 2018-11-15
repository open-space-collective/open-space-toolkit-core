# coding=utf-8

################################################################################################################################################################

# @project        Library/Core
# @file           Library/Core/LibraryCorePy/Types/Integer.test.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

from LibraryCorePy import Types

assert Types.Integer(0) == 0
assert Types.Integer(123) == 123
assert Types.Integer(+123) == +123
assert Types.Integer(-123) == -123

assert Types.Integer(0).toString() == "0"
assert Types.Integer(123).toString() == "123"
assert Types.Integer(+123).toString() == "123"
assert Types.Integer(-123).toString() == "-123"

################################################################################################################################################################