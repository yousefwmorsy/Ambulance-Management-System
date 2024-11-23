#pragma once
#include "Car.h"
#include"..//Data Structures/Queue/LinkedQueue.h"
class Hospital
{private:
	int numNcars;
	int numScars;
	int hospitalID;
	LinkedQueue <Car> * carN;
	LinkedQueue <Car> * carS;
public:
	Hospital();
	Hospital(int hID, int SpecialCarCount, int NormalCarCount);
};

