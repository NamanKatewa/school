from typing import Iterator, Tuple

from src.weather.storage.base import BaseStorage


def row_major_iter(
    storage: BaseStorage, include_missing: bool = True
) -> Iterator[Tuple[int, str, str, float, bool]]:
    """
    Provides a row-major iterator over the storage.

    Args:
        storage: The storage to iterate over.
        include_missing: Whether to include missing records.

    Yields:
        A tuple containing the year, city, date, temperature, and a present flag.
    """
    for year, city, date_key, temp, present in storage.row_major_access():
        if include_missing or present:
            yield year, city, date_key, temp, present


def column_major_iter(
    storage: BaseStorage, include_missing: bool = True
) -> Iterator[Tuple[int, str, str, float, bool]]:
    """
    Provides a column-major iterator over the storage.

    Args:
        storage: The storage to iterate over.
        include_missing: Whether to include missing records.

    Yields:
        A tuple containing the year, city, date, temperature, and a present flag.
    """
    for year, city, date_key, temp, present in storage.column_major_access():
        if include_missing or present:
            yield year, city, date_key, temp, present
