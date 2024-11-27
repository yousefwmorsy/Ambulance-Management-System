#pragma once
#include "..//Data Structures//Queue//LinkedQueue.h"
#include "..//Data Structures//LeavablePriQueue//LeavablePriQueue.h"
#include "Car.h"
#include "Request.h"
#include "Hospital.h"
#include "ReadInput.h"

struct CancelRequest {
	int PID;
	int CancelTime;
};

class Organiser
{
private:
	int timestep;
	int HospitalCount;
	int** HospitalsDistances; //Matrix Hospital Distances
	int** Cars; //Matrix Number of cars of each hospital.
	int** CancelRequist; //to be removed
	Hospital* HospitalList;
	LinkedQueue<Request*> AllRequests;
	LeavablePriQueue OutCars;
	LinkedQueue<Car*> BackCars;
	LinkedQueue<Request*> FinishList;
	LinkedQueue<CancelRequest*> CancellationRequests;
public:
	Organiser();
	bool notEnd(); //checks that the program did not end
	void ReadInputFile(); //reads file contents
	void sendRequests(); //sends requests at current timestep to suitable hospital
	void serveRequests();
	int getTime(); //returns current timestep
	void incTime(); //increments timestep
	~Organiser();
};

