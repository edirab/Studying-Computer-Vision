#include <iostream>
#include <stdio.h>
#include <string>
#include <clocale>
#include <map>
//#include <cctype>
#include <vector>

using namespace std;

class Sensor {
public:
	short id;
	string name;
	short bytesToRead;
	string value_s;
	float data;
	string units;

	Sensor(short i, string n, short b, string u) {
		id = i;
		name = n;
		bytesToRead = b;
		value_s = "";
		data = -1;
		units = u;
	}
};

// прототипы функций
void fiil_structure();
void print_sensors(map<int, Sensor*>);
float convert(string);
void parse(string);


short array_ids[] = { 5, 24, 25, 79, 77, 7, 8, 9, 21, 22, 23, 27, 28, 29, 74, 75, 76 };
string array_names[] = { "kHeading", "kPitch",  "kRoll", "kHeadingStatus", "kQuaternion", "kTemperature", "kDistortion",	"kCalStatus", "kAccelX", "kAccelY", "kAccelZ", "kMagX", "kMagY", "kMagZ", "kGyroX", "kGyroY", "kGyroZ" };
short bytesToRead[] = { 4, 4, 4, 1, 4 * 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4 };
string array_units[] = { "deg", "deg", "deg", "none", "none", "deg*s", "logic", "logic", "g", "g", "g", "mT", "mT", "mT", "rad/s", "rad/s", "rad/s" };

map<int, Sensor*> sensors;

