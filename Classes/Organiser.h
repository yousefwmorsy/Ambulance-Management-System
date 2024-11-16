#pragma once
#include "..//Data Structures//Queue//LinkedQueue.h"
#include "Car.h"
#include "Request.h"
#include "Hospital.h"

class Organiser
{
private:
	int timestep;
	int HospitalCount;
	Hospital* HospitalList;
	/*LinkedQueue<Car> OutCars;
	LinkedQueue<Car> BackCars;
	LinkedQueue<Request> FinishList;*/
public:
	Organiser();
	void readFile(); //reads file contents
	int getTime();
	void incTime();
	~Organiser();
};

