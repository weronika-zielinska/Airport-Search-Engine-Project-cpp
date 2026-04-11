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
		cout << "\n ~*~*~*~*~ AIRPORT SEARCH ENGINE ~*~*~*~*~\n";
		cout << " 1. Search airports by country" << endl;
		cout << " 2. Search airports by name" << endl;
		cout << " 3. Search by IATA code" << endl;
		cout << " 4. Display all airports" << endl;
		cout << " 5. Count airports by type" << endl;
		cout << " 6. Add new airport" << endl; 
		cout << " 7. Save changes to CSV file" << endl; // you can add few airports and after just save all to csv
		cout << " 8. Advanced options" << endl;
		cout << " 9. Exit" << endl;
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
			manager.addAirport();
			break;

		case 7: 
			manager.saveToCSV("airport-codes-updated.csv");
			break;

		case 8: {
			int advChoice;

			do {
				cout << " ~*~*~*~*~*~ ADVANCED OPTIONS ~*~*~*~*~ " << endl;;
				cout << " 1. Sort airports by name" << endl;
				cout << " 2. Sort airports by country" << endl;
				cout << " 3. Sort airports by type" << endl;
				cout << " 4. Sort airports by elevation" << endl;
				cout << " 5. Highest elevation airport" << endl;
				cout << " 6. Lowest elevation airport" << endl;
				cout << " 7. Show airports with missing IATA codes" << endl;
				cout << " 8. Back" << endl;
				cout << " Enter your choice: ";
				cin >> advChoice;

				switch (advChoice) {
				case 1:
					manager.sortByName();
					manager.printFirstN(5);
					break;

				case 2:
					manager.sortByCountry();
					manager.printFirstN(5);
					break;

				case 3:
					manager.sortByType();
					manager.printFirstN(5);
					break;

				case 4:
					manager.sortByElevation();
					manager.printFirstN(5);
					break;

				case 5:
					manager.highestElevation();
					break;

				case 6:
					manager.lowestElevation();
					break;

				case 7:
					manager.missingIATA();
					break;

				case 8:
					cout << "Returning to main menu..." << endl;
					break;

				default:
					cout << "Invalid choice!" << endl; 
				}
			} while (advChoice != 8);
			break;
		}

		case 9:
			cout << " Exiting program..." << "\n" << "Thank you!" << endl;
			break;

		default:
			cout << "Invalid choice!" << endl;
		}

	}
			while (choice != 9);

			return 0;

 
}

