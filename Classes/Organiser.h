#pragma once
#include "..//Data Structures//Queue//LinkedQueue.h"
#include "..//Data Structures//PriQueue//priQueue.h"
#include "Car.h"
#include "Request.h"
#include "Hospital.h"

class Organiser
{
private:
	int timestep;
	int HospitalCount;
	Hospital* HospitalList;
	priQueue<Car> OutCars;
	priQueue<Car> BackCars;
	LinkedQueue<Request> FinishList;
	//LinkedQueue<Request> AllRequests;
public:
	Organiser();
	void readFile(); //reads file contents
	int getTime();
	void incTime();
	~Organiser();
};

