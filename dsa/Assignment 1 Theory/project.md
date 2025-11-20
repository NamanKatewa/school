# Weather Data Storage System — Python Project Structure

## Summary

This project stores and manages temperature data organized by city and date using a 2D array structure for years × cities, exposes row-major and column-major access, handles sparse data, and documents time and space complexity for key operations.
It implements a Weather Record ADT and a Data Storage class with the exact attributes and methods specified in the assignment.

## Requirements alignment

- Weather Record ADT with attributes Date, City, Temperature, and system-level methods insert, delete, and retrieve(city, year).
- Data Storage class with a 2D array, and methods populateArray, rowMajorAccess, columnMajorAccess, handleSparseData, and analyzeComplexity.
- Support complete and sparse datasets while enabling efficient insertion, retrieval, and analysis over time.

## Directory layout

```
weather-data-system/
├─ src/
│  └─ weather/
│     ├─ __init__.py
│     ├─ models/
│     │  ├─ __init__.py
│     │  └─ record.py
│     ├─ storage/
│     │  ├─ __init__.py
│     │  ├─ base.py
│     │  ├─ dense.py
│     │  └─ sparse.py
│     ├─ indexing/
│     │  ├─ __init__.py
│     │  └─ mapping.py
│     ├─ access.py
│     ├─ complexity.py
│     ├─ utils/
│     │  ├─ __init__.py
│     │  └─ validation.py
│     └─ cli.py
├─ tests/
│  ├─ test_record.py
│  ├─ test_storage_dense.py
│  ├─ test_storage_sparse.py
│  ├─ test_access_traversal.py
│  └─ test_api_contract.py
├─ data/
│  ├─ sample_cities.txt
│  ├─ sample_years.txt
│  └─ sample_records.csv
├─ docs/
│  └─ report.md
├─ README.md
├─ pyproject.toml
└─ .gitignore
```

This structure separates ADT modeling, storage backends, index mapping, access traversal, complexity documentation, CLI, tests, and report to match the assignment deliverables.

## File responsibilities and APIs

### src/weather/models/record.py

- Defines WeatherRecord with attributes date, city, temperature and validation for types and ranges per assignment attributes.
- Provides WeatherRecordADT facade methods required at the system interface: insert(record), delete(city, date), retrieve(city, year), delegating to the configured storage backend.
- Core entities:
  - class WeatherRecord: constructor accepts date as string or tuple/day-month-year, city as string, temperature as float, plus to_tuple() helper.
  - class WeatherRecordADT: init with a storage backend; methods insert(record), delete(city, date), retrieve(city, year) that translate ADT calls to storage operations.

### src/weather/storage/base.py

- Declares abstract protocol for storage backends to guarantee required operations.
- Interface methods:
  - populateArray(records): bulk-load list of WeatherRecord into underlying structure.
  - insert(record): write one record at mapped indices or in sparse map.
  - delete(city, date): remove entry for city on given date.
  - retrieve(city, year): return temperature data for the given city and year.
  - rowMajorAccess(): iterator over rows(years) then columns(cities) yielding present or missing entries.
  - columnMajorAccess(): iterator over columns(cities) then rows(years) yielding present or missing entries.
  - handleSparseData(mode): switch or configure strategy to sentinel dense or sparse representation.
  - analyzeComplexity(): return structured time and space complexity summary for operations in current mode.

### src/weather/storage/dense.py

- Implements a dense 2D array where rows represent years and columns represent cities using a sentinel for missing data.
- Responsibilities:
  - Allocate matrix of size len(years) × len(cities) initialized to None as sentinel.
  - insert: map city and date.year to indices and set cell to temperature, overwriting if existing.
  - delete: set the mapped cell back to sentinel for missing.
  - retrieve: return a year’s sequence for the city or per-date values as required by interface, using sentinel for absent.
  - rowMajorAccess and columnMajorAccess: yield tuples (year, city, date, temperature|None, present_flag).
  - analyzeComplexity: report $$O(1)$$ insert/delete/retrieve by index mapping and $$O(Y \times C)$$ space.

### src/weather/storage/sparse.py

- Implements a sparse representation storing only present entries keyed by (year_index, city_index, date_key).
- Responsibilities:
  - Maintain dict or map for occupied cells and derive missing via absence.
  - insert/delete/retrieve operate on the map with sentinel returned for missing.
  - rowMajorAccess and columnMajorAccess traverse the full logical grid or only present entries based on mode flags for fair comparison.
  - analyzeComplexity: document $$O(1)$$ average map operations and space $$O(N)$$ for N records.

### src/weather/indexing/mapping.py

- Provides bidirectional maps year ↔ row_index and city ↔ col_index to guarantee $$O(1)$$ index resolution.
- Responsibilities:
  - construct_mappings(years, cities): returns dictionaries and reverse lists for consistent indexing.
  - validate_membership(year, city): helper to guard against unknown keys.

### src/weather/access.py

- Centralizes traversal utilities for row-major and column-major to keep storage backends thin.
- Responsibilities:
  - row_major_iter(storage): standardized generator over years then cities, skipping or yielding sentinels per flag.
  - column_major_iter(storage): standardized generator over cities then years, with identical semantics.

### src/weather/complexity.py

- Houses structured complexity reports returned by analyzeComplexity for inclusion in the report.
- Responsibilities:
  - complexity_summary(mode, Y, C, N): returns dict with time and space for insert, delete, retrieve, and traversals.

