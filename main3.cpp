#include <bits/stdc++.h>

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <osmium/io/any_input.hpp>
#include <osmium/visitor.hpp>
#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

#include "util_functions.hpp"

class MyHandler : public osmium::handler::Handler {
public:
    void way(const osmium::Way& way) {
		const char* highway = way.tags()["highway"];
		if(highway){
		    std::cout << "way " << way.id() << '\n';
		    for (const auto& n : way.nodes()) {
		        std::cout << "\t" << n.ref() << ": " << n.lon() << ", " << n.lat() << '\n';
		    }
		}
    }
};

int main() {
	//std::cout << "Hello world!" << "\n";
	//std::cout << haversine_distance(59.4832, 26.1045, 59.4847, 26.1036);
	
    auto otypes = osmium::osm_entity_bits::node | osmium::osm_entity_bits::way;
    osmium::io::Reader reader{"estonia-latest.osm.pbf", otypes};

    //namespace map = osmium::index::map;
    using index_type = osmium::index::map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
    using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;

    index_type index;
    location_handler_type location_handler{index};

    MyHandler handler;
    osmium::apply(reader, location_handler, handler);
    reader.close();
    
}
