# Project Todo List: Weather Data Storage System

This document outlines a detailed plan for implementing the "Weather Data Storage System" project, breaking down the requirements from `project.md` into actionable tasks.

## Phase 1: Project Setup and Core Structure [COMPLETED]

### Task 1.1: Initialize Project Repository [COMPLETED]

- [x] Initialize the project with the specified directory layout.
  - [x] Create `weather-data-system/` root directory.
  - [x] Create `src/`, `tests/`, `data/`, `docs/` subdirectories.
  - [x] Create `src/weather/` and its subdirectories: `models/`, `storage/`, `indexing/`, `utils/`.
  - [x] Create empty `__init__.py` files in all package directories (`src/weather/`, `src/weather/models/`, etc.).
  - [x] Create placeholder files as per `project.md` (e.g., `src/weather/models/record.py`, `tests/test_record.py`, `docs/report.md`).
  - [x] Create `README.md`, `pyproject.toml`, and `.gitignore` files.

### Task 1.2: Define Data Files [COMPLETED]

- [x] Create `data/sample_cities.txt` with sample city names.
- [x] Create `data/sample_years.txt` with sample years.
- [x] Create `data/sample_records.csv` with sample weather data (Date, City, Temperature).

## Phase 2: Weather Record ADT Implementation [COMPLETED]

### Task 2.1: `src/weather/utils/validation.py` [COMPLETED]

- [x] Implement `normalize_date(date: str|tuple) -> tuple(day, month, year)`:
  - [x] Handle date strings (e.g., "YYYY-MM-DD") and tuples (day, month, year).
  - [x] Extract year from the date.
  - [x] Return a consistent tuple format and a `date_key` string.
- [x] Implement `validate_temperature(temp: float) -> float`:
  - [x] Add type and range checks for temperature values.

### Task 2.2: `src/weather/models/record.py` - `WeatherRecord` Class [COMPLETED]

- [x] Define `class WeatherRecord`:
  - [x] Constructor `__init__(self, date, city, temperature)`:
    - [x] Use `normalize_date` and `validate_temperature` for input validation.
    - [x] Store `date`, `city`, `temperature` as attributes.
  - [x] Implement `to_tuple(self) -> tuple`: returns `(date, city, temperature)`.
  - [x] Implement `from_dict(cls, d: dict) -> WeatherRecord`: convenience constructor for bulk-loading.

### Task 2.3: `tests/test_record.py` [COMPLETED]

- [x] Write unit tests for `WeatherRecord` construction and normalization.
  - [x] Test valid date formats (string, tuple).
  - [x] Test valid temperature ranges.
  - [x] Test `to_tuple` method.
  - [x] Test `from_dict` method.
  - [x] Test edge cases and invalid inputs (e.g., invalid date, out-of-range temperature).

## Phase 3: Storage Backend - Abstract Base and Dense Implementation [COMPLETED]

### Task 3.1: `src/weather/storage/base.py` - `BaseStorage` Protocol [COMPLETED]

- [x] Define `class BaseStorage` (or an abstract base class using `abc` module):
  - [x] Declare abstract methods:
    - [x] `populateArray(records: list[WeatherRecord]) -> int`
    - [x] `insert(record: WeatherRecord) -> bool`
    - [x] `delete(city: str, date: str|tuple) -> bool`
    - [x] `retrieve(city: str, year: int) -> list|dict`
    - [x] `rowMajorAccess() -> iterator`
    - [x] `columnMajorAccess() -> iterator`
    - [x] `handleSparseData(mode: str) -> None`
    - [x] `analyzeComplexity() -> dict`

### Task 3.2: `src/weather/indexing/mapping.py` [COMPLETED]

- [x] Implement `build_year_map(years: list[int]) -> dict[int,int]` and inverse list.
- [x] Implement `build_city_map(cities: list[str]) -> dict[str,int]` and inverse list.
- [x] Implement `get_indices(year, city) -> tuple[int,int]` with validation against unknown keys.
- [x] Implement `construct_mappings(years, cities)` to return all necessary mapping structures.

### Task 3.3: `src/weather/storage/dense.py` - `DenseStorage` Class [COMPLETED]

