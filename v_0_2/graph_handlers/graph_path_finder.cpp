#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../input_readers/depos2.hpp"
#include "../input_readers/passenger_reader.cpp"
#include "../input_readers/graph_file_reader.cpp"
#include "../graph_handlers/graph_depos_handler.cpp"
#include "../graph_handlers/graph_passengers_handler.cpp"


int main(){
	std::cout << "started reading graph file \n";
	read_graph_file();
	std::cout << "started getting graph \n";
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph = get_file_graph();
	std::cout << "started getting roads \n";
	std::set<road> map_roads = get_file_roads();
	std::cout << "started getting passengers \n";
	std::vector<passenger_data> all_passengers = get_passengers();
	std::cout << "started getting depos \n";
	vector <depo_data> all_depos = get_depos();
	
	std::cout << "started adding depos \n";
	add_depos_to_graph(&map_graph, &all_depos);
	std::cout << "finished adding depos \n";
	
	for(depo_data current_depo : all_depos){
		std::cout << "depo nodes: " << current_depo.nodes.size() << "\n";
	}
	
	return 0;
}
