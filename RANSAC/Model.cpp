
#include "Model.h"


Model::Model(int range, vector<double> x, vector<double> y) {

	// для построения прямой дастаточно 2-х точек
	first_index = rand() % range;
	second_index = 0;
	do {
		second_index = rand() % range;
	} while (first_index == second_index);

	pointA.x = x[first_index];
	pointA.y = y[first_index];
	pointB.x = x[second_index];
	pointB.y = y[second_index];
}

void Model::calculateParams() {

	// y = k*x + b
	Eigen::Matrix2d A;
	Eigen::Vector2d B;
	Eigen::Vector2d X;

	A.row(0) << pointA.x, 1;
	A.row(1) << pointB.x, 1;

	B << pointA.y, pointB.y;

	//cout << A << "\n\n";
	//cout << B << "\n\n";

	X = A.lu().solve(B);

	this->k = X[0];
	this->b = X[1];
}

void Model::calculateEpsilon(vector<double> x, vector<double> y) {

	double max_distance = -1;

	// Для каждой точки из набора считаем расстояние по нормали до найденной прямой.
	// Берём наибольшее расстояние, это и есть наша метрика
	assert(x.size() == y.size());

	for (int j = 0; j < x.size(); j++) {
		if (j == first_index || j == second_index) continue;

		double A = y[first_index] - y[second_index];
		double B = x[first_index] - x[second_index];
		double C = y[first_index] * x[second_index] - y[second_index] * x[first_index];

		double H = abs((A * x[j] + B * y[j] + C) / sqrt(A * A + B * B));
		//cout << "H = " << H << "\n";

		max_distance = max(max_distance, H);
	}
	currentEpsilon = max_distance;
	cout << "Max abs distance for this iter :" << max_distance << "\n\n";
}