// cuda-test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/cudaarithm.hpp>

using namespace std;
using namespace cv;
using namespace cv::cuda;

int main() {

	Mat h_array1 = Mat::ones(1024, 1024, CV_32FC2);
	Mat h_array2 = Mat::ones(1024, 1024, CV_32FC2);
	Mat h_array3 = Mat::zeros(1024, 1024, CV_32FC2);
	Mat h_result;
	GpuMat d_array1, d_array2, d_array3, d_result;

	d_array1.upload(h_array1);
	d_array2.upload(h_array2);

	const clock_t begin_time = clock();
	cuda::gemm(d_array1, d_array2, 1.0, d_array3, 0.0, d_result);
	cout << "Time elapsed: " << (float(clock() - begin_time) / CLOCKS_PER_SEC) << " sec" << endl;

	d_result.download(h_result);

	return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
