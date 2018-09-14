#include <bits/stdc++.h>
#include "../util_functions/data_types.h"

long int epoch_time_converter(std::string target_time){
	std::tm t = {};
    std::istringstream ss(target_time);

    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&t);
}


std::vector<passenger_data> get_passengers(){
	std::ifstream input_file("../input_files/robotex2.csv");
	std::string input_line;
	std::getline(input_file, input_line);
	std::vector<passenger_data> output_vector;
	while(std::getline(input_file, input_line)){
		std::istringstream input_line_stream(input_line);
		
		std::string line_part;
		passenger_data current_passenger;
		
		std::getline(input_line_stream, line_part, ',');
		current_passenger.epoch_time = epoch_time_converter(line_part);
		
		std::getline(input_line_stream, line_part, ',');
		current_passenger.start_lat = std::stod(line_part);
		
		std::getline(input_line_stream, line_part, ',');
		current_passenger.start_lon = std::stod(line_part);
		
		std::getline(input_line_stream, line_part, ',');
		current_passenger.end_lat = std::stod(line_part);
		
		std::getline(input_line_stream, line_part, ',');
		current_passenger.end_lon = std::stod(line_part);
		
		std::getline(input_line_stream, line_part, ',');
		current_passenger.ride_value = std::stod(line_part);
		
		output_vector.push_back(current_passenger);
	}
	
	/*for(auto current_passanger : output_vector){
		std::cout 	<< current_passanger.epoch_time << " , " 
					<< current_passanger.start_lat << " , " 
					<< current_passanger.start_lon << " , " 
					<< current_passanger.end_lat << " , " 
					<< current_passanger.end_lon << " , " 
					<< current_passanger.ride_value << "\n";
	}*/
	return output_vector;
}
