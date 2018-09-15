#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../graph_handlers/graph_points_handler.cpp"

void add_passenger_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			passenger_data * passenger_pointer){
	passenger_pointer->start_nodes = add_point_to_graph(map_graph_pointer, std::make_pair(passenger_pointer->start_lat, passenger_pointer->start_lon));
	passenger_pointer->end_nodes = add_point_to_graph(map_graph_pointer, std::make_pair(passenger_pointer->end_lat, passenger_pointer->end_lon));
}

void remove_passanger_from_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			passenger_data * passenger_pointer){
	remove_points_from_graph(map_graph_pointer, std::make_pair(passenger_pointer->start_lat, passenger_pointer->start_lon), passenger_pointer->start_nodes);
	remove_points_from_graph(map_graph_pointer, std::make_pair(passenger_pointer->end_lat, passenger_pointer->end_lon), passenger_pointer->end_nodes);		
}
/*
int main(){
	return 0;
}
*/
