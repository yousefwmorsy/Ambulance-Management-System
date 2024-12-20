#include <iostream>
#include <fstream>
#include <string>

#include "Organiser.h"
using namespace std;
/*Abbreviation list:
NCSpeed: Normal car speed
SCSpeed: Special car speed
NumOfRequests: Number of entered requests
NumOfCancellation: Number of Cancellation requests
NumS: Number of special cars
NumN: Number of normal cars
CID: Car ID
*/

void Organiser::ReadInputFile() {
	fstream inputFile;
	inputFile.open("Input&Output//Input//file2dmar.txt");
	//If there exist a problem when reading the file 
	if (inputFile.fail()) {
		cout << "Can't read the file........!";
		return ;
	}

	int NCSpeed = 0, SCSpeed = 0, NumOfRequests = 0, NumOfReqCancellation = 0;
	//Reading number of hospitals and speed of normal and special cars.
	inputFile >> HospitalCount;
	inputFile >> NCSpeed >> SCSpeed;
	Car::setSpeed(SCSpeed, NCSpeed);

	//Creating Matrix to store distances of hospitals
	HospitalsDistances = new int* [HospitalCount];

	//Allocate the Matrix
	for (int i = 0; i < HospitalCount; i++) {
 		HospitalsDistances[i] = new int[HospitalCount];
	}

	//------------------------------ / Storing Data / -----------------------------------
	//Get the distances of hospitals in a matrix[n][n]
	for (int i = 0; i < HospitalCount; i++) {
		for (int j = 0; j < HospitalCount; j++) {
			inputFile >> HospitalsDistances[i][j];
		}
	}
	int NumS = 0, NumN = 0;
	
	//Getting the number of cars of each type to its hospital
	HospitalList = new Hospital[HospitalCount];
	for (int i = 0; i < HospitalCount; i++) {
		inputFile >> NumS >> NumN;
		HospitalList[i].setCarsandID(NumS, NumN, i+1);
		int CID = 1;
		for (int j = 0; j < NumS; j++) {
			Car* C = new Car(i+1, CID, true);
			HospitalList[i].addCar(C);
			CID++;
		}
		for (int j = 0; j < NumN; j++) {
			Car* C = new Car(i+1, CID, false);
			HospitalList[i].addCar(C);
			CID++;
		}
	}

	//Geting the number of requests
	inputFile >> NumOfRequests;
	for (int i = 0; i < NumOfRequests; i++) {
		string type = ""; int TimeStep = -1, PatientID = -1, HospitalID = -1, DistanceFromHospital = -1, Severty = - 1;
		inputFile >> type;
		if (type == "EP") {
			inputFile >> TimeStep >> PatientID >> HospitalID >> DistanceFromHospital >> Severty;
			EPRequest* EPR = new EPRequest(TimeStep, PatientID, HospitalID, DistanceFromHospital, Severty);
			AllRequests.enqueue(EPR);
			TotalRequestsCount++;
		}
		else {
			inputFile >> TimeStep >> PatientID >> HospitalID >> DistanceFromHospital;
			Request *R = new Request(type, TimeStep, PatientID, HospitalID ,DistanceFromHospital);
			AllRequests.enqueue(R);
			TotalRequestsCount++;
		}
		
	}

	//Store Cancelled requests
	inputFile >> NumOfReqCancellation;
	for (int i = 0; i < NumOfReqCancellation; i++) {
		CancelRequest* CancelR = new CancelRequest;
		inputFile >> CancelR->CancelTime >> CancelR->PID >> CancelR->HID;
		CancellationRequests.enqueue(CancelR);
	}


	inputFile >> OutCarsFailureProbability;
	inputFile >> BackCarsFailureProbability;
	inputFile >> CheckUpTime;
}