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
	int OutCarsFailureProbability;
	int BackCarsFailureProbability;
	int OCarCount;
	int BCarCount;
	Hospital* HospitalList;
	LeavableQueue AllRequests;
	LeavablePriQueue OutCars;
	priQueue<Car*> BackCars;
	priQueue<Car*> FailedBackCars;
	LinkedQueue<Request*> FinishList;
	LinkedQueue<CancelRequest*> CancellationRequests;
	UI I;
	priQueue<Car*> CheckupList;
public:
	Organiser();
	bool notEnd(); //checks that the program did not end
	void ReadInputFile(); //reads file contents
	void sendRequests(); //sends requests at current timestep to suitable hospital
	void Simulation();
	Car* CarFailure(int , int &t);
	void OutCarFailureAction(Car*, int t);
	void BackCarFailureAction(Car*, int t);
	void ReturnRepairedCars();
	void linkCarToPatient(Request*& Patient, Car*& Car);
	void finishRequest(Request*& Patient);
	void carReachedPatient(Car*& Car);
	void carReachedHospital(Car*& Car);
	void checkOutCarsReached();
	void checkBackCarsReached();
	void checkCancelRequests();
	~Organiser();
};

