import argparse

from src.weather.adt import WeatherRecordADT
from src.weather.models.record import WeatherRecord
from src.weather.storage.dense import DenseStorage
from src.weather.storage.sparse import SparseStorage
from src.weather.complexity import complexity_summary
from src.weather.access import row_major_iter, column_major_iter


def main():
    parser = argparse.ArgumentParser(description="Weather Data Storage System")
    parser.add_argument("--mode", choices=["dense", "sparse"], default="dense", help="Storage mode")

    # Add subparsers for different commands
    subparsers = parser.add_subparsers(dest="command")

    # Add record command
    add_parser = subparsers.add_parser("add-record", help="Add a weather record")
    add_parser.add_argument("date", help="Date in YYYY-MM-DD format")
    add_parser.add_argument("city", help="City name")
    add_parser.add_argument("temp", type=float, help="Temperature")

    # Delete record command
    delete_parser = subparsers.add_parser("delete-record", help="Delete a weather record")
    delete_parser.add_argument("date", help="Date in YYYY-MM-DD format")
    delete_parser.add_argument("city", help="City name")

    # Retrieve year command
    retrieve_parser = subparsers.add_parser("retrieve-year", help="Retrieve weather data for a year")
    retrieve_parser.add_argument("year", type=int, help="Year")
    retrieve_parser.add_argument("city", help="City name")

    # Traverse row command
    subparsers.add_parser("traverse-row", help="Traverse data in row-major order")

    # Traverse col command
    subparsers.add_parser("traverse-col", help="Traverse data in column-major order")

    # Complexity command
    complexity_parser = subparsers.add_parser("analyze-complexity", help="Analyze complexity")
    complexity_parser.add_argument("--Y", type=int, default=10, help="Number of years")
    complexity_parser.add_argument("--C", type=int, default=10, help="Number of cities")
    complexity_parser.add_argument("--N", type=int, default=50, help="Number of records")

    args = parser.parse_args()

    # Read years and cities from files
    with open("data/sample_years.txt", "r") as f:
        years = [int(year) for year in f.read().splitlines()]
    with open("data/sample_cities.txt", "r") as f:
        cities = f.read().splitlines()

    # Initialize storage and ADT
    if args.mode == "dense":
        storage = DenseStorage(years, cities)
    else:
        storage = SparseStorage(years, cities)

    adt = WeatherRecordADT(storage)

    if args.command == "add-record":
        record = WeatherRecord(args.date, args.city, args.temp)
        if adt.insert(record):
            print("Record added successfully.")
        else:
            print("Failed to add record.")

    elif args.command == "delete-record":
        if adt.delete(args.city, args.date):
            print("Record deleted successfully.")
        else:
            print("Failed to delete record.")

    elif args.command == "retrieve-year":
        temp = adt.retrieve(args.city, args.year)
        if temp is not None:
            print(f"Temperature for {args.city} in {args.year}: {temp}")
        else:
            print(f"No data found for {args.city} in {args.year}")

    elif args.command == "traverse-row":
        for year, city, date, temp, present in row_major_iter(storage):
            if present:
                print(f"{date} {city}: {temp}")

    elif args.command == "traverse-col":
        for year, city, date, temp, present in column_major_iter(storage):
            if present:
                print(f"{date} {city}: {temp}")

    elif args.command == "analyze-complexity":
        summary = complexity_summary(args.mode, args.Y, args.C, args.N)
        print(f"Complexity analysis for {args.mode} mode:")
        for key, value in summary.items():
            print(f"  {key}: {value}")


if __name__ == "__main__":
    main()
