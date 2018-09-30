#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../input_readers/input_readers.hpp"
#include "../graph_handlers/graph_handlers.hpp"
//#include "../graph_handlers/graph_passengers_handler.cpp"

int total_cars = 9990;
double car_speed = 50; //km/s
double rider_decay = 3; //min
int number_of_passenger_seats = 4;

bool check_car(
			car_data * car_pointer,
			passenger_data * passenger_pointer,
			vector<depo_data> depos,
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer){
	a_star_instance car_path;
	std::pair<double, double> passenger_start 	= std::make_pair(passenger_pointer->start_lat, 	passenger_pointer->start_lon);
	std::pair<double, double> passenger_end 	= std::make_pair(passenger_pointer->end_lat, 	passenger_pointer->end_lon);
	car_path.set_start(passenger_start, map_graph_pointer);
	double total_distance = 0;
	total_distance += car_path.get_distance_to(car_pointer->location);
	total_distance += car_path.get_distance_to(passenger_end);
	a_star_instance path_to_depo;
	path_to_depo.set_start(passenger_end, map_graph_pointer);
	double best_dist = DBL_MAX;
	depo_data best_depo;
	for(depo_data depo : depos){
		std::pair<double, double> depo_loc = std::make_pair(depo.lat, depo.lon);
		double depo_dist = path_to_depo.get_distance_to(depo_loc);
		if(depo_dist < best_dist){
			best_depo = depo;
			best_dist = depo_dist;
		}
	}
	total_distance += best_dist;
	if(car_pointer->battery >= total_distance || car_pointer->current_passengers.size() == number_of_passenger_seats){
		
	}else{
		car_pointer->usable = false;
	}
}

int main(){
	//add_depos_to_graph();

	std::cout << "started reading graph file \n";
	read_graph_file();

	std::cout << "started getting graph \n";
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer = get_file_graph();

	std::cout << "started getting passengers \n";
	std::vector<passenger_data> all_passengers = get_passengers();

	std::cout << "started getting depos \n";
	vector<depo_data> all_depos = get_depos();
	
	std::cout << "started adding depos \n";
	add_depos_to_graph(&map_graph, &all_depos);
	std::cout << "finished adding depos \n";

	std::vector<car_data> all_cars;
	for(int cur_id = 0; cur_id < total_cars; cur_id++){
		car_data new_car;
		new_car.id = cur_id;
		all_cars.push_back(new_car);
	}
	

	int depo_nr = 0;	
	for(auto current_depo : all_depos){
		std::cout << "depo: " << current_depo.lat << " , " << current_depo.lon << " nodes: " << current_depo.nodes.size() << "\n";
		for(unsigned int car_nr = 0; car_nr < (total_cars / all_depos.size()); car_nr++){
			//std::cout << "car nr: " << int(depo_nr * total_cars / all_depos.size() + car_nr) << "\n";
			all_cars[int(depo_nr * total_cars / all_depos.size() + car_nr)].location = std::make_pair(current_depo.lat, current_depo.lon);
		}
		depo_nr++;
	}
	
	
	for(passenger_data current_passenger : all_passengers){
		std::pair<double, double> start_loc = std::make_pair(current_passenger.start_lon, current_passenger.start_lat);

		a_star_instance a_star_passenger;
		a_star_passenger.set_start(start_loc, map_graph_pointer);

		double closest_distance = DBL_MAX;
		car_data * best_car;
		std::vector<std::pair<double, double> > best_path;		
		bool best_at_depo = true;
		bool best_charging = true;
		
		for(car_data current_car : all_cars){
			if(current_car.usable){
				double car_distance = a_star_passenger.get_distance_to(current_car.location);
				if(car_distance <= car_speed * 1000 / 60 * rider_decay){
					if(!(current_car.at_depo) && best_at_depo){
						
					}
					/*
					if(current_car.at_depo){
						if(car_distance < closest_distance){
							closest_parked_distance = car_distance;
							best_parked_car = &current_car;
						}
					}
					*/
				}
			}
		}
	}
	

	int unused_cars = 0;
	for(car_data current_car : all_cars){
		if(current_car.passenger_log.empty()){
			unused_cars++;
		}
	}

	std::cout << "TOTAL CARS NEEDED: " << total_cars - unused_cars << "\n";

	/*
	std::pair<double, double> last_loc;
	int last_total = 0;
	for(car_data current_car : all_cars){
		if(last_loc == current_car.location){
			last_total++;
		}else{
			std::cout << "loc: " << last_loc.first << " , " << last_loc.second << " cars: " << last_total << "\n";
			last_loc = current_car.location;
			last_total = 0;
		}
	}
	*/	
	
	/*
	std::vector<std::pair<double, double> > my_path;
	double my_length;
	add_passenger_to_graph(map_graph_pointer, &(all_passengers[0]));
	//std::cout << std::boolalpha;
	std::cout << "passenger nodes: " << all_passengers[0].start_nodes.size() << " , " << all_passengers[0].end_nodes.size() << "\n";
	std::cout << "start loc: " << all_passengers[0].start_lat << " , " << all_passengers[0].start_lon << "\n";
	bool start_is = map_graph_pointer->find(std::make_pair(all_passengers[0].start_lat, all_passengers[0].start_lon)) 	!= map_graph_pointer->end();
	bool end_is = 	map_graph_pointer->find(std::make_pair(all_passengers[0].end_lat, 	all_passengers[0].end_lon))  	!= map_graph_pointer->end();
	std::cout << "start connected: " << std::boolalpha 	<< start_is << "\n";	
	std::cout << "end loc: " << all_passengers[0].end_lat << " , " << all_passengers[0].end_lon << "\n";
	std::cout << "end connected: " << std::boolalpha << start_is << "\n";

	a_star(	std::make_pair(all_passengers[0].start_lat, all_passengers[0].start_lon), 
			std::make_pair(all_passengers[0].end_lat, all_passengers[0].end_lon),
			map_graph_pointer,
			&my_path,
			&my_length);
	
	std::cout << "path size: " << my_path.size() << " path length: " << my_length << "\n";
	*/


	return 0;
}
