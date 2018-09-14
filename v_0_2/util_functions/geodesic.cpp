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
	//std::cout << "hypotenuse: " << hypotenuse << " cos: " << cos(hypotenuse) << "\n";
	//std::cout << "side: " << side << " cos: " << cos(side) << "\n";
	
	return acos(cos(hypotenuse) / cos(side));//sqrt((hypotenuse+1)*(hypotenuse-1)/(1-side)/(1+side)+1);////asin(sin(hypotenuse)*sin(acos(tan(side)/tan(hypotenuse))));//Napier's rules
}

double calculate_heading(double lat1, double long1, double lat2, double long2)
{
    double a = lat1 * M_PI / 180;
    double b = long1 * M_PI / 180;
    double c = lat2 * M_PI / 180;
    double d = long2 * M_PI / 180;

    if (cos(c) * sin(d - b) == 0)
        if (c > a)
            return 0;
        else
            return 180;
    else
    {
        double angle = atan2(cos(c) * sin(d - b), sin(c) * cos(a) - sin(a) * cos(c) * cos(d - b));
        return std::fmod((angle * 180 / M_PI + 360), 360);
    }
}

std::set<std::pair<double, double> > geodesic_intersections(std::pair<double, double> depo_loc, road my_road){
	std::set<std::pair<double, double> > output;
	//road my_road = std::make_pair()
	//std::pair<double, double> depo_loc = std::make_pair(59.372877000, 24.641514000);
	std::pair<double, double> road_A = my_road.first;//std::make_pair(59.373220858, 24.643245935);
	std::pair<double, double> road_B = my_road.second;//std::make_pair(59.372310801, 24.640451074);
	
	std::pair<double, double> my_point = get_closest_point(road_A.first, road_A.second, road_B.first, road_B.second, depo_loc.first, depo_loc.second);//24.640451074, 59.372310801, 24.643245935, 59.373220858, 24.641514000,59.372877000);
	//std::cout << "point: " << my_point.first << " , " << my_point.second << "\n";
	
	//std::pair<double, double> n_my_point = std::make_pair(my_point.second, my_point.first);
	
	double earth_radius = 6378137;
	
	
	if(vincenty_distance(depo_loc, my_point) <= 50){
		double distance_to_line = vincenty_distance(depo_loc, my_point) / earth_radius;
		double radius = 50 / earth_radius;
		
		//double n_radius = radius/earth_radius;
		//double n_dtl = distance_to_line/earth_radius;
		//std::cout << "dist to line: " << distance_to_line << " dtl: " << n_dtl << "\n";
		//double line_distance = distance_on_line(radius, distance_to_line);
		
		double my_heading_1 = calculate_heading(my_point.first, my_point.second, road_A.first, road_A.second);
		double my_heading_2 = calculate_heading(my_point.first, my_point.second, road_B.first, road_B.second);
		
		double line_distance = distance_on_line(radius, distance_to_line) * earth_radius;
		
		//std::cout << "distance on line: " << line_distance << "\n";
		//std::cout << "headings: " << my_heading_1 << " , " << my_heading_2 << "\n";
		
		const double halfC = M_PI / 180;
		std::pair<double, double> n_my_point = std::make_pair(my_point.first*halfC, my_point.second*halfC);
		
		std::pair<double, double> circle_point_1 = vincenty_location(n_my_point, my_heading_1*halfC, line_distance);
		std::pair<double, double> circle_point_2 = vincenty_location(n_my_point, my_heading_2*halfC, line_distance);

		//std::cout << "circle point 1: " << circle_point_1.first/halfC << " , " << circle_point_1.second/halfC << "\n";
		//std::cout << "circle point 2: " << circle_point_2.first/halfC << " , " << circle_point_2.second/halfC << "\n";
		
		output.insert(std::make_pair(circle_point_1.first/halfC, circle_point_1.second/halfC));
		output.insert(std::make_pair(circle_point_2.first/halfC, circle_point_2.second/halfC));
	}
	return output;
}
/*
int main(){
	road test_road = std::make_pair(std::make_pair(59.373220858, 24.643245935), std::make_pair(59.372310801, 24.640451074));
	std::pair<double, double> test_depo = std::make_pair(59.372877000, 24.641514000);

	vector<std::pair<double, double> > points = geodesic_intersections(test_depo, test_road);
	for(auto point : points){
		std::cout << "output points: " << point.first << " , " << point.second << "\n";
	}
}*/