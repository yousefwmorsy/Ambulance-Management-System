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

void Organiser::addCar(bool isSpecial, int HospitalID)
{
	//creates car given whether it is special or not
	//assigns car to hospital
}

void Organiser::addHospital(int HospitalID)
{
	//creates hospital object
}

void Organiser::serveRequests()
{
	bool x = 1;
	while (x && notEnd())
	{
		Request* Top;
		AllRequests.peek(Top);
		if (Top->getQT() == timestep) {
			AllRequests.dequeue(Top);
			//send top to suitable hospital
		}
		else
		{
			x = 0;
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

void Organiser::SetNormlCarSpeed(int Ns){
	
}

void Organiser::SetSpecialCarSpeed(int Ss){
}

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances, Cars, CancelRequist;
	cout << "Hospital List Destroyed";
}



