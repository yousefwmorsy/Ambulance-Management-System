#pragma once
#include "Request.h"
#include "EPRequest.h"
#include "Car.h"
#include"..//Data Structures/Queue/LinkedQueue.h"
#include "..//Data Structures/PriQueue/priQueue.h"
#include "..//Data Structures/LeavableQueue/LeavableQueue.h"
#include "..//Data Structures/LeavablePriQueue/LeavablePriQueue.h"


class Hospital
{private:
	int numNcars; //number of normal cars
 	int numScars; //number of special cars
	int hospitalID; // Hospital id
	int SRCount; // Special requests counts
	int NRCount; // Normal requests counts
	int ERCount; // Emergency requests counts
	////////////////////
	int SRCountPrint; int SRIDPrint[100]; // Temp
	int NRCountPrint; int NRIDPrint[100]; // Temp
	int ERCountPrint; int ERIDPrint[100]; // Temp
	////////////////////
	LinkedQueue <Car*> carN; //
	LinkedQueue <Car*> carS;
	LeavableQueue specialRequest;
	LeavableQueue normalRequest; 
	priQueue <Request*> emergencyRequest;
public:
	Hospital(int HID = 0, int SpecialCarCount = 0, int NormalCarCount = 0);
	void addCar(Car* ptr); //send a pointer of car normal or Special and it add it to the list
	void setRequest(Request*); //for normal and special
	void setCarsandID(int special_cars, int normal_cars, int ID); // Store the cars of the hospital
	Request* FinishRequest(string type); // finishing hospital's requests 
	Car* SendCarOut(string type); //Send a car to bring the patient
	friend ostream& operator << (ostream& out, Hospital& h); 
	int getSRC(); // Get the number of special requests
	int getNRC(); // Get the number of normal requests
	int getERC(); // Get the number of emergency requests
	int getNcars(); // Get the number of normal cars
	int getScars(); // Get the number of special cars
	int getHospitalID(); // Get the hospital's id
	Car* SendCarToRescue();
	int GetTotalBusyTime();

	//assign patient to car if it is not available it will return null ptr;
	Car* assiNP();
	Car* assiSP();
	Car* assiEP();
	Car* assiEP(Request*); // only used with EP that could get to nearest hospital
	
	bool canAssign(); // check the hospital's condition of assigning 

	//Check the hospital's requests
	const bool checkEPatient(int& timestep);
	const bool checkNPatient(int& timestep);
	const bool checkSPatient(int& timestep);

	void EPtowait(priQueue<Request*>& pr, int timestep); 
	void addEPfromDiffHospital(Request* ptr);

	bool checkCancel(Request*& Patient, int timestep, int); //returns true if patient cancelled request is found

	//Print requests
	void printEP();
	void printSP();
	void printNP();

	int CarNCount();
	int CarSCount();
	void SetFailurePatient(Request*);

};

