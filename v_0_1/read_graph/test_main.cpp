#include <bits/stdc++.h>

int main(){
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph;
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
	}	
	
	
}
