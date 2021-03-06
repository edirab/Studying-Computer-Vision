﻿// Least_squares.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Eigen/LU>
#include <math.h>
#include <iomanip>

using namespace std;

const uint8_t n = 12;

//int X[12] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 };
//int Y[12] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 };

int Z[n] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176};
int T[n] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5};

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
	}

	cout << "Matrix A: \n" << A << "\n\n";
	cout << "Vector b: \n" << b << "\n\n";

	x = (A.transpose() * A).lu().solve(A.transpose() * b);
	double C = exp(x[1]);
	double k = x[0];

	cout << "The solution using normal equations is:\n";
	cout << "x1 = C = " << C << "\n";
	cout <<"x2 = k = "<< k << "\n\n";

	//cout << "The solution using the QR decomposition is:\n" << A.colPivHouseholderQr().solve(b) << endl;

	cout << "Difference with given data: \n\n";

	cout << setw(10) << "u - Y[i]" << setw(10) << "u" << setw(6) << "Y[i]" << "\n\n";

	for (int i = 0; i < n; i++) {
		double u = C * exp(k * Z[i]);
		
		cout << setw(10) << u-T[i] << setw(10) << u << setw(6) << T[i] << "\n";
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

