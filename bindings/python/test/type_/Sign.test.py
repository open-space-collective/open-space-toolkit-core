import unittest

from OpenSpaceToolkitCorePy.type import Sign

class TestSign(unittest.TestCase):

    def test_str_conversion(self):
        self.assertEqual("Undefined", str(Sign.Undefined))
        self.assertEqual("Positive", str(Sign.Positive))
        self.assertEqual("Negative", str(Sign.Negative))
        self.assertEqual("None", str(Sign.None))

    def test_from_string_valid_inputs(self):
        self.assertEqual(Sign.Undefined, Sign.from_string("Undefined"))
        self.assertEqual(Sign.Positive, Sign.from_string("Positive"))
        self.assertEqual(Sign.Negative, Sign.from_string("Negative"))
        self.assertEqual(Sign.None, Sign.from_string("None"))

    def test_from_string_invalid_inputs(self):
        with self.assertRaises(ValueError):
            Sign.from_string("InvalidInput")
        with self.assertRaises(ValueError):
            Sign.from_string("")
        with self.assertRaises(ValueError):
            Sign.from_string("positive") # Incorrect case
        with self.assertRaises(ValueError):
            Sign.from_string("NONE") # Incorrect case

if __name__ == '__main__':
    unittest.main()
