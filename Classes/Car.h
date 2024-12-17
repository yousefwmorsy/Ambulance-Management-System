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
	int timeToReach;
	int busyTime;
	string carStatus;
	bool isSpecial;
	bool isFail;
	Request* ptr; //pointer for the patient	
public:
	Car();
	Car(int hospitalID,int carID,bool isSpecial);
	static void setSpeed(int speed_special, int speed_normal);
	void setPatient(Request *);
	void setStatus(string status);
	void incBusyTime(int x);
	Request* dropPatient();
	Request* getPatient();
	int getSpeed();
	bool checkSpecial();
	int GetHospitalID();
	int GetCarID();
	bool GetFailingCondition();
	void SetCarToFail(bool fail);
	int GetBusyTime();
	void SetBusyTime(int t);
	int GetBusyTime();

	/*void SetRTimeToReq(int n);
	int GetRTimeToReq();
	void SetRTimeToFree(int n);
	int GetRTimeToFree();*/
};
