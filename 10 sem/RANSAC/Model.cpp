
#include "Model.h"

// empty
Model::Model() {

}


Model::Model(int range, vector<double> x, vector<double> y) {

	// для построения прямой дастаточно 2-х точек
	int first_index = rand() % range;
	int second_index = 0;
	do {
		second_index = rand() % range;
	} while (first_index == second_index);

	indexes = make_pair(first_index, second_index);

	pointA.x = x[indexes.first];
	pointA.y = y[indexes.first];
	pointB.x = x[indexes.second];
	pointB.y = y[indexes.second];
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
	vector<double> distances;

	// Для каждой точки из набора считаем расстояние по нормали до найденной прямой.
	// Берём наибольшее расстояние, это и есть наша метрика
	assert(x.size() == y.size());

	for (int j = 0; j < x.size(); j++) {
		if (j == indexes.first || j == indexes.second) continue;

		double A = y[indexes.first] - y[indexes.second];
		double B = x[indexes.first] - x[indexes.second];
		double C = y[indexes.first] * x[indexes.second] - y[indexes.second] * x[indexes.first];

		double H = abs((A * x[j] + B * y[j] + C) / sqrt(A * A + B * B));
		//cout << "H = " << H << "\n";

		max_distance = max(max_distance, H);
		distances.push_back(max_distance);
	}
	sort(distances.begin(), distances.end());
	//currentEpsilon = max_distance;
	currentEpsilon = distances[distances.size() - 3];

	#ifdef DEBUG
		cout << "Наибольшее расстояние с цчётом 2-х выбросов: " << currentEpsilon << "\n\n";
	#endif // DEBUG
}

bool Model::setIndexes(int range, pairsSet &pairs, vector<double> x, vector<double> y) {
	
	//bool success = true;
	int first_index = 0, second_index = 0;
	int counter = 1000;

	while (counter) {

		first_index = rand() % range;

		do {
			second_index = rand() % range;
		} while (first_index == second_index);

		if (pairs.find(make_pair(first_index, second_index)) != pairs.end()) 
			counter--;
		else 
			break;	
	}

	if (counter == 0) 
		return false;

	indexes = make_pair(first_index, second_index);
	pairs.insert(indexes);

	pointA.x = x[indexes.first];
	pointA.y = y[indexes.first];
	pointB.x = x[indexes.second];
	pointB.y = y[indexes.second];

	return true;
}