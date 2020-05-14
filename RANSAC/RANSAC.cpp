
#include "Ransac.h"

Ransac::Ransac() {
	x.resize(N);
	y.resize(N);
}

void Ransac::prepareData(int Z[N], int T[N]) {
	for (int i = 0; i < N; i++) {
		this->x[i] = T[i];
		this->y[i] = log10(Z[i]);
	}
}


void Ransac::iterate() {
	//RANSAC starts here
	for (int i = 1; i <= MAX_ITERATIONS; i++) {

		cout << "Итерация " << setw(5) << i << "\n";

		Model m(12, x,  y);
		//m.setIndexes(12);
		m.calculateParams();
		m.calculateEpsilon(x, y);

		models.push_back(m);

		/*
		можно создать множество, которое бы хранило пары индексов, чтобы избежать посторений
		*/
#ifdef DEBUG
		cout << "x[" << setw(2) << first_pair_index << "] = " << setw(2) << x[first_pair_index] << " y[" << setw(2) << first_pair_index << "] = " << setw(2) << y[first_pair_index] << "\n";
		cout << "x[" << setw(2) << second_pair_index << "] = " << setw(2) << x[second_pair_index] << " y[" << setw(2) << second_pair_index << "] = " << setw(2) << y[second_pair_index] << "\n";
#endif

#ifdef DEBUG
		cout << "k = " << setw(7) << k << " b = " << setw(7) << b << "\n";
#endif

	}
}

void Ransac::findBest() {

	//if (i == 1) {
//	best_b = b;
//	best_k = k;
//	best_max_distance = max_distance;
//	best_iter_index = i;
//}

//if (max_distance < best_max_distance) {

//	best_iter_index = i;
//	best_max_distance = max_distance;
//	best_k = k;
//	best_b = b;
//}

	//cout << "\n\nBest iteration: " << best_iter_index << " with best max distance " << best_max_distance << "\n";
//cout << "Best K = " << best_k << " best_b = " << best_b << "\n";

//double k = best_k;
//double C = pow(10, best_b);

//cout << "Final model: Z = " << C << " * 10^(" << k << " * T) \n\n";
//cout << setw(12) << "Z - Z[i]" << setw(10) << "Z" << setw(6) << "Z[i]" << setw(6) << "T[i]" << "\n\n";

//for (int i = 0; i < N; i++) {

//	double y = C * pow(10, k * T[i]);
//	cout << setw(12) << y - Z[i] << setw(10) << y << setw(6) << Z[i] << setw(6) << T[i] << "\n";
//}

}