#include <bits/stdc++.h>

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

#include <osmium/relations/relations_manager.hpp>

#include "../util_functions/util_functions.hpp"

std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > output_graph_doubles;
std::map<osmium::Location, std::map<osmium::Location, double> > output_graph;
std::set<road> map_roads;

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
}

std::map<osmium::Location, std::map<osmium::Location, double> > get_map_graph() {return output_graph;}
std::set<road> get_map_roads() {return map_roads;}
std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > get_map_graph_doubles() {return output_graph_doubles;}

