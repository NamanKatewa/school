from typing import Dict, List, Tuple


def build_year_map(years: List[int]) -> Tuple[Dict[int, int], List[int]]:
    """
    Builds a mapping from year to index and an inverse mapping from index to year.

    Args:
        years: A list of years.

    Returns:
        A tuple containing the year-to-index map and the index-to-year list.
    """
    year_map = {year: i for i, year in enumerate(years)}
    year_map_inv = years
    return year_map, year_map_inv


def build_city_map(cities: List[str]) -> Tuple[Dict[str, int], List[str]]:
    """
    Builds a mapping from city to index and an inverse mapping from index to city.

    Args:
        cities: A list of cities.

    Returns:
        A tuple containing the city-to-index map and the index-to-city list.
    """
    city_map = {city: i for i, city in enumerate(cities)}
    city_map_inv = cities
    return city_map, city_map_inv


def get_indices(
    year_map: Dict[int, int], city_map: Dict[str, int], year: int, city: str
) -> Tuple[int, int]:
    """
    Gets the indices for a given year and city.

    Args:
        year_map: The year-to-index map.
        city_map: The city-to-index map.
        year: The year.
        city: The city.

    Returns:
        A tuple containing the year and city indices.

    Raises:
        KeyError: If the year or city is not found in the maps.
    """
    try:
        year_index = year_map[year]
        city_index = city_map[city]
        return year_index, city_index
    except KeyError as e:
        raise KeyError(f"Unknown key: {e}") from e


def construct_mappings(
    years: List[int], cities: List[str]
) -> Tuple[Dict[int, int], List[int], Dict[str, int], List[str]]:
    """
    Constructs all necessary mapping structures.

    Args:
        years: A list of years.
        cities: A list of cities.

    Returns:
        A tuple containing the year map, inverse year map, city map, and inverse city map.
    """
    year_map, year_map_inv = build_year_map(years)
    city_map, city_map_inv = build_city_map(cities)
    return year_map, year_map_inv, city_map, city_map_inv
