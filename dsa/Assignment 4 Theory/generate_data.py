import csv
import random

NETWORK_FILE = "city_network.csv"
TASKS_FILE = "construction_tasks.csv"
NUM_NODES = 20
NUM_ROADS = 40

ZONES = ["Residential", "Commercial", "Industrial", "Park", "Downtown"]
INTERSECTIONS = [
    "Central Plaza", "North Gate", "South Market", "West End", "East Bridge",
    "City Hall", "Tech Park", "Old Town", "River Side", "Green Valley",
    "Metro Station", "Airport Road", "University", "Hospital Zone", "Stadium"
]

def generate_network():
    print(f"Generating City Road Network ({NUM_NODES} nodes)...")

    with open(NETWORK_FILE, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["SourceID", "SourceName", "DestID", "DestName", "Distance_km", "ZoneType"])

        for _ in range(NUM_ROADS):
            src_idx = random.randint(0, len(INTERSECTIONS)-1)
            dest_idx = random.randint(0, len(INTERSECTIONS)-1)

            if src_idx == dest_idx: continue

            src_name = INTERSECTIONS[src_idx]
            dest_name = INTERSECTIONS[dest_idx]
            dist = random.randint(1, 20)
            zone = random.choice(ZONES)

            writer.writerow([100+src_idx, src_name, 100+dest_idx, dest_name, dist, zone])

    print(f"Saved '{NETWORK_FILE}'.")

def generate_tasks():
    print("Generating Construction Tasks (DAG for Topological Sort)...")
    tasks = [
        ("Surveying", "Grading"),
        ("Grading", "Paving"),
        ("Paving", "Line Painting"),
        ("Utility Installation", "Paving"),
        ("Bridge Design", "Bridge Construction"),
        ("Bridge Construction", "Safety Inspection"),
        ("Safety Inspection", "Opening Ceremony")
    ]

    with open(TASKS_FILE, mode='w', newline='', encoding='utf-8') as file:
        writer = csv.writer(file)
        writer.writerow(["Task_A", "Task_B"])
        for t1, t2 in tasks:
            writer.writerow([t1, t2])

    print(f"Saved '{TASKS_FILE}'.")

if __name__ == "__main__":
    generate_network()
    generate_tasks()