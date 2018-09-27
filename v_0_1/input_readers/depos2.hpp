#include "../util_functions/data_types.h" 

#include <bits/stdc++.h>

using namespace std;

vector <depo_data> get_depos() {
	vector <depo_data> depos_coordinates;
	depo_data coordinates;
	int lines = 30; 

	string sissetulev_rida;
	string depos_lat_string;
	string depos_lng_string;

	ifstream inFile;
	inFile.open("../input_files/robotex-depos.csv"); //avan faili
	ifstream ifs("../input_files/robotex-depos.csv"); //analüüsib seda faili
	ifs >> sissetulev_rida;
	
	for (int i = 0; i < lines; ++i) { 
		depo_data depos_information;
		ifs >> sissetulev_rida;
		
		depos_lat_string = sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));
		
		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); 
		
		depos_lng_string = sissetulev_rida;
		
		coordinates.lat = stold(depos_lat_string);
		coordinates.lon = stold(depos_lng_string);
		
		//cout << "rida : " << i << "			" << depos_lat_string << "    " << depos_lng_string << endl;
		depos_coordinates.push_back(coordinates);
	}
	return depos_coordinates;
}
