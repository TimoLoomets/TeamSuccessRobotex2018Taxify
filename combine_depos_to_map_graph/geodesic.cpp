#include <bits/stdc++.h>

int main(){
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
}
