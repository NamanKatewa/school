"""
This module defines the WeatherRecord ADT.
"""

from src.weather.utils.validation import normalize_date, validate_temperature

class WeatherRecord:
    """
    Represents a single weather record.
    """

    def __init__(self, date, city, temperature):
        """
        Initializes a WeatherRecord object.

        Args:
            date: The date of the record (string or tuple).
            city: The city of the record.
            temperature: The temperature of the record.
        """
        self.date, self._date_key = normalize_date(date)
        self.city = city
        self.temperature = validate_temperature(temperature)

    def to_tuple(self) -> tuple:
        """
        Returns the record as a tuple.

        Returns:
            A tuple containing the date, city, and temperature.
        """
        return (self.date, self.city, self.temperature)

    @classmethod
    def from_dict(cls, d: dict):
        """
        Creates a WeatherRecord object from a dictionary.

        Args:
            d: A dictionary containing the record data.

        Returns:
            A WeatherRecord object.
        """
        return cls(d['date'], d['city'], d['temperature'])
