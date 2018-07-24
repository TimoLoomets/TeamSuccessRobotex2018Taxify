#include <bits/stdc++.h>
#include "util_functions.hpp"
#include "data_types.h" 

double hav(double i){
	return sin(i/2)*sin(i/2);
}

//double hav_dist(

std::pair<double, double> lineLineIntersection(std::pair<double, double>  A, std::pair<double, double>  B, std::pair<double, double>  C, std::pair<double, double>  D)
{
    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1*(A.first) + b1*(A.second);
 
    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2*(C.first)+ b2*(C.second);
 
    double determinant = a1*b2 - a2*b1;
 
    if (determinant == 0)
    {
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return make_pair(FLT_MAX, FLT_MAX);
    }
    else
    {
        double x = (b2*c1 - b1*c2)/determinant;
        double y = (a1*c2 - a2*c1)/determinant;
        return make_pair(x, y);
    }
}

std::pair<double, double> get_closest_point(double Ax, double Ay, double Bx, double By, double Px, double Py)
{
	double APx = Px - Ax;
	double APy = Py - Ay;
	double ABx = Bx - Ax;
	double ABy = By - Ay;
	double magAB2 = ABx*ABx + ABy*ABy; 
	double ABdotAP = ABx*APx + ABy*APy;
	double t = ABdotAP / magAB2;  
 
	if ( t < 0){
        return std::make_pair(Ax, Ay);
  	}   
  	else if (t > 1){
        return std::make_pair(Bx, By);
  	}
  	else{
        return std::make_pair(Ax + ABx*t, Ay + ABy*t);
  	} 
}

double distance_on_line( double hypotenuse, double side){
	std::cout << "hypotenuse: " << hypotenuse << " cos: " << cos(hypotenuse) << "\n";
	std::cout << "side: " << side << " cos: " << cos(side) << "\n";
	
	return acos(cos(hypotenuse) / cos(side));
}

int main(){
	//road my_road = std::make_pair()
	std::pair<double, double> depo_loc = std::make_pair(59.372877000, 24.641514000);
	
	std::pair<double, double> my_point = get_closest_point(24.640451074, 59.372310801, 24.643245935, 59.373220858, 24.641514000,59.372877000);
	std::cout << "point: " << my_point.first << " , " << my_point.second << "\n";
	
	std::pair<double, double> n_my_point = std::make_pair(my_point.second, my_point.first);
	
	double distance_to_line = vincenty_distance(depo_loc, n_my_point);
	double radius = 50;
	
	double earth_radius = 6378137;
	
	double n_radius = radius/earth_radius;
	double n_dtl = distance_to_line/earth_radius;
	std::cout << "dist to line: " << distance_to_line << " dtl: " << n_dtl << "\n";
	double line_distance = distance_on_line(n_radius, n_dtl);
	
	std::cout << "distance on line: " << line_distance << "\n";
	
	//std::cout << vincenty_distance(59.372877000, 24.641514000, 59.372737137, 24.641690254) << "\n";
	//std::cout << vincenty_distance(59.372310801, 24.640451074, 59.372737137, 24.641690254) << "\n";
	//std::cout << vincenty_distance(59.372310801, 24.640451074, 59.372877000, 24.641514000) << "\n";
	//std::cout << hav(0) << "\n";
/*
	std::pair<long double, long double> centre = {59.383130159 * M_PI / 180, 24.706647992 * M_PI / 180};
	long double radius = 0.000000137;

	std::pair<long double, long double> coord1 = {59.383709353 * M_PI / 180, 24.707420468 * M_PI / 180};
	std::pair<long double, long double> coord2 = {59.382917057 * M_PI / 180, 24.705392718 * M_PI / 180}; 
	

	long double a = 	((coord1.first - coord2.first) / (coord1.second - coord2.second)) * 
						((coord1.first - coord2.first) / (coord1.second - coord2.second)) + 
						1;
				
	long double b = 	2 * 
						((coord1.first - coord2.first) / (coord1.second - coord2.second)) * 
						(coord1.first - ((coord1.first - coord2.first) / (coord1.second - coord2.second)) - centre.first) - 
						2;
				
	long double c = 	centre.second * centre.second - 
						radius * radius +
						(coord1.first - ((coord1.first - coord2.first) / (coord1.second - coord2.second)) - centre.first);
				
	long double ans1 = 	(-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	
	long double ans2 = 	((coord1.first - coord2.first) / (coord1.second - coord2.second)) * 
						ans1 +
						coord1.first -
						((coord1.first - coord2.first) / (coord1.second - coord2.second));

	std::cout << "a: " << a << "\n";
	std::cout << "b: " << b << "\n";
	std::cout << "c: " << c << "\n";
	
	std::cout << std::fmod(ans1 / M_PI * 180, 90) << "\n";
	std::cout << ans2 / M_PI * 180 << "\n";
*/
	return 0;
}
