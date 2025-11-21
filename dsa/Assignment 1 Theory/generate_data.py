import csv
import random


FILENAME = "data.csv"
START_YEAR = 1950
END_YEAR = 2025


CHANCE_OF_MISSING_DATA = 0.20


CITIES = [
    "New Delhi", "Mumbai", "Chennai", "Kolkata", "Bengaluru", "Hyderabad", 
    "Pune", "Ahmedabad", "Jaipur", "Surat", "Lucknow", "Kanpur", "Nagpur", 
    "Indore", "Thane", "Bhopal", "Visakhapatnam", "Patna", "Vadodara", 
    "Ghaziabad", "Ludhiana", "Agra", "Nashik", "Ranchi", "Faridabad",
    "Meerut", "Rajkot", "Kalyan-Dombivli", "Vasai-Virar", "Varanasi",
    "Srinagar", "Aurangabad", "Dhanbad", "Amritsar", "Navi Mumbai",
    "Prayagraj", "Howrah", "Gwalior", "Jabalpur", "Coimbatore",
    "Vijayawada", "Jodhpur", "Madurai", "Raipur", "Kota",
    "Guwahati", "Chandigarh", "Solapur", "Hubli-Dharwad", "Mysuru"
]


def generate_dataset():
    num_cities = len(CITIES)
    
    print(f"Generating dataset from {START_YEAR} to {END_YEAR} for {num_cities} cities...")
    
    total_cells = (END_YEAR - START_YEAR + 1) * num_cities
    filled_cells = 0
    
    with open(FILENAME, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["Year", "City", "Temperature_C"])
        
        for year in range(START_YEAR, END_YEAR + 1):
            for city in CITIES:
                
                if random.random() > CHANCE_OF_MISSING_DATA:
                    
                    if city == "Srinagar":
                        temp = round(random.uniform(-5.0, 30.0), 2)
                        
                    elif city in ["Bengaluru", "Pune", "Mysuru", "Nashik", "Coimbatore", "Hubli-Dharwad"]:
                        temp = round(random.uniform(12.0, 35.0), 2)
                        
                    elif city in ["Mumbai", "Chennai", "Kolkata", "Thane", "Visakhapatnam", "Surat", "Navi Mumbai", "Kalyan-Dombivli", "Vasai-Virar", "Howrah"]:
                        temp = round(random.uniform(20.0, 38.0), 2)
                        
                    else:
                        temp = round(random.uniform(4.0, 47.0), 2)

                    writer.writerow([year, city, temp])
                    filled_cells += 1


    print(f"Done! File '{FILENAME}' created.")
    print(f"--- Statistics ---")
    print(f"Total Potential Entries: {total_cells}")
    print(f"Actual Recorded Entries: {filled_cells}")
    print(f"Sparsity: {((total_cells - filled_cells) / total_cells) * 100:.2f}% empty")


if __name__ == "__main__":
    generate_dataset()
