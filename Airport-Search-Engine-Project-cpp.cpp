// Airport-Search-Engine-Project-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> //to work with files
#include <string>
#include <vector>
#include <sstream>
#include "Airport.h"
# include "AirportManager.h"
using namespace std;


int main()
{
	AirportManager manager;

	manager.loadFromCSV("airport-codes.csv");

	cout << "Loaded airports: " << manager.airports.size() << endl;
	
	for (int i = 0; i < 5 && i < manager.airports.size(); i++) {
		manager.airports[i].display();
	}

	return 0;
 
}

