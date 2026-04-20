#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Airport.h"
#include <algorithm>
#include <map>
#include <set>
#include <cctype>

using namespace std;

//change for small letters / lower case
string toLowerCase(string text) {
	transform(text.begin(), text.end(), text.begin(),
		[](unsigned char c) {return tolower(c); });
	return text;
}

string trim(const string& str) { //delete empty spaces from start and end
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");

	if (first == string::npos) return "";

	return str.substr(first, (last - first + 1));
}

string removeQuotes(string text) {  //daleting saved extra quotations
	if (!text.empty() && text.front() == '"') {
		text.erase(0, 1);
	}

	if (!text.empty() && text.back() == '"') {
		text.pop_back();
	}
	return text;
}

class AirportManager {  // class to manage all airports functions
private:
	vector <Airport> airports; // vector with all airports list
public:
	void loadFromCSV(const string& filename); // loading data from csv

	void displayAll() { // display from csv

		for (const auto& airport : airports) {
			airport.display();
		}
	}

	void searchByCountry(const string& countryCode);  //declarations
	void searchByName(const string& namePart);
	void searchByIATA(const string& iataCode);
	void countByType();
	void addAirport();
	void saveToCSV(const string& filename);
	void printFirstN(int n);
	void sortByName();
	void sortByCountry();
	void sortByType();
	void sortByElevation();
	void highestElevation();
	void lowestElevation();
	void missingIATA(int limit) const;
	void deleteByIdent(const string& ident);
	multimap <string, Airport> groupByMunicipality() const;
	void showByMunicipality(const string& municipality) const;
	void showUniqueTypes() const;
	void countByCountry() const;
	void showByType(const string& type, int limit) const;

};

// implementations
void AirportManager::loadFromCSV(const string& filename) {

	ifstream file(filename); //input file stream - reading csv

	if (!file.is_open()) { //check if file can be open
		cout << "\n----------------------------------------\n";
		cout << "Error! Could not open file!" << endl;
		cout << "----------------------------------------\n";
		return;
	}

	string line; // it will be safe line from csv

	getline(file, line); // we leave headers in csv

	while (getline(file, line)) {

		stringstream ss(line); // ss from <sstream> making data with pieces with ,
		string column; // to save one column of csv
		Airport airport; //new object airport

		getline(ss, airport.ident, ','); //ident

		getline(ss, airport.type, ',');  //type,  read csv up to comma and save in airport.type
		
		getline(ss, airport.name, ','); // name
		airport.name = removeQuotes(airport.name);

		getline(ss, column, ','); //elevation
		if (!column.empty()) {
			try {
				airport.elevation = stoi(column);
			}
			catch (...) {
				airport.elevation = 0;
			}
		}
		else {
			airport.elevation = 0;
		}

		getline(ss, airport.continent, ','); //continent 

		getline(ss, airport.country, ','); // country

		getline(ss, airport.region, ','); //  region 

		getline(ss, airport.municipality, ','); //municipality
		airport.municipality = removeQuotes(airport.municipality);

		getline(ss, airport.icao, ','); //ICAO 

		getline(ss, airport.iata, ','); // iata
	
		getline(ss, airport.gps, ','); //gps

		getline(ss, airport.localCode, ','); // local code

		//coordinates 
		getline(ss, column); //read from ss, save to column


		//column.empty - check if string its empty - true=empty, false=something inside
		//if string its not empty and first sign its "
		if (!column.empty() && column.front() == '"') {
			column.erase(0, 1); //erase- delate first sign so "
		}
		//column.back - back with last sign from string so "
		if (!column.empty() && column.back() == '"') {
			column.pop_back(); //delete last sign 
		}

		//looking for commas
		//size_t - nymber type - used to positions in string
		//commaPos - remember where is comma
		size_t commaPos = column.find(','); 

		//chceck if comma was found
		if (commaPos != string::npos) { //checking if there is comma, string::npos =? - means not found
			string lat = column.substr(0, commaPos); //take first coordinate from position 0 to comma
			string lon = column.substr(commaPos + 1); // take secon coordinate after comma

			try {
				airport.latitude = stod(lat); //convert string>double
				airport.longitude = stod(lon);
			}
			catch (...) {
				airport.latitude = 0;
				airport.longitude = 0;
			}
		}
		else {
			airport.latitude = 0;
			airport.longitude = 0;
		}
		airports.push_back(airport); //add airport to list vector<Airport> airports

	}
	file.close();
}


