# Weather Data Storage System Report

## Introduction

This report details the design and implementation of a Weather Data Storage System. The system is designed to store and manage temperature data, organized by city and date. It provides functionalities for inserting, deleting, and retrieving weather records, as well as traversing the data in both row-major and column-major orders. The system supports both dense and sparse data storage strategies, and this report analyzes the trade-offs between them.

**Objectives:**

* To implement a `WeatherRecord` ADT to represent weather data.
* To create a data storage system using a 2D array for years and cities.
* To provide row-major and column-major access to the data.
* To handle both dense and sparse datasets efficiently.
* To analyze the time and space complexity of the implemented operations.

**Assumptions:**

* The set of years and cities is fixed and known in advance.
* Each city has at most one temperature reading per day.

**Constraints:**

* The system should be implemented in Python.
* The core data structure for the dense storage should be a 2D array (or a list of lists).

## ADT Design

### `WeatherRecord`

The `WeatherRecord` class is a simple data class that encapsulates a single weather reading. It has the following attributes:

* `date`: A tuple of `(day, month, year)`.
* `city`: The name of the city.
* `temperature`: The temperature in degrees Celsius.

The class includes validation to ensure that the date and temperature values are within valid ranges.

### `WeatherRecordADT`

The `WeatherRecordADT` class acts as a facade for the storage backend. It provides the main interface for interacting with the weather data. Its methods delegate the actual data manipulation to the underlying storage object. This design decouples the application logic from the specific storage implementation, making it easy to switch between different storage strategies (e.g., dense vs. sparse).

The ADT provides the following methods:

* `insert(record)`: Inserts a `WeatherRecord` into the storage.
* `delete(city, date)`: Deletes a record for a given city and date.
* `retrieve(city, year)`: Retrieves the temperature data for a given city and year.

## Data Storage

The system implements two types of storage backends: `DenseStorage` and `SparseStorage`.

### `DenseStorage`

The `DenseStorage` class uses a 2D list (a list of lists) to store the temperature data. The rows of the matrix correspond to years, and the columns correspond to cities. This creates a grid where each cell `(year_index, city_index)` holds the temperature for that specific year and city.

*   **Sentinel Value:** A sentinel value of `None` is used to represent missing data. When a cell in the matrix is `None`, it means that no temperature has been recorded for that year and city.

*   **Indexing:** To efficiently access the data, the storage uses mapping dictionaries to convert year and city names to their corresponding indices in the matrix. This allows for O(1) access to any cell.

### `SparseStorage`

The `SparseStorage` class is designed to be more memory-efficient when the dataset is sparse (i.e., when there are many missing records). Instead of a full 2D matrix, it uses a dictionary to store only the records that are present. The keys of the dictionary are tuples `(year_index, city_index)`, and the values are the temperatures.

## Access Patterns

The system provides two ways to traverse the data: row-major and column-major.

*   **Row-Major Traversal:** This method iterates through the data row by row. In the context of our system, it means iterating through all the cities for a given year, then moving to the next year.

*   **Column-Major Traversal:** This method iterates through the data column by column. This means iterating through all the years for a given city, then moving to the next city.

These traversal methods are implemented as iterators, which makes them memory-efficient, as they don't load the entire dataset into memory at once.

## Sparse Handling

The choice between `DenseStorage` and `SparseStorage` depends on the nature of the dataset.

*   **`DenseStorage`** is suitable for datasets that are mostly dense, meaning that there are records for most year-city combinations. In this case, the overhead of the 2D list is justified, and the access is very fast.

*   **`SparseStorage`** is preferred for datasets with many missing records. It saves a significant amount of memory by only storing the data that exists. The trade-off is a slightly higher overhead for accessing data due to the dictionary lookups, although the average time complexity is still O(1).

## Complexity Analysis

| Operation           | Dense Storage | Sparse Storage | Notes                                                                 |
| ------------------- | ------------- | -------------- | --------------------------------------------------------------------- |
| **Insert**          | O(1)          | O(1)           | Average case for dictionary insertion.                                |
| **Delete**          | O(1)          | O(1)           | Average case for dictionary deletion.                                 |
| **Retrieve**        | O(1)          | O(1)           | Average case for dictionary lookup.                                   |
| **Space**           | O(Y * C)      | O(N)           | Y = years, C = cities, N = number of records.                         |
| **Row-Major Access**  | O(Y * C)      | O(Y * C)       | Iterates through the entire logical grid.                             |
| **Column-Major Access** | O(Y * C)      | O(Y * C)       | Iterates through the entire logical grid.                             |

## Testing

The project includes a comprehensive test suite to ensure the correctness of the implementation. The tests cover:

*   The `WeatherRecord` class and its validation logic.
*   The `DenseStorage` and `SparseStorage` classes, including insertion, deletion, retrieval, and traversal.
*   The API contract to ensure that the ADT correctly delegates calls to the storage backend.
*   The access traversal utilities to verify the correct ordering and content.

## Conclusion

This project successfully implements a flexible and efficient system for storing and managing weather data. The use of an ADT and a pluggable storage backend allows the system to be adapted to different data densities and requirements. The complexity analysis and the choice between dense and sparse storage demonstrate a clear understanding of the trade-offs involved in data structure design.
