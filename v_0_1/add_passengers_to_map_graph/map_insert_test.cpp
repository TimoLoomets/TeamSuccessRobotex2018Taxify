#include <bits/stdc++.h>

void test1(){
	std::map<std::string, std::map<std::string, int> > my_map;
	std::map<std::string, std::map<std::string, int> > * my_map_pointer = &my_map;
	std::string key1 = "a";
	std::string key2 = "b";
	std::string key3 = "c";
	int value_to_insert = 9;
	
	my_map[key1][key2] = 7;
	
	my_map_pointer->find(key1)->second.insert(std::make_pair(key3, value_to_insert));
	
	std::cout << "my_map " << key1 << " " << key2 << " : " << my_map[key1][key2] << "\n";
	std::cout << "my_map " << key1 << " " << key3 << " : " << my_map[key1][key3] << "\n";
}

void test2(
			std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * my_map_pointer,
			std::pair<double, double> key1,
			std::pair<double, double> key3,
			double value_to_insert){
	
	if(my_map_pointer->find(key1) != my_map_pointer->end()){
		my_map_pointer->find(key1)->second.insert(std::make_pair(key3, value_to_insert));
	}else{
		my_map_pointer->insert(std::make_pair(key1, std::map<std::pair<double, double>, double>{{key3, value_to_insert}}));
	}
}

int main(){
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > my_map;
	std::map<std::pair<double, double>, std::map<std::pair<double, double>, double> > * my_map_pointer = &my_map;
	
	std::pair<double, double> key1 = std::make_pair(1.1, 1.2);
	std::pair<double, double> key2 = std::make_pair(2.1, 2.2);
	std::pair<double, double> key3 = std::make_pair(3.1, 3.2);
	double value_to_insert_2 = 7.4;
	double value_to_insert_3 = 9.5;
	
	test2(&my_map, key1, key2, value_to_insert_2);	
	test2(&my_map, key1, key3, value_to_insert_3);
	
	std::cout << "my_map " << key1.first << " , " << key1.second << " ; " << key2.first << " , " << key2.second << " : " << my_map[key1][key2] << "\n";
	std::cout << "my_map " << key1.first << " , " << key1.second << " ; " << key3.first << " , " << key3.second << " : " << my_map[key1][key3] << "\n";
	return 0;
}
