#include "PNI.h"
#include "functions.h"
#include <stdio.h>

using namespace std;

Float::Float() {
	this->value = 0.0;
}
Float::Float(float value) {
	this->value = value;
}
Float::~Float() {
}
string Float::toString() {
	return to_string(this->value);
}
void Float::read(string val, int* index) {
	unsigned long result = 0;
	result = convert(val.substr(0, 4*2));
	*index += 4*2;
	this->value = *reinterpret_cast<float*>(&result);
}


Char::Char() {
	this->value = 0;
}
Char::Char(char value) {
	this->value = value;
}
Char::~Char() {
}
string Char::toString() {
	return std::to_string(this->value);
}
void Char::read(string val, int* index) {
	unsigned long result = 0;
	result = convert(val.substr(0, 1*2));
	*index += 2;
	this->value = *reinterpret_cast<char*>(&result);
}


Boolean::Boolean() {
	this->value = false;
}
Boolean::Boolean(bool value) {
	this->value = value;
}
Boolean::~Boolean() {
}
std::string Boolean::toString() {
	return this->value ? "+" : "-";
}
void Boolean::read(std::string val, int* index) {
	unsigned long result = 0;
	result = convert(val.substr(0, 1*2));
	*index += 2;
	this->value = *reinterpret_cast<bool*>(&result);
}

Quaternion::Quaternion() {
	this->w = 0.0;
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
}
Quaternion::Quaternion(float w, float x, float y, float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}
Quaternion::Quaternion(float value[]) {
	this->w = value[0];
	this->x = value[1];
	this->y = value[2];
	this->z = value[3];
}
Quaternion::~Quaternion() {
}
std::string Quaternion::toString() {
	return std::to_string(this->w) + " + " +
		std::to_string(this->x) + "i + " +
		std::to_string(this->y) + "j + " +
		std::to_string(this->z) + "k";
}
void Quaternion::read(std::string val, int* index) {
	unsigned long result = 0;
	result = convert( val.substr(0, 4*2));
	this->w = *reinterpret_cast<float*>(&result);
	result = convert(val.substr(4*2, 4*2));
	this->x = *reinterpret_cast<float*>(&result);
	result = convert(val.substr(8*2, 4*2));
	this->y = *reinterpret_cast<float*>(&result);
	result = convert(val.substr(12*2, 4*2));
	this->z = *reinterpret_cast<float*>(&result);
	
	*index += 16*2;
}


Parcel::Parcel() {
	}

Parcel::~Parcel() {
		for (auto it = data.begin(); it != data.end(); ++it) {
			delete it->second;
		}
	}

void Parcel::addField(int id, std::string name, std::string unit, Field type) {
	this->names[id] = name;
	this->units[id] = unit;
	this->types[id] = type;
}

void Parcel::readId(int id, std::string val, int* index) {
	Object* field = nullptr;
	switch (types[id]) {
	case Field::Boolean:
		field = new Boolean();
		break;
	case Field::Char:
		field = new Char();
		break;
	case Field::Float:
		field = new Float();
		break;
	case Field::Quaternion:
		field = new Quaternion();
		break;
	}
	field->read(val,  index);
	if (data.find(id) != data.end()) {
		delete data[id];
	}
	this->data[id] = field;
}

void Parcel::toString() {
	//std::string str = "id   name        value\n";
	printf("%2s | %14s | %10s | %6s \n", "id", "name", "value", "unit");
	for (auto const& pair : data) {
		int id = pair.first;
		string value = pair.second->toString();
		string name = names[id];
		string unit = units[id];
		//str += to_string(id) + "   " + name + "    " + value + " " + unit + "\n";
		printf("%2d | %14s | %10s | %6s \n", id, name.c_str(), value.c_str(), unit.c_str());
	}
	return;
}


PNITraxParcel::PNITraxParcel() : Parcel() {
		this->addField(5, "kHeading", "deg.", Field::Float);
		this->addField(24, "kPitch", "deg.", Field::Float);
		this->addField(25, "kRoll", "deg.", Field::Float);
		this->addField(79, "kHeadingStatus", "", Field::Char);
		this->addField(77, "kQuaternion", "", Field::Quaternion);
		this->addField(7, "kTemperature", "deg.C", Field::Float);
		this->addField(8, "kDistortion", "", Field::Boolean);
		this->addField(9, "kCalStatus", "", Field::Boolean);
		this->addField(21, "kAccelX", "g", Field::Float);
		this->addField(22, "kAccelY", "g", Field::Float);
		this->addField(23, "kAccelZ", "g", Field::Float);
		this->addField(27, "kMagX", "mT", Field::Float);
		this->addField(28, "kMagY", "mT", Field::Float);
		this->addField(29, "kMagZ", "mT", Field::Float);
		this->addField(74, "kGyroX", "rad/s", Field::Float);
		this->addField(75, "kGyroY", "rad/s", Field::Float);
		this->addField(76, "kGyroZ", "rad/s", Field::Float);
}
