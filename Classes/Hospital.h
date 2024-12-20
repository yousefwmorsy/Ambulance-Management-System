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
	int numNcars;
	int numScars;
	int hospitalID;
	int SRCount;
	int NRCount;
	int ERCount;
	////////////////////
	int SRCountPrint; int SRIDPrint[100]; // Temp
	int NRCountPrint; int NRIDPrint[100]; // Temp
	int ERCountPrint; int ERIDPrint[100]; // Temp
	////////////////////
	LinkedQueue <Car*> carN;
	LinkedQueue <Car*> carS;
	LinkedQueue <Request*> specialRequest;
	LeavableQueue normalRequest; 
	priQueue <Request*> emergencyRequest;
public:
	Hospital(int HID = 0, int SpecialCarCount = 0, int NormalCarCount = 0);
	void addCar(Car* ptr); //send a pointer of car normal or Special and it add it to the list
	void setRequest(Request*); //for normal and special
	void setCarsandID(int special_cars, int normal_cars, int ID);
	Request* FinishRequest(string type);
	Car* SendCarOut(string type);
	friend ostream& operator << (ostream& out, Hospital& h);
	int getSRC();
	int getNRC();
	int getERC();
	int getNcars();
	int getScars();
	int getHospitalID();

	//assign patient to car if it is not avalible it will return null ptr;
	Car* assiNP();
	Car* assiSP();
	Car* assiEP();
	Car* assiEP(Request*); // only used with EP that could get to nearest hospital
	
	bool canAssign();
	const bool checkEPatient(int& timestep);
	const bool checkNPatient(int& timestep);
	const bool checkSPatient(int& timestep);

	void EPtowait(priQueue<Request*>& pr, int timestep);


	bool checkCancel(Request*& Patient, int timestep); //returns true if patient cancelled request is found

	void printEP();
	void printSP();
	void printNP();
	int CarNCount();
	int CarSCount();
	void SetFailurePatient(Request*);

};