void AirportManager::searchByCountry(const string& countryCode) {
	
	bool found = false; //if there is any results
	string code = toLowerCase(countryCode);

	for (const auto& airport : airports) { // check all airports
		if (toLowerCase (airport.country) == code) { // check if country matching
			airport.display();
			found = true;
		}
	}

	if (!found) { // if its not found then print
		cout << "\n----------------------------------------\n";
		cout << "No airports found for country: " << countryCode << endl;
		cout << "----------------------------------------\n";
	}
}

void AirportManager::searchByName(const string& namePart) {
	bool found = false;
	string searchText = toLowerCase(namePart);

	for (const auto& airport : airports) {
		//check if any part of airport name its existing in file  
		// .find() - to find just parts of words
		if (toLowerCase(airport.name).find(searchText) != string::npos) { //npos - means found
			airport.display();
			found = true;
		}
	}
	if (!found) {
		cout << "\n----------------------------------------\n";
		cout << "No Airports matching the criteria: " << namePart << endl;
		cout << "----------------------------------------\n";
	}
}

void AirportManager::searchByIATA(const string& iataCode) {
	bool found = false;

	string code = toLowerCase(iataCode); // cleaning user input

	for (const auto& airport : airports) {
		if (toLowerCase (airport.iata) == code) { //looking exactly matching code
			airport.display();
			found = true;
		}
	}
	if (!found) {
		cout << "\n----------------------------------------\n";
		cout << " No airport found with IATA code: " << iataCode << endl;
		cout << "----------------------------------------\n";
	}
}

void AirportManager::countByType() { // using map - key-value container
	map <string, int> counts; //saving data because column 'type' its number 
	// key - string , value - int, map saving pairs of data (key, value)

	for (const auto& airport : airports) {
		counts[airport.type]++;  // if type dont exist then create it and increase number of 1
		cout << "---------------------------------------" << endl;
		cout << "        Airports by type:        " << endl;
		cout << "---------------------------------------" << endl;

		for (const auto& pair : counts) { //take every pair form map counts
			cout << left << setw(15) << pair.first << ": " << pair.second << endl; // going to 1st and 2nd element of pair 
		}
	}
}

void AirportManager::addAirport() {  //validation for text an numbers to avoid errors
	//adding to vector
	Airport airport;

	cout << "---------------------------------------\n";
	cout << "             ADD NEW AIRPORT\n";
	cout << "---------------------------------------\n";

	cout << "Enter ident: ";
	getline(cin, airport.ident);

	cout << "Enter type: ";
	getline(cin, airport.type);

	cout << "Enter name: ";
	getline(cin, airport.name);

	cout << "Enter elevation (ft): ";
	cin >> airport.elevation;
	while (cin.fail()) {  //wehn fail its true asking one more time
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\n----------------------------------------\n";
		cout << "Invalid input. Please enter a number for elevation: " << endl;;
		cout << "----------------------------------------\n";
		cin >> airport.elevation;
	}
	cin.ignore(1000, '\n'); // delate enter from bufor

	cout << "Enter continent: ";
	getline(cin, airport.continent);

	cout << "Enter country code: ";
	getline(cin, airport.country);

	cout << "Enter region code: ";
	getline(cin, airport.region);

	cout << "Enter municipality: ";
	getline(cin, airport.municipality);

	cout << "Enter ICAO code: ";
	getline(cin, airport.icao);

	cout << "Enter IATA code: ";
	getline(cin, airport.iata);

	cout << "Enter GPS code: ";
	getline(cin, airport.gps);

	cout << "Enter local code: ";
	getline(cin, airport.localCode);

	cout << "Enter latitude: ";
	cin >> airport.latitude;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\n----------------------------------------\n";
		cout << "Invalid input. Please enter a number for latitude: " << endl;
		cout << "----------------------------------------\n";
		cin >> airport.latitude;
	}
	cin.ignore(1000, '\n');

	cout << "Enter longitude: ";
	cin >> airport.longitude;
	while (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "\n----------------------------------------\n";
		cout << "Invalid input. Please enter a number for longitude: " << endl;
		cout << "----------------------------------------\n";
		cin >> airport.longitude;
	}
	cin.ignore(1000, '\n');

	airports.push_back(airport);

	cout << "\n========================================\n";
	cout << "|                                      |\n";
	cout << "|        *~* NEW AIRPORT ADDED *~*     |\n";
	cout << "|                                      |\n";
	cout << "|        Data saved successfully       |\n";
	cout << "|                                      |\n";
	cout << "========================================\n";
}

