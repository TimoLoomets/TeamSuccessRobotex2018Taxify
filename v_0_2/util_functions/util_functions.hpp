#ifndef UTIL_FUNCTIONS_HPP
#define UTIL_FUNCTIONS_HPP

#include <bits/stdc++.h>

#include "haversine.cpp"
#include "vincenty.cpp"
#include "intersect_check.cpp"
#include "qtree_4.cpp"
#include "data_types.h"
#include "geodesic.cpp"
#include "kml_exporter.cpp"
#include "a_star.cpp"


double haversine_distance(double lat1d, double lon1d, double lat2d, double lon2d);
double vincenty_distance(double latitude_01, double longitude_01, double latitude_02, double longitude_02);
double vincenty_distance(pair<double, double> point1, pair<double, double> point2);
std::pair<double, double> vincenty_location(std::pair<double, double> &pt, double brng, double dist);

void populate(std::set<road> inputs, double upper_x, double upper_y, double width, int iterations_left, int node);
std::set<road> relevant_roads(double x, double y, double current_x, double current_y, double width, int node, int iterations_left);

bool do_intersect(road road1, road road2);

std::set<std::pair<double, double> > geodesic_intersections(std::pair<double, double> depo_loc, road my_road);

void kml_start();
void kml_end();
void kml_point(std::pair<double, double> point);
void kml_road(road my_road);

void a_star_set_start(	std::pair<double, double> start_loc,
						std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * graph);
std::vector<std::pair<double, double> > a_star_get_path_to(std::pair<double, double> end_loc);
double a_star_get_distance_to(std::pair<double, double> end_loc);


#endif

