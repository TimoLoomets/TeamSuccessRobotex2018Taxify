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

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > output_graph;
std::vector<road> map_roads;
 
/*   
void simplify_node(std::pair<osmium::Location, std::map<osmium::Location, double> > start_node){//needs updating
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
		    bool out_of_tallinn = false;
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
		    		std::pair<double, double> loc0 = std::make_pair(vincenty_distance(node0.lat(), node0.lon(), 0, node0.lon()), vincenty_distance(node0.lat(), node0.lon(), node0.lat(), 0));
		    		std::pair<double, double> loc1 = std::make_pair(vincenty_distance(node1.lat(), node1.lon(), 0, node1.lon()), vincenty_distance(node1.lat(), node1.lon(), node1.lat(), 0));
					
					map_roads.push_back(std::make_pair(loc0, loc1));
					
					output_graph[loc0][loc1] = vincenty_distance(node0.lat(), node0.lon(), node1.lat(), node1.lon());
					output_graph[loc1][loc0] = vincenty_distance(node0.lat(), node0.lon(), node1.lat(), node1.lon());
				}
		    }
		}
    }
};


void calculate_map_graph_and_roads() {
    std::string input_file = "estonia-latest.osm.pbf";
    
    
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
    
	/*
	int counter = 0;
	
	std::cout << std::fixed << std::setprecision(0);
	for(auto start_node : output_graph){
		std::cout << start_node.first.first << " , " << start_node.first.second << "\n";
		counter++;
		for(auto end_node : start_node.second){
			std::cout << "\t" << end_node.first.first << " , " << end_node.first.second << " - " << end_node.second << "\n";
		}
	}
	std::cout << counter << "\n";
	*/
}

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > get_map_graph() {return output_graph;}
std::vector<road> get_map_roads() {return map_roads;}

