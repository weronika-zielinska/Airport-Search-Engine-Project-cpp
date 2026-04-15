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
		cout << " 8. Delete airport drom CSV by ident" << endl;
		cout << " 9. Advanced options" << endl;
		cout << " 10. Exit" << endl;
		cout << "Enter your choice: " << endl;
		cin >> choice;

		//uzywamy metod z <iostream> zeby dodac validation
		if (cin.fail()) { // sprawdza czy wpisana wartosc byla zla, jak zla to wchodzi w stan bledu
			cin.clear(); //resetuje stan bledu
			cin.ignore(1000, '\n'); // wyrzuca z bufora zle dane do konca linii
			// 1000 - ignoruje do 1000 znakow, max liczba znakow do usuniecia
			// \n - do momentu napotkania na enter, nowej linni
			cout << "Invalid input. Please enter a number." << endl;
			continue;
		}
		cin.ignore(); // jak poprawna liczba to ignoruje enter

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
			getline(cin, name); // to search more than 1 word

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
			string id;
			cout << "Enter airport ident to delete: ";
			cin >> id;

			manager.deleteByIdent(id);
			break;
		}

		case 9: {
			int advChoice;

			do {
				cout << " ~*~*~*~*~*~ ADVANCED OPTIONS ~*~*~*~*~ " << endl;;
				cout << " 1. Sort airports by name" << endl;
				cout << " 2. Sort airports by country" << endl;
				cout << " 3. Filter airports by type and sort alphabetically" << endl;
				cout << " 4. Sort airports by elevation" << endl;
				cout << " 5. Highest elevation airport" << endl;
				cout << " 6. Lowest elevation airport" << endl;
				cout << " 7. Show airports with missing IATA codes" << endl;
				cout << " 8. Show airports by municipality" << endl;
				cout << " 9. Show unique airport types: " << endl;
				cout << " 10. Count airports by country" << endl;
				cout << " 11. Back to main menu" << endl;
				cout << " Enter your choice: ";
				cin >> advChoice;

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input. Please enter a number." << endl;
					continue;
				}

				cin.ignore(1000, '\n');

				switch (advChoice) {
				case 1:
					manager.sortByName();
					manager.printFirstN(5);
					break;

				case 2:
					manager.sortByCountry();
					manager.printFirstN(5);
					break;

				case 3: {

					string type;
					cout << "Enter airport type:" << "\n";
					cout << "(small_airport / medium_airport / large_airport / heliport / seaplane_base / balloonport) : ";
					getline(cin, type);

					int option;
					cout << "How many results do you want to see?" << "\n";
					cout << "1. 5 results, \n2. 10 results \n3. 25 results \n4. All results" << endl;
					cout << "Enter your choice (1/2/3/4): ";
					cin >> option;

					cin.ignore(1000, '\n');

					int limit;

					switch (option) {
					case 1: limit = 5; break;
					case 2: limit = 10; break;
					case 3: limit = 25; break;
					case 4: limit = -1; break;
					default: limit = 5;
					}

					manager.showByType(type, limit);
					break;
				}

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

				case 8: {
					string municipality;
					cout << "Enter municipality: ";
					getline(cin, municipality);

					manager.showByMunicipality(municipality);
					break;
				}
					  
				case 9: 
					manager.showUniqueTypes();
					break;

				case 10: 
					manager.countByCountry();
					break;

				case 11:
					cout << "Returning to main menu..." << endl;
					break;

				default:
					cout << "Invalid choice!" << endl; 
				}
			} while (advChoice != 11);
			break;
		}

		case 10:
			cout << " Exiting program..." << "\n" << "Thank you!" << endl;
			break;

		default:
			cout << "Invalid choice!" << endl;
		}

	}
			while (choice != 10);

			return 0;

 
}

