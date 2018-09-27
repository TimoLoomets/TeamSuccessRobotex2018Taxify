#ifndef GRAPH_POINTS_HANDLER_CPP
#define GRAPH_POINTS_HANDLER_CPP

#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"

void insert_to_map_pointer(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> loc1, 
			std::pair<double, double> loc2, 
			double val){
	if(val != 0){
		if(map_graph_pointer->find(loc1) != map_graph_pointer->end()){
			map_graph_pointer->find(loc1)->second.insert(std::make_pair(loc2, val)); 
		}else{
			map_graph_pointer->insert(std::make_pair(loc1, std::map<std::pair<double, double>, double>{{loc2, val}}));
		}
	}
}

void delete_from_map_pointer(std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> loc1, 
			std::pair<double, double> loc2){
	if(map_graph_pointer->find(loc1) != map_graph_pointer->end()){
		map_graph_pointer->find(loc1)->second.erase(loc2); 
	}
}

std::set<std::pair<double, double> > add_point_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> point_location){
			
	std::set<std::pair<double, double> > output_nodes;
	std::set<road> my_roads = relevant_roads_around(point_location.second, point_location.first, 	
														Tallinn_E, 		Tallinn_N, 
														std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
	//std::cout << "relevant roads: " << my_roads.size() << "\n";
											
	for(road r : my_roads){
		if(r.first.first == r.second.first && r.first.second == r.second.second){
			std::cout << "bad road in my_roads: " << r.first.first << " , " << r.first.second << " - " << r.second.first << " , " << r.second.second << "\n";
			while(true){}
		}
	}			
														
	for(auto current_road : my_roads){
		//std::cout << "cp0\n";
		//std::cout << "current_road: " << current_road.first.first << " , " << current_road.first.second << " - " << current_road.second.first << " , " << current_road.second.second << "\n";
		std::set<std::pair<double, double> > road_intersections = geodesic_intersections(point_location, current_road);
		//std::cout << "cp1\n";
		//std::cout << "\tintersections: " << road_intersections.size() << "\n";
		if(!road_intersections.empty()){
			//std::cout << "cp2\n";
			if(road_intersections.size() == 1){
				//std::cout << "cp3\n";
				std::pair<double, double> current_intersection = *(road_intersections.begin());
				insert_to_map_pointer(map_graph_pointer, current_intersection, point_location, 50);
				insert_to_map_pointer(map_graph_pointer, point_location, current_intersection, 50);
				double first_distance = vincenty_distance(current_road.first, current_intersection);
				double second_distance = vincenty_distance(current_road.second, current_intersection);
				insert_to_map_pointer(map_graph_pointer, current_road.first, current_intersection, first_distance);
				insert_to_map_pointer(map_graph_pointer, current_intersection, current_road.first, first_distance);
				insert_to_map_pointer(map_graph_pointer, current_road.second, current_intersection, second_distance);
				insert_to_map_pointer(map_graph_pointer, current_intersection, current_road.second, second_distance);
				output_nodes.insert(current_intersection);
			}else if(road_intersections.size() == 2){
				//std::cout << "cp4\n";
				std::pair<double, double> current_intersection_1 = *(road_intersections.begin());
				std::pair<double, double> current_intersection_2 = *std::next(road_intersections.begin(), 1);
				insert_to_map_pointer(map_graph_pointer, point_location, current_intersection_1, 50);
				insert_to_map_pointer(map_graph_pointer, point_location, current_intersection_2, 50);
				insert_to_map_pointer(map_graph_pointer, current_intersection_1, point_location, 50);
				insert_to_map_pointer(map_graph_pointer, current_intersection_2, point_location, 50);
				double intersection_distance = vincenty_distance(current_intersection_1, current_intersection_2);
				insert_to_map_pointer(map_graph_pointer, current_intersection_1, current_intersection_2, intersection_distance);
				insert_to_map_pointer(map_graph_pointer, current_intersection_2, current_intersection_1, intersection_distance);
				output_nodes.insert(current_intersection_1);
				output_nodes.insert(current_intersection_2);
				std::pair<double, double> road_point;
				double first_distance;
				double second_distance;
				road_point = current_road.first;
				first_distance = vincenty_distance(road_point, current_intersection_1);
				second_distance = vincenty_distance(road_point, current_intersection_2);
				if(first_distance < second_distance){
					insert_to_map_pointer(map_graph_pointer, road_point, current_intersection_1, first_distance);
					insert_to_map_pointer(map_graph_pointer, current_intersection_1, road_point, first_distance);
				}else{
					insert_to_map_pointer(map_graph_pointer, road_point, current_intersection_2, second_distance);
					insert_to_map_pointer(map_graph_pointer, current_intersection_2, road_point, second_distance);
				}
				road_point = current_road.second;
				first_distance = vincenty_distance(road_point, current_intersection_1);
				second_distance = vincenty_distance(road_point, current_intersection_2);
				if(first_distance < second_distance){
					insert_to_map_pointer(map_graph_pointer, road_point, current_intersection_1, first_distance);
					insert_to_map_pointer(map_graph_pointer, current_intersection_1, road_point, first_distance);
				}else{
					insert_to_map_pointer(map_graph_pointer, road_point, current_intersection_2, second_distance);
					insert_to_map_pointer(map_graph_pointer, current_intersection_2, road_point, second_distance);
				}
			}
		}
	}
	return output_nodes;
}

void remove_points_from_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> point_location, 
			std::set<std::pair<double, double> > nodes){
	for(auto current_node : nodes){
		delete_from_map_pointer(map_graph_pointer, point_location, current_node);
		delete_from_map_pointer(map_graph_pointer, current_node, point_location);
	}
}

/*
int main(){
	return 0;
}
*/

#endif