void AirportManager::saveToCSV(const string& filename) {
	ofstream file(filename);

		if (!file.is_open()) {
			cout << "\n----------------------------------------\n";
			cout << "Error! File could not be opened for saving." << endl;
			cout << "----------------------------------------\n";
			return;
		}
	//zapis naglowka csv
	file << "ident,type,name,elevation_ft,continent,iso_country,iso_region,municipality,icao_code,iata_code,gps_code,local_code,coordinates" << endl;

	for (const auto& airport : airports) {
		file << airport.ident << ",";
		file << airport.type << ",";
		file << "\"" << airport.name << "\"" << ","; 
		file << airport.elevation << ",";
		file << airport.continent << ",";
		file << airport.country << ",";
		file << airport.region << ",";
		file << "\"" << airport.municipality << "\"" << ",";
		file << airport.icao << ",";
		file << airport.iata << ",";
		file << airport.gps << ",";
		file << airport.localCode << ",";
		file << "\"" << airport.latitude << "," << airport.longitude << "\"" << endl;
	}

	file.close();
		cout << "\n========================================\n";
	cout << "|                                      |\n";
	cout << "|    *~* Data saved successfully *~*   |\n";
	cout << "|                                      |\n";
	cout << "|               Thank You!             |\n";
	cout << "|                                      |\n";
	cout << "========================================\n";
}

void AirportManager::printFirstN(int n) {  //writing fiirst N airports

	if (n == -1) {
		for (const auto& airport : airports) {
			airport.display();
		}
		return;
	}

	for (int i = 0; i < n && i < airports.size(); i++) {
		airports[i].display();
	}
}

void AirportManager::sortByName() {

	sort(airports.begin(), airports.end(), // sort - for vector sorting
		[](Airport a, Airport b) {  // lambda [] compare two airports
			return a.name < b.name; // sort alphabetically
		});
}

void AirportManager::sortByCountry() {

	sort(airports.begin(), airports.end(), //sort vector from first element to last element
		[](Airport a, Airport b) {
			return a.country < b.country;
		});
}

void AirportManager::sortByType() {

	sort(airports.begin(), airports.end(),
		[](Airport a, Airport b) {
			return a.type < b.type;
		});
}

void AirportManager::sortByElevation() {

	sort(airports.begin(), airports.end(),
		[](Airport a, Airport b) {
			return a.elevation < b.elevation;
		});
}

void AirportManager::highestElevation() {

	if (airports.empty()) {
		cout << "\n----------------------------------------\n";
		cout << "No airports loaded." << endl;
		cout << "----------------------------------------\n";
		return;
	}

	Airport highest = airports[0]; //take 1st airport and compare to next one

	for (const auto& airport : airports) {
		if (airport.elevation > highest.elevation) {
			highest = airport; // save highest
		}
	}
	cout << "Highest elevation airport: " << "\n";
	highest.display();
}

void AirportManager::lowestElevation() {

	if (airports.empty()) {
		cout << "\n----------------------------------------\n";
		cout << "No airports loaded." << endl;
		cout << "----------------------------------------\n";
		return;
	}

	Airport lowest = airports[0];

	for (const auto& airport : airports) {
		if (airport.elevation < lowest.elevation) {
			lowest = airport;
		}
	}
	cout << "Lowest elevation airport: " << endl;
	lowest.display();
}

