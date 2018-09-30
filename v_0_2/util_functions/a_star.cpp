#ifndef A_STAR_CPP
#define A_STAR_CPP

#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
//#include "../input_readers/graph_file_reader.cpp"
//#include "../graph_handlers/graph_depos_handler.cpp"

class a_star_instance{
	public:

	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph;
	std::set<std::pair<double, double> > closed_set;
	std::set<std::pair<double, double> > open_set;
	std::map<std::pair<double, double>, std::pair<double, double> > came_from;
	std::map<std::pair<double, double>, double> g_score;
	/*>*/
	double path_length(	std::vector<std::pair<double, double> > path,
						std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph){
		double total_length = 0;	
		for(unsigned int i=0; i<path.size()-1; i++){
			total_length += graph->find(path[i])->second.find(path[i+1])->second;
		}
		return total_length;
	}
	/*<*/
	std::vector<std::pair<double, double> > reconstruct_path(std::pair<double, double> current){
		std::vector<std::pair<double, double> > total_path = {current};
		while(came_from.find(current)!=came_from.end()){
			current = came_from[current];
			total_path.push_back(current);
		}
		return total_path;
	}

	void set_start(	std::pair<double, double> start_loc,
							std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph){
		graph = graph;
		closed_set = std::set<std::pair<double, double> >();
		open_set = std::set<std::pair<double, double> >();
		open_set.insert(start_loc);
		came_from = std::map<std::pair<double, double>, std::pair<double, double> >();
		g_score = std::map<std::pair<double, double>, double>();
	}

	void calculate_path_to(std::pair<double, double> end_loc){
		if(closed_set.find(end_loc) == closed_set.end()){
			std::map<std::pair<double, double>, double> f_score;
			for(std::pair<double, double> point : open_set){
				f_score[point] = vincenty_distance(point, end_loc);
			}
			while(!open_set.empty()){
				double min_f_score = DBL_MAX;
				std::pair<double, double> current;
				for(auto node : open_set){
					if(f_score[node] < min_f_score){
						current = node;
					}
				}
				if(current == end_loc){
					break;
				}
				
				if(open_set.find(current) != open_set.end()){
					open_set.erase(open_set.find(current));
				}
				
				closed_set.insert(current);
				
				for(auto neighbor : graph->find(current)->second){
					if(closed_set.find(neighbor.first) != closed_set.end()){
						continue;
					}
					
					double tentative_g_score = g_score[current] + neighbor.second;
					
					if(open_set.find(neighbor.first) == open_set.end()){
						open_set.insert(neighbor.first);
					}
					else if(tentative_g_score >= g_score[neighbor.first]){
						continue;
					}
					
					came_from[neighbor.first] = current;
					g_score[neighbor.first] = tentative_g_score;
					f_score[neighbor.first] = g_score[neighbor.first] + vincenty_distance(neighbor.first, end_loc);
				}
			}
		}
	}

	std::vector<std::pair<double, double> > get_path_to(std::pair<double, double> end_loc){
		calculate_path_to(end_loc);
		return reconstruct_path(end_loc);
	}

	double get_distance_to(std::pair<double, double> end_loc){
		calculate_path_to(end_loc);
		return g_score[end_loc];
	}
};

#endif
