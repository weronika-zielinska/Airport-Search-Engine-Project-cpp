#pragma once
#include <string>
#include <iostream>
using namespace std;

class Airport {
public:
	string ident;
	string type;
	string name;
	int elevation = 0;
	string continent;
	string country;
	string region;
	string municipality;
	string icao;
	string iata;
	string gps;
	string localCode;
	double latitude = 0.0; //coordinates 1
	double longitude = 0.0; // coordinates 2

	void display() const {
		cout << "ID: " << ident
			<< "| Name: " << name
			<< "| Type: " << type
			<< "| Country: " << country
			<< "| Region: " << region
			<< "| Municipality: " << municipality 
			<< "| ICAO: " << icao
			<< "| IATA: " << iata
			<< "| GPS: " << gps
			<< "| Local: " << localCode
			<< "| Elevation: " << elevation
			<< "| Coordinates: " << latitude << "," << longitude
			<< endl;

	}
};
