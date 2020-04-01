// Gauss_2.cpp: определяет точку входа для консольного приложения.

#include <iostream>
#include <clocale>
#include <conio.h>

using namespace std;

int main() {

	setlocale(0, "");

	float matrixA[4][4] = {
							{10, 6, 2, 0},
							{5, 1, -2, 4},
							{3, 5, 1, -1},
							{0, 6, -2, 2}
							};

	float vectorB[4] = { 25, 14, 10, 8 };
	float vectorX[4] = { 0 };

	int n = sizeof(matrixA) / sizeof(matrixA[0]);
	//cout << n;

	// прямой ход
	
	//указывает на диагональный элемент
	for (int k = 0; k < n-1; k++) {

		//указывает на строку
		for (int i = k+1; i < n; i++) {

			float u = matrixA[i][k] / matrixA[k][k];
			//j++;

			cout << "Строка " << i << ": " << u << "\n\n";

			// Проходим строку целиком по всем столбцам
			for (int j = 0; j < n; j++) {
				matrixA[i][j] = matrixA[i][j] - u * matrixA[k][j];
				cout << matrixA[i][j] << " ";
			}

			vectorB[i] = vectorB[i] - u * vectorB[k];
			cout << "\n";
		}
		cout << "\n\n";

		// Обратный ход:
		for (int i = n - 1; i >= 0; i--) {
			float partialSum = 0;

			for (int j = i+1; j < n; j++) {
				partialSum += matrixA[i][j] * vectorX[j];
			}
			vectorX[i] = (vectorB[i] - partialSum) / matrixA[i][i];
		}

		// Print Matrix
		for (int l = 0; l < n; l++) {
			for (int m = 0; m < n; m++)
				cout << matrixA[l][m] << " ";

			cout << "\n";
		}
		cout << "\n\n";

		for (int L = 0; L < n; L++) {
			cout << vectorB[L] << " ";
		}
		cout << "\n\n";

		for (int L = 0; L < n; L++) {
			cout << vectorX[L] << " ";
		}
		cout << "\n";
	}

	return 0;
}
