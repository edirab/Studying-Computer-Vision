#pragma once


// реализует проверку корректности отсчёта координат
class ROV {

public:
	double x = 0;
	double y = 0;
	double z = 0;
	double depth = 0;

	const int MAX_X = 10000;
	const int MAX_Y = 10000;
	const int MAX_Z = 100;
	const int MAX_DEPTH = 100;

	ROV(double X, double Y, double Z, double D);
	~ROV() {};

	bool update_coords(char command, double op1, double op2 = -1);
};