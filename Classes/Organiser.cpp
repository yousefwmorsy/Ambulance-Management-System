#pragma once
#include "Organiser.h"
#include <iostream>
#include "..//Functions//ReadFile.cpp"
using namespace std;

Organiser::Organiser()
{
	readFile();
	timestep = 0;
	HospitalList = new Hospital[HospitalCount];
	cout << "Hospital List Created (" << HospitalCount << ") Hospitals";
}

void Organiser::readFile()
{
	ReadFile(HospitalCount, AllRequests);
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



