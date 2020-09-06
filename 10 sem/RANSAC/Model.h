#pragma once

//#include <clocale>
//#include <iomanip>

#include <iostream>

#include <Eigen/LU>
#include <math.h>
#include <vector>
#include <algorithm>

#include <utility>
#include <unordered_set>
#include <boost/functional/hash.hpp>

using namespace std;

typedef unordered_set<pair<int, int>, boost::hash<std::pair<int, int>>> pairsSet;

class Model {
	
	class Point {
		
	public:
		double x = 0;
		double y = 0;
	};

	Point pointA;
	Point pointB;
	
public:
	//int first_index = 0;
	//int second_index = 0;
	pair<int, int> indexes;

	double k = 0;
	double b = 0;
	double currentEpsilon = 0;

	Model();
	Model(int IdxRange, vector<double> x, vector<double> y);

	void calculateParams();
	void calculateEpsilon(vector<double> x, vector<double> y);
	bool setIndexes(int range, pairsSet &pairs, vector<double> x, vector<double> y);
};