
#include "Ransac.h"

Ransac::Ransac() {
	x.resize(N);
	y.resize(N);
}

void Ransac::prepareData(int Z[N], int T[N]) {
	for (int i = 0; i < N; i++) {
		this->x[i] = T[i] - 25;
		this->y[i] = log10(Z[i]);
	}
}


void Ransac::iterate() {
	//RANSAC starts here
	cout << "Построение моделей...\n";

	for (int i = 1; i <= MAX_ITERATIONS; i++) {

		#ifdef DEBUG
			cout << "Итерация " << setw(5) << i << "\n";
		#endif // DEBUG

		//Model m(12, x,  y);
		Model m;
		bool success = m.setIndexes(12, indexPairs, x, y);

		if (!success) {
			cout << "Итерация " << i << ": невозможно подобрать новую пару индексов" << "\n";
			break;
		}

		m.calculateParams();
		m.calculateEpsilon(x, y);

		models.push_back(m);

		#ifdef DEBUG
				printAll();
		#endif
	}
}

bool compareIndexes(Model a, Model b) {
	return (a.indexes.first < b.indexes.first);
}

void Ransac::printAll() {

	sort(models.begin(), models.end(), compareIndexes);

	for (int i = 0; i < models.size(); i++) {
		
		cout << setw(3) << i + 1 << setw(8) << "(" << models[i].indexes.first << ", ";
		cout << models[i].indexes.second << ")" << "\n";
	}
}

bool compareEpsilon(Model a, Model b) {
	return (a.currentEpsilon < b.currentEpsilon);
}

void Ransac::findBest() {

	sort(models.begin(), models.end(), compareEpsilon);

	Model m = models[0];

	cout << "Лучшее совпадение: \n";
	cout << "k = " << m.k << " b = " << m.b << " eps = " << m.currentEpsilon << "\n\n";

	double R0 = pow(10, m.b);

	cout << "Итоговаая модель: \n";
	cout << "Z = R0 * 10 ^ ( k * (T - T0) )\n";

	cout << "Z = " << R0 << " * 10^(" << m.k << " * (T - T0) \n\n";
}