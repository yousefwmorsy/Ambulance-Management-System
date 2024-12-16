#include "Organiser.h"
#include <iostream>
#include "time.h"
#include "random"
#include "UI.h"
using namespace std;

Organiser::Organiser()
{
	timestep = 0;
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

int Organiser::getTime()
{
	return timestep;
}

void Organiser::incTime()
{
	timestep++;
}

void Organiser::Simulation(){
	ReadInputFile();
 	
	int EnteredRequests = 0;

	while (notEnd()) {
		Request* R = new Request;
		sendRequests();
		for (int i = 0; i < HospitalCount; i++) {
			srand(time(0));
			int randomtime = rand() % 100 + 1;
			if (randomtime >=10 && randomtime < 20) { //If  10 <= number < 20, Move one SP patient to the Finish list.
				if (HospitalList[i].getSRC())
				{
					FinishList.enqueue(HospitalList[i].FinishRequest("SP"));
					FinishedRequestsCount++;
				}
			}
			else if (randomtime >= 20 && randomtime < 25) { //If  20 <= number < 25, Move one EP patient to the Finish list.
				if (HospitalList[i].getERC()) {
					FinishList.enqueue(HospitalList[i].FinishRequest("EP"));
					FinishedRequestsCount++;
				}
			}
			else if (randomtime >= 30 && randomtime < 40) { //If  30 <= number < 40, Move one NP patient to the Finish list.
				if (HospitalList[i].getNRC()) {
					FinishList.enqueue(HospitalList[i].FinishRequest("NP"));
					FinishedRequestsCount++;
				}
			}
			else if (randomtime >= 40 && randomtime < 45) { //if  40 <= number < 45, Move one Scar from free to out list.
				if (HospitalList[i].getScars())
				{
					OutCars.enqueue(HospitalList[i].SendCarOut("SC"),timestep);
				}
			}
			else if (randomtime >= 70 && randomtime < 75) { //if  70 <= number < 75, Move one Ncar from free to out list.
				if (HospitalList[i].getNcars()) {
					OutCars.enqueue(HospitalList[i].SendCarOut("NC"), timestep);
				}
			}
			else if (randomtime >= 20 && randomtime < 25) { //if  80 <= number < 90, Move one car from out to back list.
				Car* C;
				int i=0;
				if (!OutCars.isEmpty()) {
					OutCars.dequeue(C,i);
					BackCars.enqueue(C);
				}
				
			}
			else if (randomtime >= 91 && randomtime < 95) { //if 91 <= number < 95, Move one car from back to “Free” list of its hospital.
				Car* C;
				if (!BackCars.isEmpty()) {
				BackCars.dequeue(C);
				HospitalList[C->GetHospitalID()-1].addCar(C);
				}
			
			}
			I.PrintHospital(HospitalList[i], timestep, FinishList, FinishedRequestsCount);
			cout << "Press any key to display next hospital\n";
			cin.ignore();
		}
		incTime();
	}

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

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances;
}



