#include <bits/stdc++.h>
#include "../graph_builders/map_to_graph_3.cpp"

void write_graph_file(std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph){//move to seperate file
	std::ofstream graphout;
	graphout.open("../input_files/graph.txt");
	for(std::pair<std::pair<double, double>, std::map<std::pair<double, double>, double> > start_loc : (*map_graph)){
		for(std::pair<std::pair<double, double>, double> end_loc : start_loc.second){
			if(start_loc.first.first == end_loc.first.first && start_loc.first.second == end_loc.first.second){
				std::cout << "bad road insert: " << start_loc.first.first << " , " << start_loc.first.second << " - " << end_loc.first.first << " , " << end_loc.first.second << "\n";
			}else{
				graphout << start_loc.first.first 	<< " " << start_loc.first.second 	<< " " << 
							end_loc.first.first 	<< " " << end_loc.first.second 		<< " " << 
							end_loc.second << "\n";
			}
		}
	}
}

int main(){
	calculate_map_graph_and_roads();
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph = get_map_graph_doubles();
	write_graph_file(&map_graph);
	return 0;
}
