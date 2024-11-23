#pragma once
#include "Organiser.h"
#include <iostream>

#include "..//Functions//ReadInput.h"
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
	ReadFile(HospitalCount);
	cout <<"\nTest: " << HospitalCount << endl;
{
	//add function here
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