void AirportManager::missingIATA(int limit) const {

	int count = 0;
	bool found = false;

	for (const auto& airport : airports) {

		if (airport.iata.empty()) { // check if iata its empty
			airport.display();
			found = true;
			count++;

			if (limit != -1 && count >= limit) {
				break;
			}
		}
	}

	if (!found) {
		cout << "\n----------------------------------------\n";
		cout << "All airports have IATA codes." << endl;
		cout << "----------------------------------------\n";
	}
	else {
		cout << endl;
	}
}

void AirportManager::deleteByIdent(const string& ident) {

	bool found = false;
	string code = toLowerCase(ident);

	for (auto it = airports.begin(); it != airports.end(); ) {
		// 'it' its  iterator - showin for element in vector
		
			if (toLowerCase(it->ident) == code) { // tak actual airport and check ident
				it = airports.erase(it); // erase(it) - delete element from veector
				// it = erase(it)  - going to next elemet 
				found = true;
			}
			else {
				++it;
			}
	}

	if (found) {
		cout << "\n============================================\n";
		cout << "|                                          |\n";
		cout << "|  *~* Airport deleted successfully! *~*   |\n";
		cout << "|                                          |\n";
		cout << "============================================\n";
		cout << "" << endl;
	}
	else {
		cout << "\n----------------------------------------\n";
		cout << "No airport found with ident: " << ident << endl;
		cout << "\n----------------------------------------\n";
	}
}
//multimap allow to kave few records in on kay 
// map - data structure - have key and value eg. ["Anna"] =20
multimap < string, Airport> AirportManager::groupByMunicipality() const {
	multimap <string, Airport> grouped; // create multimap grouped - 1st its string, 2nd airport

	for (const auto& airport : airports) {
		grouped.insert({ airport.municipality, airport }); // add element to map
	}

	return grouped; // return ready map withn data
}


void AirportManager::showByMunicipality(const string& municipality) const {

	bool found = false;
	string searchMunicipality = toLowerCase(municipality);

	for (const auto& airport : airports) {
		if (toLowerCase(airport.municipality) == searchMunicipality) {
			airport.display();
			found = true;
		}
	}

	if (!found) {
		cout << "\n----------------------------------------\n";
		cout << "No airports found in municipality: " << municipality << endl;
		cout << "----------------------------------------\n";
	}
}

void AirportManager::showUniqueTypes() const {

	set <string> types; // make a new set - always have unique data

	for (const auto& airport : airports) {
		types.insert(airport.type); // add airport type, if already exist then ignore
	}
	cout << "\n----------------------------------------\n";
	cout << "Unique airport types: " << endl;
	cout << "----------------------------------------\n";

	for (const auto& type : types) { //going around unique types in loop
		cout << type << endl;
	}

}

void AirportManager::countByCountry() const {

	map<string, int> counts; // string - county, int - number

	for (const auto& airport : airports) {
		counts[airport.country]++; // if country dont exist then create with 0 and icrease for 1
		
	}

	cout << "\n----------------------------------------\n";
	cout << "Airports by country: " << endl;
	cout << "----------------------------------------\n";

	for (const auto& pair : counts) {
		cout << pair.first << ": " << pair.second << endl;
	//pair.first key-country, pair.second value-number
	}
}

void AirportManager::showByType(const string& type, int limit) const {
	string searchType = toLowerCase(type);
	vector<Airport> filtered; //new list just to filtgered type

	//filtering
	for (const auto& airport : airports) {

		if (toLowerCase(airport.type) == searchType) {
			filtered.push_back(airport); //add only matching airports
		}
	}

	//check if found someting
	if (filtered.empty()) {
		cout << "\n----------------------------------------\n";
		cout << "No airports found by type: " << type << endl;
		cout << "----------------------------------------\n";
		return;
	}

	//sorting alphabetically by name
	sort(filtered.begin(), filtered.end(),
		[](const Airport& a, const Airport& b) { //
			return a.name < b.name;
		});
	//showing
	int count = 0;

	for (const auto& airport : filtered) {
		airport.display();
		count++;

		if (limit != -1 && count >= limit) {
			break;
		}
	}
}