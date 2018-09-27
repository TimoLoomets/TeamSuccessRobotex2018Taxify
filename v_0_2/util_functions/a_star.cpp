#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../input_readers/graph_file_reader.cpp"
#include "../graph_handlers/graph_depos_handler.cpp"


double path_length(	std::vector<std::pair<double, double> > path,
					std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph){
	double total_length = 0;	
	for(int i=0; i<path.size()-1; i++){
		total_length += graph->find(path[i])->second.find(path[i+1])->second;
	}
	return total_length;
}

std::vector<std::pair<double, double> > reconstruct_path(std::map<std::pair<double, double>, std::pair<double, double> > came_from, std::pair<double, double> current){
	std::vector<std::pair<double, double> > total_path = {current};
	while(came_from.find(current)!=came_from.end()){
		current = came_from[current];
		total_path.push_back(current);
	}
	return total_path;
}

void a_star(std::pair<double, double> start_loc, 
			std::pair<double, double> end_loc, 
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph, 
			std::vector<std::pair<double, double> > * path, 
			double * length){
	//std::set<std::pair<double, vector<std::pair<double, double> > > > to_check;
	std::set<std::pair<double, double> > closed_set;
	std::set<std::pair<double, double> > open_set;
	open_set.insert(start_loc);
	
	std::map<std::pair<double, double>, std::pair<double, double> > came_from;
	std::map<std::pair<double, double>, double> g_score;
	g_score[start_loc] = 0;
	std::map<std::pair<double, double>, double> f_score;
	f_score[start_loc] = vincenty_distance(start_loc, end_loc);
	
	while(!open_set.empty()){
		double min_f_score = DBL_MAX;
		std::pair<double, double> current;
		for(auto node : open_set){
			if(f_score[node] < min_f_score){
				current = node;
			}
		}
		//std::cout << "current: " << current.first << " , " << current.second << "\n";
		if(current == end_loc){
			*path = reconstruct_path(came_from, end_loc);
			*length = path_length(*path, graph);
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

/*
int main(){
	read_graph_file();
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer = get_file_graph();
	
	
	
	
	return 0;
}*/
