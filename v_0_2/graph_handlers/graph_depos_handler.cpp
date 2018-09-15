#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../graph_handlers/graph_points_handler.cpp"

void add_depo_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			depo_data * depo_pointer){
	depo_pointer->nodes = add_point_to_graph(map_graph_pointer, std::make_pair(depo_pointer->lat, depo_pointer->lon));
}

void add_depos_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer,
			std::vector<depo_data> * depos_pointer){
	for(std::vector<depo_data>::iterator depos_it = (*depos_pointer).begin(); depos_it < (*depos_pointer).end(); ++depos_it){
		std::cout << "adding depo nr: " << depos_it - (*depos_pointer).begin() << "\n";
		add_depo_to_graph(map_graph_pointer, &(*depos_it));
	}
}
/*
int main(){
	return 0;
}
*/
