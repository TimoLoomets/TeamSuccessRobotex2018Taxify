#include "haversine.cpp"
#include "vincety.cpp"

#ifndef UTIL_FUNCTIONS_H
#define UTIL_FUNCTIONS_H
// This is the content of the .h file, which is where the declarations go
double haversine_distance(double lat1d, double lon1d, double lat2d, double lon2d);
double vincety_distance(double latitude_01, double longitude_01, double latitude_02, double longitude_02);
#endif

