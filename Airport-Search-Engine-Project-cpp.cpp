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

	int choice;

	do {
		cout << "\n ~*~*~*~*~ Airport Serch Engine ~*~*~*~*~\n";
		cout << " 1. Search Airports by Country" << endl;
		cout << " 2. Display all airports" << endl;
		cout << " 3. Show total number of airports" << endl;
		cout << " 4. Exit" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;

		switch (choice) { //wybiera co zrobic w zaleznosci od opcji
		case 1: {
			string country;
			cout << "Enter country code (e.g. GB, US): ";
			cin >> country;

			manager.searchByCountry(country);
			break;
		}
		case 2:
			manager.displayAll();
			break;
		case 3:
			cout << "Total airports: " << manager.airports.size() << endl;
			break;
		case  4:
			cout << " Exiting program..." << "\n" << "Thank you!" << endl;
			break;

		default:
			cout << "Invalid choice!" << endl;
		}

	}
			while (choice != 0);

			return 0;

 
}

