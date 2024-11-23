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
	LinkedQueue<Request> AllRequests;
	LinkedQueue<Car> OutCars;
	LinkedQueue<Car> BackCars;
	LinkedQueue<Request> FinishList;
public:
	Organiser();
	void readFile(); //reads file contents
	void addCar(bool isSpecial, int HospitalID); //creates car object and assigns to hospital
	void addHospital(int HospitalID); //creates hospital object
	void addNPRequest(); //creates NP request object and assigns to hospital
	void addSPRequest(); //creates SP request object and assigns to hospital
	void addEPRequest(); //creates EP request object and assigns to hospital
	int getTime(); //returns current timestep
	void incTime(); //increments timestep
	~Organiser();
};

