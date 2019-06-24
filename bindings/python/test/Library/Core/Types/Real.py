# coding=utf-8

################################################################################################################################################################

# @project        Library ▸ Core
# @file           Library/Core/LibraryCorePy/Types/Real.test.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

from LibraryCorePy import Types

assert Types.Real(0.0) == 0.0
assert Types.Real(123.456) == 123.456
assert Types.Real(+123.456) == +123.456
assert Types.Real(-123.456) == -123.456

assert Types.Real(0.0).toString() == "0.0"
assert Types.Real(123.456).toString() == "123.456"
assert Types.Real(+123.456).toString() == "123.456"
assert Types.Real(-123.456).toString() == "-123.456"

################################################################################################################################################################
