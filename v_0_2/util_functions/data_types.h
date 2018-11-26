#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <bits/stdc++.h>

#define Tallinn_S 59.245521563
#define Tallinn_N 59.544064638
#define Tallinn_W 24.275665283
#define Tallinn_E 25.190277100
#define used_depth 9

typedef std::pair<std::pair<double, double>, std::pair<double, double> > road;

class passenger_data
{
public:
	long int epoch_time;
	double start_lat;
	double start_lon;
	double end_lat;
	double end_lon;
	double ride_value;	
	std::set<std::pair<double, double> > start_nodes;
	std::set<std::pair<double, double> > end_nodes;
	int on_board_timer = 0;
	int deploy_early = 0;
	bool in_car = false;
	long int epoch_start;
	long int epoch_end;
};

class car_data
{
public:
	int id;
	std::pair<double, double> location;
	std::set<passenger_data * > current_passengers;
	std::set<passenger_data * > passenger_log;
	int battery = 200000;
	std::vector<std::pair<double, double> > current_path;
	bool usable = true;
	bool at_depo = true;
	bool charging = false;
	int time = 0;
};

class depo_data 
{
public:
	double lat;
	double lon;
	std::set<std::pair<double, double> > nodes;
	bool normal = true;
	std::vector<car_data> cars;
};

#endif
