#include "stdafx.h"
#include "passenger_info.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <locale>
#include <iomanip>
#include <time.h>
#include <stdio.h>

using namespace std;

extern passenger_data passenger;


string displayer()
{
	string kanapraad = (passenger.ride_value + "kapsas");
	return string (kanapraad);
}
