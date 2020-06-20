#include "functions.h"
#include "ROV.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// реализует проверку корректности отсчёта координат

bool check_tasks(vector<Mission*> tasks) {
	string error = "";

	ROV rov(0, 0, 0, 0);

	MoveTo* moveto = nullptr;
	Dive* dive = nullptr;
	Lift* lift = nullptr;
	Return* ret = nullptr;


	for (int i = 0; i < tasks.size(); i++) {

		if (dynamic_cast<MoveTo*>(tasks[i])) {
			moveto = dynamic_cast<MoveTo*>(tasks[i]);
			if (!rov.update_coords('M', moveto->x, moveto->y)) {
				cout << "Invalid task: " << i+1 << " \n";
				return false;
			}
		}
		else if(dynamic_cast<Dive*>(tasks[i])){
			dive = dynamic_cast<Dive*>(tasks[i]);
			if (!rov.update_coords('D', dive->z, -1)) {
				cout << "> Invalid task: " << i+1 << " \n";
				cout << "> Current z = " << rov.z << ", can't dive to " << dive->z << "\n";
				return false;
			}
		}
		else if (dynamic_cast<Lift*>(tasks[i])) {
			lift = dynamic_cast<Lift*>(tasks[i]);
			if (!rov.update_coords('L', lift->z, -1)) {
				cout << "> Invalid task: " << i+1 << " \n";
				cout << "> Current z = " << rov.z << ", can't lift to " << lift->z << "\n";		
				return false;
			}
		}
		else if (dynamic_cast<Return*>(tasks[i])) {
			ret = dynamic_cast<Return*>(tasks[i]);
			rov.update_coords('R', -1, -1);
		}
	}
	return true;
}


void printTasks(vector<Mission*> mission) {
	cout << "\nAll tasks: \n";

	for (int i = 0; i < mission.size(); i++) {
		string s_ = mission[i]->toFile();
		cout << i + 1 << ". " << s_ << "\n";
	}
	/*
		for (vector<Mission*>::iterator it = mission.begin(); it != mission.end(); it++) {
		//cout << *it << "\n";
		string s_ = (*it)->toFile();
		cout << s_ << "\n";
	}
	*/

}

void writeToFile(vector<Mission*> &mission) {

	// If not empty
	if (mission.size() == 0) {
		cout << "Can't write to file empty Task list \n";
	return;
	} 

	// If inside specified area
	if (!check_tasks(mission)) {
		cout << "\nPlease, edit mission and then try again\n";
		return;
	}
		

	Return* last = dynamic_cast<Return*>(mission[mission.size() - 1]);

	// If finished with Return
	if (last == nullptr) {
		cout << "Every missoin must be ended with Return. Appending... \n";
		Return *r = new Return();
		mission.push_back(r);
	}

	ofstream file;
	file.open("Mission.txt", ofstream::out | ofstream::trunc);

	for (int i = 0; i < mission.size(); i++) {
		string s_ = to_string(i + 1) + " " + mission[i]->toFile();
		cout << s_ << endl;
		file << s_ << endl;
	}
	file << flush;
	file.close();
	cout << "Tasks were written to file 'Missins.txt' \n";
	return;
}

void edit_task(vector<Mission*> & Missions, int id) {

	cout << "> ";
	string input_string;
	getline(cin, input_string);

	char command = input_string[0];
	int op1 = -1;
	int op2 = -1;

	istringstream iss(input_string);

	MoveTo* moveto = nullptr;
	Dive* dive = nullptr;
	Lift* lift = nullptr;
	Return* ret = nullptr;

	Mission* deleting = Missions[id - 1];
	delete(deleting);

	switch (command) {
	case 'M':
		iss >> command >> op1 >> op2;
		moveto = new MoveTo(op1, op2);
		Missions[id - 1] = moveto;
		break; 
	case 'R':
		ret = new Return();
		Missions[id - 1] = ret;
		break;
	case 'D':
		iss >> command >> op1;
		dive = new Dive(op1);
		Missions[id - 1] = dive;
		break;
	case 'L':
		iss >> command >> op1;
		lift = new Lift(op1);
		Missions[id - 1] = lift;
		break;
	}
	return;
}

void delete_task(vector<Mission*>& Missions, int id) {

	//NB: id = [1..size()]
	if (Missions.size() == 0) {
		cout << "No tasks to delete";
		return;
	}
	else if (id > Missions.size() || id < 1) {
		cout << "Index is out of range";
		return;
	}
	else if (Missions.size() == 1) {
		delete(Missions[id - 1]);
		return;
	}

	Mission* deleting = Missions[id - 1];
	delete(deleting);

	for (int i = id - 1; i < Missions.size()-1; i++) {
		Missions[i] = Missions[i+1];
	}
	//delete(Missions[Missions.size() - 1]);
	Missions.resize(Missions.size() - 1);

	return;
}