### src/weather/utils/validation.py

- Input validation and normalization for dates, temperatures, and membership checks.
- Responsibilities:
  - normalize_date(date): ensure date is consistent string or tuple with extracted year.
  - validate_temperature(value): type and range checks as needed.

### src/weather/cli.py

- Minimal command-line interface to demonstrate insertion, deletion, retrieval, and traversals.
- Responsibilities:
  - Commands: add-record, delete-record, retrieve-year, traverse-row, traverse-col, mode-sparse, mode-dense.
  - Wire ADT calls to showcase required features for evaluation.

### tests/ suite

- test_record.py: validates WeatherRecord construction and normalization.
- test_storage_dense.py: covers insert, delete, retrieve, traversals, and sentinel behavior for dense backend.
- test_storage_sparse.py: covers insert, delete, retrieve, and traversal parity with dense semantics for sparse backend.
- test_access_traversal.py: asserts ordering differences and coverage equality between row-major and column-major.
- test_api_contract.py: ensures WeatherRecordADT methods call storage and satisfy assignment method signatures.

### docs/report.md skeleton

- Introduction: problem, objectives, assumptions about years and cities, and constraints.
- ADT design: describe WeatherRecord attributes and ADT interface insert, delete, retrieve with rationale.
- Data storage: 2D array layout rows=years, columns=cities, sentinel choice, and sparse alternative.
- Access patterns: implementation and comparison of row-major vs column-major traversals.
- Sparse handling: sentinel vs sparse matrix representation trade-offs with when to prefer each.
- Complexity analysis: time $$O(1)$$ for indexed ops in dense, $$O(1)$$ average for sparse map ops, space $$O(Y \times C)$$ vs $$O(N)$$, and traversal $$O(Y \times C)$$.
- Testing: summarize test matrix and key results.
- Conclusion: alignment with assignment outcomes and lessons learned.

## Core classes and methods overview

### WeatherRecord (models/record.py)

- Fields: date, city, temperature.
- Methods:
  - to_tuple(): returns (date, city, temperature).
  - from_dict(d): convenience constructor for bulk-loading.

### WeatherRecordADT (models/record.py)

- Methods:
  - insert(record: WeatherRecord) -> bool: validate and forward to storage.
  - delete(city: str, date: str|tuple) -> bool: remove matching record and return success.
  - retrieve(city: str, year: int) -> list|dict: fetch temperature data for specified city and year.

### BaseStorage (storage/base.py)

- Methods:
  - populateArray(records: list[WeatherRecord]) -> int: load count of inserted records.
  - insert(record: WeatherRecord) -> bool.
  - delete(city: str, date: str|tuple) -> bool.
  - retrieve(city: str, year: int) -> list|dict.
  - rowMajorAccess() -> iterator.
  - columnMajorAccess() -> iterator.
  - handleSparseData(mode: str) -> None.
  - analyzeComplexity() -> dict.

### DenseStorage (storage/dense.py)

- Data:
  - matrix: list[list[float|None]] with None sentinel, years_map, cities_map, and reverse lists.
- Methods:
  - insert/delete/retrieve with direct index mapping via maps.
  - rowMajorAccess/columnMajorAccess yielding year, city, date, value, present_flag.
  - analyzeComplexity returning dense-mode time and space detail.

### SparseStorage (storage/sparse.py)

- Data:
  - store: dict[(row, col, date_key) -> float], plus maps identical to dense for consistent API.
- Methods:
  - insert/delete/retrieve on dict with sentinel None for missing when composing sequences.
  - rowMajorAccess/columnMajorAccess traversing logical grid or present entries based on a flag.
  - analyzeComplexity returning sparse-mode time and space detail.

### Mapping utilities (indexing/mapping.py)

- Methods:
  - build_year_map(years: list[int]) -> dict[int,int] and inverse list.
  - build_city_map(cities: list[str]) -> dict[str,int] and inverse list.
  - get_indices(year, city) -> tuple[int,int] with validation.

### Access utilities (access.py)

- Methods:
  - row_major_iter(storage, include_missing=True) -> iterator.
  - column_major_iter(storage, include_missing=True) -> iterator.

### Validation utilities (utils/validation.py)

- Methods:
  - normalize_date(date: str|tuple) -> tuple(day, month, year) and date_key string.
  - validate_temperature(temp: float) -> float.

## Data and indexing assumptions

- Rows represent years and columns represent cities, with lookups ensuring constant-time index mapping.
- Dates must resolve to a year present in the configured years domain, and cities must be in the configured city list.

## Operational complexity summary

- Dense: insert, delete, retrieve are $$O(1)$$ with $$O(Y \times C)$$ space, and traversals are $$O(Y \times C)$$.
- Sparse: map-based insert, delete, retrieve average $$O(1)$$ with $$O(N)$$ space for the number of present records $$N$$, and traversals over the logical grid remain $$O(Y \times C)$$.

## How this earns full marks

- Implements all specified ADT attributes and methods, storage methods, row and column access, sparse handling, and complexity analysis as required.
- Supports a clear report structure mapping code decisions to assignment objectives and evaluation criteria.

## Next steps

- Initialize the repository with this structure, implement DenseStorage first with a None sentinel, then add SparseStorage and ensure identical API behavior.
- Complete docs/report.md with your measured and reasoned complexity notes and traversal comparisons.
