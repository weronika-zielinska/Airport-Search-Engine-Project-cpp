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

int askResultLimit() {
	int option;

	do {
		cout << "How many results do you want to see?" << endl;
		cout << "1. 5 results" << endl;
		cout << "2. 10 results" << endl;
		cout << "3. 25 results" << endl;
		cout << "4. All results" << endl;
		cout << "Enter your choice (1/2/3/4): ";
		cin >> option;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "---- Invalid input. Please eneter a number. ----" << endl;
			option = 0;
			continue;
		}

		cin.ignore(1000, '\n');

		if (option < 1 || option >4) {
			cout << "---- Invalid choice. Please select 1, 2, 3 or 4. ----" << endl;
		}

	} while (option < 1 || option>4);


			switch (option) {
			case1: return 5;
			case 2: return 10;
			case 3: return 25;
			case 4: return -1;
			}

			return -1;
	
}

int main()
{
	AirportManager manager;
	manager.loadFromCSV("airport-codes.csv");

	int choice;

	do {
		cout << "\n ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl;
		cout << "         AIRPORT SEARCH ENGINE       " << endl;
		cout << " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl;
		cout << " 1. Search airports by country" << endl;
		cout << " 2. Search airports by name" << endl;
		cout << " 3. Search by IATA code" << endl;
		cout << " 4. Display all airports" << endl;
		cout << " 5. Count airports by type" << endl;
		cout << " 6. Add new airport" << endl;
		cout << " 7. Delete airport by ident" << endl;
		cout << " 8. Save changes to CSV file" << endl; // you can add few airports and after just save all to csv
		cout << " 9. Advanced options" << endl;
		cout << " 10. Exit" << endl;
		cout << "---------------------------------------" << endl;
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
		cin.ignore(1000, '\n'); // jak poprawna liczba to ignoruje enter

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

		case 7: {
			string id;
			cout << "Enter airport ident to delete: ";
			cin >> id;

			manager.deleteByIdent(id);
			break;
		}

		case 8:
			manager.saveToCSV("airport-codes.csv");
			break;


		case 9: {
			int advChoice;

			do {
				cout << " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl;
				cout << "           ADVANCED OPTIONS         " << endl;
				cout << " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~" << endl;
				cout << " 1. Sort airports by name (alphabetical)" << endl;
				cout << " 2. Sort airports by country (alphabetical)" << endl;
				cout << " 3. Filter airports by type and sort alphabetically" << endl;
				cout << " 4. Sort airports by elevation (low to high)" << endl;
				cout << " 5. Highest elevation airport" << endl;
				cout << " 6. Lowest elevation airport" << endl;
				cout << " 7. Show airports with missing IATA codes" << endl;
				cout << " 8. Show airports by municipality" << endl;
				cout << " 9. Show unique airport types: " << endl;
				cout << " 10. Count airports by country" << endl;
				cout << " 11. Back to main menu" << endl;
				cout << "---------------------------------------" << endl;
				cout << " Enter your choice: ";
				cin >> advChoice;
				cout << "\n";

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input. Please enter a number." << endl;
					continue;
				}

				cin.ignore(1000, '\n');

				switch (advChoice) {
				case 1: {
					int limit = askResultLimit();
					manager.sortByName();
					manager.printFirstN(limit);
					break;
				}

				case 2: {
					int limit = askResultLimit();
					manager.sortByCountry();
					manager.printFirstN(limit);
					break;
				}

				case 3: {

					string type;
					cout << "Enter airport type:" << "\n";
					cout << "(small_airport / medium_airport / large_airport / heliport / seaplane_base / balloonport) : ";
					getline(cin, type);
					int limit = askResultLimit();
					
					manager.showByType(type, limit);
					break;
				}

				case 4: {
					int limit = askResultLimit();
					manager.sortByElevation();
					manager.printFirstN(limit);
					break;
				}

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

		case 10: {
			char saveChoice;

			do {
				cout << "\nDo you want to save changes before exiting? (y/n): ";
				cin >> saveChoice;
				cin.ignore(1000, '\n');

				if (saveChoice != 'y' && saveChoice != 'Y' &&
					saveChoice != 'n' && saveChoice != 'N') {
					cout << "Invalid input. Please enter y or n.\n";
				}

			} while (saveChoice != 'y' && saveChoice != 'Y' &&
				saveChoice != 'n' && saveChoice != 'N');

			if (saveChoice == 'y' || saveChoice == 'Y') {
				manager.saveToCSV("airport-codes.csv");
				cout << " ~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*~*" << endl;
			
			}
			cout << "\n";
			cout << "========================================\n";
			cout << "|                                      |\n";
			cout << "|             THANK YOU!               |\n";
			cout << "|                                      |\n";
			cout << "|   for using Airport Search Engine    |\n";
			cout << "|                                      |\n";
			cout << "|          Have a nice day :)          |\n";
			cout << "|                                      |\n";
			cout << "========================================\n";
			break;
		}
		default:
			cout << " ------- Invalid choice! ------" << endl;
		}


	} while (choice != 10);

	return 0;
}
