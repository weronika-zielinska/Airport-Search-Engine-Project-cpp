// Airport-Search-Engine-Project-cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream> //to work with files
#include <string>
using namespace std;

int main()
{
	ifstream file("airport-codes.csv"); //input file stream - reading csv

	if (!file.is_open()) { //check if file can be open
		cout << "Error! Could not open file!" << endl;
		return 1;
	}

	cout << "File is opened!" << endl;

	file.close();
	return 0;
 
}

