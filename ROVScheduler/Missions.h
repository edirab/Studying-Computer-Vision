
#ifndef __MISSION_H__
#define __MISSION_H__

#pragma once

#include <string>

using namespace std;


class Mission {
public:
	virtual string toFile() = 0;
};


class MoveTo : public Mission {

public:
	double x = 0;
	double y = 0;

	MoveTo(double X, double Y);
	string toFile();
};


class Dive : public Mission {
	
public:
	double z = 0;

	Dive(double d);
	string toFile();
};


class Lift : public Mission {
	
public:
	double z = 0;

	Lift(double UP);
	string toFile();
};


class Return : public Mission {
public:
	Return() {};
	string toFile();
};

#endif