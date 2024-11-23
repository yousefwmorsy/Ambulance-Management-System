#pragma once
#include "Car.h"
class Request
{
private:
	bool isSpecial;
	int QT;
	int Pid;
	int nearestHid;
	int distance;
	Car* PickUpcar; //not needed, car would point to patient not the other way around
};

