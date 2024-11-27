#pragma once
#include "..//Data Structures//Queue//LinkedQueue.h"
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
	LinkedQueue<Car*> OutCars;
	LinkedQueue<Car*> BackCars;
	LinkedQueue<Request*> FinishList;
	LinkedQueue<CancelRequest*> CancellationRequests;
public:
	Organiser();
	bool notEnd(); //checks that the program did not end
	void ReadInputFile(); //reads file contents
	void addCar(bool isSpecial, int HospitalID); //creates car object and assigns to hospital
	void addHospital(int HospitalID); //creates hospital object
	void serveRequests();
	int getTime(); //returns current timestep
	void incTime(); //increments timestep
	void SetNormlCarSpeed(int Ns); //Set the speed of the normal car.
	void SetSpecialCarSpeed(int Ss);
	~Organiser();
};

