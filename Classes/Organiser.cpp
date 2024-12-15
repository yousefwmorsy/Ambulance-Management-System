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

void Organiser::linkCarToPatient(Request*& Patient)
{
	int hospitalID = Patient->getHospitalID();
	Car* Car = HospitalList[hospitalID].SendCarOut(Patient->getType());
	OutCars.enqueue(Car, -1 * (timestep + (Patient->getDistance()) / Car->getSpeed()));
	Patient->setPT(timestep);
	Car->setPatient(Patient);
}

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances;
}



