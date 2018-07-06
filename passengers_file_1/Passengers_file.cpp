

#include "passenger_info.h" 
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

extern passenger_data passenger;

int lines = 10; // amount of lines 420001

string sissetulev_rida;

vector < passenger_data > passengers; //teen uue vektori

string most_of_data;

string time_of_year;

string epoch_string;

string start_time;

string lane_to_print;

string str_aasta;

string str_kuu;

string str_paev;

string str_tund;

string str_minut;

string str_sekund;


int amount_of_days;

int aasta;

int kuu;

int paev;

int tund;

int minut;

double sekund;

int passenger_information() {

	ifstream inFile;
	inFile.open("robotex2.csv"); //avan faili
	ifstream ifs("robotex2.csv"); //analüüsib seda faili
	ifs >> sissetulev_rida;

	for (int i = 0; i < lines; ++i) { //vaatab read läbi(420000 tk)

		passenger_data passenger;

		ifs >> sissetulev_rida; //string >> siin saan kätte kuupäeva
		time_of_year = sissetulev_rida;

		ifs >> sissetulev_rida; //string >> siin saan kätte start_time,start_lat,start_lng,end_lat,end_lng,ride_value
		most_of_data = sissetulev_rida;

		start_time =


			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); // new string

		passenger.start_lat =
			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); // new string

		passenger.start_lng =
			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); // new string

		passenger.end_lat =
			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); // new string

		passenger.end_lng =
			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); // new string

		passenger.ride_value =
			sissetulev_rida.substr(0, sissetulev_rida.find(",", 0));

		sissetulev_rida = sissetulev_rida.substr(sissetulev_rida.find(",", 0) + 1, sissetulev_rida.length()); // new string

		epoch_string = time_of_year + "-" + start_time;

		str_aasta = epoch_string.substr(0, epoch_string.find("-", 0));
		epoch_string = epoch_string.substr(epoch_string.find("-", 0) + 1, epoch_string.length()); // new string

		str_kuu = epoch_string.substr(0, epoch_string.find("-", 0));
		epoch_string = epoch_string.substr(epoch_string.find("-", 0) + 1, epoch_string.length()); // new string

		str_paev = epoch_string.substr(0, epoch_string.find("-", 0));
		epoch_string = epoch_string.substr(epoch_string.find("-", 0) + 1, epoch_string.length()); // new string

		str_tund = epoch_string.substr(0, epoch_string.find(":", 0));
		epoch_string = epoch_string.substr(epoch_string.find(":", 0) + 1, epoch_string.length()); // new string

		str_minut = epoch_string.substr(0, epoch_string.find(":", 0));
		epoch_string = epoch_string.substr(epoch_string.find(":", 0) + 1, epoch_string.length()); // new string

		str_sekund = epoch_string;

		int aasta = stoi(str_aasta);
		int kuu = stoi(str_kuu);
		int paev = stoi(str_paev);
		int tund = stoi(str_tund);
		int minut = stoi(str_minut);
		double sekund = stod(str_sekund);

		int leap_years = 99;

		if (int aasta = 2020) {
			leap_years = leap_years + 1;
			if (int aasta = 2024) {
				leap_years = leap_years + 1;
				if (int aasta = 2028) {
					leap_years = leap_years + 1;
					if (int aasta = 2032) {
						leap_years = leap_years + 1;

					}


				}


			}


		}



		if (int kuu = 1) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400;

		}
		if (int kuu = 2) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 31 * 86400;

		}
		if (int kuu = 3) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 59 * 86400;

		}
		if (int kuu = 4) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 90 * 86400;

		}
		if (int kuu = 5) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 120 * 86400;

		}
		if (int kuu = 6) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 151 * 86400;

		}
		if (int kuu = 7) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 181 * 86400;

		}
		if (int kuu = 8) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 212 * 86400;

		}
		if (int kuu = 9) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 243 * 86400;

		}
		if (int kuu = 10) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 273 * 86400;

		}
		if (int kuu = 11) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 304 * 86400;

		}
		if (int kuu = 12) {

			passenger.epoch_time = sekund + minut * 60 + tund * 3600 + (paev - 1) * 86400 + (aasta - 1971) * 31536000 + leap_years * 86400 + 334 * 86400;

		}


		lane_to_print = ("   start lat: " + passenger.start_lat + "   start lng: " + passenger.start_lng + "   end lat: " + passenger.end_lat + "   end lng: " + passenger.end_lng + "  ride value: " + passenger.ride_value);
		std::cout << std::setprecision(22) << std::showpoint << std::fixed;
		cout << passenger.epoch_time << endl;

		passengers.push_back(passenger);

	}

}
