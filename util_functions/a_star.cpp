#include <bits/stdc++.h>
#include "util_functions.hpp"

std::vector<std::pair<double, double> > reconstruct_path(std::map<std::pair<double, double>, std::pair<double, double> > came_from, std::pair<double, double> current){
	std::vector<std::pair<double, double> > total_path = {current};
	while(came_from.find(current)!=came_from.end()){
		current = came_from[current];
		total_path.push_back(current);
	}
	return total_path;
}

void a_star(
			std::pair<double, double> start_loc, 
			std::pair<double, double> end_loc, 
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph, 
			std::vector<std::pair<double, double> > * path, 
			double * length){
	//std::set<std::pair<double, vector<std::pair<double, double> > > > to_check;
	std::set<std::pair<double, double> > closed_set;
	std::set<std::pair<double, double> > open_set;
	
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
		
		if(current == end_loc){
			*path = reconstruct_path(came_from, end_loc);
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

int main(){
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph;
	std::ifstream input_graph;
	input_graph.open("../input_files/graph.txt");
	std::string current_line;
	
	while(getline(input_graph, current_line)){
		std::istringstream iss(current_line);
		std::string start_lat;
		std::string start_lon;
		std::string end_lat;
		std::string end_lon;
		std::string length;
		iss >> start_lat >> start_lon >> end_lat >> end_lon >> length;
		map_graph[std::make_pair(std::stod(start_lat), std::stod(start_lon))][std::make_pair(std::stod(end_lat), std::stod(end_lon))] = std::stod(length);
	}
	
	
	
	return 0;
}
