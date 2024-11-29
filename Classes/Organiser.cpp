#include "Organiser.h"
#include <iostream>
#include "time.h"
#include "random"
#include "UI.h"
using namespace std;

Organiser::Organiser()
{
	timestep = 0;
	//cout << "Hospital List Created (" << HospitalCount << ") Hospitals" << endl;
}


bool Organiser::notEnd()
{
	return (FinishedRequestsCount != TotalRequestsCount);
}



void Organiser::sendRequests()
{
	//sends request to suitable hospital in the suitable list
	//called every timestep
	bool x = 1;
	while (x && notEnd())
	{
		Request* Top;
		AllRequests.peek(Top);
		
		if (Top->getQT() == timestep) {
			AllRequests.dequeue(Top);
			
			/*if (Top->getType() == "EP")
			{
				HospitalList[Top->gethid()].setRequest((EPRequest*)Top, ((EPRequest*)Top)->getSeverity());
			}
			else */
			HospitalList[Top->gethid()-1].setRequest(Top);
		}
		else
		{
			x = 0;
		}
	}
}

//void Organiser::serveRequests()
//{
//	for (int i = 0; i < HospitalCount; i++)
//	{
//		while (HospitalList[i].hasEPRequests() && (HospitalList[i].hasNCars() || HospitalList[i].hasSCars()) )
//		{
//			HospitalList[i].serveEP();
//		}
//		while (HospitalList[i].hasSPRequests() && HospitalList[i].hasSCars())
//		{
//			HospitalList[i].serveSP();
//		}
//		while (HospitalList[i].hasNPRequests() && HospitalList[i].hasNCars())
//		{
//			HospitalList[i].serveNP();
//		}
//	}
//}

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
 	Request* R = new Request;
	//while (AllRequests.dequeue(R)) {
	//	HospitalList[R->gitHospitalID()-1].setRequest(R);
	//}

	while (notEnd()) {
		sendRequests();
		for (int i = 0; i < HospitalCount; i++) {
			srand(time(0));
			int randomtime = rand() % 100 + 1;
			//int arr[] = {42, 92};
			//int randomtime = arr[i%2];
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
			else if (randomtime >= 20 && randomtime < 25) { // if  80 <= number < 90, Move one car from out to back list.
				Car* C;
				int i=0;
				if (!OutCars.isEmpty()) {
					OutCars.dequeue(C, i);
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
	int x; cin >> x; // To prevent the program from closing;
}

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances;
	cout << "Hospital List Destroyed";
}



