#include <bits/stdc++.h>

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

#include <osmium/relations/relations_manager.hpp>

#include "util_functions.hpp"

#define Tallinn_S 59.245521563
#define Tallinn_N 59.544064638
#define Tallinn_W 24.275665283
#define Tallinn_E 25.190277100

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > output_graph_doubles;
std::map<osmium::Location, std::map<osmium::Location, double> > output_graph;
std::set<road> map_roads;
  
/*  
void simplify_node(std::pair<osmium::Location, std::map<osmium::Location, double> > start_node){
	std::vector<std::pair<osmium::Location, double> > end_nodes;  
	for(auto end_node : start_node.second){
		end_nodes.push_back(end_node);
	}
	if(end_nodes.size() == 2){
		double distance = end_nodes[0].second + end_nodes[1].second;
		osmium::Location a = end_nodes[0].first;
		osmium::Location b = end_nodes[1].first;

		std::map<osmium::Location, double> temp;
		temp.insert(std::make_pair(end_nodes[1].first, distance));
		
		road_graph.insert(std::make_pair(end_nodes[0].first, temp));
		road_graph[end_nodes[1].first][end_nodes[0].first] = distance;
		road_graph.erase(start_node.first);
		//simplify_node(std::make_pair(end_nodes[0].first, road_graph[end_nodes[0].first]));
		//simplify_node(std::make_pair(end_nodes[1].first, road_graph[end_nodes[1].first]));
	}
}
*/ 
    

class MyHandler : public osmium::handler::Handler {
public:
    void way(const osmium::Way& way) {
		const char* highway = way.tags()["highway"];
		if(highway){
		    std::vector<osmium::NodeRef> road;
		    for (const auto& n : way.nodes()) {
		    	if(n.lat() > Tallinn_S && n.lat() < Tallinn_N && n.lon() > Tallinn_W && n.lon() < Tallinn_E){
		    		road.push_back(n);
		    	} 
		    }
		    if (road.size() != 0){
		    	//std::cout << "way " << way.id() << '\n';
		    	for(int i=0; i<road.size()-1; i++){
		    		osmium::NodeRef& node0 = road[i];
		    		osmium::NodeRef& node1 = road[i+1];
		    		//std::cout << "\t" << node0.ref() << ": " << node0.lon() << ", " << node0.lat() << '\n';
					
					map_roads.insert(std::make_pair(std::make_pair(node0.lat(), node0.lon()), std::make_pair(node1.lat(), node1.lon())));
					
					output_graph[node0.location()][node1.location()] = vincenty_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
					output_graph[node1.location()][node0.location()] = vincenty_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
					
					output_graph_doubles[std::make_pair(node0.lat(), node0.lon())][std::make_pair(node1.lat(), node1.lon())] = vincenty_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
					output_graph_doubles[std::make_pair(node1.lat(), node1.lon())][std::make_pair(node0.lat(), node0.lon())] = vincenty_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
				}
		    }
		}
    }
};


void calculate_map_graph_and_roads(){
    std::string input_file = "../input_files/estonia-latest.osm.pbf";
    
    
    auto otypes = osmium::osm_entity_bits::node | osmium::osm_entity_bits::way;
    osmium::io::Reader reader{input_file};

    using index_type = osmium::index::map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
    using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;

    index_type index;
    location_handler_type location_handler{index};

    MyHandler my_handler;
    osmium::apply(reader, location_handler, my_handler);
    reader.close();
    
    
    /*for(auto start_node : road_graph){
    	simplify_node(start_node);
    }*/
    
    
	/*std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > output_graph;
	
	for(auto start_node : output_graph){
		//std::cout << start_node.first << "\n";
		osmium::Location start_location = start_node.first;
		std::pair<double, double> start_location_o = std::make_pair(start_location.lat(), start_location.lon());
		for(auto end_node : start_node.second){
			//std::cout << "\t" << end_node.first << " - " << end_node.second << "\n";
			osmium::Location end_location = end_node.first;
			std::pair<double, double> end_location_o = std::make_pair(end_location.lat(), end_location.lon());
			output_graph[start_location_o][end_location_o] = end_node.second;
		}
	}*/
}

std::map<osmium::Location, std::map<osmium::Location, double> > get_map_graph() {return output_graph;}
std::set<road> get_map_roads() {return map_roads;}
std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > get_map_graph_doubles() {return output_graph_doubles;}

