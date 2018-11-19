#include <bits/stdc++.h>
#include "../util_functions/util_functions.hpp"
#include "../input_readers/input_readers.hpp"
#include "../graph_handlers/graph_handlers.hpp"

int total_cars = 9990;
double car_speed = 50 / 3.6; //m/s
double rider_decay = 3 * 60; //s
double max_destination_time = 30 * 60; //s
int number_of_passenger_seats = 4;

int main(){
	std::cout << "started reading graph file \n";
	read_graph_file();

	std::cout << "started getting graph \n";
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * map_graph_pointer = get_file_graph();

	std::cout << "started getting passengers \n";
	std::vector<passenger_data> all_passengers = get_passengers();

	std::cout << "started getting depos \n";
	vector<depo_data> all_depos = get_depos();
	
	std::cout << "started adding depos \n";
	add_depos_to_graph(map_graph_pointer, &all_depos);

	std::cout << "started iterating depos \n";
	std::vector<a_star_instance> depos_a_stars;
	int depo_nr = 0;
	int total_id = 0;
	for(std::vector<depo_data>::iterator all_depos_i = all_depos.begin(); all_depos_i != all_depos.end(); all_depos_i++){
		for(unsigned int cur_id = 0; cur_id < total_cars / all_depos.size(); cur_id++){
			car_data new_car;
			new_car.id = total_id;
			total_id++;
			all_depos_i->cars.push_back(new_car);
		}
		a_star_instance new_depo_a_star;
		new_depo_a_star.set_start(std::make_pair(all_depos_i->lat, all_depos_i->lon), map_graph_pointer);
		depos_a_stars.push_back(new_depo_a_star);
		depo_nr++;
	}

	for(auto depo: all_depos){
		std::cout << "depo at: " << depo.lat << " , " << depo.lon << " nodes: " << depo.nodes.size() << " cars: " << depo.cars.size() << "\n";
	}

	std::cout << "started iterating passengers \n";
	int unconnected_passengers = 0;
	int early_passengers = 0;
	long int
	for(std::vector<passenger_data>::iterator all_passengers_i = all_passengers.begin(); all_passengers_i != all_passengers.end(); all_passengers_i++){
		std::cout << "adding passenger: " << all_passengers_i->epoch_time << "\n";
		add_passenger_to_graph(map_graph_pointer, &(*all_passengers_i));
		if(all_passengers_i->start_nodes.size() > 0 && all_passengers_i->end_nodes.size() > 0){
			int best_depo;
			double best_distance = DBL_MAX;
			for(unsigned int depo_id = 0; depo_id < all_depos.size(); depo_id++){
				double new_distance = haversine_distance(all_passengers_i->start_lat, all_passengers_i->start_lon, all_depos[depo_id].lat, all_depos[depo_id].lon);
				if(new_distance < best_distance){
					best_depo = depo_id;
					best_distance = new_distance;
				}
			}
			std::cout << "\tcalculating distance to drive \n";
			std::cout << "best depo: " << best_depo << "\n";
			double distance_to_drive = depos_a_stars[best_depo].get_distance_to(std::make_pair(all_passengers_i->start_lat, all_passengers_i->start_lon));
			double time_to_drive = distance_to_drive / car_speed;
			if(time_to_drive > rider_decay){
				std::cout << "\tadding early deploy time \n";
				all_passengers_i->deploy_early = time_to_drive - rider_decay;
				early_passengers++;
			}
		}else{
			unconnected_passengers++;
			std::cout << "\tunconnectable passenger \n";
		}
		std::cout << "\tdeleting passenger \n";
		remove_passanger_from_graph(map_graph_pointer, &(*all_passengers_i));
	}
	std::cout << "total unconnected passengers: " << unconnected_passengers << "\n";
	std::cout << "total early passengers: " << early_passengers << "\n";

	int counter = 0;
	for(auto passenger: all_passengers){
		if(passenger.start_nodes.size() == 0 || passenger.end_nodes.size() == 0){
			counter++;
			//std::cout << "passenger start: " << passenger.start_lat << " , " << passenger.start_lon << " nodes: " << passenger.start_nodes.size() << "\n";
			//std::cout << "passenger end: " << passenger.end_lat << " , " << passenger.end_lon << " nodes: " << passenger.end_nodes.size() << "\n";
		}
	}
	std::cout << "total unconnected passengers: " << counter << "\n";
}
