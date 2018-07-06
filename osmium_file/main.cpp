#include <iostream>
#include <bits/stdc++.h>


#include <bzlib.h>
#include <osmium/io/any_input.hpp>

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/way.hpp>
#include <osmium/visitor.hpp>

#include <osmium/index/map/sparse_mem_array.hpp>
#include <osmium/handler/node_locations_for_ways.hpp>

class my_handler_class : public osmium::handler::Handler {
public:
    void way(const osmium::Way& way) {
        const char* highway = way.tags()["highway"];
        if(highway){
            std::cout << "way " << way.id() << '\n';
            for (const osmium::Tag& t : way.tags()) {
                std::cout << "\t" << t.key() << "=" << t.value() << '\n';
            }
            try{
                for (const osmium::NodeRef& node : way.nodes()){

                        std::cout << "\t" << node.ref() << " : " << node.lon() << ", " << node.lat() << "\n";

                    /*for (const osmium::Tag& t2 : node.tags()) {
                        std::cout << "\t\t" << t2.key() << "=" << t2.value() << '\n';
                    }*/
                }
            }
            catch(osmium::invalid_location){
                std::cout << "location not set" << "\n";
            }
        }
    }

    /*void node(const osmium::Node& node) {
        std::cout << "node " << node.id() << " : " << node.location() << '\n';
    }*/
};



using namespace std;

int main()
{
    std::map<unsigned int, std::vector<std::pair<unsigned int, unsigned int> > > my_graph;

    std::string file_name = "estonia-latest.osm.pbf";
    auto otypes = osmium::osm_entity_bits::way | osmium::osm_entity_bits::node;// |
    //osmium::io::File my_file{file_name};
    osmium::io::Reader my_reader{file_name, otypes};
    my_handler_class my_handler;


    namespace map = osmium::index::map;
    using index_type = map::SparseMemArray<osmium::unsigned_object_id_type, osmium::Location>;
    using location_handler_type = osmium::handler::NodeLocationsForWays<index_type>;

    index_type index;
    location_handler_type location_handler{index};


    osmium::apply(my_reader, my_handler, location_handler);


    //osmium::io::Reader my_reader = osmium::io::Reader(my_file);

    //osmium::io::ReaderWithProgressBar my_reader = osmium::io::ReaderWithProgressBar(true, my_file);

    cout << "Hello world2!" << endl;
    return 0;
}
