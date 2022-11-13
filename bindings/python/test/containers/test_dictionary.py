################################################################################################################################################################

# @project        Open Space Toolkit ▸ Core
# @file           bindings/python/test/types/test_dictionary.py
# @author         Lucas Brémond <lucas@loftorbital.com>
# @license        Apache License 2.0

################################################################################################################################################################

import pytest

from ostk.core.containers import Dictionary
from ostk.core.containers import Object

################################################################################################################################################################

@pytest.fixture
def dictionary () -> Dictionary:

    return Dictionary({
        'boolean': True,
        'integer': 123,
        'real': 123.456,
        'string': 'abc',
        'array': [123, 123.456, 'abc'],
        'dictionary': {'key': 'value'},
    })

################################################################################################################################################################

class TestDictionary:

    def test_constructor (self):

        dictionary = Dictionary({
            'boolean': True,
            'integer': 123,
            'real': 123.456,
            'string': 'abc',
            'array': [123, 123.456, 'abc'],
            'dictionary': {'key': 'value'},
        })

        assert dictionary['boolean'] == Object.boolean(True)
        assert dictionary['integer'] == Object.integer(123)
        assert dictionary['real'] == Object.real(123.456)
        assert dictionary['string'] == Object.string('abc')
        assert dictionary['array'] == Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')])
        assert dictionary['dictionary'] == Object.dictionary(Dictionary({'key': 'value'}))

    def test_operator___eq__ (self, dictionary: Dictionary):

        assert (dictionary == dictionary) is True

    def test_operator___ne__ (self, dictionary: Dictionary):

        assert (dictionary != dictionary) is False

    def test_operator___bool__ (self, dictionary: Dictionary):

        assert bool(dictionary) is True

    def test_operator___len__ (self, dictionary: Dictionary):

        assert len(dictionary) == 6

    def test_operator___iter__ (self, dictionary: Dictionary):

        for item in dictionary:
            assert str(item.access_key()) in {'boolean', 'integer', 'real', 'string', 'array', 'dictionary'}
            assert isinstance(item.access_value(), Object)

    def test_operator___contains__ (self, dictionary: Dictionary):

        assert 'boolean' in dictionary
        assert 'abc' not in dictionary

    def test_operator___getitem__ (self, dictionary: Dictionary):

        assert dictionary['boolean'] == Object.boolean(True)
        assert dictionary['integer'] == Object.integer(123)
        assert dictionary['real'] == Object.real(123.456)
        assert dictionary['string'] == Object.string('abc')
        assert dictionary['array'] == Object.array([Object.integer(123), Object.real(123.456), Object.string('abc')])
        assert dictionary['dictionary'] == Object.dictionary(Dictionary({'key': 'value'}))

    # def test_operator___delitem__ (self, dictionary: Dictionary):

    #     ...

    def test_operator___str__ (self, dictionary: Dictionary):

        assert isinstance(str(dictionary), str)

    def test_operator___repr__ (self, dictionary: Dictionary):

        assert isinstance(repr(dictionary), str)

    def test_is_empty (self, dictionary: Dictionary):

        assert dictionary.is_empty() is False

    def test_has_value_for_key (self, dictionary: Dictionary):

        assert dictionary.has_value_for_key(key = 'boolean') is True

    def test_get_size (self, dictionary: Dictionary):

        assert dictionary.get_size() == 6

    def test_add_value_for_key (self, dictionary: Dictionary):

        assert dictionary.has_value_for_key('abc') is False

        dictionary.add_value_for_key(value = Object.integer(123), key = 'abc')

        assert dictionary.has_value_for_key('abc') is True

    def test_empty (self):

        assert Dictionary.empty().is_empty() is True

    def test_parse (self):

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

        dictionary = Dictionary.parse(string = data, format = Object.Format.YAML)

        assert dictionary['count'] == Object.integer(1)

################################################################################################################################################################
