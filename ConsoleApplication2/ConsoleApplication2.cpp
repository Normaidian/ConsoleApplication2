#include "pch.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>


std::vector<std::vector<std::string>> forOperations(std::string forLine);
unsigned long long hexToDec(std::string hexValue);
std::string decToHex(unsigned long long decValue);


int main()
{
	for (auto q : forOperations("		%for (8)(0x1C,0x01)(10,-1)(1,1)(list:\"a\",\"b\",\"c\",\"d\",\"e\",\"f\",\"g\",\"h\")")) {
		for (auto e : q) {
			std::cout << std::setw(6) << e;
		}
		std::cout << std::endl;
	}
	system("pause");
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::vector<std::string>> forOperations(std::string forLine) {
	//!!!!!!!!!!!!!!!!--- Zmienne stałe do wyszukiwania ---!!!!!!!!!!!!!!!!
	std::string const searchingFor{ "%for " };
	std::string const searchingList{ "list:" };
	std::string const searchingComa{ "," };
	std::string const searchingBracket{ ")" };
	std::string const searchingHex{ "0x" };
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!


	forLine.erase(0, forLine.find(searchingFor) + searchingFor.length());

	std::vector<std::vector<std::string>> parametry;
	std::string tempLine = forLine, parametr;
	int i = 0, iterations;

	do {
		parametr = tempLine.substr(0, tempLine.find(searchingBracket) + 1);
		tempLine.erase(0, tempLine.find(searchingBracket) + 1);

		if (!i++) {
			iterations = atoi(parametr.substr(1, parametr.length() - 1).c_str());
		}
		else {
			std::vector<std::string> parameters;

			if (parametr.find(searchingList) != std::string::npos) {
				parametr.erase(0, parametr.find(searchingList) + 5);
				parametr.pop_back();
				parametr += ',';

				for (int k = 0; k < iterations; ++k) {
					parameters.push_back(parametr.substr(1, parametr.find(searchingComa)-2));
					parametr.erase(0, parametr.find(searchingComa)+1);
				}
				parametry.push_back(parameters);
			}
			else {
				std::string firstS = parametr.substr(1, parametr.find(searchingComa));
				std::string jumpS = parametr.substr(parametr.find(searchingComa) + 1, parametr.find_last_of(searchingBracket) - parametr.find(searchingComa) - 1);

				unsigned long long  firstI, jumpI;

				if (firstS.find(searchingHex) != std::string::npos) {
					firstI = hexToDec(firstS);
				}
				else {
					firstI = atoi(firstS.c_str());
				}
				if (jumpS.find(searchingHex) != std::string::npos) {
					jumpI = hexToDec(jumpS);
				}
				else {
					jumpI = atoi(jumpS.c_str());
				}

				for (int k = 0; k < iterations; ++k) {
					int wynik = firstI + (jumpI*k);
					if (firstS.find(searchingHex) != std::string::npos) {
						parameters.push_back(decToHex(wynik));
					}
					else {
						parameters.push_back(std::to_string(wynik));
					}
				}
				parametry.push_back(parameters);
			}
		}
	} while (!tempLine.empty());

	return parametry;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

unsigned long long hexToDec(std::string hexValue) {
	unsigned long long decValue;
	std::stringstream stream;

	stream << hexValue;
	stream >> std::hex >> decValue;

	return decValue;
}
std::string decToHex(unsigned long long decValue) {
	std::stringstream ss;

	ss << std::hex << decValue;
	std::string hexValue = "0x" + ss.str();
	
	return hexValue;
}