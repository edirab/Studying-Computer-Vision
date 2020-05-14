#pragma once

#include <iostream>
//#include <clocale>
#include <Eigen/LU>
#include <math.h>
//#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

class Model {
	
	class Point {
		
	public:
		double x = 0;
		double y = 0;
	};

	Point pointA;
	Point pointB;
	
public:
	Model(int IdxRange, vector<double> x, vector<double> y);
	int first_index = 0;
	int second_index = 0;

	double k = 0;
	double b = 0;
	double currentEpsilon = 0;

	void calculateParams();
	void calculateEpsilon(vector<double> x, vector<double> y);
	//void setIndexes(int range, vector<int> x, vector<int> y);
};