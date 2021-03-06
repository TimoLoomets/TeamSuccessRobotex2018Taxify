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
	std::pair<double, double> start_loc;
	/*<deprecated>*/
	double path_length(	std::vector<std::pair<double, double> > path,
						std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph){
		double total_length = 0;	
		for(unsigned int i=0; i<path.size()-1; i++){
			total_length += graph->find(path[i])->second.find(path[i+1])->second;
		}
		return total_length;
	}
	/*</deprecated>*/
	std::vector<std::pair<double, double> > reconstruct_path(std::pair<double, double> current){
		std::vector<std::pair<double, double> > total_path = {current};
		while(came_from.find(current)!=came_from.end()){
			current = came_from[current];
			total_path.push_back(current);
		}
		return total_path;
	}

	void set_start(std::pair<double, double> start_loc_in,
				   std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph_i){
		start_loc = start_loc_in;
		graph = graph_i;
		closed_set = std::set<std::pair<double, double> >();
		open_set = std::set<std::pair<double, double> >();
		open_set.insert(start_loc);
		came_from = std::map<std::pair<double, double>, std::pair<double, double> >();
		g_score = std::map<std::pair<double, double>, double>();
	}

	void calculate_path_to(std::pair<double, double> end_loc){
		if(closed_set.find(end_loc) == closed_set.end()){
			//std::cout << "\t\tcalculating path\n";
			std::map<std::pair<double, double>, double> f_score;
			for(std::pair<double, double> point : open_set){
				f_score[point] = vincenty_distance(point, end_loc);
			}
			//std::cout << "\t\tstarting while\n";
			while(!open_set.empty()){
				//std::cout << "\t\t\tfinding min f score\n";
				double min_f_score = DBL_MAX;
				std::pair<double, double> current;
				for(auto node : open_set){
					if(f_score[node] < min_f_score){
						current = node;
					}
				}
				//std::cout << "\t\t\tcheck if end\n";
				if(current == end_loc){
					break;
				}
				//std::cout << "\t\t\tcp0\n";
				if(open_set.find(current) != open_set.end()){
					open_set.erase(open_set.find(current));
				}
				//std::cout << "\t\t\tcp1\n";
				closed_set.insert(current);
				//std::cout << "\t\t\tcp2\n";
				//std::cout << "\t\t\tcurrent: " << current.first << " , " << current.second << "\n";
				//std::cout << "\t\t\tcp666\n";
				graph->find(current);
				//std::cout << "\t\t\tcp777\n";
				//bool is_end_check = graph->find(current) != graph->end();
				//std::cout << "\t\t\tfind: " << is_end_check << "\n";				
				for(auto neighbor : graph->find(current)->second){
					//std::cout << "\t\t\tcp3\n";
					if(closed_set.find(neighbor.first) != closed_set.end()){
						continue;
					}
					//std::cout << "\t\t\tcp4\n";
					double tentative_g_score = g_score[current] + neighbor.second;
					//std::cout << "\t\t\tcp5\n";
					if(open_set.find(neighbor.first) == open_set.end()){
						open_set.insert(neighbor.first);
					}else if(tentative_g_score >= g_score[neighbor.first]){
						continue;
					}
					//std::cout << "\t\t\tcp7\n";
					came_from[neighbor.first] = current;
					//std::cout << "\t\t\tcp8\n";
					g_score[neighbor.first] = tentative_g_score;
					//std::cout << "\t\t\tcp9\n";
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
		//std::cout << "\tcalculating distance to: " << end_loc.first << " , " << end_loc.second << "\n";
		calculate_path_to(end_loc);
		//std::cout << "\treturning \n";
		return g_score[end_loc];
	}

	std::pair<double, double> get_last_to(std::pair<double, double> end_loc){
		calculate_path_to(end_loc);
		return came_from[end_loc];
	}
};

#endif
