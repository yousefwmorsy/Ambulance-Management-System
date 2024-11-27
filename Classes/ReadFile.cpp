#include <iostream>
#include <fstream>
#include <string>
#include "ReadInput.h"
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

	//Variables where the data will be stored
	//struct Request { // Dummy
	//	string type = "";
	//	int TimeStep = 0;
	//	int PatientID = 0;
	//	int HospitalID = 0;
	//	int DistanceFromHospital = 0;
	//};

	//struct CancelReq { // Dummy
	//	int PatientID = 0;
	//	int TimeStep = 0;
	//};
	//Hospital-->
	int NCSpeed = 0, SCSpeed = 0, NumOfRequests = 0, NumOfReqCancellation = 0;


	//Reading number of hospitals and speed of normal and special cars.
	inputFile >> Organiser::HospitalCount;
	inputFile >> NCSpeed >> SCSpeed;

	//Creating Matrecies to sotre distances of hospitals and its number of cars of each type
	/*int** Hospitalsdistances = new int* [HospitalCount];*/
	Cars = new int* [2];
	HospitalsDistances = new int* [HospitalCount];

	//Allocate the Matrices
	for (int i = 0; i < HospitalCount; i++) {
 		HospitalsDistances[i] = new int[HospitalCount];
		Cars[i] = new int[2];
	}

	//------------------------------ / Storing Data / -----------------------------------

	//Get the distances of hospitals in a matrix[n][n]
	for (int i = 0; i < HospitalCount; i++) {
		for (int j = 0; j < HospitalCount; j++) {
			inputFile >> HospitalsDistances[i][j];
		}
	}

	//Geting the number of cars of each type to its hospial
	for (int i = 0; i < HospitalCount; i++) {
		for (int j = 0; j < 2; j++) {
			inputFile >> Cars[i][j];
		}
	}

	//Geting the number of reqquists
	inputFile >> NumOfRequests;


	for (int i = 0; i < NumOfRequests; i++) {

		string type; int TimeStep, PatientID, HospitalID, DistanceFromHospital; bool t;
 		inputFile >> type >> TimeStep >> PatientID >> HospitalID >> DistanceFromHospital;
		if (type =="SP") {
			t = true;
		}
		Request *R = new Request(t, TimeStep, PatientID, HospitalID ,DistanceFromHospital);
		AllRequests.enqueue(R);
		
	}

	CancelRequist = new int* [2];
	inputFile >> NumOfReqCancellation;
	for (int i = 0; i < NumOfReqCancellation; i++) {
		CancelRequist[i] = new int[2];
	}
	for (int i = 0; i < NumOfReqCancellation; i++) {
		inputFile >> CancelRequist[i][0] >> CancelRequist[i][1];
	}
	
	SetNormlCarSpeed(NCSpeed);
	SetSpecialCarSpeed(SCSpeed);
}