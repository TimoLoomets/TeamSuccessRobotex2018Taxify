#ifndef UTIL_FUNCTIONS_HPP
#define UTIL_FUNCTIONS_HPP

#include <bits/stdc++.h>

#include "haversine.cpp"
#include "vincenty.cpp"
#include "qtree.cpp"
#include "data_types.h"


double haversine_distance(double lat1d, double lon1d, double lat2d, double lon2d);
double vincenty_distance(double latitude_01, double longitude_01, double latitude_02, double longitude_02);

void populate(std::vector<road> inputs, double upper_x, double upper_y, double width, int iterations_left, int node);
std::vector<road> relevant_roads(double x, double y, double current_x, double current_y, double width, int node, int iterations_left);

#endif

