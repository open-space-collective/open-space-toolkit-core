################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/types/test_object.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from tempfile import NamedTemporaryFile

from ostk.core.containers import Object
from ostk.core.containers import Dictionary
from ostk.core.filesystem import Path
from ostk.core.filesystem import File

################################################################################################################################################################

class TestObject:

    def test_operators (self):

        assert (Object.boolean(True) == Object.boolean(True)) is True
        assert (Object.boolean(True) != Object.boolean(True)) is False

        assert Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')])[0] == Object.integer(123)
        assert Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')])[1] == Object.real(123.456)
        assert Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')])[2] == Object.string('abc')

    def test_str (self):

        assert isinstance(str(Object.boolean(True)), str)

    def test_is_defined (self):

        assert Object.boolean(True).is_defined()

    def test_is_boolean (self):

        assert Object.boolean(True).is_boolean()

    def test_is_integer (self):

        assert Object.integer(123).is_integer()

    def test_is_real (self):

        assert Object.real(123.456).is_real()

    def test_is_string (self):

        assert Object.string('abc').is_string()

    def test_is_dictionary (self):

        assert Object.dictionary(Dictionary({})).is_dictionary()

    def test_is_array (self):

        assert Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')]).is_array()

    def test_get_type (self):

        assert Object.boolean(True).get_type() == Object.Type.Boolean

    def test_get_boolean (self):

        assert Object.boolean(True).get_boolean() == True

    def test_get_integer (self):

        assert Object.integer(123).get_integer() == 123

    def test_get_real (self):

        assert Object.real(123.456).get_real() == 123.456

    def test_get_string (self):

        assert Object.string('abc').get_string() == 'abc'

    def test_get_dictionary (self):

        assert Object.dictionary(Dictionary.empty()).get_dictionary() == Dictionary.empty()

    def test_get_array (self):

        assert Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')]).get_array() == [Object.integer(123), Object.real(123.456), Object.string('abc')]

    def test_to_string (self):

        assert Object.real(123.456).to_string(Object.Format.JSON) == '123.456'
        # assert Object.real(123.456).to_string(Object.Format.YAML) == '123.456'

    def test_undefined (self):

        assert Object.undefined().is_defined() is False

    def test_boolean (self):

        assert Object.boolean(True).is_defined() is True

    def test_integer (self):

        assert Object.integer(123).is_defined() is True

    def test_real (self):

        assert Object.real(123.456).is_defined() is True

    def test_string (self):

        assert Object.string('abc').is_defined() is True

    def test_dictionary (self):

        assert Object.dictionary(Dictionary.empty()).is_defined() is True

    def test_array (self):

        assert Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')]).is_defined() is True

    def test_parse (self):

        assert Object.parse('', Object.Format.YAML) == Object.undefined()
        assert Object.parse('null', Object.Format.YAML) == Object.undefined()

        assert Object.parse('true', Object.Format.YAML) == Object.boolean(True)
        assert Object.parse('false', Object.Format.YAML) == Object.boolean(False)

        assert Object.parse('0', Object.Format.YAML) == Object.integer(0)
        assert Object.parse('123', Object.Format.YAML) == Object.integer(123)

        assert Object.parse('0.0', Object.Format.YAML) == Object.real(0.0)
        assert Object.parse('123.456', Object.Format.YAML) == Object.real(123.456)

        data: str = '''
        doe: "a deer, a female deer"
        ray: "a drop of golden sun"
        pi: 3.14159
        xmas: true
        french-hens: 3
        calling-birds:
          - huey
          - dewey
          - louie
          - fred
        xmas-fifth-day:
          calling-birds: four
          french-hens: 3
          golden-rings: 5
          partridges:
            count: 1
            location: "a pear tree"
          turtle-doves: two
        '''

        obj = Object.parse(string = data, format = Object.Format.YAML)
        assert obj.is_dictionary() is True
        assert obj['xmas-fifth-day']['partridges']['count'] == Object.integer(1)

    def test_load (self):

        data: str = '''
        doe: "a deer, a female deer"
        ray: "a drop of golden sun"
        pi: 3.14159
        xmas: true
        french-hens: 3
        calling-birds:
          - huey
          - dewey
          - louie
          - fred
        xmas-fifth-day:
          calling-birds: four
          french-hens: 3
          golden-rings: 5
          partridges:
            count: 1
            location: "a pear tree"
          turtle-doves: two
        '''

        reference_object = Object.parse(string = data, format = Object.Format.YAML)

        with NamedTemporaryFile() as file:

            file.write(data.encode('utf-8'))
            file.flush()

            assert Object.load(file = File.path(Path.parse(file.name)), format = Object.Format.YAML) == reference_object

    def test_string_from_type (self):

        assert Object.string_from_type(Object.Type.Boolean) == 'Boolean'

    def test_type_from_string (self):

        assert Object.type_from_string('Boolean') == Object.Type.Boolean

################################################################################################################################################################
