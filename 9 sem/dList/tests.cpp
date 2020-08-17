#include "my_list.h"

template <typename T>
void test(my_list<T>* list) {
	cout << "Push Back: " << "\n";
	list->push_back(1);
	list->push_back(2);
	list->push_back(3);
	list->push_back(4);

	list->print();
	list->printReversed();

	cout << "Push Front: " << "\n";
	list->push_front(0);
	list->push_front(-1);
	list->push_front(-2);
	list->push_front(-3);

	list->print();
	list->printReversed();

	cout << "Get: " << "\n";
	if (list->getElem(-2) != nullptr)
		cout << "Get: " << list->getElem(-2)->data << "\n";

	cout << "Get: " << list->getElem(0)->data << "\n";
	cout << "Get: " << list->getElem(1)->data << "\n";
	cout << "Get: " << list->getElem(7)->data << "\n";

	list->print();
	list->printReversed();

	list->insertElem(0, 10);
	list->insertElem(8, 100);
	list->insertElem(2, 20);
	list->insertElem(8, 80);

	list->print();
	list->printReversed();

	cout << "-----------------------\n";

	//cout << list->deleteElem_2(0)->data << "\n";
	list->print();
	cout << list->deleteElem(10) << "\n";
	list->print();
	cout << list->deleteElem(5) << "\n";
	list->print();

	cout << "-----------------------\n";

	list->replaceElems(0, 8);
	list->print();

	list->mergeSort(&(list->head));

	list->print();
	list->printReversed();
}


template <typename T>
void test_2(my_list<T> * list) {

	int n_push_back = 300 + rand() % 500;
	cout << "Pushing back..." << n_push_back << " times \n";
	for (int i = 0; i < n_push_back; i++) {
		list->push_back(rand() % 1000);
	}

	list->print();
	cout << "\n\n";

	int n_delete = 100 + rand() % list->capacity;
	cout << "Deleting..." << n_delete << " times \n";
	for (int i = 0; i < n_delete; i++) {
		list->deleteElem_2(rand() % list->capacity);
	}

	list->print();
	cout << "\n\n";

	int n_push_front = 200 + rand() % 100;
	cout << "Pushing front..." << n_push_front << " times \n";
	for (int i = 0; i < n_push_front; i++) {
		list->push_front(rand() % 1000);
	}

	list->print();
	cout << "\n\n";

	int n_replace = 500 + rand() % 1000;
	int a = rand() % list->capacity;
	int b = rand() % list->capacity;
	cout << "Replacing..." << n_replace << " pairs \n";
	for (int i = 0; i < n_replace; i++) {
		list->replaceElems(a, b);
	}

	list->print();
	cout << "\n\n";

	cout << "Now sort it \n";
	list->mergeSort(&(list->head));

	list->print();

	return;
}


template <typename T>
void test_3(my_list<T> * list) {
	int n_case = rand() % 4;

	switch (n_case) {
	case 0:
		int n_push_back = 300 + rand() % 500;
		cout << "Pushing back..." << n_push_back << " times \n";
		for (int i = 0; i < n_push_back; i++) {
			list->push_back(rand() % 1000);
		}
		break;
	case 1:
		int n_push_front = 200 + rand() % 100;
		cout << "Pushing front..." << n_push_front << " times \n";
		for (int i = 0; i < n_push_front; i++) {
			list->push_front(rand() % 1000);
		}
		break;
	case 2:
		int n_replace = 500 + rand() % 1000;
		int a = rand() % list->capacity;
		int b = rand() % list->capacity;
		cout << "Replacing..." << n_replace << " pairs \n";
		for (int i = 0; i < n_replace; i++) {
			list->replaceElems(a, b);
		}
		break;
	case 3:
		int n_delete = 100 + rand() % list->capacity;
		cout << "Deleting..." << n_delete << " times \n";
		for (int i = 0; i < n_delete; i++) {
			list->deleteElem_2(rand() % list->capacity);
		}
		break;
	default:
		break;
	}
}