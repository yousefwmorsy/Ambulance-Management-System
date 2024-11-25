#pragma once
#include "Car.h"
#include <iostream>
using namespace std;
class Request
{
protected:
	bool isSpecial;
	int QT;
	int Pid;
	int nearestHid;
	int distance;
	Car* PickUpcar; //not needed, car would point to patient not the other way around
public:
	Request(bool t , int q, int p, int hi, int d);
	int getQT();
	friend ostream& operator << (ostream& out, const Request& r);
	//Make operator (=) overloading
};

