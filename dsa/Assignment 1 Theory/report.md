# Weather Record ADT Analysis Report

This report provides a detailed analysis of the Weather Record Abstract Data Type (ADT) implemented in the `WeatherSystem` C++ project. It covers the ADT's description, memory representation, sparse data handling, and complexity analysis.

## 1. Description of the Weather Record ADT

The Weather Record ADT, implemented as the `WeatherSystem` class, is designed to store and manage a large dataset of historical temperature records. The ADT organizes data by year and city, providing an interface to load, access, modify, and traverse this two-dimensional data structure.

### a. Logical Structure

Logically, the ADT represents a table where:
- **Rows** correspond to years, spanning from 1948 to 2023 (a total of 76 years).
- **Columns** correspond to 50 specific cities.
- Each **Cell** `(year, city)` holds a single `double` value representing the temperature in Celsius.

### b. Key Operations

The ADT's public interface, defined in `WeatherSystem.h`, supports the following primary operations:

- **`WeatherSystem()`**: Constructor that initializes the data structure.
- **`~WeatherSystem()`**: Destructor that deallocates all dynamically allocated memory to prevent leaks.
- **`loadFromCSV(string path)`**: Populates the ADT with data from a given CSV file.
- **`insertData(int year, string city, double temperature)`**: Inserts or updates the temperature for a given year and city.
- **`retrieveData(int year, string city)`**: Retrieves the temperature for a given year and city.
- **`deleteData(int year, string city)`**: Removes a record by setting its value to the sentinel for missing data.
- **`printRowMajor()`**: Traverses and prints the data in row-major order.
- **`printColumnMajor()`**: Traverses and prints the data in column-major order.

## 2. Data Structure and Memory Representation

The core of the ADT is a `double** weatherData` pointer, which is used to create a 2D dynamic array.

### a. Memory Allocation

The system allocates a 2D array of size `NUM_YEARS` x `NUM_CITIES` (76x50). This allocation is performed in the `WeatherSystem` constructor.

### b. Memory Representation Strategy: Row-Major

The ADT employs a **row-major** memory representation. This is evident from the constructor's implementation in `WeatherSystem.cpp`:

```cpp
// From WeatherSystem.cpp
weatherData = new double*[NUM_YEARS];
for (int i = 0; i < NUM_YEARS; ++i) {
    weatherData[i] = new double[NUM_CITIES];
    // ... initialization ...
}
```

First, an array of `NUM_YEARS` pointers is allocated. Then, for each of these pointers, a contiguous block of `NUM_CITIES` doubles is allocated. In memory, each row is a continuous block, but the rows themselves may not be contiguous with each other.

This strategy makes row-wise traversal highly efficient and cache-friendly, as demonstrated by the `printRowMajor` function. Accessing elements `[i][0], [i][1], [i][2], ...` involves sequential memory access.

## 3. Approach to Handling Sparse Data

The dataset is known to be sparse, with `generate_data.py` intentionally omitting approximately 20% of the possible data points.

The ADT handles this sparsity by using a **dense matrix combined with a sentinel value**.

- **Dense Matrix**: The full `76 * 50` matrix is allocated in memory, regardless of how many data points are actually present.
- **Sentinel Value**: The value `-999.0` is used to represent missing or non-existent data records. The `WeatherSystem` constructor pre-fills the entire `weatherData` array with this value before any real data is loaded. Operations like `retrieveData` can check for this value to determine if a record exists.

This approach trades space efficiency for simplicity and constant-time access. While it consumes more memory than a truly sparse data structure (like a list of lists or a hash map), it makes data retrieval and updates computationally faster once the indices are known.

## 4. Time and Space Complexity Analysis

The choice of data structures directly impacts the system's performance.

### a. Space Complexity

The space complexity is **O(R * C)**, where `R` is the number of years and `C` is the number of cities. The system allocates the entire 2D array, so memory usage is proportional to the total possible data points, not the number of actual data points.

### b. Time Complexity

The `README.md` file suggests that city lookups are O(C), but analysis of the source code reveals a more efficient implementation.

The ADT uses a `std::map<string, int> cityIndexMap` to map city names to their corresponding column indices in the `weatherData` array.

- **`insertData`, `retrieveData`, `deleteData`**: The time complexity for these key operations is **O(log C)**.
  - The year is mapped to a row index with an O(1) arithmetic operation (`year - START_YEAR`).
  - The city name is mapped to a column index using the `cityIndexMap`, which is a balanced binary search tree operation with a time complexity of **O(log C)**.
  - Accessing or updating the `weatherData[row][col]` cell is an O(1) operation thereafter.

- **`loadFromCSV(path)`**: The time complexity is **O(N * log C)**, where `N` is the number of records (lines) in the CSV file and `C` is the number of cities. For each line, the system performs one map lookup.

- **`printRowMajor()` & `printColumnMajor()`**: The time complexity for full traversal is **O(R * C)**, as both methods must visit every cell in the 2D array. However, `printRowMajor` will typically be faster in practice due to better CPU cache utilization.
