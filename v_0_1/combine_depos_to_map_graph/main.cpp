#include <bits/stdc++.h>

#include "map_to_graph.cpp"
#include "depos2.hpp"
#include "depos_header.h"

depos_data cordinates;
extern depos_data cordinates;

/*struct location_comparator {
    bool operator()(const std::string& a, const std::string& b) const {
        return a.length() < b.length();
    }
};*/

int main(){
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > map_graph = get_map_graph();
	
	
	int counter = 0;
	bool first_check = true;
	bool second_check = true;
	double first_last = 0;
	double second_last = 0;
	double longest_road = 0;
	
	for(auto start_node : map_graph){
		std::cout << start_node.first.first << " , " << start_node.first.second << "\n";
		if(start_node.first.first < first_last)first_check = false;
		else if(start_node.first.first == first_last){
			if(start_node.first.second < second_last)second_check = false;
		}
		first_last = start_node.first.first;
		second_last = start_node.first.second;
		counter++;
		for(auto end_node : start_node.second){
			std::cout << "\t" << end_node.first.first << " , " << end_node.first.second << " - " << end_node.second << "\n";
			if(end_node.second > longest_road)longest_road = end_node.second;
		}
	}
	std::cout << "Number of roads: " << counter << "\n";
	std::cout << "First in order: " << first_check << "\n";
	std::cout << "Second in order: " << second_check << "\n";
	std::cout << "Longest road: " << longest_road << "\n";
	
	
	vector <depos_data> depos_locations = get_depos_coordinates();
	/*for(auto coordinates : depos_locations){
		std::cout << coordinates.depo_lat << " : " << coordinates.depo_lng << "\n";
	}*/
	
	return 0;
}
