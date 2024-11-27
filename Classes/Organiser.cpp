#include "Organiser.h"
#include <iostream>
using namespace std;

Organiser::Organiser()
{
	ReadInputFile();
	timestep = 0;
	HospitalList = new Hospital[HospitalCount];
	cout << "Hospital List Created (" << HospitalCount << ") Hospitals" << endl;
}


bool Organiser::notEnd()
{
	return AllRequests.isEmpty() ? 0 : 1;
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
			if (Top->getType() == 'E')
			{
				HospitalList[Top->gethid()].setRequest((EPRequest*)Top, ((EPRequest*)Top)->getSeverity());
			}
			else 
				HospitalList[Top->gethid()].setRequest(Top);
		}
		else
		{
			x = 0;
		}
	}
}

void Organiser::serveRequests()
{
	for (int i = 0; i < HospitalCount; i++)
	{
		while (HospitalList[i].hasEPRequests() && (HospitalList[i].hasNCars() || HospitalList[i].hasSCars()) )
		{
			HospitalList[i].serveEP();
		}
		while (HospitalList[i].hasSPRequests() && HospitalList[i].hasSCars())
		{
			HospitalList[i].serveSP();
		}
		while (HospitalList[i].hasNPRequests() && HospitalList[i].hasNCars())
		{
			HospitalList[i].serveNP();
		}
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

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances, Cars, CancelRequist;
	cout << "Hospital List Destroyed";
}



