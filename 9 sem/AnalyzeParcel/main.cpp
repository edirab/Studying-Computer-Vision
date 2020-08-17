// task_1.cpp: главный файл проекта.

#include <iostream>
#include <stdio.h>
#include <string>
#include <clocale>
#include <map>
#include <vector>
#include "PNI.h"

using namespace std;




int main() {
	setlocale(0, "");

	PNITraxParcel *PNI = new PNITraxParcel();

	std::string parcelAsString;
	std::cin >> parcelAsString;


	int *i = new int(0);
	char* id = new char(2);

	while (*i < parcelAsString.size()) {

		int id_dec = 0;

		id[0] = parcelAsString[*i];
		id[1] = parcelAsString[*i + 1];
		*i += 2;

		sscanf_s(id, "%x", &id_dec);

		PNI->readId(id_dec, parcelAsString.substr(*i), i);
	}

	PNI->toString();

	system("pause");
	return 0;
}