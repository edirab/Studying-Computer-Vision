// Gauss_2.cpp: определяет точку входа для консольного приложения.

#include <iostream>
#include <clocale>
#include <conio.h>

using namespace std;

void printVector(double vector_[4], int n) {

	for (int L = 0; L < n; L++) {
		cout << vector_[L] << " ";
	}
	cout << "\n\n";
}

void printMatrix(double matrix_[4][4], int n) {

	for (int l = 0; l < n; l++) {
		for (int m = 0; m < n; m++)
			cout << matrix_[l][m] << " ";

		cout << "\n";
	}
	cout << "\n\n";
	return;
}

int main() {

	setlocale(0, "");

	double matrixA[4][4] = {
							{10, 6, 2, 0},
							{5, 1, -2, 4},
							{3, 5, 1, -1},
							{0, 6, -2, 2}
							};
	double inverseMatrix[4][4] = {
							{1, 0, 0, 0},
							{0, 1, 0, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 1}
							};

	double vectorB[4] = { 25, 14, 10, 8 };
	double vectorX[4] = { 0 };

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

			double temp = vectorB[k];
			vectorB[k] = vectorB[maxInCol_index];
			vectorB[maxInCol_index] = temp;

			for (int r = 0; r < n; r++) {
				temp = matrixA[k][r];
				matrixA[k][r] = matrixA[maxInCol_index][r];
				matrixA[maxInCol_index][r] = temp;
				// Эквивалентные преобразования с единичной
				temp = inverseMatrix[k][r];
				inverseMatrix[k][r] = inverseMatrix[maxInCol_index][r];
				inverseMatrix[maxInCol_index][r] = temp;
			}
		}
		cout << "Проход " << k+1 << ":\n\n";
		printMatrix(matrixA, n);

		//указывает на строку
		for (int i = k+1; i < n; i++) {

			double u = matrixA[i][k] / matrixA[k][k];
			cout << "Строка " << i << ": u (" << i << ", " << k << ") = " << u << "\n";

			// Проходим строку целиком по всем столбцам
			for (int j = 0; j < n; j++) {
				matrixA[i][j] = matrixA[i][j] - u * matrixA[k][j];
				inverseMatrix[i][j] = inverseMatrix[i][j] - u * inverseMatrix[k][j];
			}

			vectorB[i] = vectorB[i] - u * vectorB[k];
		}
		cout << "\n\n";

		// Обратный ход:
		for (int i = n - 1; i >= 0; i--) {
			double partialSum = 0;

			for (int j = i+1; j < n; j++) {
				partialSum += matrixA[i][j] * vectorX[j];
			}
			vectorX[i] = (vectorB[i] - partialSum) / matrixA[i][i];
		}
	}

	cout << "Matrix A: \n";
	printMatrix(matrixA, n);
	cout << "Вектор b: \n";
	printVector(vectorB, n);
	cout << "Вектор Х:\n";
	printVector(vectorX, n);

	cout << "Matrix Inverse: \n";
	printMatrix(inverseMatrix, n);

	cout << "\n\n****** Поиск обратной матрицы **********\n\n";

	// Идём вверх по диагональным элементам
	for (int k = n - 1; k >= 0; k--) {
		//указывает на строку
		for (int i = k - 1; i >= 0; i--) {
			double u = matrixA[i][k] / matrixA[k][k];
			matrixA[i][k] = matrixA[i][k] - u * matrixA[k][k];

			// Проходим строку целиком по всем столбцам
			for (int j = 0; j < n; j++) {
				
				inverseMatrix[i][j] = inverseMatrix[i][j] - u * inverseMatrix[k][j];
			}
		}
	}

	// Нормировка
	for (int m = 0; m < n; m++) {

		double diag = matrixA[m][m];
		matrixA[m][m] /= diag;

		for (int L = 0; L < n; L++) {
			inverseMatrix[m][L] /= diag;
		}
	}

	cout << "Matrix A: \n";
	printMatrix(matrixA, n);

	cout << "Matrix Inverse: \n";
	printMatrix(inverseMatrix, n);

	// Проверка перемножением:
	double matrixA_[4][4] = {
						{10, 6, 2, 0},
						{5, 1, -2, 4},
						{3, 5, 1, -1},
						{0, 6, -2, 2}
	};
	
	// указываем на строку A-1
	for (int i = 0; i < n; i++) {
		

		// указываем на столбец A
		for (int k = 0; k < n; k++) {
			double elem = 0;

			for (int j = 0; j < n; j++) {
				elem += inverseMatrix[i][j] * matrixA_[j][k];
			}
			cout << elem << " ";
		}
		cout << "\n";
	}
	

	return 0;
}
