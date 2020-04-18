// RANSAC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
12 * 11 = 132 итерации это максимум
*/

#define MAX_ITERATIONS 500
//#define DEBUG

#include <iostream>
#include <clocale>
#include <Eigen/LU>
#include <math.h>
#include <iomanip>
#include <vector>
#include <algorithm>

using namespace std;

const uint8_t N = 12;

//int X[12] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 };
//int Y[12] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 };

int Z[N] = { 27, 31, 43, 58, 69, 86, 102, 111, 122, 137, 18, 176 }; // y
int T[N] = { 71, 64, 52, 41, 33, 23, 17, 12, 2, 0, 87, -5 }; // x

vector<double> y(12);
vector<double> x(12);

double epsilon = 0.01;

int main() {
	//Используемая модель: Z = C* e ^(k*T)
	//У неё 2 параметра: С и k. Их и нужно найти
	//После линеаризации: ln Z = k*T + ln C
	setlocale(0, "");

	for (int i = 0; i < N; i++) {
		x[i] = T[i];
		y[i] = log10(Z[i]);
	}

	int best_iter_index = 0;
	double best_max_distance = -1;
	double best_k = -1;
	double best_b = -1;
	//RANSAC starts here
	for (int i = 1; i <= MAX_ITERATIONS; i++) {
		
		cout << "Итерация " << setw(5) << i << "\n";
		// y = k*x + b
		double k = 0;
		double b = 0;

		Eigen::Matrix2d A;// = Eigen::Matrix2f::Ones(2, 2);
		Eigen::Vector2d B;// = Eigen::Vector2f::Ones(2);
		Eigen::Vector2d X;


		// для построения прямой дастаточно 2-х точек
		int first_pair_index = rand() % 12;
		int second_pair_index = 0;
		do { 
			second_pair_index = rand() % 12; 
		} 
		while (first_pair_index == second_pair_index);
	
		/*
		можно создать множество, которое бы хранило пары индексов, чтобы избежать посторений
		*/
		#ifdef DEBUG
		cout << "x[" << setw(2) << first_pair_index <<  "] = " << setw(2) << x[first_pair_index]  << " y[" << setw(2) <<  first_pair_index <<  "] = " << setw(2) << y[first_pair_index] << "\n";
		cout <<	"x[" << setw(2) << second_pair_index << "] = " << setw(2) << x[second_pair_index] << " y[" << setw(2) << second_pair_index << "] = " << setw(2) << y[second_pair_index] << "\n";
		#endif

		A.row(0) << x[first_pair_index], 1;
		A.row(1) << x[second_pair_index], 1;

		B << y[first_pair_index], y[second_pair_index];

		//cout << A << "\n\n";
		//cout << B << "\n\n";

		X = A.lu().solve(B);

		k = X[0];
		b = X[1];

		#ifdef DEBUG
		cout << "k = " << setw(7) << k << " b = " << setw(7) << b << "\n";
		#endif

		double max_distance = -1;

		// Что-то там такое посчитали. Теперь надо проверить
		// Для каждой точки из набора считаем расстояние по нормали д найденной прямой.
		// Берём наибольшее расстояние
		for (int j = 0; j < N; j++) {
			if (j == first_pair_index || j == second_pair_index) continue;

			double A = y[first_pair_index] - y[second_pair_index];
			double B = x[first_pair_index] - x[second_pair_index];
			double C = y[first_pair_index]*x[second_pair_index] - y[second_pair_index]*x[first_pair_index];

			double H = abs((A * x[j] + B * y[j] + C) / sqrt(A * A + B * B));
			//cout << "H = " << H << "\n";

			if (j == 0)
				max_distance = H;
			else {
				max_distance = max(max_distance, H);
			}
		}
		cout << "Max abs distance for this iter :" << max_distance << "\n\n";

		if (i == 1) {
			best_b = b;
			best_k = k;
			best_max_distance = max_distance;
			best_iter_index = i;
		}

		if (max_distance < best_max_distance) {

			best_iter_index = i;
			best_max_distance = max_distance;
			best_k = k;
			best_b = b;
		}
	}

	cout << "\n\nBest iteration: " << best_iter_index << " with best max distance " << best_max_distance <<  "\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

