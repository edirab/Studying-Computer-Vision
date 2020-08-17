// task_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <string>
#include <clocale>
#include "my_list.h"

using namespace std;


void print_help() {
	cout << "Small help \n";
	cout << "b /op1 - push_back" << "\n";
	cout << "f /op1 - push_front" << "\n";
	cout << "d /idx - delete" << "\n";
	cout << "i /idx1 /op1 - insert" << "\n";
	cout << "e /idx1 /idx2 - exchange" << "\n";
	cout << "s - sort" << "\n";
	cout << "g /idx1 - get" << "\n";
	cout << "p - print list" << "\n";
	cout << "r - print reversed" << "\n";
	cout << "h - print this help" << "\n\n";
}

int main() {
	setlocale(0, "");

	my_list<int>* list = new my_list<int>;

	string Input = "";

	char command;

	int op1 = -1;
	char op1_k = '.';

	int op2 = -1;
	char op2_k = '.';

	const char key = '/';

	print_help();

	while (true) {

		getline(cin, Input);
		if (Input == "q") 
			break;

		command = Input[0];
		op1_k = op2_k = '.';

		istringstream iss(Input);
		iss >> command >> op1_k >> op1 >> op2_k >> op2;


		switch (command) {
		case 'b':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			list->push_back(op1);
			break;
		case 'f':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			list->push_front(op1);
			break;
		case 'e':
			if (op1_k != key || op2_k != key) {
				cout << "Not enough args \n";
				break;
			}
			list->replaceElems(op1, op2);
			break;
		case 's':
			list->mergeSort(&list->head);
			break;
		case 'd':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			list->deleteElem_2(op1);
			break;
		case 'i':
			if (op1_k != key || op2_k != key) {
				cout << "Not enough args \n";
				break;
			}
			list->insertElem(op1, op2);
			break;
		case 'g':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			if (list->getElem(op1) != nullptr)
				cout << op1 << " : " << list->getElem(op1)->data << "\n";
			else
				cout << " : nullptr \n";
			break;
		case 'h':
			print_help();
			break;
		case 'p':
			list->print();
			break;
		case 'r':
			list->printReversed();
			break;

		}
	}

	system("pause");
	return 0;
}
