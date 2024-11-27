#pragma once
#include "Request.h"
#include "EPRequest.h"
#include "Car.h"
#include"..//Data Structures/Queue/LinkedQueue.h"
#include "..//Data Structures/PriQueue/priQueue.h"

class Hospital
{private:
	int numNcars;
	int numScars;
	int hospitalID;
	LinkedQueue <Car*> carN;
	LinkedQueue <Car*> carS;
	LinkedQueue <Request*> specialRequest;
	LinkedQueue <Request*> normalRequest; //in the future it need to be special linkedqueue
	priQueue <Request*> emergencyRequest;
public:
	Hospital() {}
	Hospital(int SpecialCarCount, int NormalCarCount);
	void addCar(Car* ptr); //send a pointer of car normal or Special and it add it to the list
	void setRequest(Request*); //for normal and special
	//friend ostream& operator << (ostream& out, const Hospital& h);
};

