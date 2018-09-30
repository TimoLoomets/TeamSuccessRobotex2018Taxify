#ifndef INPUT_READERS_HPP
#define INPUT_READERS_HPP

#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "graph_file_reader.cpp"
#include "passenger_reader.cpp"
#include "depos2.cpp"

vector <depo_data> get_depos();

void read_graph_file();
std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * get_file_graph();
std::set<road> get_file_roads();

std::vector<passenger_data> get_passengers();

#endif
