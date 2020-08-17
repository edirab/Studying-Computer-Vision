#pragma once

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

class Object {
public:
	virtual std::string toString() = 0;
	virtual void read(std::string val, int* index) = 0;

	virtual ~Object() = default;
};

class Float : public Object {
public:
	float value;
	Float();
	Float(float value);
	~Float();
	std::string toString();
	void read(std::string val, int* index);
};

class Char : public Object {
public:
	char value;
	Char();
	Char(char value);
	~Char();
	std::string toString();
	void read(std::string val, int* index);
};

class Boolean : public Object {
public:
	bool value;
	Boolean();
	Boolean(bool value);
	~Boolean();
	std::string toString();
	void read(std::string val, int* index);
};

class Quaternion : public Object {
public:
	float w, x, y, z;
	Quaternion();
	Quaternion(float w, float x, float y, float z);
	Quaternion(float value[]);
	~Quaternion();
	std::string toString() override;
	void read(std::string val, int* index);
};


class Parcel {
public:
	enum class Field { Boolean, Char, Float, Quaternion };

private:
	std::map<int, Object*> data;
	std::map<int, std::string> names;
	std::map<int, std::string> units;
	std::map<int, Field> types;

public:
	Parcel();
	~Parcel();

	void addField(int id, std::string name, std::string unit, Field type);
	void readId(int id, std::string val, int *index);
	void toString();
};

class PNITraxParcel : public Parcel {
public:
	PNITraxParcel();
};