#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Airport.h"

using namespace std;

class AirportManager {  // klasa zarzajaca wszystkimi lotniskami
public:
	vector <Airport> airports; // lista wszystkich lotnisk

	void loadFromCSV(const string& filename); //funkcja do wczytywanie z csv

	void displayAll() { // funckja do wyswietlanie z csv
		for (const auto& airport : airports) {
			airport.display();
		}
	}

	void searchByCountry(const string& countryCode);
	void searchByName(const string& namePart);

};

// implementacja funkcji
void AirportManager::loadFromCSV(const string& filename) {

	ifstream file(filename); //input file stream - reading csv

	if (!file.is_open()) { //check if file can be open
		cout << "Error! Could not open file!" << endl;
		return;
	}

	string line; // it will be safe line from csv

	getline(file, line); // pomijamy naglowek

	while (getline(file, line)) {

		stringstream ss(line); // ss from <sstream> making data with pieces with ,
		string column; // to save one column of csv
		Airport airport; //nowy obiekt airport


		getline(ss, airport.ident, ',');
		getline(ss, airport.type, ',');  // read csv up to comma and save in airport.type
		getline(ss, airport.name, ',');

		getline(ss, column, ',');
		if (!column.empty()) {
			try {
				airport.elevation = stoi(column);
			}
			catch (...) {
				airport.elevation = 0;
			}
		}

		getline(ss, column, ','); //skip continent column
		getline(ss, airport.country, ',');
		getline(ss, column, ','); // skip region column
		getline(ss, airport.municipality, ',');
		getline(ss, column, ','); // skip icao column
		getline(ss, airport.iata, ',');
		getline(ss, column, ','); //skip gps column
		getline(ss, column, ','); // skip local column

		//coordinates 
		getline(ss, column, ',');
		size_t commaPos = column.find(','); //looking for forst comma in row

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
		airports.push_back(airport); //add airport to list vector<Airport> airports

	}
	file.close();
}


void AirportManager::searchByCountry(const string& countryCode) {
	
	bool found = false; //czy znaleziono jakiekolwiek wyniki

	for (const auto& airport : airports) { // przechodzi przez wszystkie lotniska

		if (airport.country == countryCode) { // sprawdza czy kraj sie zgadza
			airport.display();
			found = true;
		}
	}

	if (!found) { // jesli nie znalazlo to komunikat
		cout << "No airports found for country: " << countryCode << endl;
	}
}

void AirportManager::searchByName(const string& namePart) {
	bool found = false;

	for (const auto& airport : airports) {
		//sprawdzamy czy fragment nazwy wystepuje w nazwie jakiegos lotniska
		if (airport.name.find(namePart) != string::npos) { //npos oznacza znaleziono
			airport.display();
			found = true;
		}
	}
	if (!found) {
		cout << "No Airports matching the criteria: " << namePart << endl;
	}
}
