#pragma once
#include "Car.h"
#include"..//Data Structures/Queue/LinkedQueue.h"
#include "Organiser.h"
#include "..//Data Structures/PriQueue/priQueue.h"
class Hospital
{private:
	int numNcars;
	int numScars;
	int hospitalID;
	LinkedQueue <Car*> * carN;
	LinkedQueue <Car*> * carS;
	LinkedQueue <Request*>* specialRequest;
	LinkedQueue <Request*>* normalRequest; //in the future it need to be special linkedqueue
	priQueue <Request*>* emergencyRequest;
	Organiser* org;
public:
	Hospital();
	Hospital(int SpecialCarCount, int NormalCarCount,Organiser *orga);
	void addCar(Car* ptr); //send a pointer of car normal or Spectial and it add it to the list
	void setRequest(Request*); //for normal and special
	friend ostream& operator << (ostream& out, const Hospital& h);
};

