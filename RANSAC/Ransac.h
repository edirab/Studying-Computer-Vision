#pragma once

#include <vector>
#include <iostream>
#include <Eigen/LU>
#include <iomanip>
#include "Model.h"

using namespace std;

#define MAX_ITERATIONS 500
//#define DEBUG
const int N = 12;
const int outliersNum = 2;

//extern double epsilon;
//
//extern int best_iter_index;
//extern double best_max_distance;
//extern double best_k;
//extern double best_b;

//Используемая модель: Z = C* e ^(k*T)
//У неё 2 параметра: С и k. Их и нужно найти
//После линеаризации: ln Z = k*T + ln C

class Ransac {

public:
	vector<double> y;
	vector<double> x;

	vector<Model> models;

	Ransac();

	void prepareData(int Z[N], int X[N]);
	void iterate();
	void findBest();
};
