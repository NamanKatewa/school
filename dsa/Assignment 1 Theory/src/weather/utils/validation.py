"""
This module provides validation and normalization functions for weather data.
"""

def normalize_date(date: str | tuple) -> tuple[tuple[int, int, int], str]:
    """
    Normalizes a date from a string or tuple to a tuple of (day, month, year)
    and a date_key string "YYYY-MM-DD".

    Args:
        date: The date to normalize, as a "YYYY-MM-DD" string or a (day, month, year) tuple.

    Returns:
        A tuple containing the normalized date tuple and a date_key string.
    """
    if isinstance(date, str):
        parts = date.split('-')
        if len(parts) != 3:
            raise ValueError("Invalid date string format. Expected 'YYYY-MM-DD'.")
        year, month, day = int(parts[0]), int(parts[1]), int(parts[2])
    elif isinstance(date, tuple):
        if len(date) != 3:
            raise ValueError("Invalid date tuple format. Expected (day, month, year).")
        day, month, year = date
    else:
        raise TypeError("Invalid date type. Expected a string or a tuple.")

    if not (1 <= month <= 12):
        raise ValueError("Month must be between 1 and 12.")
    if not (1 <= day <= 31):
        raise ValueError("Day must be between 1 and 31.")

    date_key = f"{year:04d}-{month:02d}-{day:02d}"
    return (day, month, year), date_key


def validate_temperature(temp: float) -> float:
    """
    Validates a temperature value.

    Args:
        temp: The temperature to validate.

    Returns:
        The validated temperature.
    """
    if not isinstance(temp, (int, float)):
        raise TypeError("Temperature must be a number.")
    if not -100 < temp < 100:
        raise ValueError("Temperature must be between -100 and 100 degrees.")
    return temp
