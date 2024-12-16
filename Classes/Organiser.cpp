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

int Organiser::getTime()  //WHY?
{
	return timestep; 
}

void Organiser::incTime() //WHY?
{
	timestep++;
}

void Organiser::Simulation(){
	ReadInputFile();
 	
	int EnteredRequests = 0;

	while (notEnd()) {
		Request* R = new Request;
		Car* FailedCar;
		//Step1: Send each request to it's hospital at it's request time
		sendRequests();

		//Step2: Assigns Hospitals' FREE cars to it's APPROPRIATE patients
		for (int i = 0; i < HospitalCount; i++)
		{
		/*
		Looping at each timestep on all patients
		and Assign Cars to
		its patient "IF HOSPITAL HAS THE APPROPRIATE CAR OF THE REQUEST" -> ASSSIGN FUNCTIONS
		*/
		}

		//Step3: Random on OutCats for choose a car and start OutCar failure Action
		if (!OutCars.isEmpty()) {
			FailedCar = CarFailure(1);
			if (FailedCar) {
				OutCarFailureAction(FailedCar);
			}
		}
		
		//Step4: Random on BackCars for choose a car and start BackCar failure Action
		if (!BackCars.isEmpty()) {
			FailedCar = CarFailure(0);
			if (FailedCar) {

			}
		}
		
		//When the time of reaching car to its hospital comes,
		//the car should return to its Hospital and drop the patient.
		//Otherwise decrease the time of reaching the hospital
		Car* C; int i;
		while (BackCars.dequeue(C, i)) {
			if (i == timestep) {
				if (C->GetFailingCondition()) {
					CheckupList.enqueue(C,-1*timestep);
				}
				else {
					carReachedHospital(C);
				}
			}
			else {
				i++;
				BackCars.enqueue(C,i);
			}
		}
		//Step5: Check for returned cars from the checklist
		Car* FC; int FI; priQueue<Car*> temp;
		while (CheckupList.dequeue(FC, FI)) {
			if (FI == 0) {
				HospitalList[FC->GetHospitalID() - 1].addCar(FC);
			}
			else {
				FI++;
				temp.enqueue(FC, FI);
			}
		}
		CheckupList = temp;

		//for (int i = 0; i < HospitalCount; i++) {
		//	srand(time(0));
		//	int randomtime = rand() % 100 + 1;
		//	if (randomtime >=10 && randomtime < 20) { //If  10 <= number < 20, Move one SP patient to the Finish list.
		//		if (HospitalList[i].getSRC())
		//		{
		//			FinishList.enqueue(HospitalList[i].FinishRequest("SP"));
		//			FinishedRequestsCount++;
		//		}
		//	}
		//	else if (randomtime >= 20 && randomtime < 25) { //If  20 <= number < 25, Move one EP patient to the Finish list.
		//		if (HospitalList[i].getERC()) {
		//			FinishList.enqueue(HospitalList[i].FinishRequest("EP"));
		//			FinishedRequestsCount++;
		//		}
		//	}
		//	else if (randomtime >= 30 && randomtime < 40) { //If  30 <= number < 40, Move one NP patient to the Finish list.
		//		if (HospitalList[i].getNRC()) {
		//			FinishList.enqueue(HospitalList[i].FinishRequest("NP"));
		//			FinishedRequestsCount++;
		//		}
		//	}
		//	else if (randomtime >= 40 && randomtime < 45) { //if  40 <= number < 45, Move one Scar from free to out list.
		//		if (HospitalList[i].getScars())
		//		{
		//			OutCars.enqueue(HospitalList[i].SendCarOut("SC"),timestep);
		//		}
		//	}
		//	else if (randomtime >= 70 && randomtime < 75) { //if  70 <= number < 75, Move one Ncar from free to out list.
		//		if (HospitalList[i].getNcars()) {
		//			OutCars.enqueue(HospitalList[i].SendCarOut("NC"), timestep);
		//		}
		//	}
		//	else if (randomtime >= 20 && randomtime < 25) { //if  80 <= number < 90, Move one car from out to back list.
		//		Car* C;
		//		int i=0;
		//		if (!OutCars.isEmpty()) {
		//			OutCars.dequeue(C,i);
		//			BackCars.enqueue(C);
		//		}
		//		
		//	}
		//	else if (randomtime >= 91 && randomtime < 95) { //if 91 <= number < 95, Move one car from back to “Free” list of its hospital.
		//		Car* C;
		//		if (!BackCars.isEmpty()) {
		//		BackCars.dequeue(C);
		//		HospitalList[C->GetHospitalID()-1].addCar(C);
		//		}
		//	
		//	}
		//	I.PrintHospital(HospitalList[i], timestep, FinishList, FinishedRequestsCount);
		//	cout << "Press any key to display next hospital\n";
		//	cin.ignore();
		//}
		incTime();
	}

}

Car* Organiser::CarFailure(int x)
{
	/*
	Generate a number and chick if the number is within the Failure Probability
	make a copy of the OutCars and Generate a number within the num of OutCars
	then Bick the car from the list; 
	*/
	int FailurePropability, CarsCount;
	LeavablePriQueue Temp;
	if (x) {   // 1: OutCars, 0: BackCars = 1;
		FailurePropability = OutCarsFailureProbability;
		CarsCount = OCarCount;
		Temp = OutCars;
	}
	else {
		FailurePropability = BackCarsFailureProbability;
		CarsCount = BCarCount;
		priQueue<Car*> Temp = BackCars;
	}
	srand(time(0));
	int randProp = rand() % 100 + 1;
	Car* RandCar = nullptr;
	if (randProp < FailurePropability) {
		int x = rand() % CarsCount, y;
		for (int i = 0; i <= x; i++) {
			Temp.dequeue(RandCar, y);
		}
		RandCar->SetCarToFail();
		return RandCar;
	}
	return RandCar;
}

//NOT FINISHED
void Organiser::OutCarFailureAction(Car* C)
{
	int p, id = C->GetCarID();
	LeavablePriQueue Temp;
	Car* CarOUT;
	while (OutCars.dequeue(CarOUT,p)) {
		if (id == CarOUT->GetCarID()) {
			BackCars.enqueue(CarOUT, -1 * p);
			HospitalList[CarOUT->GetHospitalID() - 1].SetFailurePatient(CarOUT->dropPatient());
		}
		else {
			Temp.enqueue(CarOUT,p);
		}
	}
	OutCars = Temp;
}

void Organiser::BackCarFailureAction(Car*)
{
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



