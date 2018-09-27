#include <bits/stdc++.h>

#include "../graph_builders/map_to_graph_3.cpp"
#include "../input_readers/depos2.hpp"

//1428921 - 1365523 = 63398
//6603278 - 6570020 = 33258
std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph;
vector<depo_data> depos;

void add_depos_to_graph(){
	calculate_map_graph_and_roads();
	std::set<road> map_roads = get_map_roads();
	
	std::cout << std::fixed;
	
	depos = get_depos();
	
	map_graph = get_map_graph_doubles();

	populate(map_roads, Tallinn_E, Tallinn_N, std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
	
	//kml_start();//kml
	for(vector<depo_data>::iterator depo_it = depos.begin(); depo_it < depos.end(); ++depo_it){
		//std::cout << "depo: " << (*depo_it).lat << " , " << (*depo_it).lon << "\n";//out
		std::pair<double, double> depo_location = std::make_pair((*depo_it).lat, (*depo_it).lon);
		//kml_point(depo_location);//kml
		std::set<road> my_roads = relevant_roads_around((*depo_it).lon, (*depo_it).lat, 	
														Tallinn_E, 		Tallinn_N, 
														std::max(Tallinn_N - Tallinn_S, Tallinn_E - Tallinn_W), 0, used_depth);
		
		//std::cout << "roads: " << my_roads.size() << "\n";//out
		for(auto current_road : my_roads){
			std::set<std::pair<double, double> > road_intersections = geodesic_intersections(depo_location, current_road);
			if(!road_intersections.empty()){
				//kml_road(current_road);//kml
				/*for(auto current_intersection : road_intersections){//out & kml
					kml_point(current_intersection);//kml
					std::cout << current_intersection.first << " , " << current_intersection.second << "\n";//out
				}*/
				if(road_intersections.size() == 1){
					pair<double, double> current_intersection = *(road_intersections.begin());
					double first_distance = vincenty_distance(current_road.first, current_intersection);
					double second_distance = vincenty_distance(current_road.second, current_intersection);
					map_graph[current_road.first][current_intersection] = first_distance;
					map_graph[current_intersection][current_road.first] = first_distance;
					map_graph[current_road.second][current_intersection] = second_distance;
					map_graph[current_intersection][current_road.second] = second_distance;
					depo_it->nodes.insert(current_intersection);
				}else if(road_intersections.size() == 2){
					pair<double, double> current_intersection_1 = *(road_intersections.begin());
					pair<double, double> current_intersection_2 = *std::next(road_intersections.begin(), 1);
					double intersection_distance = vincenty_distance(current_intersection_1, current_intersection_2);
					map_graph[current_intersection_1][current_intersection_2] = intersection_distance;
					map_graph[current_intersection_2][current_intersection_1] = intersection_distance;
					
					depo_it->nodes.insert(current_intersection_1);
					depo_it->nodes.insert(current_intersection_2);
					
					pair<double, double> road_point;
					double first_distance;
					double second_distance;
					road_point = current_road.first;
					first_distance = vincenty_distance(road_point, current_intersection_1);
					second_distance = vincenty_distance(road_point, current_intersection_2);
					if(first_distance < second_distance){
						map_graph[road_point][current_intersection_1] = first_distance;
						map_graph[current_intersection_1][road_point] = first_distance;
					}else{
						map_graph[road_point][current_intersection_2] = second_distance;
						map_graph[current_intersection_2][road_point] = second_distance;
					}
					
					road_point = current_road.second;
					first_distance = vincenty_distance(road_point, current_intersection_1);
					second_distance = vincenty_distance(road_point, current_intersection_2);
					if(first_distance < second_distance){
						map_graph[road_point][current_intersection_1] = first_distance;
						map_graph[current_intersection_1][road_point] = first_distance;
					}else{
						map_graph[road_point][current_intersection_2] = second_distance;
						map_graph[current_intersection_2][road_point] = second_distance;
					}
				}
			}
		}
	}
	//kml_end();//kml
}

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > get_map_graph_with_depos(){
	return map_graph;
}

vector<depo_data> get_depos_with_connections(){
	return depos;
}