void insert_task(vector<Mission*>& Missions, int id) {

	if (id < 1 || id > Missions.size() + 1) {
		cout << "Index out of range \n";
		return;
	}

	cout << "> ";

	string input_string;
	char command;

	double op1 = -1;
	char op1_k = '.';
	double op2 = -1;
	char op2_k = '.';

	const char key = '/';
	
	getline(cin, input_string);

	command = input_string[0];

	istringstream iss(input_string);
	iss >> command >> op1_k >> op1 >> op2_k >> op2;

	MoveTo* moveto = nullptr;
	Dive* dive = nullptr;
	Lift* lift = nullptr;
	Return* ret = nullptr;
	Mission* m = nullptr;

	ROV r(0, 0, 0, 0);

	switch (command) {
	case 'M':
		if (op1_k != key || op2_k != key) {
			cout << "Not enough args \n";
			break;
		}
		else if (op1 < 0 || op2 < 0 || op1 > r.MAX_X || op2 > r.MAX_Y) {
			cout << "\t Insertion failed: " << "op1 < 0 || op2 < 0 || op1 > MAX_X || op2 > MAX_Y \n";
			break;
		}
		moveto = new MoveTo(op1, op2);
		m = moveto;
		break;

	case 'R':
		ret = new Return();
		m = ret;
		break;

	case 'D':
		if (op1_k != key) {
			cout << "Not enough args \n";
			break;
		}
		else if (op1 > r.MAX_Z || op1 < 0 || r.z > op1) {
			cout << "\t Insertion failed: " << "op1 > MAX_Z || op1 < 0 || z > op1 \n";
			break;
		}
		dive = new Dive(op1);
		m = dive;
		break;

	case 'L':
		if (op1_k != key) {
			cout << "Not enough args \n";
			break;
		}
		else if (op1 > r.MAX_Z || op1 < 0 || r.z < op1) {
			cout << "\t Insertion failed: " << "op1 > MAX_Z || op1 < 0 || z < op1 \n";
			break;
		}
		lift = new Lift(op1);
		m = lift;
		break;
	}

	if (Missions.size() == 0 || id > Missions.size()) {
		Missions.push_back(m);
		return;
	}


	int counter = 0;
	for (auto it = Missions.begin(); it != Missions.end(); ++it) {
		counter++;
		if (counter == id) {
			Missions.insert(++it, m);
			break;
		}
	}

	return;
}

void exchange_tasks(vector<Mission*>& Missions, int id1, int id2) {

	Mission* temp = nullptr;

	if (id1 > 0 && id1 <= Missions.size() && id2 > 0 && id2 <= Missions.size()) {
		temp = Missions[id1-1];
		Missions[id1-1] = Missions[id2-1];
		Missions[id2-1] = temp;
	}
	else {
		cout << "Argumants out of range \n";
	}
	return;
}

void read_from_file(vector<Mission*>& Missions, string path = "Mission.txt") {

	string line;
	int id = 0;
	string command = "";
	double op1 = -1;
	double op2 = -1;

	ifstream in(path);

	if (in.is_open()) {
		while (getline(in, line)) {
			cout << line << endl;

			istringstream iss(line);
			iss >> id >> command;

			MoveTo* moveto = nullptr;
			Dive* dive = nullptr;
			Lift* lift = nullptr;
			Return* ret = nullptr;

			switch (command[0]) {
			case 'M':
				iss >>  op1 >> op2;
				moveto = new MoveTo(op1, op2);
				Missions.push_back(moveto);
				break;
			case 'R':
				iss >> op1;
				ret = new Return();
				Missions.push_back(ret);
				break;
			case 'D':
				iss  >> op1;
				dive = new Dive(op1);
				Missions.push_back(dive);
				break;
			case 'L':
				iss >> op1;
				lift = new Lift(op1);
				Missions.push_back(lift);
				break;
			}
		}
		in.close();
		cout << "End of reading of file \n";
	}
	else {
		cout << "Can't read from file";
	}
	return;
}

void print_help() {
	cout << "  Small help \n";

	cout << setw(9) << " M /X /Y"  <<" - move to" << "\n";
	cout << setw(9) << " R"  << " - return" << "\n";
	cout << setw(9) << " D /d" << " - dive to Depth" << "\n";
	cout << setw(9) << " L /h"  << " - lift" << "\n";

	cout << "\n";
	cout << setw(9) << "e /id" << " - edit" << "\n";
	cout << setw(9) << "p" << " - print tasks" << "\n";
	cout << setw(9) << "d /id" << " - delete task" << "\n";
	cout << setw(9) << "i /id" << " - insert task" << "\n";
	cout << setw(9) << "x /id1 /id2" << " - exchange tasks" << "\n";

	cout << setw(9) << "w" << " - write to file" << "\n";
	cout << setw(9) << "r" << " - read from file" << "\n";
	cout << setw(9) << "q" << " - quit" << "\n\n";
}