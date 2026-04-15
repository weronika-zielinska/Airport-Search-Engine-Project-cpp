#pragma once
#include <string>
#include <iostream>
#include <iomanip>
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
		cout << string(120, '-') << endl;
		cout << left
			<< "ID: " << setw(10) << ident
			<< "Name: "<< setw(30) << name
			<< "Type: "<< setw(18) << type
			<< "Country: "<< setw(4) << country
			<< "Region: "<< setw(12) << region
			<< "GPS: " << setw(8) << gps
			<< "Municipality: "<< setw(20) << municipality
			<< "ICAO: " << setw(10) << icao
			<< "IATA: " << setw(5) << iata
			<< "Local: " << setw(6) << localCode
			<< "Elev: " << setw(7) << elevation
			<< "Coord: " << latitude << ", " << longitude
			<< endl;

		cout << string(120, '-') << endl;
	}





	//	cout << left
	//		<< "ID: " << ident
	//		<< "| Name: " << name
	//		<< "| Type: " << type
	//		<< "| Country: " << country
	//		<< "| Region: " << region
	//		<< "| Municipality: " << municipality 
	//		<< "| ICAO: " << icao
	//		<< "| IATA: " << iata
	//		<< "| GPS: " << gps
	//		<< "| Local: " << localCode
	//		<< "| Coordinates: " << latitude << "," << longitude
	//		<< endl;

	
};
