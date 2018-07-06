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

std::map<osmium::Location, std::map<osmium::Location, double> > road_graph;
    

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
		    	std::cout << "way " << way.id() << '\n';
		    	for(int i=0; i<road.size()-1; i++){//const auto& n : road
		    		osmium::NodeRef& node0 = road[i];
		    		osmium::NodeRef& node1 = road[i+1];
		    		std::cout << "\t" << node0.ref() << ": " << node0.lon() << ", " << node0.lat() << '\n';
					
					road_graph[node0.location()][node1.location()] = haversine_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
					road_graph[node1.location()][node0.location()] = haversine_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
				}
		    }
		}
    }
};


int main() {
	//std::cout << "Hello world!" << "\n";
	//std::cout << haversine_distance(58.5962, 24.9571, 58.5962, 24.9574) << "\n";
	
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
    
    for(auto start_node : road_graph){
    	std::cout << start_node.first << "\n";
    	for(auto end_node : start_node.second){
    		std::cout << "\t" << end_node.first << " - " << end_node.second << "\n";
    	}
    }
}
