#include <bits/stdc++.h>

#include "data_types.h"

using namespace std;


const int square_amount = 1024; // Change this to be the amount of squares at the lowest level (must be divisible by four)


const int northwest = 0;
const int southwest = 1;
const int southeast = 2;
const int northeast = 3;


// This is the actual data structure
const int tree_size = square_amount * 2 * 4;

vector<road> tree[tree_size];

inline int parent(int node){
  return node/2;
}

inline int child(int parent, int index){
  return parent * 4 + index;
}

inline int index(int node){
  return node % 4;
}

// Check if the line intersects a circumscribed circle around the square. Quick and dirty hack. A real solution gives better perf

bool intersects_square(road r, double upper_x, double upper_y, double width){

  // Center of the square

  pair<double, double> center = {upper_x + width/2, upper_y + width/2};

  // Direction of the road

  pair<double, double> dir = {r.second.first - r.first.first, r.second.second - r.first.second};

  // Length of road

  double length = sqrt(dir.first*dir.first + dir.second*dir.second);

  // unit normal of the road

  pair<double, double> normal = {-dir.second/length, dir.first/length};

  double dist = normal.first * (center.first - r.first.first) + normal.second * (center.second - r.first.second);

  return dist <= (sqrt(2)/2)*width;

}

// Populate the tree with roads

void populate(vector<road> inputs, double upper_x, double upper_y, double width, int iterations_left, int node){

  // Add all the roads that intersect the square to the road list for the square

  for(road r : inputs){
    if(intersects_square(r, upper_x, upper_y, width)){
      tree[node].push_back(r);
    }
  }

  // If we haven't reached the target depth yet and at least one road goes through this square

  if(tree[node].size() != 0 && iterations_left > 0){
    populate(tree[node], upper_x + (width / 2), upper_y, width / 2, iterations_left - 1, child(node, northeast));
    populate(tree[node], upper_x + (width / 2), upper_y - (width / 2), width / 2, iterations_left - 1, child(node, southeast));
    populate(tree[node], upper_x, upper_y - (width / 2), width / 2, iterations_left - 1, child(node, southwest));
    populate(tree[node], upper_x, upper_y, width / 2, iterations_left - 1, child(node, northwest));
  }
}

// Return the roads nearby a point

vector<road> relevant_roads(double x, double y, double current_x, double current_y, double width, int node, int iterations_left){
  if(iterations_left == 0) return tree[node];
  else{
    if(current_x + (width / 2) > x){
      if(current_y - (width / 2) < y){
        return relevant_roads(x, y, current_x, current_y, width/2, child(node, northwest), iterations_left-1);
      }else{
        return relevant_roads(x, y, current_x, current_y - (width / 2), width/2, child(node, southwest), iterations_left-1);
      }
    }else{
      if(current_y - (width / 2) < y){
        return relevant_roads(x, y, current_x + (width / 2), current_y, width/2, child(node, northeast), iterations_left-1);
      }else{
        return relevant_roads(x, y, current_x + (width / 2), current_y - (width / 2), width/2, child(node, southeast), iterations_left-1);
      }
    }
  }
}
