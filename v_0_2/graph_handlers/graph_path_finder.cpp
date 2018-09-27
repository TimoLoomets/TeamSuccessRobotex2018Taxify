#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../input_readers/input_readers.hpp"
#include "../graph_handlers/graph_handlers.hpp"
#include "graph_passengers_handler.cpp"


int main(){
	std::cout << "started reading graph file \n";
	read_graph_file();
	std::cout << "started getting graph \n";
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer = get_file_graph();
	std::cout << "started getting roads \n";
	std::set<road> my_map_roads = get_file_roads();
	for(road r : map_roads){
		if(r.first.first == r.second.first && r.first.second == r.second.second){
			std::cout << "bad road in map_roads: " << r.first.first << " , " << r.first.second << " - " << r.second.first << " , " << r.second.second << "\n";
			while(true){}
		}
	}
	std::cout << "started getting passengers \n";
	std::vector<passenger_data> all_passengers = get_passengers();
	std::cout << "started getting depos \n";
	vector <depo_data> all_depos = get_depos();
	
	std::cout << "started adding depos \n";
	add_depos_to_graph(&map_graph, &all_depos);
	std::cout << "finished adding depos \n";
	/*
	for(depo_data current_depo : all_depos){
		std::cout << "depo nodes: " << current_depo.nodes.size() << "\n";
	}
	
	std::cout << "\n";

	for(int i=0; i<10; i++){
		add_passenger_to_graph(map_graph_pointer, &(all_passengers[i]));//
		passenger_data current_passenger = all_passengers[i];
		std::cout << "passenger nodes: " << current_passenger.start_nodes.size() << " , " << current_passenger.end_nodes.size() << "\n";
	}*/

	std::vector<std::pair<double, double> > my_path;
	double my_length;
	add_passenger_to_graph(map_graph_pointer, &(all_passengers[0]));
	//std::cout << std::boolalpha;
	std::cout << "passenger nodes: " << all_passengers[0].start_nodes.size() << " , " << all_passengers[0].end_nodes.size() << "\n";
	std::cout << "start loc: " << all_passengers[0].start_lat << " , " << all_passengers[0].start_lon << "\n";
	bool start_is = map_graph_pointer->find(std::make_pair(all_passengers[0].start_lat, all_passengers[0].start_lon)) 	!= map_graph_pointer->end();
	bool end_is = 	map_graph_pointer->find(std::make_pair(all_passengers[0].end_lat, 	all_passengers[0].end_lon))  	!= map_graph_pointer->end();
	std::cout << "start connected: " << std::boolalpha 	<< start_is << "\n";	
	std::cout << "end loc: " << all_passengers[0].end_lat << " , " << all_passengers[0].end_lon << "\n";
	std::cout << "end connected: " << std::boolalpha << start_is << "\n";

	a_star(	std::make_pair(all_passengers[0].start_lat, all_passengers[0].start_lon), 
			std::make_pair(all_passengers[0].end_lat, all_passengers[0].end_lon),
			map_graph_pointer,
			&my_path,
			&my_length);
	
	std::cout << "path size: " << my_path.size() << "\n";

	return 0;
}
