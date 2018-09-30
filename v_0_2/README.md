<<<<<<< HEAD
Graph builder compile line: g++ graph_file_writer.cpp --std=c++17 -lpthread -lz -lexpat -lbz2 -pipe -Wall
Main file compile line: g++ main.cpp --std=c++17 -pipe -Wall
=======
g++ .cpp --std=c++17 -lpthread -lz -lexpat -lbz2 -pipe -Wall

input_files:
estonia_latest contains latest roads located in Tallinn
graph and robotex2 both contain information about the passengers
robotex_depos has the information for depos
input_readers:
graph_reader and passenger_reader cycle through input_files and create a vektory that can be used later on
input_readers is a header file what can be imported in from other programs located inside same project
util_functions:
useful formulas used to make all sorts of calculations, how to place passengers and depos, roads and crossovers onto map
graph_builder:
map_to_graph takes .osm.pbf file and makes a graph out of it. Graph_file_writer takes in a graph file and makes a  .txt file out of it.
main and graph_handlers:
imports in all the programs mentioned before and makes a complete graph out of it to calculate optimal route to get the best ride_value out of data that was given to us.
>>>>>>> 3c1521e2fce3c614a3b548fff621502ad78aed9f
