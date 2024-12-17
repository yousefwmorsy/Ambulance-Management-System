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
		
		//Step3: Random on OutCats for choose a car and start OutCar failure Action
		if (!OutCars.isEmpty()) {
			FailedCar = CarFailure(1);
			if (FailedCar) {
				OutCarFailureAction(FailedCar); 
			}
		}
		
		//Step4: If the car reached the patient put it in BackCars from OutCars
		checkOutCarsReached();
		
		//Step5: Random on BackCars for choose a car and start BackCar failure Action
		if (!BackCars.isEmpty()) {
			FailedCar = CarFailure(0);
			if (FailedCar) {
				BackCarFailureAction(FailedCar); //Not Finished
			}
		}
		
		//Step6: When the time of reaching car to its hospital comes,
		//the car should return to its Hospital and drop the patient.
		checkBackCarsReached();

		//Step7: Check for returned cars from the checkup list
		while (CheckupList.peek(C,i) && -1*i == timestep) {
			CheckupList.dequeue(C, i);
			C->SetCarToFail(false);
			HospitalList[C->GetHospitalID() - 1].addCar(C);
		}

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
	int randProb = rand() % 100 + 1;
	Car* RandCar = nullptr;
	if (randProb < FailurePropability) {
		int x = rand() % CarsCount, y;
		for (int i = 0; i <= x; i++) {
			Temp.dequeue(RandCar, y);
		}
		RandCar->SetCarToFail(true);
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

//void Organiser::linkCarToPatient(Request*& Patient, Car*& Car)
//{
//	int timeToReach = ((Patient->getDistance()) / Car->getSpeed());
//	int pickupTime = timestep + timeToReach;
//	OutCars.enqueue(Car, -1 * pickupTime); //add to outcars, priority is the absolute reach time [timestep + distance/speed]
//	Patient->setAT(timestep); //sets the assignment time of patient to current timestep
//	Car->setPatient(Patient); //links patient to car and sets status as "Assigned"
//	Car->incBusyTime(timeToReach); //increments busy time
//}

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

void Organiser::linkCarToPatient( Car*& Car)
{
	Request* Patient = Car->getPatient();
	int timeToReach = ((Patient->getDistance()) / Car->getSpeed());
	int pickupTime = timestep + timeToReach;
	OutCars.enqueue(Car, -1 * pickupTime); //add to outcars, priority is the absolute reach time [timestep + distance/speed]
	Patient->setAT(timestep); //sets the assignment time of patient to current timestep
	Car->setPatient(Patient); //links patient to car and sets status as "Assigned"
	Car->incBusyTime(timeToReach); //increments busy time
}

void Organiser::handlingEP()
{
	Car* assignCar = nullptr;
	Request* eP = nullptr;
	int x;
	for (int i = 0; i < HospitalCount; i++)
	{
		while (HospitalList[i].canAssign()&&!waitEP.isEmpty())
		{
			waitEP.dequeue(eP, x);
			assignCar = HospitalList[i].assiEP(eP);
			linkCarToPatient(assignCar);
		}
	}
	return;
}

void Organiser::serveRequests()
{
	Car* temp;
	for (int i = 0; i < HospitalCount; i++)
	{
		while (HospitalList[i].checkEPatient(timestep))
		{
			temp = HospitalList[i].assiEP();
			if (temp == nullptr)
			{
				HospitalList[i].EPtowait(waitEP, timestep);// should implement function that takes all the current EP that couldn't be assigned
				break;
			}
			else
			{
				linkCarToPatient(temp);//here you need to assign car to the out and set return time
			}
		}
	}
	handlingEP();//handling the EP that couldn't be assigned
	for (int i = 0; i < HospitalCount; i++)
	{
		while (HospitalList[i].checkSPatient(timestep))
		{
			temp = HospitalList[i].assiSP();
			if (temp == nullptr)
			{
				break;
			}
			else
			{
				linkCarToPatient(temp);//here you need to assign car to the out and set return time
			}
		}
		while (HospitalList[i].checkNPatient(timestep))
		{
			temp = HospitalList[i].assiNP();
			if (temp == nullptr)
			{
				break;
			}
			else
			{
				linkCarToPatient(temp);//here you need to assign car to the out and set return time
			}
		}
	}
}

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances;
}
