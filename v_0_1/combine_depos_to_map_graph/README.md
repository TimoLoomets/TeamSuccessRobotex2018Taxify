g++ main.cpp util_functions.hpp depos_header.h depos2.hpp --std=c++11 -lpthread -lz -lexpat -lbz2

g++ main2.cpp util_functions.hpp --std=c++17 -lpthread -lz -lexpat -lbz2 -pipe

g++ test_main.cpp --std=c++17 -lpthread -lz -lexpat -lbz2 -pipe
