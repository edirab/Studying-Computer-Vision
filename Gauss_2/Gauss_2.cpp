// Gauss_2.cpp: определяет точку входа для консольного приложения.

#include <vector>
#include <iostream>
#include <clocale>
#include <conio.h>
#include <iomanip>

//#define DEBUG

using namespace std;

// Dimension of input square matrix   
#define N 4   

// Function to get determinant of matrix   
int determinantOfMatrix(double mat[N][N], int n) {
	double num1, num2, det = 1, total = 1; // Initialize result   
	int index = 1;

	// temporary array for storing row 
	vector<double> temp(n+1);
	//int temp[n + 1];

	//loop for traversing the diagonal elements  
	for (int i = 0; i < n; i++) {
		index = i; // initialize the index   

		//finding the index which has non zero value   
		while (mat[index][i] == 0 && index < n) {
			index++;
		}
		// if there is non zero element   
		if (index == n) {
			// the determinat of matrix as zero   
			continue;
		}

		if (index != i)	{
			//loop for swaping the diagonal element row and index row   
			for (int j = 0; j < n; j++) {
				swap(mat[index][j], mat[i][j]);
			}
			//determinant sign changes when we shift rows   
			//go through determinant properties   
			det = det * pow(-1, index - i);
		}

		//storing the values of diagonal row elements   
		for (int j = 0; j < n; j++) {
			temp[j] = mat[i][j];
		}

		//traversing every row below the diagonal element   
		for (int j = i + 1; j < n; j++) {
			num1 = temp[i]; //value of diagonal element   
			num2 = mat[j][i]; //value of next row element   

			//traversing every column of row   
			// and multiplying to every row   
			for (int k = 0; k < n; k++) {
				//multiplying to make the diagonal   
				// element and next row element equal   
				mat[j][k] = (num1 * mat[j][k]) - (num2 * temp[k]);

			}
			total = total * num1; // Det(kA)=kDet(A);   
		}
	}

	//mulitplying the diagonal elements to get determinant   
	for (int i = 0; i < n; i++) {
		det = det * mat[i][i];
	}
	return (det / total); //Det(kA)/k=Det(A);   
}

void printVector(double vector_[N], int n) {

	for (int L = 0; L < n; L++) {
		cout << vector_[L] << " ";
	}
	cout << "\n\n";
}

void printMatrix(double matrix_[N][N], int n, int width = 5) {

	for (int l = 0; l < n; l++) {
		for (int m = 0; m < n; m++)
			cout << setw(width) << matrix_[l][m] << " ";

		cout << "\n";
	}
	cout << "\n\n";
	return;
}

int main() {

	setlocale(0, "");

	double matrixA[N][N] = {
							{10, 6, 2, 0},
							{5, 1, -2, 4},
							{3, 5, 1, -1},
							//{20, 12, 4, 0},
							{0, 6, -2, 2}
							};

	double detMatrinx[N][N] = { 0 };

	double inverseMatrix[N][N] = {
							{1, 0, 0, 0},
							{0, 1, 0, 0},
							{0, 0, 1, 0},
							{0, 0, 0, 1}
							};

	double vectorB[4] = { 25, 14, 10, 8 };
	double vectorX[4] = { 0 };

	int n = sizeof(matrixA) / sizeof(matrixA[0]);

	for (int i = 0; i < n; i++) 
		for (int j = 0; j < n; j++) {
			detMatrinx[i][j] = matrixA[i][j];
		}

	double det = determinantOfMatrix(detMatrinx, n);

	if (det == 0) {
		cout << "Определитель равен нулю, вычисление невозможно \n\n";
		return 0;
	}
	else {
		cout << "Определитель равен " << det << "\n";
		cout << "Решаем систему... " << "\n\n";
	}

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
		#ifdef DEBUG
			cout << "Проход " << k+1 << ":\n\n";
			printMatrix(matrixA, n);
		#endif // DEBUG

		//указывает на строку
		for (int i = k+1; i < n; i++) {

			double u = matrixA[i][k] / matrixA[k][k];

			#ifdef DEBUG
				cout << "Строка " << i << ": u (" << i << ", " << k << ") = " << u << "\n";
			#endif // DEBUG

			// Проходим строку целиком по всем столбцам
			for (int j = 0; j < n; j++) {
				matrixA[i][j] = matrixA[i][j] - u * matrixA[k][j];
				inverseMatrix[i][j] = inverseMatrix[i][j] - u * inverseMatrix[k][j];
			}

			vectorB[i] = vectorB[i] - u * vectorB[k];
		}
		#ifdef DEBUG
				cout << "\n\n";
		#endif // DEBUG

		// Обратный ход:
		for (int i = n - 1; i >= 0; i--) {
			double partialSum = 0;

			for (int j = i+1; j < n; j++) {
				partialSum += matrixA[i][j] * vectorX[j];
			}
			vectorX[i] = (vectorB[i] - partialSum) / matrixA[i][i];
		}
	}

	cout << " Покорёженная матрица A: \n";
	printMatrix(matrixA, n, 8);

	cout << " Вектор b: \n";
	printVector(vectorB, n);

	cout << " Вектор Х:\n";
	printVector(vectorX, n);

	cout << " Что в это время произошло с единичной матрицей: \n";
	printMatrix(inverseMatrix, n, 10);

	cout << "****** Поиск обратной матрицы **********\n\n";

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

	cout << " Теперь матрица А - единичная: \n";
	printMatrix(matrixA, n);

	cout << " А это обратная матрица: \n";
	printMatrix(inverseMatrix, n, 10);

	// Проверка перемножением:
	double matrixA_[4][4] = {
						{10, 6, 2, 0},
						{5, 1, -2, 4},
						{3, 5, 1, -1},
						{0, 6, -2, 2}
	};
	
	cout << " Проведём проверку перемножением. \n Должны получить единичную: \n\n";
	// указываем на строку A-1
	for (int i = 0; i < n; i++) {
		
		// указываем на столбец A
		for (int k = 0; k < n; k++) {
			double elem = 0;

			for (int j = 0; j < n; j++) {
				elem += inverseMatrix[i][j] * matrixA_[j][k];
			}
			cout << setw(14) << elem << " ";
		}
		cout << "\n";
	}
	return 0;
}
