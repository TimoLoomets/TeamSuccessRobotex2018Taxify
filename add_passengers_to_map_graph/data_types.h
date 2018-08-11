#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <bits/stdc++.h>

typedef std::pair<std::pair<double, double>, std::pair<double, double> > road;

class depos_data 
{
public:
	double lat;
	double lon;
	std::set<std::pair<double, double> > nodes;
};

 class passenger_data
{
public:
	long int epoch_time;
	double start_lat;
	double start_lon;
	double end_lat;
	double end_lon;
	double ride_value;	
};

#endif
