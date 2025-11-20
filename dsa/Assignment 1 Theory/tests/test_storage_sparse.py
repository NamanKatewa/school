import unittest

from src.weather.models.record import WeatherRecord
from src.weather.storage.sparse import SparseStorage


class TestSparseStorage(unittest.TestCase):
    def setUp(self):
        self.years = [2022, 2023, 2024]
        self.cities = ["London", "New York", "Tokyo"]
        self.storage = SparseStorage(self.years, self.cities)

    def test_insert_and_retrieve(self):
        record = WeatherRecord("2023-01-01", "New York", 10.0)
        self.assertTrue(self.storage.insert(record))
        self.assertEqual(self.storage.retrieve("New York", 2023), 10.0)

    def test_insert_overwrite(self):
        record1 = WeatherRecord("2023-01-01", "New York", 10.0)
        self.storage.insert(record1)
        record2 = WeatherRecord("2023-01-01", "New York", 12.0)
        self.assertTrue(self.storage.insert(record2))
        self.assertEqual(self.storage.retrieve("New York", 2023), 12.0)

    def test_delete(self):
        record = WeatherRecord("2023-01-01", "New York", 10.0)
        self.storage.insert(record)
        self.assertTrue(self.storage.delete("New York", "2023-01-01"))
        self.assertIsNone(self.storage.retrieve("New York", 2023))

    def test_retrieve_non_existent(self):
        self.assertIsNone(self.storage.retrieve("Paris", 2023))

    def test_row_major_access(self):
        record1 = WeatherRecord("2022-01-01", "London", 5.0)
        record2 = WeatherRecord("2023-01-01", "New York", 10.0)
        self.storage.insert(record1)
        self.storage.insert(record2)

        expected_order = [
            (2022, "London"),
            (2022, "New York"),
            (2022, "Tokyo"),
            (2023, "London"),
            (2023, "New York"),
            (2023, "Tokyo"),
            (2024, "London"),
            (2024, "New York"),
            (2024, "Tokyo"),
        ]

        access_order = [
            (year, city) for year, city, _, _, _ in self.storage.row_major_access()
        ]
        self.assertEqual(access_order, expected_order)

    def test_column_major_access(self):
        record1 = WeatherRecord("2022-01-01", "London", 5.0)
        record2 = WeatherRecord("2023-01-01", "New York", 10.0)
        self.storage.insert(record1)
        self.storage.insert(record2)

        expected_order = [
            (2022, "London"),
            (2023, "London"),
            (2024, "London"),
            (2022, "New York"),
            (2023, "New York"),
            (2024, "New York"),
            (2022, "Tokyo"),
            (2023, "Tokyo"),
            (2024, "Tokyo"),
        ]

        access_order = [
            (year, city)
            for year, city, _, _, _ in self.storage.column_major_access()
        ]
        self.assertEqual(access_order, expected_order)

    def test_analyze_complexity(self):
        complexity = self.storage.analyze_complexity()
        self.assertEqual(complexity["insert"], "O(1)")
        self.assertEqual(complexity["delete"], "O(1)")
        self.assertEqual(complexity["retrieve"], "O(1)")
        self.assertEqual(complexity["space"], "O(N)")
        self.assertEqual(complexity["row_major_access"], "O(Y * C)")
        self.assertEqual(complexity["column_major_access"], "O(Y * C)")


if __name__ == "__main__":
    unittest.main()
