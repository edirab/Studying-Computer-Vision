// Gauss_2.cpp: определяет точку входа для консольного приложения.

#include <iostream>
#include <clocale>
#include <conio.h>

using namespace std;

void printVector(float vector_[4], int n) {

	for (int L = 0; L < n; L++) {
		cout << vector_[L] << " ";
	}
	cout << "\n\n";
}

void printMatrix(float matrixA[4][4], int n) {
	cout << "Matrix A: \n";

	for (int l = 0; l < n; l++) {
		for (int m = 0; m < n; m++)
			cout << matrixA[l][m] << " ";

		cout << "\n";
	}
	cout << "\n\n";
	return;
}

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

	// прямой ход
	//указывает на диагональный элемент
	for (int k = 0; k < n-1; k++) {

		//Выбираем наибольший в столбце
		int maxInCol_index = k;
		for (int m = k; m < n; m++) {
			if (matrixA[m][k] > matrixA[k][k]) {
				maxInCol_index = m;
			}
		}

		if (maxInCol_index != k) {

			float temp = vectorB[k];
			vectorB[k] = vectorB[maxInCol_index];
			vectorB[maxInCol_index] = temp;

			for (int r = 0; r < n; r++) {
				temp = matrixA[k][r];
				matrixA[k][r] = matrixA[maxInCol_index][r];
				matrixA[maxInCol_index][r] = temp;
			}
		}
		cout << "Проход " << k+1 << ":\n\n";
		printMatrix(matrixA, n);

		//указывает на строку
		for (int i = k+1; i < n; i++) {

			float u = matrixA[i][k] / matrixA[k][k];

			cout << "Строка " << i << ": u (" << i << ", " << k << ") = " << u << "\n";

			// Проходим строку целиком по всем столбцам
			for (int j = 0; j < n; j++) {
				matrixA[i][j] = matrixA[i][j] - u * matrixA[k][j];
			}

			vectorB[i] = vectorB[i] - u * vectorB[k];
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
	}

	printMatrix(matrixA, n);
	cout << "Вектор b: \n";
	printVector(vectorB, n);
	cout << "Вектор Х:\n";
	printVector(vectorX, n);

	return 0;
}
