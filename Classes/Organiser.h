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
	int** CancelRequist; //
	Hospital* HospitalList;
	LinkedQueue<Car> OutCars;
	LinkedQueue<Car> BackCars;
	LinkedQueue<Request> Requests;
	LinkedQueue<Request> FinishList;
	LinkedQueue<Request*> AllRequests;
	LinkedQueue<Car*> OutCars;
	LinkedQueue<Car*> BackCars;
	LinkedQueue<Request*> FinishList;
	LinkedQueue<CancelRequest*> CancellationRequests;
public:

	Organiser();
	void readFile(); //reads file contents
	bool notEnd(); //checks that the program did not end
	void  ReadInputFile(); //reads file contents
	void addCar(bool isSpecial, int HospitalID); //creates car object and assigns to hospital
	void addHospital(int HospitalID); //creates hospital object
	void serveRequests();
	void addNPRequest(); //creates NP request object and assigns to hospital
	void addSPRequest(); //creates SP request object and assigns to hospital
	void addEPRequest(); //creates EP request object and assigns to hospital
	int getTime(); //returns current timestep
	void incTime(); //increments timestep

	void SetNormlCarSpeed(int Ns); //Set the speed of the normal car.
	void SetSpecialCarSpeed(int Ss);
	~Organiser();
};

