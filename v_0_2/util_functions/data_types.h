#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <bits/stdc++.h>

#define Tallinn_S 59.245521563
#define Tallinn_N 59.544064638
#define Tallinn_W 24.275665283
#define Tallinn_E 25.190277100
#define used_depth 9

typedef std::pair<std::pair<double, double>, std::pair<double, double> > road;

class depo_data 
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
	std::set<std::pair<double, double> > start_nodes;
	std::set<std::pair<double, double> > end_nodes;
};

#endif
