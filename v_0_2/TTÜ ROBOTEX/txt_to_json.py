import json
import csv


data = {}
data["taxy"] = []
proxy = {}
with open("robotex.txt") as f, open("robotex_json.json", "w") as out, open("robotex_csv.csv", "w") as out2:
    csv_writer = csv.writer(out2, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    first_line = f.readline()
    taxy_properties = first_line.strip().split(', ')
    for line in f:
        elements = line.strip().split(', ')
        csv_writer.writerow(elements)
        for i in range(len(taxy_properties)):
            proxy[taxy_properties[i]] = elements[i]
        data["taxy"].append(proxy)
        proxy = {}
    json.dump(data, out)
    out.write("\n")
print("Done")