- [x] Define `class DenseStorage(BaseStorage)`:
  - [x] Constructor `__init__(self, years: list[int], cities: list[str])`:
    - [x] Initialize `matrix` as `list[list[float|None]]` of size `len(years) x len(cities)`, filled with `None` (sentinel).
    - [x] Use `mapping.py` to build `years_map`, `cities_map`, and their inverse lists.
  - [x] Implement `insert(record: WeatherRecord) -> bool`:
    - [x] Map city and `record.date.year` to indices.
    - [x] Set cell to `record.temperature`, overwriting if existing.
  - [x] Implement `delete(city: str, date: str|tuple) -> bool`:
    - [x] Map city and `date.year` to indices.
    - [x] Set the mapped cell back to `None`.
  - [x] Implement `retrieve(city: str, year: int) -> list|dict`:
    - [x] Return temperature data for the given city and year, using `None` for absent data. (Clarify if it should return a list of daily temperatures or just the yearly average/summary for the city). _Assumption: Return a list of daily temperatures for the given city and year, or a dictionary mapping dates to temperatures._
  - [x] Implement `rowMajorAccess(self) -> iterator`:
    - [x] Yield tuples `(year, city, date, temperature|None, present_flag)` iterating over rows (years) then columns (cities).
  - [x] Implement `columnMajorAccess(self) -> iterator`:
    - [x] Yield tuples `(year, city, date, temperature|None, present_flag)` iterating over columns (cities) then rows (years).
  - [x] Implement `handleSparseData(mode: str) -> None`: (For DenseStorage, this might be a no-op or raise an error if an invalid mode is passed, as it's always dense).
  - [x] Implement `analyzeComplexity() -> dict`:
    - [x] Report `O(1)` for insert/delete/retrieve by index mapping.
    - [x] Report `O(Y * C)` for space.
    - [x] Report `O(Y * C)` for traversals.

### Task 3.4: `tests/test_storage_dense.py` [COMPLETED]

- [x] Write unit tests for `DenseStorage`:
  - [x] Test `insert` functionality (new records, overwriting).
  - [x] Test `delete` functionality.
  - [x] Test `retrieve` functionality (existing data, missing data).
  - [x] Test `rowMajorAccess` and `columnMajorAccess` for correct order and content (including sentinels).
  - [x] Test `analyzeComplexity` output.
  - [x] Test edge cases (e.g., inserting/deleting non-existent city/year).

## Phase 4: Sparse Storage Implementation [COMPLETED]

### Task 4.1: `src/weather/storage/sparse.py` - `SparseStorage` Class [COMPLETED]

- [x] Define `class SparseStorage(BaseStorage)`:
  - [x] Constructor `__init__(self, years: list[int], cities: list[str])`:
    - [x] Initialize `store` as `dict[(row, col, date_key) -> float]`.
    - [x] Use `mapping.py` to build `years_map`, `cities_map`, and their inverse lists (same as DenseStorage).
  - [x] Implement `insert(record: WeatherRecord) -> bool`:
    - [x] Operate on the `store` dictionary.
  - [x] Implement `delete(city: str, date: str|tuple) -> bool`:
    - [x] Remove entry from `store`.
  - [x] Implement `retrieve(city: str, year: int) -> list|dict`:
    - [x] Fetch temperature data from `store`, returning `None` for missing.
  - [x] Implement `rowMajorAccess(self) -> iterator`:
    - [x] Traverse the full logical grid (years x cities) or only present entries based on a flag (for fair comparison). _Assumption: Initially, traverse the full logical grid, yielding `None` for missing entries to match `DenseStorage` API._
  - [x] Implement `columnMajorAccess(self) -> iterator`:
    - [x] Similar to `rowMajorAccess`.
  - [x] Implement `handleSparseData(mode: str) -> None`: (For SparseStorage, this might be a no-op or raise an error if an invalid mode is passed, as it's always sparse).
  - [x] Implement `analyzeComplexity() -> dict`:
    - [x] Document `O(1)` average for map operations (insert, delete, retrieve).
    - [x] Document `O(N)` space for `N` records.
    - [x] Document `O(Y * C)` for traversals over the logical grid.

### Task 4.2: `tests/test_storage_sparse.py` [COMPLETED]

- [x] Write unit tests for `SparseStorage`:
  - [x] Test `insert`, `delete`, `retrieve` functionality.
  - [x] Test `rowMajorAccess` and `columnMajorAccess` for correct order and content (including missing entries).
  - [x] Ensure API behavior parity with `DenseStorage` where applicable.
  - [x] Test `analyzeComplexity` output.

## Phase 5: ADT Facade and Access Utilities [COMPLETED]

### Task 5.1: `src/weather/models/record.py` - `WeatherRecordADT` Class [COMPLETED]

- [x] Define `class WeatherRecordADT`:
  - [x] Constructor `__init__(self, storage_backend: BaseStorage)`:
    - [x] Store the `storage_backend` instance.
  - [x] Implement `insert(record: WeatherRecord) -> bool`:
    - [x] Delegate to `storage_backend.insert()`.
  - [x] Implement `delete(city: str, date: str|tuple) -> bool`:
    - [x] Delegate to `storage_backend.delete()`.
  - [x] Implement `retrieve(city: str, year: int) -> list|dict`:
    - [x] Delegate to `storage_backend.retrieve()`.

### Task 5.2: `src/weather/access.py` [COMPLETED]

- [x] Implement `row_major_iter(storage: BaseStorage, include_missing=True) -> iterator`:
  - [x] Call `storage.rowMajorAccess()` and handle `include_missing` flag if needed (storage backend should ideally handle this).
- [x] Implement `column_major_iter(storage: BaseStorage, include_missing=True) -> iterator`:
  - [x] Call `storage.columnMajorAccess()` and handle `include_missing` flag if needed.

### Task 5.3: `tests/test_access_traversal.py` [COMPLETED]

- [x] Write unit tests for `access.py` traversal utilities:
  - [x] Assert ordering differences between row-major and column-major.
  - [x] Assert coverage equality (all cells visited) for both traversals.
  - [x] Test with both `DenseStorage` and `SparseStorage` instances.

### Task 5.4: `tests/test_api_contract.py` [COMPLETED]

- [x] Write tests to ensure `WeatherRecordADT` methods call the storage backend correctly.
- [x] Verify that all required method signatures are satisfied across `WeatherRecordADT` and `BaseStorage` implementations.

## Phase 6: Complexity Analysis and CLI [COMPLETED]

### Task 6.1: `src/weather/complexity.py` [COMPLETED]

- [x] Implement `complexity_summary(mode: str, Y: int, C: int, N: int) -> dict`:
  - [x] Return a dictionary with time and space complexity for insert, delete, retrieve, and traversals based on the `mode` (dense/sparse) and input parameters (Y=years, C=cities, N=records).

### Task 6.2: `src/weather/cli.py` [COMPLETED]

- [x] Implement a minimal command-line interface:
  - [x] Use `argparse` or similar for command-line arguments.
  - [x] Commands: `add-record`, `delete-record`, `retrieve-year`, `traverse-row`, `traverse-col`, `mode-sparse`, `mode-dense`.
  - [x] Wire ADT calls to showcase required features.
  - [x] Allow switching between dense and sparse storage modes.
  - [x] Display complexity analysis using `analyzeComplexity`.

## Phase 7: Documentation and Final Review [COMPLETED]

### Task 7.1: `docs/report.md` [COMPLETED]

- [x] Complete `docs/report.md` with detailed sections:
  - [x] **Introduction:** Problem, objectives, assumptions, constraints.
  - [x] **ADT Design:** Describe `WeatherRecord` and `WeatherRecordADT` with rationale.
  - [x] **Data Storage:** Explain 2D array layout, sentinel choice, and sparse alternative.
  - [x] **Access Patterns:** Compare row-major vs. column-major traversals.
  - [x] **Sparse Handling:** Discuss trade-offs and preferences for dense vs. sparse.
  - [x] **Complexity Analysis:** Include measured and reasoned complexity notes from `complexity.py` and `analyzeComplexity` methods.
  - [x] **Testing:** Summarize test matrix and key results.
  - [x] **Conclusion:** Alignment with assignment outcomes and lessons learned.

### Task 7.2: Code Review and Refinement [COMPLETED]

- [x] Review all code for adherence to Python best practices, readability, and maintainability.
- [x] Ensure consistent naming conventions and code style.
- [x] Add necessary comments for complex logic (sparingly).
- [x] Verify all requirements from `project.md` are met.

### Task 7.3: Final Testing [COMPLETED]

- [x] Run all unit tests to ensure full coverage and no regressions.
- [x] Perform integration tests using the CLI to verify end-to-end functionality.

## Assumptions and Clarifications Needed:

- **`retrieve(city, year)` return type:** Clarify if it should return a list of daily temperatures for the given city and year, or a dictionary mapping dates to temperatures, or a single aggregated value. _Initial assumption: Return a list of daily temperatures for the given city and year, or a dictionary mapping dates to temperatures._
- **`rowMajorAccess` and `columnMajorAccess` in `SparseStorage`:** Clarify if they should traverse the full logical grid (Y x C) yielding `None` for missing, or only yield present entries. _Initial assumption: Traverse the full logical grid, yielding `None` for missing entries to match `DenseStorage` API for fair comparison._
- **`handleSparseData` in `DenseStorage` and `SparseStorage`:** Clarify expected behavior if a mode switch is attempted on a storage type that doesn't support it (e.g., calling `handleSparseData('sparse')` on `DenseStorage`). _Initial assumption: For `DenseStorage` and `SparseStorage`, this method will either be a no-op or raise an error if an invalid mode is passed, as they are inherently one type._