// Airport-Search-Engine-Project-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> //to work with files
#include <string>
#include <vector>
#include <sstream>
using namespace std;


struct Airport {
	string ident;
	string type;
	string name;
	int elevation;
	string country;
	string municipality;
	string iata;
	double latitude; //coordinates 1
	double longitude; // coordinates 2
};



int main()
{

	vector <Airport> airports;

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

		
		getline(ss, airport.type, ",");  // read csv up to comma and save in airport.type
		getline(ss,airport.ident, ","); 
		getline(ss, airport.name, ",");

		getline(ss, column, ",");
		airport.elevation = column.empty() ? 0 : stoi(column); // column.empty() check if string its empty, stoi change string to int, ?0: - if;
		getline(ss, column, ","); //skip continent column
		getline(ss, airport.country, ",");
		getline(ss, column, ","); // skip region column
		getline(ss, airport.municipality, ",");
		getline(ss, column, ","); // skip icao column
		getline(ss, airport.iata, ",");
		getline(ss, column, ","); //skip gps column
		getline(ss, column, ","); // skip local column
		
		//coordinates 
		getline(ss, column, ",");

		stringstream coordStream(column); //new strong for coordinates
		string lat, lon; //new changes for coordinates
		

		getline(coordStream, lat, ""); // thisn line reading up to first space 

		if (!lat.empty() && !lon.empty()) { //check if data exist , if lat and lot are not empty then:
			airport.latitude = stod(lat); //conver string>double
			airport.longitude = stod(lon);
		}

		airports.push_back(airport); //add airport to list vector<Airport> airports

	}
	file.close();


	cout << "Loaded airports: " << airport.size() << endl;

	return 0;
 
}

