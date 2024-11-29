#pragma once
#include <iostream>
#include "Request.h"

using namespace std;

class Car
{
private:
	static int speedS;
	static int speedN;
	int carID;
	int hospitalID;
	int busyTime;
	bool isSpecial;
	Request* ptr; //pointer for the patient	
public:
	Car();
	Car(int hospitalID,int carID,bool isSpecial);
	static void setSpeed(int speed_special, int speed_normal);
	void setPatient(Request *);
	Request* dropPatient();
	Request* getPatient();
	bool checkSpecial();
	int GetHospitalID();
	friend ostream& operator << (ostream& out, const Car& c);
};
