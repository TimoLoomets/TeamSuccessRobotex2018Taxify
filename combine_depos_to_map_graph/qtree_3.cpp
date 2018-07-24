#include <bits/stdc++.h>

#include "data_types.h"
#include "util_functions.hpp"

using namespace std;


//const int square_amount = 1024; // Change this to be the amount of squares at the lowest level (must be divisible by four)


const int northwest = 1;
const int southwest = 2;
const int southeast = 3;
const int northeast = 4;

int max_depth = 0;

// This is the actual data structure
//const int tree_size = square_amount * 2 * 4;

unordered_map <int, vector <pair<double, double > > > tree;

inline int child(int parent, int index){
  return parent * 4 + index;
}




bool inside_square(pair<double, double > r, double upper_x, double upper_y, double width){
	double lat = r.first;
	double lon = r.second;
	return 	lat <= upper_y &&
			lat >= upper_y - width &&
			lon <= upper_x &&
			lon >= upper_x - width; 
}

// Populate the tree with roads

void populate(vector<pair<double, double > > inputs, double upper_x, double upper_y, double width, int node, int iterations_left){

  // Add all the roads that intersect the square to the road list for the square

  for(pair<double, double > r : inputs){
    if(inside_square(r, upper_x, upper_y, width)){
      	tree[node].push_back(r);
      	//cout << "inside" << "\n";
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

vector<pair<double, double > > relevant_points(double x, double y, double current_x, double current_y, double width, int node, int iterations_left){
	//cout << "iterations_left: " << iterations_left << " roads: " << tree[node].size() << "\n";
	//pair <double, double> upper_right = make_pair(current_y, current_x);
	pair <double, double> upper_left = make_pair(current_y, current_x - width);
	pair <double, double> lower_right = make_pair(current_y - width, current_x);
	
	
	cout << "bbox: " << upper_left.first << " , " << upper_left.second << " - " << lower_right.first << " , " << lower_right.second << "\n";
  	if(iterations_left == 0) return tree[node];
  	else{
    	if(current_x - (width / 2) > x){
      		if(current_y - (width / 2) > y){
        		return relevant_points(x, y, current_x - (width / 2), 	current_y - (width / 2), 	width/2, child(node, southwest), iterations_left-1);
      		}else{
        		return relevant_points(x, y, current_x - (width / 2), 	current_y, 					width/2, child(node, northwest), iterations_left-1);
			}
    	}else{
      		if(current_y - (width / 2) > y){
        		return relevant_points(x, y, current_x, 					current_y - (width / 2), 	width/2, child(node, southeast), iterations_left-1);
      		}else{
        		return relevant_points(x, y, current_x, 					current_y, 					width/2, child(node, northeast), iterations_left-1);
      		}
    	}
  	}
}
