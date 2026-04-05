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
	string country;
	string municipality;
	string iata;
	double latitude = 0.0; //coordinates 1
	double longitude = 0.0; // coordinates 2

	void display() const {
		cout << "ID: " << ident
			<< "| Name: " << name
			<< "| Country: " << country
			<< "| IATA: " << iata
			<< endl;

	}
};
