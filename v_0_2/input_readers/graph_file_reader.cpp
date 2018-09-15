#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp" 

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph;
std::set<road> map_roads;

void read_graph_file(){
	std::ifstream input_graph;
	input_graph.open("../input_files/graph.txt");
	std::string current_line;	
	
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
}

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > get_file_graph(){
	return map_graph;
}

std::set<road> get_file_roads(){
	return map_roads;
}
/*
int main(){
	read_graph_file();
	return 0;
}
*/