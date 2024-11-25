#include "Organiser.h"
#include <iostream>
using namespace std;

Organiser::Organiser()
{
	readFile();
	timestep = 0;
	HospitalList = new Hospital[HospitalCount];
	Request x;
	AllRequests.enqueue(x);
	cout << "Hospital List Created (" << HospitalCount << ") Hospitals";
}

void Organiser::readFile()
{
	//add function here
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
	delete[] HospitalList;
	cout << "Hospital List Destroyed";
}



