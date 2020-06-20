// task_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <sstream>
#include <string>
#include <clocale>
#include <vector>

#include "Missions.h"
#include "ROV.h"
#include "functions.h"

using namespace std;

int main() {

	
	ROV Rov(0, 0, 0, 0);
	vector<Mission*> Tasks;
	vector<char> TasksSequence;

	string Input = "";
	string New_missin = "";

	char command;

	double op1 = -1;
	char op1_k = '.';
	double op2 = -1;
	char op2_k = '.';

	const char key = '/';

	print_help();

	while (true) {

		getline(cin, Input);

		if (Input == "q") break;
		else if (Input == "" || Input == "\n") continue;

		op1_k = op2_k = '.';

		command = Input[0];

		istringstream iss(Input);
		iss >> command >> op1_k >> op1 >> op2_k >> op2;

		MoveTo *moveto = nullptr;
		Dive* dive = nullptr;
		Lift *lift = nullptr;
		Return *ret = nullptr;


		switch (command) {
		case 'M':
			if (op1_k != key || op2_k != key) {
				cout << "Not enough args \n";
				break;
			}
			else if (!Rov.update_coords(command, op1, op2)) break;
				moveto = new MoveTo(op1, op2);
				Tasks.push_back(moveto);
				TasksSequence.push_back(command);
			break;
		case 'R':
				ret = new Return();
				Tasks.push_back(ret);
				TasksSequence.push_back(command);
			break;

		// задаётся координата по z (z < 0)
		case 'D':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			else if (!Rov.update_coords(command, op1, op2)) break;
				dive = new Dive(op1);
				Tasks.push_back(dive);
				TasksSequence.push_back(command);
			break;
		// задаётся координата по z (z > 0)
		case 'L':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			else if (!Rov.update_coords(command, op1, op2)) break;
				lift = new Lift(op1);
				Tasks.push_back(lift);
				TasksSequence.push_back(command);
			break;

		case 'e':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			edit_task(Tasks, int(op1));
			break;
		case 'h':
			print_help();
			break;
		case 'p':
			printTasks(Tasks);
			break;
		case 'w':
			writeToFile(Tasks);
			break;
		case 'd':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			delete_task(Tasks, int(op1));
			break;
		case 'i':
			if (op1_k != key) {
				cout << "Not enough args \n";
				break;
			}
			else
			insert_task(Tasks, int(op1));
			break;
		case 'x':
			if (op1_k != key || op2_k != key) {
				cout << "Not enough args \n";
				break;
			}
			exchange_tasks(Tasks, int(op1), int(op2));
			break;
		case 'r':
			// ../Missions.txt
			// D:\Университет\9 sem\С++\code\task_3
			read_from_file(Tasks, "F:\\Университет\\9sem\\С++\\code\\task_3\\Mission.txt");
			break;
		}
	}
}

