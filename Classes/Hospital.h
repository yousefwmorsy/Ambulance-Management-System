#pragma once
#include "Request.h"
#include "EPRequest.h"
#include "Car.h"
#include"..//Data Structures/Queue/LinkedQueue.h"
#include "..//Data Structures/PriQueue/priQueue.h"

class Hospital
{private:
	int numNcars;
	int numScars;
	int hospitalID;
	int SRCount;
	int NRCount;
	int ERCount;
	LinkedQueue <Car*> carN;
	LinkedQueue <Car*> carS;
	LinkedQueue <Request*> specialRequest;
	LinkedQueue <Request*> normalRequest; 
	priQueue <Request*> emergencyRequest;
	//LinkedQueue <Request*> emergencyRequest;
public:
	Hospital(int HID = 0, int SpecialCarCount = 0, int NormalCarCount = 0);
	void addCar(Car* ptr); //send a pointer of car normal or Special and it add it to the list
	void setRequest(Request*); //for normal and special
	void setCarsandID(int special_cars, int normal_cars, int ID);
	Request* FinishRequest(string type);
	Car* SendCarOut(string type);
	void SetCarFree(Car*C);
	friend ostream& operator << (ostream& out, Hospital& h);
	//void Print();
	int getSRC();
	int getNRC();
	int getERC();
	int getNcars();
	int getScars();
	//void setRequest(EPRequest*, int); //for emergency
	/*Car* serveEP();
	Car* serveSP();
	Car* serveNP();
	bool hasEPRequests();
	bool hasNPRequests();
	bool hasSPRequests();
	bool hasSCars();
	bool hasNCars();*/
};

