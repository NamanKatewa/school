from typing import Iterator, Union, Tuple, List, Dict

from src.weather.models.record import WeatherRecord
from src.weather.utils.validation import normalize_date
from src.weather.storage.base import BaseStorage
from src.weather.indexing import mapping


class SparseStorage(BaseStorage):
    """
    Sparse storage implementation for weather data.
    """

    def __init__(self, years: List[int], cities: List[str]):
        """
        Initializes the sparse storage.

        Args:
            years: A list of years.
            cities: A list of cities.
        """
        self.year_map, self.year_map_inv, self.city_map, self.city_map_inv = (
            mapping.construct_mappings(years, cities)
        )
        self.store: Dict[Tuple[int, int], float] = {}

    def populate_array(self, records: List[WeatherRecord]) -> int:
        """
        Populates the storage with a list of weather records.

        Args:
            records: A list of weather records.

        Returns:
            The number of records inserted.
        """
        count = 0
        for record in records:
            if self.insert(record):
                count += 1
        return count

    def insert(self, record: WeatherRecord) -> bool:
        """
        Inserts a single weather record into the storage.

        Args:
            record: The weather record to insert.

        Returns:
            True if the insertion was successful, False otherwise.
        """
        try:
            year_index, city_index = mapping.get_indices(
                self.year_map, self.city_map, record.date[2], record.city
            )
            self.store[(year_index, city_index)] = record.temperature
            return True
        except KeyError:
            return False

    def delete(self, city: str, date: Union[str, Tuple[int, int, int]]) -> bool:
        """
        Deletes a weather record from the storage.

        Args:
            city: The city of the record to delete.
            date: The date of the record to delete.

        Returns:
            True if the deletion was successful, False otherwise.
        """
        try:
            date_tuple, _ = normalize_date(date)
            year_index, city_index = mapping.get_indices(
                self.year_map, self.city_map, date_tuple[2], city
            )
            if (year_index, city_index) in self.store:
                del self.store[(year_index, city_index)]
            return True
        except KeyError:
            return False

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
        try:
            year_index, city_index = mapping.get_indices(
                self.year_map, self.city_map, year, city
            )
            return self.store.get((year_index, city_index))
        except KeyError:
            return None

    def row_major_access(self) -> Iterator[Tuple[int, str, str, float, bool]]:
        """
        Provides row-major access to the stored data.

        Yields:
            A tuple containing the year, city, date, temperature, and a present flag.
        """
        for year_index, year in enumerate(self.year_map_inv):
            for city_index, city in enumerate(self.city_map_inv):
                temp = self.store.get((year_index, city_index))
                present = temp is not None
                date_key = f"{year}-01-01"
                yield year, city, date_key, temp, present

    def column_major_access(self) -> Iterator[Tuple[int, str, str, float, bool]]:
        """
        Provides column-major access to the stored data.

        Yields:
            A tuple containing the year, city, date, temperature, and a present flag.
        """
        for city_index, city in enumerate(self.city_map_inv):
            for year_index, year in enumerate(self.year_map_inv):
                temp = self.store.get((year_index, city_index))
                present = temp is not None
                date_key = f"{year}-01-01"
                yield year, city, date_key, temp, present

    def handle_sparse_data(self, mode: str) -> None:
        """
        Handles sparse data based on the given mode.

        Raises:
            NotImplementedError: This method is not implemented for SparseStorage.
        """
        raise NotImplementedError("SparseStorage does not handle sparse data modes.")

    def analyze_complexity(self) -> Dict[str, str]:
        """
        Analyzes the complexity of the storage operations.

        Returns:
            A dictionary containing the complexity analysis.
        """
        return {
            "insert": "O(1)",
            "delete": "O(1)",
            "retrieve": "O(1)",
            "space": "O(N)",
            "row_major_access": "O(Y * C)",
            "column_major_access": "O(Y * C)",
        }
