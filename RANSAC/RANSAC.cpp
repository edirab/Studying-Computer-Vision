// RANSAC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#define MAX_ITERATIONS 1000

#include <iostream>
#include <Eigen/LU>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const uint8_t n = 12;

//int X[12] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 };
//int Y[12] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 };

int Z[n] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 };
int T[n] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 };

vector<int> y(12);
vector<int> x(12);

double epsilon = 0.01;

int main()
{
	Eigen::MatrixXf A = Eigen::MatrixXf::Ones(n, 2);
	Eigen::VectorXf b = Eigen::VectorXf::Ones(n);
	Eigen::Vector2f x;

	//Используемая модель: Z = C* e ^(k*T)
	//У неё 2 параметра: С и k. Их и нужно найти
	//После линеаризации: ln Z = k*T + ln C

	for (int i = 0; i < n; i++) {
		A.row(i) << T[i], 1;
		b[i] = log(Z[i]);

		x[i] = T[i];
		y[i] = log(Z[i]);
	}

	double global_min_distance = -1;
	//RANSAC starts here
	for (int i = 0; i < MAX_ITERATIONS; i++) {
		
		// y = k*x + b
		double k = 0;
		double b = 0;

		Eigen::Matrix2f A = Eigen::MatrixXf::Ones(n, 2);
		Eigen::Vector2f B = Eigen::VectorXf::Ones(n);
		Eigen::Vector2f X;


		// для построения прямой дастаточно 2-х точек
		int first_pair_index = rand() % 12;
		int second_pair_index = 0;
		do { 
			second_pair_index = rand() % 12; 
		} 
		while (first_pair_index == second_pair_index);
	
		cout << "1-st index:" << first_pair_index << "2-nd index" << second_pair_index << "\n\n";


		A.row(0) << x[first_pair_index], 1;
		A.row(1) << x[second_pair_index], 1;

		B << y[first_pair_index], y[second_pair_index];

		X = A.transpose().lu().solve(B);

		k = X[0];
		b = X[1];

		cout << "Итерация " << i << ":\n";
		cout << "k = " << k << "b = " << b << "\n\n";

		double min_distance = -1;

		// Что-то там такое посчитали. Теперь надо проверить
		for (int j = 0; j < n; j++) {
			if (i == first_pair_index || i == second_pair_index) continue;

			double A = y[first_pair_index] - y[second_pair_index];
			double B = x[first_pair_index] - x[second_pair_index];
			double C = y[first_pair_index]*x[second_pair_index] - y[second_pair_index]*x[first_pair_index];

			double H = (A * x[j] + B * y[j] + C) / sqrt(A * A + B * B);

			if (min_distance == -1)
				min_distance = H;
			else
			{
				min_distance = min(min_distance, H);
			}
		}
		cout << "Min distance :" << min_distance << "\n";
	}

	cout << "Matrix A: \n" << A << "\n\n";
	cout << "Vector b: \n" << b << "\n\n";

	x = (A.transpose() * A).lu().solve(A.transpose() * b);
	double C = exp(x[1]);
	double k = x[0];

	cout << "The solution using normal equations is:\n";
	cout << "x1 = C = " << C << "\n";
	cout << "x2 = k = " << k << "\n\n";

	//cout << "The solution using the QR decomposition is:\n" << A.colPivHouseholderQr().solve(b) << endl;

	cout << "Difference with given data: \n\n";

	cout << setw(10) << "u - Y[i]" << setw(10) << "u" << setw(6) << "Y[i]" << "\n\n";

	for (int i = 0; i < n; i++) {
		double u = C * exp(k * Z[i]);

		cout << setw(10) << u - T[i] << setw(10) << u << setw(6) << T[i] << "\n";
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

