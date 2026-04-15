#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Airport.h"
#include <algorithm>
#include <map>
#include <set>

using namespace std;

string trim(const string& str) { //usuwamy spacje z poczatku i konca
	size_t first = str.find_first_not_of(" \t\n\r");
	size_t last = str.find_last_not_of(" \t\n\r");

	if (first == string::npos) return "";

	return str.substr(first, (last - first + 1));
}

class AirportManager {  // klasa zarzajaca wszystkimi lotniskami
public:
	vector <Airport> airports; // lista wszystkich lotnisk

	void loadFromCSV(const string& filename); //funkcja do wczytywanie z csv

	void displayAll() { // funckja do wyswietlanie z csv
		for (const auto& airport : airports) {
			airport.display();
		}
	}

	void searchByCountry(const string& countryCode);  //deklaracje
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
	void missingIATA();
	void deleteByIdent(const string& ident);
	multimap <string, Airport> groupByMunicipality() const;
	void showByMunicipality(const string& municipality) const;
	void showUniqueTypes() const;
	void countByCountry() const;

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


		getline(ss, airport.ident, ','); //ident

		getline(ss, airport.type, ',');  //type,  read csv up to comma and save in airport.type
		
		getline(ss, airport.name, ','); // name

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

		getline(ss, airport.icao, ','); //ICAO 

		getline(ss, airport.iata, ','); // iata
	
		getline(ss, airport.gps, ','); //gps

		getline(ss, airport.localCode, ','); // local code

		//coordinates 
		getline(ss, column);


		//remove quotes if they exist 
		if (!column.empty() && column.front() == '"') {
			column.erase(0, 1);
		}

		if (!column.empty() && column.back() == '"') {
			column.pop_back();
		}

		size_t commaPos = column.find(',');

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
		//sprawdzamy czy fragment nazwy wystepuje w nazwie jakiegos lotniska dlatego .find() - do fragnmentowego szukania
		if (airport.name.find(namePart) != string::npos) { //npos oznacza znaleziono
			airport.display();
			found = true;
		}
	}
	if (!found) {
		cout << "No Airports matching the criteria: " << namePart << endl;
	}
}

void AirportManager::searchByIATA(const string& iataCode) {
	bool found = false;

	string code = trim(iataCode); // czyscimy input uzytkownika

	for (const auto& airport : airports) {
		if (airport.iata == code) { //szukamy dokladnego dopasowania kodu
			airport.display();
			found = true;
		}
	}
	if (!found) {
		cout << " No airpost found with IATA code: " << iataCode << endl;
	}
}

void AirportManager::countByType() { // using map - key-value container
	map <string, int> counts; //przechowuje dane bo kolumna "type" to liczba
	// klucz - string , wartosc - int, map przechowuje pary danych pair=(klucz,wartosc)

	for (const auto& airport : airports) {
		counts[airport.type]++;  // jesli typ nie istnieje to sie tgworzy automatycznie i zwieksza licznik o jeden
	}

	cout << "Airports by type: " << endl;

	for (const auto& pair : counts) { //wez kazda pare z mapy counts
		cout << pair.first << ": " << pair.second << endl; //dostep do pierwszewgo i drugiego elementu pary
	}
}

void AirportManager::addAirport() {

	Airport airport;

	cout << "~*~*~*~*~*~*~*~ ADD NEW AIRPORT ~*~*~*~*~*~*~*~" << endl;
	cout << "Enter ident: ";
	cin >> airport.ident;  //cin uzywam do prostych danych bez spacji i przecinkow

	cout << "Entery type: ";
	cin >> airport.type;

	cin.ignore(); //czysci bufor/enter z poprzedniego cin bez tego getline nie dziala

	cout << "Enter name: ";
	getline(cin, airport.name); // getline(..) to tekstow ze spacjami

	cout << "Enter elevation (ft): ";
	cin >> airport.elevation;

	cout << "Enter continent: ";
	cin >> airport.continent;

	cout << "Enter country code: ";
	cin >> airport.country;

	cout << "Enter region code: ";
	cin >> airport.region;

	cin.ignore(); 

	cout << "Enter municipality: ";
	getline(cin, airport.municipality);

	cout << "Enter ICAO code: ";
	cin >> airport.icao;

	cout << "Enter IATA code: ";
	cin >> airport.iata;

	cout << "Enter GPS code: ";
	cin >> airport.gps;

	cout << "Enter local code: ";
		cin >> airport.localCode;

	cout << "Enter latitude: ";
	cin >> airport.latitude;

	cout << "Enter longitude: ";
	cin >> airport.longitude;

	//dodanie nowe lotkisko do vectora
	airports.push_back(airport);

	cout << "~*~*~*~*~*~*~*~ Airport added successfully! ~*~*~*~*~*~*~*~" << endl;

}

