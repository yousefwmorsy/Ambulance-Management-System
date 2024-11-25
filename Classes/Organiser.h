#pragma once
#include "..//Data Structures//Queue//LinkedQueue.h"
#include "Car.h"
#include "Request.h"
#include "Hospital.h"

struct CancelRequest {
	int PID;
	int CancelTime;
};

class Organiser
{
private:
	int timestep;
	int HospitalCount;
	Hospital* HospitalList;
	LinkedQueue<Request> AllRequests;
	LinkedQueue<Car> OutCars;
	LinkedQueue<Car> BackCars;
	LinkedQueue<Request> FinishList;
	LinkedQueue<CancelRequest> CancellationRequests;
public:
	Organiser();
	void readFile(); //reads file contents
	bool notEnd(); //checks that the program did not end
	void addCar(bool isSpecial, int HospitalID); //creates car object and assigns to hospital
	void addHospital(int HospitalID); //creates hospital object
	void addNPRequest(); //creates NP request object and assigns to hospital
	void addSPRequest(); //creates SP request object and assigns to hospital
	void addEPRequest(); //creates EP request object and assigns to hospital
	int getTime(); //returns current timestep
	void incTime(); //increments timestep
	~Organiser();
};

