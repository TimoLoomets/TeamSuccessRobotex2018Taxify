#include <bits/stdc++.h>

#include "data_types.h"
#include "util_functions.hpp"

using namespace std;


//const int square_amount = 1024; // Change this to be the amount of squares at the lowest level (must be divisible by four)


const int northwest = 1;
const int southwest = 2;
const int southeast = 3;
const int northeast = 4;


// This is the actual data structure
//const int tree_size = square_amount * 2 * 4;

unordered_map <int, vector <road> > tree;

/*inline int parent(int node){//never used
  return node/2;
}*/

inline int child(int parent, int index){
  return parent * 4 + index;
}

/*inline int index(int node){//never used
  return node % 4;
}*/

// Check if the line intersects a circumscribed circle around the square. Quick and dirty hack. A real solution gives better perf

bool intersects_square(road r, double upper_x, double upper_y, double width){
	/*
  // Center of the square

  pair<double, double> center = {upper_x - width/2, upper_y - width/2};

  // Direction of the road

  pair<double, double> dir = {r.second.first - r.first.first, r.second.second - r.first.second};

  // Length of road

  double length = sqrt(dir.first*dir.first + dir.second*dir.second);

  // unit normal of the road

  pair<double, double> normal = {-dir.second/length, dir.first/length};

  double dist = normal.first * (center.first - r.first.first) + normal.second * (center.second - r.first.second);

  return dist <= (sqrt(2)/2)*width;
*/
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
	
	/*
	cout << "first_point_inside: " << first_point_inside << "\n"; 
	cout << "\t" << upper_y - width << " < " << r.first.first << " < " << upper_y << "\n";
	cout << "\t" << upper_x - width << " < " << r.first.second << " < " << upper_x << "\n";
	cout << "second_point_inside: " << second_point_inside << "\n";
	cout << "\t" << upper_y - width << " < " << r.second.first << " < " << upper_y << "\n";
	cout << "\t" << upper_x - width << " < " << r.second.second << " < " << upper_x << "\n";
	*/
	
	return 	first_point_inside 			||
			second_point_inside			||
			do_intersect(r, upper_side) || 
			do_intersect(r, right_side) || 
			do_intersect(r, lower_side) || 
			do_intersect(r, left_side);
}

// Populate the tree with roads

void populate(vector<road> inputs, double upper_x, double upper_y, double width, int node, int iterations_left){

  // Add all the roads that intersect the square to the road list for the square

  for(road r : inputs){
    if(intersects_square(r, upper_x, upper_y, width)){
      	tree[node].push_back(r);
      	//cout << "intersects" << "\n";
    }
    /*else{
    	cout << "doesn't intersect" << "\n";
    }*/
  }
  	/*
  	cout << "populate: " << node << " size: " << tree[node].size() << "\n";
  	cout << "\t" << "lower_x: " << upper_x - width << " - " << "upper_x: " << upper_x << "\n";
  	cout << "\t" << "lower_y: " << upper_y - width << " - " << "upper_y: " << upper_y << "\n";
  	*/
  // If we haven't reached the target depth yet and at least one road goes through this square

  if(tree[node].size() != 0 && iterations_left > 0){
    populate(tree[node], upper_x - (width / 2), upper_y, 				width / 2, child(node, northwest), iterations_left - 1);
    populate(tree[node], upper_x - (width / 2), upper_y - (width / 2), 	width / 2, child(node, southwest), iterations_left - 1);
    populate(tree[node], upper_x, 				upper_y - (width / 2), 	width / 2, child(node, southeast), iterations_left - 1);
    populate(tree[node], upper_x, 				upper_y, 				width / 2, child(node, northeast), iterations_left - 1);
  }
}

// Return the roads nearby a point

vector<road> relevant_roads(double x, double y, double current_x, double current_y, double width, int node, int iterations_left){
	cout << "iterations_left: " << iterations_left << " roads: " << tree[node].size() << "\n";
  if(iterations_left == 0) return tree[node];
  else{
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
  }
}
