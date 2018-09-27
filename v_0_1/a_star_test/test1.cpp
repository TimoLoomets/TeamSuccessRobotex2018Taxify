#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "passenger_reader.cpp"
#include "passenger_adder.cpp"

int main(){
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph;
	std::ifstream input_graph;
	input_graph.open("../input_files/graph.txt");
	std::string current_line;
	
	std::set<road> map_roads;
	
	while(getline(input_graph, current_line)){
		std::istringstream iss(current_line);
		std::string start_lat;
		std::string start_lon;
		std::string end_lat;
		std::string end_lon;
		std::string length;
		iss >> start_lat >> start_lon >> end_lat >> end_lon >> length;
		map_graph[std::make_pair(std::stod(start_lat), std::stod(start_lon))][std::make_pair(std::stod(end_lat), std::stod(end_lon))] = std::stod(length);
		map_roads.insert(std::make_pair(std::make_pair(std::stod(start_lat), std::stod(start_lon)), std::make_pair(std::stod(end_lat), std::stod(end_lon))));
	}
	
	populate(map_roads, Tallinn_E, Tallinn_N, std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
	
	std::vector<passenger_data> all_passengers = get_passengers();
	
	for(int i = 0; i < 1; i++){
		passenger_data test_passenger = all_passengers[i];
		
		add_passenger(&map_graph, &test_passenger);
		std::cout << test_passenger.start_lat << " " << test_passenger.start_lon << "\n";
		std::cout << test_passenger.end_lat << " " << test_passenger.end_lon << "\n";
		std::cout << test_passenger.start_nodes.size() << " " << test_passenger.end_nodes.size() << "\n\n";
	}
}
