#include <bits/stdc++.h>
#include "combine_depos_to_graph.cpp"
#include "passenger_reader.cpp"

#define Tallinn_S 59.245521563
#define Tallinn_N 59.544064638
#define Tallinn_W 24.275665283
#define Tallinn_E 25.190277100


void insert_to_map_pointer(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> loc1, 
			std::pair<double, double> loc2, 
			double val){
	if(map_graph_pointer->find(loc1) != map_graph_pointer->end()){
		map_graph_pointer->find(loc1)->second.insert(std::make_pair(loc2, val)); 
	}else{
		map_graph_pointer->insert(std::make_pair(loc1, std::map<std::pair<double, double>, double>{{loc2, val}}));
	}
}

std::set<std::pair<double, double> > add_point_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> point_location){
			
	std::set<std::pair<double, double> > output_nodes;
	std::set<road> my_roads = relevant_roads_around(point_location.second, point_location.first, 	
														Tallinn_E, 		Tallinn_N, 
														std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
	for(auto current_road : my_roads){
		std::set<std::pair<double, double> > road_intersections = geodesic_intersections(point_location, current_road);
		if(!road_intersections.empty()){
			if(road_intersections.size() == 1){
				std::pair<double, double> current_intersection = *(road_intersections.begin());
				double first_distance = vincenty_distance(current_road.first, current_intersection);
				double second_distance = vincenty_distance(current_road.second, current_intersection);
				insert_to_map_pointer(map_graph_pointer, current_road.first, current_intersection, first_distance);
				insert_to_map_pointer(map_graph_pointer, current_intersection, current_road.first, first_distance);
				insert_to_map_pointer(map_graph_pointer, current_road.second, current_intersection, second_distance);
				insert_to_map_pointer(map_graph_pointer, current_intersection, current_road.second, second_distance);
				output_nodes.insert(current_intersection);
			}else if(road_intersections.size() == 2){
				std::pair<double, double> current_intersection_1 = *(road_intersections.begin());
				std::pair<double, double> current_intersection_2 = *std::next(road_intersections.begin(), 1);
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

int main(){
	add_depos_to_graph();
	/*vector<depos_data> my_depos = get_depos_with_connections();
	for(auto current_depo : my_depos){
		std::cout << current_depo.lat << " , " << current_depo.lon << "\n";
	}*/
	std::vector<passenger_data> passengers = get_passengers();
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph = get_map_graph_with_depos();
	
	for(vector<passenger_data>::iterator passenger_it = passengers.begin(); passenger_it < passengers.end(); ++passenger_it){
		//std::cout << "passanger start: " << passenger_it->start_lat << " , " << passenger_it->start_lon << "\n";
		std::cout << passengers.end()-passenger_it << "\n";//258348 
		passenger_it->start_nodes = add_point_to_graph(&map_graph, std::make_pair(passenger_it->start_lat, passenger_it->start_lon));
		//std::cout << "passanger end: " << passenger_it->end_lat << " , " << passenger_it->end_lon << "\n";
		passenger_it->end_nodes = add_point_to_graph(&map_graph, std::make_pair(passenger_it->end_lat, passenger_it->end_lon));
	}
	
	return 0;
}
