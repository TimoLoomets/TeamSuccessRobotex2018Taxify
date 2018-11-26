#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../input_readers/input_readers.hpp"
#include "../graph_handlers/graph_handlers.hpp"

int main(){
	std::cout << "started reading graph file \n";
	read_graph_file();

	std::cout << "started getting graph \n";
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer = get_file_graph();

	std::cout << "started getting depos \n";
	vector<depo_data> all_depos = get_depos();
	
	std::cout << "started adding depos \n";
	add_depos_to_graph(map_graph_pointer, &all_depos);

	std::cout << "started iterating depos \n";
	int counter = 0;
	for(std::vector<depo_data>::iterator all_depos_i = all_depos.begin(); all_depos_i != all_depos.end(); all_depos_i++){
		a_star_instance new_depo_a_star;
		std::pair<double, double> depo_loc = std::make_pair(all_depos_i->lat, all_depos_i->lon);
		new_depo_a_star.set_start(depo_loc, map_graph_pointer);
		counter++;
		std::ofstream a_star_file;
		a_star_file.open ("../input_files/a_star_" + std::to_string(counter) + ".txt");
		a_star_file << depo_loc.first 
					<< " , " 
					<< depo_loc.second
					<< "\n";
		for(auto node: *map_graph_pointer){
			double distance = new_depo_a_star.get_distance_to(node.first);
			std::pair<double, double> last = new_depo_a_star.get_last_to(node.first);
			if(distance != 0){
				a_star_file << node.first.first 
							<< " , " 
							<< node.first.second 
							<< " : " 
							<< last.first 
							<< " , " 
							<< last.second 
							<< " : " 
							<< distance 
							<< "\n";
			}
		}
		a_star_file.close();
	}
}
