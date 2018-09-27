#include "depos_header.h" 
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <locale>
#include <iomanip>
#include <time.h>
#include <stdio.h>

using namespace std;

extern depos_data cordinates;

int lines = 31; 

string sissetulev_rida;

string depos_lat_string;

string depos_lng_string;


vector <depos_data> depos_cor() {


	vector <depos_data> depos_cordinates;

	ifstream inFile;
	inFile.open("robotex-depos.csv"); //avan faili
	ifstream ifs("robotex-depos.csv"); //analüüsib seda faili
	ifs >> sissetulev_rida;
	
	for (int i = 0; i < lines; ++i) { 

		depos_data depos_information;

		ifs >> sissetulev_rida;

		depos_lat_string =
			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); 

		depos_lng_string = sissetulev_rida;

		cordinates.depo_lat = stold(depos_lat_string);

		cordinates.depo_lng = stold(depos_lng_string);
		
		cout << "rida : " << i << "			" << depos_lat_string << "    " << depos_lng_string << endl;

	}
	
	
	return depos_cordinates;
};