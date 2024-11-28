#include <iostream>
#include <fstream>
#include <string>

#include "Organiser.h"
using namespace std;

void Organiser::ReadInputFile() {
	//Reading input file
	fstream inputFile;

	inputFile.open("Input&Output//Requests.txt");
	//If there exist a problem when reading the file 
	if (inputFile.fail()) {
		cout << "Can't read the file........";
		return ;
	}

	int NCSpeed = 0, SCSpeed = 0, NumOfRequests = 0, NumOfReqCancellation = 0;
	//Reading number of hospitals and speed of normal and special cars.
	inputFile >> HospitalCount;
	inputFile >> NCSpeed >> SCSpeed;
	Car::setSpeed(SCSpeed, NCSpeed);

	//Creating Matrecies to sotre distances of hospitals and its number of cars of each type
	HospitalsDistances = new int* [HospitalCount];

	//Allocate the Matrices
	for (int i = 0; i < HospitalCount; i++) {
 		HospitalsDistances[i] = new int[HospitalCount];
	}

	//------------------------------ / Storing Data / -----------------------------------

	//Creating Hospital Objects into HospitalList
	
	//Get the distances of hospitals in a matrix[n][n]
	for (int i = 0; i < HospitalCount; i++) {
		for (int j = 0; j < HospitalCount; j++) {
			inputFile >> HospitalsDistances[i][j];
		}
	}
	int NumS = 0, NumN = 0;
	inputFile >> NumS >> NumN;

	//Geting the number of cars of each type to its hospial
	HospitalList = new Hospital[HospitalCount];
	for (int i = 0; i < HospitalCount; i++) {
		HospitalList[i].setCarsandID(NumS, NumN, i);
		int CID = 0;
		for (int j = 0; j < NumS; j++) {
			Car* C = new Car(i, CID, true);
			HospitalList[i].addCar(C);
			CID++;
		}
		for (int j = 0; j < NumN; j++) {
			Car* C = new Car(i, CID, false);
			HospitalList[i].addCar(C);
			CID++;
		}
	}

	//Geting the number of reqquists
	inputFile >> NumOfRequests;


	for (int i = 0; i < NumOfRequests; i++) {
		string type; int TimeStep, PatientID, HospitalID, DistanceFromHospital, Severty;
		inputFile >> type;
		if (type == "EP") {
			inputFile >> TimeStep >> PatientID >> HospitalID >> DistanceFromHospital >> Severty;
			EPRequest* EPR = new EPRequest(TimeStep, PatientID, HospitalID, DistanceFromHospital, Severty);
			AllRequests.enqueue(EPR);
			TotalRequestsCount++;
		}
		inputFile >> TimeStep >> PatientID >> HospitalID >> DistanceFromHospital;
		Request *R = new Request(type, TimeStep, PatientID, HospitalID ,DistanceFromHospital);
		AllRequests.enqueue(R);
		TotalRequestsCount++;
	}

	
	inputFile >> NumOfReqCancellation;
	for (int i = 0; i < NumOfReqCancellation; i++) {
		CancelRequest* CancelR = new CancelRequest;
		inputFile >> CancelR->CancelTime >> CancelR->PID, CancelR->HID;
		CancellationRequests.enqueue(CancelR);
	}
}