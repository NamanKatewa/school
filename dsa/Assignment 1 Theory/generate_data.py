import datetime
import random
import os

script_dir = os.path.dirname(__file__)
data_dir = os.path.join(script_dir, "data")

cities_path = os.path.join(data_dir, "sample_cities.txt")
years_path = os.path.join(data_dir, "sample_years.txt")
records_path = os.path.join(data_dir, "sample_records.csv")

with open(cities_path, 'r') as f:
    cities = [line.strip() for line in f if line.strip()]

with open(years_path, 'r') as f:
    years = [int(line.strip()) for line in f if line.strip()]

with open(records_path, 'w') as f:
    f.write("Date,City,Temperature\n")
    for year in years:
        for city in cities:
            city_base_temp = 10 + random.random() * 15

            start_date = datetime.date(year, 1, 1)
            end_date = datetime.date(year, 12, 31)
            delta = datetime.timedelta(days=1)
            current_date = start_date
            while current_date <= end_date:
                day_of_year = current_date.timetuple().tm_yday

                seasonal_offset = 15 * (1 - (day_of_year - 180)**2 / 180**2) * (0.8 + random.random() * 0.4)

                daily_random = (random.random() * 12 - 6)

                anomaly = 0
                if random.random() < 0.02:
                    anomaly = (random.random() * 20 - 10)

                temperature = city_base_temp + seasonal_offset + daily_random + anomaly

                f.write(f"{current_date.strftime('%Y-%m-%d')},{city},{temperature:.1f}\n")
                current_date += delta

print("Generated random sample_records.csv")