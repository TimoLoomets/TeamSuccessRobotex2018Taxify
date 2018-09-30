#ifndef QTREE_4_CPP
#define QTREE_4_CPP

#include <bits/stdc++.h>

#include "data_types.h"
#include "util_functions.hpp"

using namespace std;

const int northwest = 1;
const int southwest = 2;
const int southeast = 3;
const int northeast = 4;

unordered_map <int, std::set<road> > tree;

int max_iterations_left = 0;
int min_iterations_left = 100;
double min_width = 181;

inline int child(int parent, int index){
	return parent * 4 + index;
}

// Check if the line intersects a circumscribed circle around the square. Quick and dirty hack. A real solution gives better perf

bool intersects_square(road r, double upper_x, double upper_y, double width){

	road upper_side = make_pair(make_pair(upper_y, 			upper_x - width), 	make_pair(upper_y, 			upper_x));
	road right_side = make_pair(make_pair(upper_y, 			upper_x), 			make_pair(upper_y - width, 	upper_x));
	road lower_side = make_pair(make_pair(upper_y - width, 	upper_x), 			make_pair(upper_y - width, 	upper_x - width));
	road left_side = make_pair(	make_pair(upper_y - width, 	upper_x - width), 	make_pair(upper_y, 			upper_x - width));
	
	bool first_point_inside = 	upper_y - width < 	r.first.first 	&&
								upper_y 		>	r.first.first 	&& 
								upper_x - width < 	r.first.second 	&&
								upper_x			> 	r.first.second;
	
	bool second_point_inside = 	upper_y - width < 	r.second.first	&&
								upper_y 		> 	r.second.first 	&& 
								upper_x - width < 	r.second.second &&
								upper_x			>	r.second.second;
	
	return 	first_point_inside 			||
			second_point_inside			||
			do_intersect(r, upper_side) || 
			do_intersect(r, right_side) || 
			do_intersect(r, lower_side) || 
			do_intersect(r, left_side);
}

// Populate the tree with roads

void populate(std::set<road> inputs, double upper_x, double upper_y, double width, int node, int iterations_left){

	max_iterations_left = std::max(max_iterations_left, iterations_left);
	min_iterations_left = std::min(min_iterations_left, iterations_left);
	min_width = std::min(min_width, width);

	// Add all the roads that intersect the square to the road list for the square

	for(road r : inputs){
		if(intersects_square(r, upper_x, upper_y, width)){
			if(r.first.first == r.second.first && r.first.second == r.second.second){
				std::cout << "bad road insert: " << r.first.first << " , " << r.first.second << " - " << r.second.first << " , " << r.second.second << "\n";
				while(true){}
			}
			tree[node].insert(r);
		}
	}
	// If we haven't reached the target depth yet and at least one road goes through this square

	if(tree[node].size() != 0 && iterations_left > 0){
		populate(tree[node], upper_x - (width / 2), upper_y, 				width / 2, child(node, northwest), iterations_left - 1);
		populate(tree[node], upper_x - (width / 2), upper_y - (width / 2), 	width / 2, child(node, southwest), iterations_left - 1);
		populate(tree[node], upper_x, 				upper_y - (width / 2), 	width / 2, child(node, southeast), iterations_left - 1);
		populate(tree[node], upper_x, 				upper_y, 				width / 2, child(node, northeast), iterations_left - 1);
  	}
}


// Return the roads nearby a point

std::set<road> relevant_roads(double x, double y, double current_x, double current_y, double width, int node, int iterations_left){
	/*
	pair <double, double> upper_right = make_pair(current_y, current_x);
	pair <double, double> upper_left = make_pair(current_y, current_x - width);
	pair <double, double> lower_right = make_pair(current_y - width, current_x);
	*/
	
	if(tree[node].size() != 0 && iterations_left > 0){
		if(current_x - (width / 2) > x){
			if(current_y - (width / 2) > y){
				return relevant_roads(x, y, current_x - (width / 2), 	current_y - (width / 2), 	width/2, child(node, southwest), iterations_left-1);
			}else{
				return relevant_roads(x, y, current_x - (width / 2), 	current_y, 					width/2, child(node, northwest), iterations_left-1);
			}
		}else{
			if(current_y - (width / 2) > y){
				return relevant_roads(x, y, current_x, 					current_y - (width / 2), 	width/2, child(node, southeast), iterations_left-1);
			}else{
				return relevant_roads(x, y, current_x, 					current_y, 					width/2, child(node, northeast), iterations_left-1);
			}
		}
	}else{
		for(road r : tree[node]){
			if(r.first.first == r.second.first && r.first.second == r.second.second){
				std::cout << "bad road return: " << r.first.first << " , " << r.first.second << " - " << r.second.first << " , " << r.second.second << "\n";
				while(true){}
			}
		}
		return tree[node];
	}
}

int get_max_depth(){
	return max_iterations_left - min_iterations_left;
}

std::set<road> relevant_roads_around(double x, double y, double current_x, double current_y, double width, int node, int iterations){
	std::set<road> output_roads;
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			double now_x = x + i*min_width;
			double now_y = y + j*min_width;
			std::set<road> current_roads = relevant_roads(now_x, now_y, current_x, current_y, width, node, iterations);
			for(auto current_road : current_roads){
				output_roads.insert(current_road);
			}
		}
	}
	return output_roads;
}

#endif
