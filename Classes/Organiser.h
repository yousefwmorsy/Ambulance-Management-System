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
	int CheckUpTime;
	int CheckCarCount;
	int SCarCount;
	int NCarCount;
	int CarsCount;
	Hospital* HospitalList;
	LeavableQueue AllRequests;
	LeavablePriQueue OutCars;
	LeavablePriQueue BackCars;
	LeavablePriQueue FailedBackCars;
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
	void Simulation();
	Car* CarFailure(int , int &t, int &c);
	void OutCarFailureAction(Car*, int t);
	void BackCarFailureAction(Car*, int t);
	void ReturnRepairedCars();
	void linkCarToPatient(Car* Car, Request* R, int t);
	void finishRequest(Request* Patient);
	void carReachedPatient(Car* Car, int t);
	void carReachedHospital(Car* Car);
	void checkCancelRequests();
	void checkOutCarsReached();
	void checkBackCarsReached();
	void handlingEP();
	void serveRequests();
	bool thereIsHospitalCanServe();
	int CheckUpCarC();
	void CreateOutputFile();
	void rescueFailedCar(Car*C);
	~Organiser();
};

