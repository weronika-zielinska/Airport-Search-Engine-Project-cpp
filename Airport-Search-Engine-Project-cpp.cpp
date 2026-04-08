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
		cout << " 1. Search airports by Country" << endl;
		cout << " 2. Search airports by name" << endl;
		cout << " 3. Search by IATA code" << endl;
		cout << " 4. Display all airports" << endl;
		cout << " 5. Count airports by type" << endl;
		cout << " 6. Exit" << endl;
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
		case 2: {
			string name; //nowy variables to szukania po nazwie
			cout << "Enter part of airport name: ";
			cin >> name;

			manager.searchByName(name);
			break;
		}
			
		case 3: {
			string iata; // nowy variables to iata
			cout << "Enter IATA code (e.g. LHR, JFK): ";
			cin >> iata;;

			manager.searchByIATA(iata);
			break;
		}

		case  4:
			manager.displayAll();
			break;

		case 5:
			manager.countByType();
			break;
		
		case 6:
			cout << " Exiting program..." << "\n" << "Thank you!" << endl;
			break;

		default:
			cout << "Invalid choice!" << endl;
		}

	}
			while (choice != 0);

			return 0;

 
}

