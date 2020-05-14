// RANSAC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
12 * 11 = 132 итерации это максимум
*/

#include <iostream>
#include <clocale>
#include <Eigen/LU>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>

#include "Ransac.h"

using namespace std;


//#define DEBUG

//int X[12] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 };
//int Y[12] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 };

int Z[N] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 }; // y
int T[N] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 }; // x


int main() {

	setlocale(0, "");
	Ransac r;
	r.prepareData(Z, T);
	r.iterate();
	r.findBest();

	return 0;
}

