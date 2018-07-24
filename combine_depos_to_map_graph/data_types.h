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

#endif
