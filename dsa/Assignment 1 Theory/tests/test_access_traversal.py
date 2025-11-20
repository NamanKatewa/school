import unittest

from src.weather.access import row_major_iter, column_major_iter
from src.weather.models.record import WeatherRecord
from src.weather.storage.dense import DenseStorage
from src.weather.storage.sparse import SparseStorage


class TestAccessTraversal(unittest.TestCase):
    def setUp(self):
        self.years = [2022, 2023]
        self.cities = ["London", "New York"]
        self.dense_storage = DenseStorage(self.years, self.cities)
        self.sparse_storage = SparseStorage(self.years, self.cities)

        self.record1 = WeatherRecord("2022-01-01", "London", 5.0)
        self.record2 = WeatherRecord("2023-01-01", "New York", 10.0)

        self.dense_storage.insert(self.record1)
        self.dense_storage.insert(self.record2)
        self.sparse_storage.insert(self.record1)
        self.sparse_storage.insert(self.record2)

    def test_row_major_iter_dense(self):
        expected_order = [(2022, "London"), (2022, "New York"), (2023, "London"), (2023, "New York")]
        access_order = [(year, city) for year, city, _, _, _ in row_major_iter(self.dense_storage)]
        self.assertEqual(access_order, expected_order)

    def test_column_major_iter_dense(self):
        expected_order = [(2022, "London"), (2023, "London"), (2022, "New York"), (2023, "New York")]
        access_order = [(year, city) for year, city, _, _, _ in column_major_iter(self.dense_storage)]
        self.assertEqual(access_order, expected_order)

    def test_row_major_iter_sparse(self):
        expected_order = [(2022, "London"), (2022, "New York"), (2023, "London"), (2023, "New York")]
        access_order = [(year, city) for year, city, _, _, _ in row_major_iter(self.sparse_storage)]
        self.assertEqual(access_order, expected_order)

    def test_column_major_iter_sparse(self):
        expected_order = [(2022, "London"), (2023, "London"), (2022, "New York"), (2023, "New York")]
        access_order = [(year, city) for year, city, _, _, _ in column_major_iter(self.sparse_storage)]
        self.assertEqual(access_order, expected_order)

    def test_iter_content_dense(self):
        row_items = list(row_major_iter(self.dense_storage))
        col_items = list(column_major_iter(self.dense_storage))
        self.assertEqual(len(row_items), 4)
        self.assertEqual(len(col_items), 4)
        self.assertIn((2022, "London", "2022-01-01", 5.0, True), row_items)
        self.assertIn((2023, "New York", "2023-01-01", 10.0, True), row_items)
        self.assertIn((2022, "New York", "2022-01-01", None, False), row_items)

    def test_iter_content_sparse(self):
        row_items = list(row_major_iter(self.sparse_storage))
        col_items = list(column_major_iter(self.sparse_storage))
        self.assertEqual(len(row_items), 4)
        self.assertEqual(len(col_items), 4)
        self.assertIn((2022, "London", "2022-01-01", 5.0, True), row_items)
        self.assertIn((2023, "New York", "2023-01-01", 10.0, True), row_items)
        self.assertIn((2022, "New York", "2022-01-01", None, False), row_items)

if __name__ == "__main__":
    unittest.main()
