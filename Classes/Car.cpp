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

		timestep++;
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

int Car::GetCarID()
{
	return carID;
}
bool Car::GetFailingCondition()
{
	return isFail;
}
void Car::SetCarToFail(bool fail)
{
	isFail = fail;
}

int Car::GetBusyTime()
{
	return busyTime;
}


Car::Car()
{
	isFail = false;
}

Car::Car(int hid, int cid, bool isS) {
	hospitalID = hid;
	carID = cid;
	isSpecial = isS;
	carStatus = "Ready";
	busyTime = 0;
	ptr = nullptr;
	isFail = false;
}
void Organiser::finishRequest(Request*& Patient)
{
	Patient->setFT(timestep); //finish time is set to current timestep
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
	finishRequest(Patient); //patient sent to finished request list
}

void Organiser::checkCancelRequests()
{
	CancelRequest* CancelReq;
	Request* Patient = nullptr;
	Car* Car = nullptr;
	while (CancellationRequests.peek(CancelReq) && timestep == CancelReq->CancelTime)
	{
		CancellationRequests.dequeue(CancelReq);
		Request* Patient;
		int timetoreach;
		for (int i = 0; i < HospitalCount; i++) //loops on hospitals and check np list
		{
			while (HospitalList[i].checkCancel(Patient, timestep)) {
				finishRequest(Patient); //patient sent to finished request list
			}
		}
		if (OutCars.LeaveQueue(Car, timetoreach, CancelReq->PID)) {
			Patient = Car->dropPatient();
			int timetoreturn = timestep + ((Patient->getDistance()) / Car->getSpeed()) - (timetoreach-timestep);
			BackCars.enqueue(Car, -1 * timetoreturn);
			finishRequest(Patient); //patient sent to finished request list
		}
		if (AllRequests.LeaveQueue(Patient, CancelReq->PID)) {
			finishRequest(Patient); //patient sent to finished request list
		}
	}
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



ostream& operator<<(ostream& out, const Car& c)
{
	if (c.isSpecial)
	{
		out << "S" << c.carID << "_H" << c.hospitalID << "_P" << *c.ptr;
	}
	else
	{
		out << "N" << c.carID << "_H" << c.hospitalID << "_P" << *c.ptr;
	}
	return out;
	// TODO: insert return statement here
}
