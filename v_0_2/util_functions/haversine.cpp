#ifndef HAVERSINE_CPP
#define HAVERSINE_CPP

#include <bits/stdc++.h>

#include <math.h>
#include <cmath> 
#define earthRadiusM 6371000

// This function converts decimal degrees to radians
double deg2rad(double deg) {
  return (deg * M_PI / 180);
}

double haversine_distance(double lat1d, double lon1d, double lat2d, double lon2d) {
  double lat1r, lon1r, lat2r, lon2r, u, v;
  lat1r = deg2rad(lat1d);
  lon1r = deg2rad(lon1d);
  lat2r = deg2rad(lat2d);
  lon2r = deg2rad(lon2d);
  u = sin((lat2r - lat1r)/2);
  v = sin((lon2r - lon1r)/2);
  return 2.0 * earthRadiusM * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

#endif
