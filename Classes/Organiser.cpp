#include "Organiser.h"
#include <iostream>
using namespace std;

Organiser::Organiser(int Count)
{
	timestep = 0;
	HospitalList = new Hospital[Count];
	HospitalCount = Count;
	cout << "Hospital List Created";
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

