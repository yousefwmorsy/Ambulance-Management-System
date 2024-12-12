#pragma once
#include "..//Data Structures//Queue//LinkedQueue.h"
#include "..//Data Structures//LeavablePriQueue//LeavablePriQueue.h"
#include "Car.h"
#include "Request.h"
#include "Hospital.h"
#include "UI.h"

struct CancelRequest {
	int PID;
	int HID;
	int CancelTime;
};

class Organiser
{
private:
	int timestep;
	int HospitalCount;
	int** HospitalsDistances; //Matrix Hospital Distances
	int TotalRequestsCount;
	int FinishedRequestsCount;
	Hospital* HospitalList;
	LinkedQueue<Request*> AllRequests;
	LeavablePriQueue OutCars;
	LinkedQueue<Car*> BackCars;
	LinkedQueue<Request*> FinishList;
	LinkedQueue<CancelRequest*> CancellationRequests;
	UI I;
public:
	Organiser();
	bool notEnd(); //checks that the program did not end
	void ReadInputFile(); //reads file contents
	void sendRequests(); //sends requests at current timestep to suitable hospital
	int getTime(); //returns current timestep
	void incTime(); //increments timestep
	void Simulation();
	~Organiser();
};

