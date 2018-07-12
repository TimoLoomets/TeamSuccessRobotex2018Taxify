#include <bits/stdc++.h>

#include "map_to_graph_2.cpp"

#define Tallinn_S 59.245521563
#define Tallinn_N 59.544064638
#define Tallinn_W 24.275665283
#define Tallinn_E 25.190277100
//1428921 - 1365523 = 63398
//6603278 - 6570020 = 33258
int main(){
	calculate_map_graph_and_roads();
	std::vector<road> map_roads = get_map_roads();
	
	std::cout << std::fixed << std::setprecision(0);
	std::cout << "WN" << vincety_distance(Tallinn_N, Tallinn_W, Tallinn_N, 0) << "\n";
	std::cout << "WS" << vincety_distance(Tallinn_S, Tallinn_W, Tallinn_S, 0) << "\n";
	std::cout << "SW" << vincety_distance(Tallinn_S, Tallinn_W, 0, Tallinn_W) << "\n";
	std::cout << "SE" << vincety_distance(Tallinn_S, Tallinn_E, 0, Tallinn_E) << "\n";
	//populate(map_roads, 1428921, 6603278
}
