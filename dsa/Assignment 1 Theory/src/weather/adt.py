from typing import Union, Tuple, List, Dict

from src.weather.models.record import WeatherRecord
from src.weather.storage.base import BaseStorage


class WeatherRecordADT:
    """
    ADT for managing weather records.
    """

    def __init__(self, storage_backend: BaseStorage):
        """
        Initializes the WeatherRecordADT.

        Args:
            storage_backend: The storage backend to use.
        """
        self.storage = storage_backend

    def insert(self, record: WeatherRecord) -> bool:
        """
        Inserts a weather record.

        Args:
            record: The weather record to insert.

        Returns:
            True if the insertion was successful, False otherwise.
        """
        return self.storage.insert(record)

    def delete(self, city: str, date: Union[str, Tuple[int, int, int]]) -> bool:
        """
        Deletes a weather record.

        Args:
            city: The city of the record to delete.
            date: The date of the record to delete.

        Returns:
            True if the deletion was successful, False otherwise.
        """
        return self.storage.delete(city, date)

    def retrieve(
        self, city: str, year: int
    ) -> Union[List[float], Dict[str, float], None]:
        """
        Retrieves weather data for a given city and year.

        Args:
            city: The city to retrieve data for.
            year: The year to retrieve data for.

        Returns:
            The temperature data for the given city and year, or None if not found.
        """
        return self.storage.retrieve(city, year)
