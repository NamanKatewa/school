"""
Unit tests for the WeatherRecord class.
"""

import unittest
from src.weather.models.record import WeatherRecord

class TestWeatherRecord(unittest.TestCase):

    def test_valid_string_date(self):
        """Tests that a valid string date is parsed correctly."""
        record = WeatherRecord("2025-10-05", "London", 20.0)
        self.assertEqual(record.date, (5, 10, 2025))

    def test_valid_tuple_date(self):
        """Tests that a valid tuple date is parsed correctly."""
        record = WeatherRecord((5, 10, 2025), "London", 20.0)
        self.assertEqual(record.date, (5, 10, 2025))

    def test_invalid_date_format(self):
        """Tests that an invalid date format raises a ValueError."""
        with self.assertRaises(ValueError):
            WeatherRecord("2025/10/05", "London", 20.0)

    def test_invalid_date_type(self):
        """Tests that an invalid date type raises a TypeError."""
        with self.assertRaises(TypeError):
            WeatherRecord(12345, "London", 20.0)

    def test_valid_temperature(self):
        """Tests that a valid temperature is accepted."""
        record = WeatherRecord("2025-10-05", "London", 20.0)
        self.assertEqual(record.temperature, 20.0)

    def test_invalid_temperature_type(self):
        """Tests that an invalid temperature type raises a TypeError."""
        with self.assertRaises(TypeError):
            WeatherRecord("2025-10-05", "London", "20.0")

    def test_out_of_range_temperature(self):
        """Tests that an out-of-range temperature raises a ValueError."""
        with self.assertRaises(ValueError):
            WeatherRecord("2025-10-05", "London", 120.0)

    def test_to_tuple(self):
        """Tests that the to_tuple method returns the correct tuple."""
        record = WeatherRecord("2025-10-05", "London", 20.0)
        self.assertEqual(record.to_tuple(), ((5, 10, 2025), "London", 20.0))

    def test_from_dict(self):
        """Tests that the from_dict method creates a correct record."""
        record_dict = {"date": "2025-10-05", "city": "London", "temperature": 20.0}
        record = WeatherRecord.from_dict(record_dict)
        self.assertEqual(record.date, (5, 10, 2025))
        self.assertEqual(record.city, "London")
        self.assertEqual(record.temperature, 20.0)

if __name__ == '__main__':
    unittest.main()
