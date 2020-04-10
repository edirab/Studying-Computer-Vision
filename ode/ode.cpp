// ode.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
/*
	dy/dx = ax - by, 
	y(0) = d;

	a = -2
	b = 0.2
	d = 1

	C = d + a/b^2 = 1 + (-2)/0.2^2 = -49

	Решаем на интервале  0,1 с шагом 0.01
*/

#include <iostream>
#include <algorithm>
// #define _USE_MATH_DEFINES
// #define M_PI 3.14159265358979323846

#include <clocale>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

double f(double x, double y)
{
	//return (-sin(x));
	return (-2 * x - 0.2 * y);
}

double runge4(double t, double y0, double step)
{
	double k1, k2, k3, k4;
	k1 = f(t, y0);
	k2 = f(t + step / 2, y0 + step * k1 / 2);
	k3 = f(t + step / 2, y0 + step * k2 / 2);
	k4 = f(t + step, y0 + step * k3);
	double y = y0 + (k1 + 2 * k2 + 2 * k3 + k4) * step / 6;
	return y;
}

double euler(double x, double y0, double step) {
	double y_n_1 = 0;
	y_n_1 = y0 + step * f(x, y0);

	return y_n_1;
}

int main() {

	setlocale(0, "");

	double initVal = 1;
	double step = 0.01;

	std::vector<double> time, y;
	time.push_back(0);
	y.push_back(initVal);

	for (double t = step; t < 1 + step/2; t += step) {

		double dy = runge4(time.back(), y.back(), step);
		//double dy = euler(time.back(), y.back(), step);

		time.push_back(t);
		y.push_back(dy);
	}

	double max_delta = 0;

	cout <<setw(17) << "Аналитическое"  << setw(18) << "Найденное" << setw(17) << "delta \n\n";

	for (int i = 0; i < time.size(); i++)
	{
		double u = -2 / 0.2 * (time[i] - 1 / 0.2) + (-49) * exp(-0.2 * time[i]);
		double delta = abs(u - y[i]);
		max_delta = max(delta, max_delta);

		cout << "u(t) =" << setw(11) << u << " y(t) =" << setw(11) << y[i] << setw(15) << delta << endl;
	}
	cout << "\nmax delta: " << max_delta << "\n";

	return 0;
}

