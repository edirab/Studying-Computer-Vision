#include <iostream>
#include <string>
#include <vector>
#include "Missions.h"

using namespace std;






MoveTo::MoveTo(double X, double Y) {
	if (X < 0 || Y < 0) {
		cout << "Can't Move to negative coords";
		x = y = 0;
	}
	x = X;
	y = Y;
}

string MoveTo::toFile() {
	string data = "MoveTo " + to_string(x) + " " + to_string(y);
	return data;
}


Dive::Dive(double d) {
	z = d;
}

string Dive::toFile() {
	string data = "Dive: " + to_string(z);
	return data;
}


Lift::Lift(double UP) {
	z = UP;
}

string Lift::toFile() {
	string data = "Lift: " + to_string(z);
	return data;
}


string Return::toFile() {
	string data = "Return to (0, 0)";
	return data;
}