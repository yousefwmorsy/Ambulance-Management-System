#pragma once
#include "Car.h"
#include"..//Data Structures/Queue/LinkedQueue.h"
class Hospital
{private:
	int numNcars;
	int numScars;
	int hospitalID;
	LinkedQueue <Car> carN;
	LinkedQueue <Car> carS;
public:
	Hospital(){}
	Hospital(int hID,int SpecialCarCount,int NormalCarCount) {
		for (int i = 0; i < SpecialCarCount; i++)
		{
			Car* temp = new Car(hID,i+1,true);
			carS.enqueue(*temp);
		}
		for (int i = 0; i < NormalCarCount; i++)
		{
			Car* temp = new Car(hID,i+1,false);
			carN.enqueue(*temp);
		}
	}
};

