// secondary_task_1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <Eigen/LU>

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.


using namespace std;
int main(int argc, char* argv[])
{
	Eigen::Matrix4d A, lower, upper;
	Eigen::Vector4d b, x;
	A << 10, 6, 2, 0, 5, 1, -2, 4, 3, 5, 1, -1, 0, 6, -2, 2;
	b << 25, 14, 10, 8;
	Eigen::PartialPivLU<Eigen::Matrix4d> lu(A);

	cout << "Matrix A" << endl << A << endl;
	cout << "Vector b" << endl << b << endl;
	cout << "LU-decomp" << endl << lu.matrixLU() << endl;

	lower = lu.matrixLU().triangularView<Eigen::StrictlyLower>();
	lower = lower + Eigen::Matrix4d::Identity();
	upper = lu.matrixLU().triangularView<Eigen::Upper>();

	cout << "Matrix lower" << endl << lower << endl;
	cout << "Matrix upper" << endl << upper << endl;
	cout << "Multiplication" << endl << lower * upper << endl;
	cout << "Multiplication with permutation" << endl
		<< lu.permutationP().inverse() * lower * upper << endl;

	return 0;
}