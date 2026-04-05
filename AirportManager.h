#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include "Airport.h"

using namespace std;

class AirportManager {
public:
    vector <Airport> airports;

    void loadFromCSV(const string& filename);

    void displayAll() {
        for (const auto& airport : airports) {
            airport.display();
        }
    }

	AirportManager manager;

	ifstream file("airport-codes.csv"); //input file stream - reading csv

	if (!file.is_open()) { //check if file can be open
		cout << "Error! Could not open file!" << endl;
		return 1;
	}

	string line; // it will be safe line from csv

	getline(file, line); //getline its function from <string> library to reading whole line of text
	// taking one line from file and save it in string line

	while (getline(file, line)) {

		stringstream ss(line); // ss from <sstream> making data with pieces with ,
		string column; // to save one column of csv
		Airport airport;


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
		else {
			airport.elevation = 0;
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


		manager.airports.push_back(airport); //add airport to list vector<Airport> airports

	}
	file.close();
};

