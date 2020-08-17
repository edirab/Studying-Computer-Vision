#include "ROV.h"
#include <string>
#include <iostream>

using namespace std;

ROV::ROV(double X = 0, double Y = 0, double Z = 0, double D = 0) {
	x = X;
	y = Y;
	z = Z;
	depth = D;
};

bool ROV::update_coords(char command, double op1, double op2) {
	string result = "none";

	switch (command) {

	case 'M':
		if (op1 < 0 || op2 < 0 || op1 > MAX_X || op2 > MAX_Y) {
			cout << "\t Error: " << "op1 < 0 || op2 < 0 || op1 > MAX_X || op2 > MAX_Y \n";
			return false;
		}
			
		x = op1;
		y = op2;
		break;

	case 'R':
		x = 0;
		y = 0;
		z = 0;
		break;

	case 'D':
		if (op1 > MAX_Z || op1 < 0 || z >= op1) {
			cout << "\t Error: " << "op1 > MAX_Z || op1 < 0 || z >= op1 \n";
			return false;
		}
		z = op1;
		depth = op1;
		break;

	case 'L':
		if (op1 > MAX_Z || op1 < 0 || z <= op1) {
			cout << "\t Error: " << "op1 > MAX_Z || op1 < 0 || z <= op1 \n";
			return false;
		}
		z = op1;
		depth = op1;
		break;
	}
	return true;
}