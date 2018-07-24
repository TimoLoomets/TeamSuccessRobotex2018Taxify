#include <bits/stdc++.h>

#include "map_to_graph_3.cpp"
#include "depos2.hpp"

#define Tallinn_S 59.245521563
#define Tallinn_N 59.544064638
#define Tallinn_W 24.275665283
#define Tallinn_E 25.190277100

int used_depth = 9;
//1428921 - 1365523 = 63398
//6603278 - 6570020 = 33258

int main(){
	calculate_map_graph_and_roads();
	std::vector<road> map_roads = get_map_roads();
	
	std::cout << std::fixed;// << std::setprecision(0);
	//std::cout << "WN" << vincety_distance(Tallinn_N, Tallinn_W, Tallinn_N, 0) << "\n";
	//std::cout << "WS" << vincety_distance(Tallinn_S, Tallinn_W, Tallinn_S, 0) << "\n";
	//std::cout << "SW" << vincety_distance(Tallinn_S, Tallinn_W, 0, Tallinn_W) << "\n";
	//std::cout << "SE" << vincety_distance(Tallinn_S, Tallinn_E, 0, Tallinn_E) << "\n";
	
	/*
	double x = 24.700312614;
	double y = 59.429101562;
	//std::cout << "total roads: " << map_roads.size() << "\n";
	
	populate(map_roads, 							Tallinn_E, Tallinn_N, std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, 10);
	vector<road> my_roads = relevant_roads(x, y, 	Tallinn_E, Tallinn_N, std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, 10);
	*/
	
	//std::cout << my_roads.size() << "\n";
	/*for(auto road : my_roads){
		std::cout << road.first.first << " , " << road.first.second << " - " << road.second.first << " , " << road.second.second << "\n";
	}*/
	
	/*
	std::vector<pair<double, road> > length_map_roads;
	for(auto road : map_roads){
		length_map_roads.push_back(std::make_pair(vincenty_distance(road.first.first, road.first.second, road.second.first, road.second.second), road));
	}
	
	std::sort(length_map_roads.begin(), length_map_roads.end());
	
	for(auto len_road : length_map_roads){
		road road_i = len_road.second;
		std::cout << road_i.first.first << " , " << road_i.first.second << " - " << road_i.second.first << " , " << road_i.second.second << " = " << len_road.first << "\n";
	}
	*/
	//std::cout << vincenty_distance(std::make_pair(Tallinn_S, Tallinn_W), std::make_pair(Tallinn_N, Tallinn_E)) << "\n";
	
	
	
	//std::cout << "depos: " << depos.size() << "\n";
	
	/*for(auto depo : depos){
		std::cout << "depo: " << depo.lat << " , " << depo.lon << "\n";
	}*/
	
	vector<depos_data> depos = get_depos_coordinates();
	
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph = get_map_graph_doubles();
	
	std::set<std::pair<double, double> > map_nodes;
	for(std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> >::iterator it = map_graph.begin(); it != map_graph.end(); ++it) {
		map_nodes.insert(it->first);
	}
	//std::sort(map_nodes.begin(), map_nodes.end());
	
	double x = 24.700312614;
	double y = 59.429101562;
	populate(map_nodes, 							Tallinn_E, Tallinn_N, std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
	
	for(vector<depos_data>::iterator depo_it = depos.begin(); depo_it < depos.end(); depo_it++){
		std::cout << "depo: " << (*depo_it).lat << " , " << (*depo_it).lon << "\n";
		std::pair<double, double> depo_location = std::make_pair((*depo_it).lat, (*depo_it).lon);
		std::set<std::pair<double, double> > my_nodes = relevant_points_around(	(*depo_it).lon, (*depo_it).lat, 	
																				Tallinn_E, 		Tallinn_N, 
																				std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
		
		std::cout << "nodes: " << my_nodes.size() << "\n";
		for(auto cur : my_nodes){
			double distance = vincenty_distance(cur, depo_location);
			if(distance > 50)my_nodes.erase(cur);
		}
		std::cout << "nodes: " << my_nodes.size() << "\n";
	}
}
