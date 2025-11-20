from __future__ import annotations
from abc import ABC, abstractmethod
from typing import Iterator, Union, Tuple, List, Dict, TYPE_CHECKING

if TYPE_CHECKING:
    from src.weather.models.record import WeatherRecord


class BaseStorage(ABC):
    """
    Abstract base class for weather data storage.
    """

    @abstractmethod
    def populate_array(self, records: List[WeatherRecord]) -> int:
        """
        Populates the storage with a list of weather records.
        """
        pass

    @abstractmethod
    def insert(self, record: WeatherRecord) -> bool:
        """
        Inserts a single weather record into the storage.
        """
        pass

    @abstractmethod
    def delete(self, city: str, date: Union[str, Tuple[int, int, int]]) -> bool:
        """
        Deletes a weather record from the storage.
        """
        pass

    @abstractmethod
    def retrieve(
        self, city: str, year: int
    ) -> Union[List[float], Dict[str, float], None]:
        """
        Retrieves weather data for a given city and year.
        """
        pass

    @abstractmethod
    def row_major_access(self) -> Iterator[Tuple[int, str, str, float, bool]]:
        """
        Provides row-major access to the stored data.
        """
        pass

    @abstractmethod
    def column_major_access(self) -> Iterator[Tuple[int, str, str, float, bool]]:
        """
        Provides column-major access to the stored data.
        """
        pass

    @abstractmethod
    def handle_sparse_data(self, mode: str) -> None:
        """
        Handles sparse data based on the given mode.
        """
        pass

    @abstractmethod
    def analyze_complexity(self) -> Dict[str, str]:
        """
        Analyzes the complexity of the storage operations.
        """
        pass
