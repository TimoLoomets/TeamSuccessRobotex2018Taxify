#include <iostream>

#include <osmium/io/any_input.hpp>
#include <osmium/io/any_output.hpp>






using namespace std;

int main()
{
    std::string file_name = "planet-latest.osm.pbf";
    osmium::io::File my_file = osmium::io::File(file_name);

    //osmium::io::Reader my_reader = osmium::io::Reader(my_file);

    //osmium::io::ReaderWithProgressBar my_reader = osmium::io::ReaderWithProgressBar(true, my_file);

    cout << "Hello world!" << endl;
    return 0;
}
