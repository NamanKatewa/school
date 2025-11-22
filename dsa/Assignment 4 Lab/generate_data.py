import csv

def generate_data():
    """
    Generates sample building and edge data for the Campus Navigation and Utility Planner.
    """
    buildings = [
        [1, "Main Building", "Central campus area"],
        [2, "Library", "West of Main Building"],
        [3, "Engineering Hall", "East of Main Building"],
        [4, "Student Center", "South of Main Building"],
        [5, "Gymnasium", "North of Main Building"]
    ]

    edges = [
        [1, 2, 50.0],
        [1, 3, 60.0],
        [1, 4, 40.0],
        [2, 3, 70.0],
        [3, 4, 80.0],
        [4, 5, 90.0]
    ]

    with open('buildings.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['BuildingID', 'BuildingName', 'LocationDetails'])
        writer.writerows(buildings)

    with open('edges.csv', 'w', newline='') as f:
        writer = csv.writer(f)
        writer.writerow(['BuildingID1', 'BuildingID2', 'Distance'])
        writer.writerows(edges)

    print("Generated buildings.csv and edges.csv")

if __name__ == '__main__':
    generate_data()
