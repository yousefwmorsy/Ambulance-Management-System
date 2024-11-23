#pragma once
#include "Car.h"
#include <iostream>
using namespace std;
class Request
{
private:
	bool isSpecial;
	int QT;
	int Pid;
	int nearestHid;
	int distance;
	Car* PickUpcar; //not needed, car would point to patient not the other way around
public:
	friend ostream& operator << (ostream& out, const Request& r);
};

