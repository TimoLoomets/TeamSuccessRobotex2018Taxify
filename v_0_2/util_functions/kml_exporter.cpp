#ifndef KML_EXPORTER_CPP
#define KML_EXPORTER_CPP

#include <bits/stdc++.h>

#include "data_types.h"

std::ofstream outfile ("output.kml");

void kml_start(){
	outfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	outfile << "<kml xmlns=\"http://earth.google.com/kml/2.0\">\n";
	outfile << "\t<Document>\n";
}

void kml_end(){
	outfile << "\t</Document>\n";
	outfile << "</kml>";
	outfile.close();
}

void kml_point(std::pair<double, double> point){
	outfile << "\t\t<Placemark>\n";
	outfile << "\t\t\t<Point>\n";
	outfile << "\t\t\t\t<coordinates>" << point.second << ", " << point.first << ", 0</coordinates>\n";
	outfile << "\t\t\t</Point>\n";
	outfile << "\t\t</Placemark>\n";
}

void kml_road(road my_road){
	outfile << "\t\t<Placemark>\n";
	outfile << "\t\t\t<LineString>\n";
	outfile << "\t\t\t\t<coordinates>\n";
	outfile << "\t\t\t\t\t"<< my_road.first.second << "," << my_road.first.first << ",400\n";
	outfile << "\t\t\t\t\t"<< my_road.second.second << "," << my_road.second.first << ",400\n";
	outfile << "\t\t\t\t</coordinates>\n";
	outfile << "\t\t\t</LineString>\n";
	outfile << "\t\t</Placemark>\n";
}
/*
int main(){
	kml_start();
	
	kml_point(std::make_pair(1,2));
	kml_road(std::make_pair(std::make_pair(1,2),std::make_pair(1,2)));
	
	kml_end();
}*/

#endif
