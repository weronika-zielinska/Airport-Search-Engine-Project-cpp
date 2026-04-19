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
			cout << "\n----------------------------------------\n";
			cout << " Invalid input. Please eneter a number." << endl;
			cout << "----------------------------------------\n";
			option = 0;
			continue;
		}

		cin.ignore(1000, '\n');

		if (option < 1 || option >4) {
			cout << "\n----------------------------------------\n";
			cout << " Invalid choice. Please select 1, 2, 3 or 4. " << endl;
			cout << "----------------------------------------\n";
		}

	} while (option < 1 || option>4);


			switch (option) {
			case 1: return 5;
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

		//used method from <iostream> to add validation
		if (cin.fail()) { // check if value was wrong, if wrong then error
			cin.clear(); //reset error
			cin.ignore(1000, '\n'); // clear bufor - wrong data up to end of line
			// 1000 - ignore up to 1000 signs
			// \n - up to enter 
			cout << "\n----------------------------------------\n";
			cout << "Invalid input. Please enter a number." << endl;
			cout << "----------------------------------------\n";
			continue;
		}
		cin.ignore(1000, '\n'); // if good number then ignore enter

		switch (choice) { // choice to do
		case 1: {
			string country;
			cout << "----------------------------------------\n";
			cout << "Enter country code (e.g. GB, US): ";
			cin >> country;
			cout << "\n----------------------------------------\n";

			manager.searchByCountry(country);
			break;
		}
		case 2: {
			string name; //new variable to searching by name
			cout << "----------------------------------------\n";
			cout << "Enter part of airport name: ";
			getline(cin, name); // to search more than 1 word
			cout << "----------------------------------------\n";

			manager.searchByName(name);
			break;
		}

		case 3: {
			string iata; // new variable to searching by iata
			cout << "\n----------------------------------------\n";
			cout << "Enter IATA code (e.g. LHR, JFK): ";
			cin >> iata;;
			cout << "----------------------------------------\n";

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
				cout << " 9. Show unique airport types" << endl;
				cout << " 10. Count airports by country" << endl;
				cout << " 11. Back to main menu" << endl;
				cout << "---------------------------------------" << endl;
				cout << " Enter your choice: ";
				cin >> advChoice;
				cout << "\n";

				if (cin.fail()) {
					cin.clear();
					cin.ignore(1000, '\n');
					cout << "\n----------------------------------------\n";
					cout << "Invalid input. Please enter a number." << endl;
					cout << "----------------------------------------\n";
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
					cout << "\n----------------------------------------\n";
					cout << "Enter airport type:" << "\n";
					cout << "(small_airport / medium_airport / large_airport / heliport / seaplane_base / balloonport) : ";
					getline(cin, type);
					cout << "----------------------------------------\n";
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

				case 7: {
					int limit = askResultLimit();
					manager.missingIATA(limit);
					break;
				}

				case 8: {
					string municipality;
					cout << "\n----------------------------------------\n";
					cout << "Enter municipality: ";
					getline(cin, municipality);
					cout << "----------------------------------------\n";

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
					cout << "\n----------------------------------------\n";
					cout << "Returning to main menu..." << endl;
					cout << "----------------------------------------\n";
					break;

				default:
					cout << "\n----------------------------------------\n";
					cout << "Invalid choice!" << endl;
					cout << "----------------------------------------\n";
				}
			} while (advChoice != 11);
			break;
		}

		case 10: {
			char saveChoice;

			do {
				cout << "\n----------------------------------------\n";
				cout << "\nDo you want to save changes before exiting? (y/n): ";
				cin >> saveChoice;
				cout << "----------------------------------------\n";
				cin.ignore(1000, '\n');

				if (saveChoice != 'y' && saveChoice != 'Y' &&
					saveChoice != 'n' && saveChoice != 'N') {
					cout << "\n----------------------------------------\n";
					cout << "Invalid input. Please enter y or n." << endl;
					cout << "----------------------------------------\n";
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
			cout << "\n----------------------------------------\n";
			cout << " Invalid choice! " << endl;
			cout << "----------------------------------------\n";
		}


	} while (choice != 10);

	return 0;
}
