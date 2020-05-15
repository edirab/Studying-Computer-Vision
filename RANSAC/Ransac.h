#pragma once

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

//������������ ������: Z = C* e ^(k*T)
//� �� 2 ���������: � � k. �� � ����� �����
//����� ������������: ln Z = k*T + ln C



class Ransac {

public:
	vector<double> y;
	vector<double> x;

	vector<Model> models;
	pairsSet indexPairs;

	Ransac();

	void prepareData(int Z[N], int X[N]);
	void iterate();
	void findBest();
	void printAll();
};
