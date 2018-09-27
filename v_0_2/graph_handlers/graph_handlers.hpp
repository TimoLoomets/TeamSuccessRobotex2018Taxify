#ifndef GRAPH_HANDLERS_HPP
#define GRAPH_HANDLERS_HPP

#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "graph_points_handler.cpp"
#include "graph_depos_handler.cpp"
#include "graph_passengers_handler.cpp"


std::set<std::pair<double, double> > add_point_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> point_location);
void remove_points_from_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			std::pair<double, double> point_location, 
			std::set<std::pair<double, double> > nodes);

void add_depos_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer,
			std::vector<depo_data> * depos_pointer);

void add_passenger_to_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			passenger_data * passenger_pointer);
void remove_passanger_from_graph(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer, 
			passenger_data * passenger_pointer);

#endif
