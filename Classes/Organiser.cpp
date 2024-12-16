#include "Organiser.h"
#include <iostream>
#include "time.h"
#include "random"
#include "UI.h"
using namespace std;

Organiser::Organiser()
{
	timestep = 0;
	OCarCount = 0;
	BCarCount = 0;
}

bool Organiser::notEnd()
{
	//checks if all requests were served
	return (FinishedRequestsCount != TotalRequestsCount);
}

void Organiser::sendRequests()
{
	//sends request to suitable hospital in the suitable list
	//called every timestep
	Request* R;
	while (AllRequests.peek(R) && R->getQT() == timestep) {
		AllRequests.dequeue(R);
		HospitalList[R->getHospitalID() - 1].setRequest(R);
	}
}

void Organiser::Simulation(){
	ReadInputFile();
	Car* C; int i;
	int EnteredRequests = 0;

	while (notEnd()) {
		Request* R = new Request;
		Car* FailedCar;
		//Step1: Send each request to it's hospital at it's request time
		sendRequests();

		//Step2: Assigns Hospitals' patients to it's APPROPRIATE FREE cars
		for (int i = 0; i < HospitalCount; i++)
		{
		/*
		Looping at each timestep on all patients
		and Assign Cars to
		its patient "IF HOSPITAL HAS THE APPROPRIATE CAR OF THE REQUEST" -> ASSSIGN FUNCTIONS
		*/
		}

		//Step3: Check the canceled requests
		//Yousef Wael
		
		//Step4: Random on OutCats for choose a car and start OutCar failure Action
		if (!OutCars.isEmpty()) {
			int t = 0;
			FailedCar = CarFailure(1, t);
			if (FailedCar) {
				OutCarFailureAction(FailedCar, t); 
			}
		}
		
		//Step5: If the car reached the patient put it in BackCars from OutCars
		checkOutCarsReached();
		
		//Step6: Random on BackCars for choose a car and start BackCar failure Action
		if (!BackCars.isEmpty()) {
			int t = 0;
			FailedCar = CarFailure(0, t);
			if (FailedCar) {
				BackCarFailureAction(FailedCar, t); //Not Finished
			}
		}
		
		//Step7: When the time of reaching car to its hospital comes,
		//the car should return to its Hospital and drop the patient.
		checkBackCarsReached();

		//Step8: Check for returned cars from the checkup list
		while (CheckupList.peek(C,i) && -1*i == timestep) {
			CheckupList.dequeue(C, i);
			C->SetCarToFail(false);
			HospitalList[C->GetHospitalID() - 1].addCar(C);
		}
		timestep++;
	}

}

Car* Organiser::CarFailure(int x, int &t)
{
	/*
	Generate a number and chick if the number is within the Failure Probability
	make a copy of the OutCars and Generate a number within the num of OutCars
	then Bick the car from the list; 
	*/
	int FailureProbability, CarsCount;
	LeavablePriQueue Temp;
	if (x) {   // 1: OutCars, 0: BackCars = 1;
		FailureProbability = OutCarsFailureProbability;
		CarsCount = OCarCount;
		Temp = OutCars;
	}
	else {
		FailureProbability = BackCarsFailureProbability;
		CarsCount = BCarCount;
		priQueue<Car*> Temp = BackCars;
	}
	srand(time(0));
	int randProb = rand() % 100 + 1;
	Car* RandCar = nullptr;
	if (randProb < FailureProbability) {
		int x = rand() % CarsCount, y;
		for (int i = 0; i <= x; i++) {
			Temp.dequeue(RandCar, y);
		}
		RandCar->SetCarToFail(true);
		t = y;
		return RandCar;
	}
	return RandCar;
}

void Organiser::OutCarFailureAction(Car* C, int t)
{
	int p, id = C->GetCarID();
	Request* R = C->getPatient();
	int TimeToBack = t - timestep; // Get the time to return to the hospital
	HospitalList[C->GetHospitalID() - 2].SetFailurePatient(C->dropPatient()); //Return the request to the hospital
	BackCars.enqueue(C, -1*t); // Put the car in the BackCars from its frailer position
}
//NOT FINISHED
void Organiser::BackCarFailureAction(Car*C, int t)
{
	FailedBackCars.enqueue(C,t);
	Car* FBC; int StopedBackTime;
	int CarsCount = HospitalList[C->GetHospitalID() - 1].getNcars() + HospitalList[C->GetHospitalID() - 1].getScars();
	if (CarsCount) {
		//Assign new car from the same hospital to pick the patient and come with the car
		// Waiting for Assigns functions.....
		if (/*Assigning is */true) {
			// Set the Car to BackCars
		}
	}
	while (FailedBackCars.dequeue(FBC, StopedBackTime)) {
		StopedBackTime--;
		FailedBackCars.enqueue(FBC, StopedBackTime);
	}
}

void Organiser::ReturnRepairedCars()
{
}

void Organiser::linkCarToPatient(Request*& Patient, Car*& Car)
{
	int timeToReach = ((Patient->getDistance()) / Car->getSpeed());
	int pickupTime = timestep + timeToReach;
	OutCars.enqueue(Car, -1 * pickupTime); //add to outcars, priority is the absolute reach time [timestep + distance/speed]
	Patient->setAT(timestep); //sets the assignment time of patient to current timestep
	Car->setPatient(Patient); //links patient to car and sets status as "Assigned"
	Car->incBusyTime(timeToReach); //increments busy time
}

void Organiser::finishRequest(Request*& Patient)
{
	FinishList.enqueue(Patient);
	FinishedRequestsCount++;
}

void Organiser::carReachedPatient(Car*& Car)
{
	Request* Patient = Car->getPatient();
	int timeToReach = ((Patient->getDistance()) / Car->getSpeed());
	int returnTime = timestep + timeToReach;
	Patient->setPT(timestep); //sets the pickup time of patient to current timestep
	Car->setStatus("Loaded"); //sets status of car to "Loaded"
	Car->incBusyTime(timeToReach); //increments busy time
	BackCars.enqueue(Car, -1 * returnTime); //add to backcars, priority is absolute reach time
}

void Organiser::carReachedHospital(Car*& Car)
{
	if (Car->GetFailingCondition()) {
		CheckupList.enqueue(Car,timestep + 10);
		return;
	}
	Request* Patient = Car->dropPatient();//car drops patient and status set to free
	HospitalList[Car->GetHospitalID()].addCar(Car); //car is added to free list of hospital
	Patient->setFT(timestep); //finish time is set to current timestep
	finishRequest(Patient); //patient sent to finished request list
}

void Organiser::checkOutCarsReached()
{
	Car* Car;
	int priority;
	while (OutCars.peek(Car, priority) && timestep == priority*-1)
	{
		OutCars.dequeue(Car, priority);
		carReachedPatient(Car);
	}
}

void Organiser::checkBackCarsReached()
{
	Car* Car;
	int priority;
	while (BackCars.peek(Car, priority) && timestep == priority * -1)
	{
		BackCars.dequeue(Car, priority);
		carReachedHospital(Car);
	}
}

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances;
}



