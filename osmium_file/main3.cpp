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
    
void simplify_node(std::pair<osmium::Location, std::map<osmium::Location, double> > start_node){
	std::cout << "c1" << "\n";
	std::vector<std::pair<osmium::Location, double> > end_nodes;  
	std::cout << "c2" << "\n";
	for(auto end_node : start_node.second){
		std::cout << "c3" << "\n";
		end_nodes.push_back(end_node);
		std::cout << "c4" << "\n";
	}
	if(end_nodes.size() == 2){
		std::cout << "c5" << "\n";
		double distance = end_nodes[0].second + end_nodes[1].second;
		std::cout << "c6" << "\n";
		osmium::Location a = end_nodes[0].first;
		std::cout << "c6.0" << "\n";
		osmium::Location b = end_nodes[1].first;
		std::cout << "c6.1" << "\n";
		std::cout << a << b << "\n";
		std::cout << "c6.2" << "\n";
		for(auto elem : road_graph[end_nodes[0].first]){
			std::cout << elem.first << " : " << elem.second;
		}
		std::cout << "c6.3" << "\n";
//		road_graph[end_nodes[0].first][end_nodes[1].first] = distance;

		std::map<osmium::Location, double> temp;
		temp.insert(std::make_pair(end_nodes[1].first, distance));
		
		road_graph.insert(std::make_pair(end_nodes[0].first, temp));
		std::cout << "c7" << "\n";
		road_graph[end_nodes[1].first][end_nodes[0].first] = distance;
		std::cout << "c8" << "\n";
		road_graph.erase(start_node.first);
		std::cout << "c9" << "\n";
		simplify_node(std::make_pair(end_nodes[0].first, road_graph[end_nodes[0].first]));
		std::cout << "c10" << "\n";
		simplify_node(std::make_pair(end_nodes[1].first, road_graph[end_nodes[1].first]));
		std::cout << "c11" << "\n";
	}
}
    
    

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
					
					road_graph[node0.location()][node1.location()] = haversine_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
					road_graph[node1.location()][node0.location()] = haversine_distance(node0.lon(), node0.lat(), node1.lon(), node1.lat());
				}
		    }
		}
    }
};


int main() {
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
    	simplify_node(start_node);
    }
    
    int counter = 0;
    
    for(auto start_node : road_graph){
    	std::cout << start_node.first << "\n";
    	counter++;
    	for(auto end_node : start_node.second){
    		std::cout << "\t" << end_node.first << " - " << end_node.second << "\n";
    	}
    }
    std::cout << counter << "\n";
}