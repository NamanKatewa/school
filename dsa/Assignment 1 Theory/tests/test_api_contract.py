import unittest
from unittest.mock import Mock

from src.weather.models.record import WeatherRecord
from src.weather.adt import WeatherRecordADT
from src.weather.storage.base import BaseStorage


class TestApiContract(unittest.TestCase):
    def test_adt_calls_backend(self):
        mock_storage = Mock(spec=BaseStorage)
        adt = WeatherRecordADT(mock_storage)

        record = WeatherRecord("2023-01-01", "New York", 10.0)
        adt.insert(record)
        mock_storage.insert.assert_called_once_with(record)

        adt.delete("New York", "2023-01-01")
        mock_storage.delete.assert_called_once_with("New York", "2023-01-01")

        adt.retrieve("New York", 2023)
        mock_storage.retrieve.assert_called_once_with("New York", 2023)


if __name__ == "__main__":
    unittest.main()