void AirportManager::saveToCSV(const string& filename) {
	ofstream file(filename);

		if (!file.is_open()) {
			cout << "Error! File could not be opened for saving." << endl;
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
	cout << "Data saved successfully!" << endl;
}

void AirportManager::printFirstN(int n) {  //wypisuje pierwsze N lotnisk

	for (int i = 0; i < n && i < airports.size(); i++) {
		airports[i].display();
	}
}

void AirportManager::sortByName() {

	sort(airports.begin(), airports.end(), // sort sortuyje vector
		[](Airport a, Airport b) {  // lambda [] porownuje dwa lotniska
			return a.name < b.name; // warunek sortuje alfabetycznie
		});
}

void AirportManager::sortByCountry() {

	sort(airports.begin(), airports.end(), //sortuje vector od pierwszego elementu do ostatiego
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
		cout << "No airports loaded." << endl;
		return;
	}

	Airport highest = airports[0]; //bierzemy pierwsze lotnisko i porownyjemy z kolejnym

	for (const auto& airport : airports) {
		if (airport.elevation > highest.elevation) {
			highest = airport; // zapisujemy najwyzsze
		}
	}
	cout << "Highest elevation airport: " << "\n";
	highest.display();
}

void AirportManager::lowestElevation() {

	if (airports.empty()) {
		cout << "No airports loaded." << endl;
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

void AirportManager::missingIATA() {

	bool found = false;

	for (const auto& airport : airports) {

		if (airport.iata.empty()) { // sprawdzamy czy iata puste
			airport.display();
			found = true;
		}
	}

	if (!found) {
		cout << "All airports have IATA codes." << endl;
	}
}

void AirportManager::deleteByIdent(const string& ident) {

	bool found = false;

	for (auto it = airports.begin(); it != airports.end(); ) {
		// it to iterator - wskazuje na element w vektorze
		
			if (it->ident == ident) { // wez aktualny airport sprawdz jego ident
				it = airports.erase(it); // erase(it)usun element z veectora
				// it = erase(it) przechodzi do nastepnego elementu
				found = true;
			}
			else {
				++it;
			}
	}

	if (found) {
		cout << "Airport deleted successfully!" << endl;
	}
	else {
		cout << "No airport found with ident: " << ident << endl;
	}
}
//multimap pozwala miec duzo rekordow pod tym samym kluczem
// map to struktura danych klucz i wartosc np age["Anna"] =20
multimap < string, Airport> AirportManager::groupByMunicipality() const {
	multimap <string, Airport> grouped; // tworzymy multimap grouped, pierwsza wartosc to string, druga airport

	for (const auto& airport : airports) {
		grouped.insert({ airport.municipality, airport }); // dodaje element do map
	}

	return grouped; // zwracamy gotowa mape z danymi
}

void AirportManager::showByMunicipality(const string& municipality) const {

	multimap <string, Airport> grouped = groupByMunicipality();

	auto range = grouped.equal_range(municipality); // zwraca zakres wszystkich rekodrow dla danego klucza
	// ato zgaduje typ, range to para iteratorw(poczatek, koniec)
	bool found = false;

	// w petli przechodze po wszystkich danych dla tego municipality
	for (auto it = range.first; it != range.second; ++it) {
		it->second.display(); // first - key, second - value
		found = true;
	}

	if (!found) {
		cout << "No airports found in municipality: " << municipality << endl;
	}
}

void AirportManager::showUniqueTypes() const {

	set <string> types; // ustawiamy nowy set - zawsze ma unikalne wartosci, nie powtarza

	for (const auto& airport : airports) {
		types.insert(airport.type); // dodajemy typ lotniska, jak juz istenie to ignoruje
	}

	cout << "Unique airport types: " << endl;

	for (const auto& type : types) { //przechodzimy po unikalnych tgypach w petli
		cout << type << endl;
	}

}

void AirportManager::countByCountry() const {

	map<string, int> counts; // string - county, int - number

	for (const auto& airport : airports) {
		counts[airport.country]++; // jesli kraj nie istnieje, tworzy go z wartoscia 0 i potem zwieksza o 1
	}

	cout << "Airports by country: " << endl;

	for (const auto& pair : counts) {
		cout << pair.first << ": " << pair.second << endl;
	//pair.first key-country, pair.second value-number
	}
}