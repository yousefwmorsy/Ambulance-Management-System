#pragma once
#include <iostream>
#include "Request.h"

using namespace std;

class Car
{
private:
	static int speedS; //Speed of the special cars
	static int speedN; //Speed of Normal Cars
	int carID; // Car ID
	int hospitalID; // Car's Hospital ID
	int timeToReach; // time to reach the patient
	int busyTime; //absolute total busy time
	string carStatus; // current car's state
	bool isSpecial; // type of the car
	bool isFail; // fail condition of the car
	int TimeToBack; // time to back from picking the patient
	Request* ptr; //pointer for the patient	
	bool toRescue;
public:
	Car(); //constructor
	Car(int hospitalID,int carID,bool isSpecial); //parameterized constructor
	static void setSpeed(int speed_special, int speed_normal); // Set the speeds of the cars at the bigenning of the program
	void setPatient(Request *); // set the car's patient 
	void setStatus(string status); // set the current statue
	string getStatus(); // get the current statue
	void incBusyTime(int x); // set the busy time
	Request* dropPatient(); // drop the patient from the car
	Request* getPatient(); // get a copy from the car
	int getSpeed(); // get the speed of the car
	bool checkSpecial(); // get the type of the car
	int GetHospitalID(); // get the car's hospital's id
	int GetCarID(); // get car id
	bool GetFailingCondition(); // get the car's fail condition
	void SetCarToFail(bool fail); // set the failing
	int GetBusyTime(); // Get the busy time
	void SetTimeToBack(int t); // Set the car's time taken to get back to the hospital
	int GetTimeToBack(); // Get the car's time taken to get back to the hospital
	void setToResqeu(bool);
	bool isToResque();
	friend ostream& operator << (ostream& out, const Car& c); // ostream operator overloading to print the car
};
