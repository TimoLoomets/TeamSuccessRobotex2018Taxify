import random

with open("robotex.txt", "w") as txt:
    txt.write("car_id, car_lat, car_lng, ride_start_time, nr_of_people_in_cars\n")
    for i in range(1000):
        line_to_write = f"{random.randint(1, 100)}, {random.uniform(59, 60)}, {random.uniform(24, 25)}, {1542290702 + i}, {random.randint(1, 4)}\n"
        txt.write(line_to_write)
