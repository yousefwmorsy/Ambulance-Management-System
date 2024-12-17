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
	LinkedQueue<Request*> FinishList;
	LinkedQueue<CancelRequest*> CancellationRequests;
	priQueue <Request*>  waitEP; //used for handling EP that couldn't be handled in there timestep
	UI I;
	priQueue<Car*> CheckupList;
public:
	Organiser();
	bool notEnd(); //checks that the program did not end
	void ReadInputFile(); //reads file contents
	void sendRequests(); //sends requests at current timestep to suitable hospital
	int getTime(); //returns current timestep
	void incTime(); //increments timestep
	void Simulation();
	Car* CarFailure(int);
	void OutCarFailureAction(Car*);
	void BackCarFailureAction(Car*);
	void ReturnRepairedCars();
	void linkCarToPatient( Car*& Car);
	void linkCarToPatient(Request*& Patient, Car*& Car);
	void finishRequest(Request*& Patient);
	void carReachedPatient(Car*& Car);
	void carReachedHospital(Car*& Car);
	void checkCancelRequests();
	void checkOutCarsReached();
	void checkBackCarsReached();
	void handlingEP();
	void serveRequests();
	~Organiser();
};

