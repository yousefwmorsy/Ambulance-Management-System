#pragma once
#include "..//Classes/Organiser.h"
#include <iostream>
#include <fstream>
#include <string>
#include "..//Classes//Organiser.h"
#include "..//Data Structures/Queue/LinkedQueue.h"
#include "..//Classes//Request.h"
#include "..//Classes//Car.h"
#include "..//Classes//Hospital.h"



using namespace std;

void ReadFile(int& H/*, LinkedQueue<Request> &Re, LinkedQueue<Car> &ca, LinkedQueue<Hospital> &Ho*/) {
	//Reading input file
	fstream inputFile;

	inputFile.open("InputFile.txt");
	//If there exist a problem when reading the file 
	if (inputFile.fail()) {
		cout << "Can't read the file........";
		return;
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
	int NumberOfHospitals = 0, NCSpeed = 0, SCSpeed = 0, distance = 0, NumOfRequests = 0, NumOfReqCancellation = 0;
	Request R;
	Car C;


	//Reading number of hospitals and speed of normal and special cars.
	inputFile >> NumberOfHospitals;
	inputFile >> NCSpeed >> SCSpeed;

	//Creating Matrecies to sotre distances of hospitals and its number of cars of each type
	int** Hospitalsdistances = new int* [NumberOfHospitals];
	int** Cars = new int* [2];

	//Allocate the Matrices
	for (int i = 0; i < NumberOfHospitals; i++) {
		Hospitalsdistances[i] = new int[NumberOfHospitals];
		Cars[i] = new int[2];
	}

	//------------------------------ / Storing Data / -----------------------------------

	//Get the distances of hospitals in a matrix[n][n]
	for (int i = 0; i < NumberOfHospitals; i++) {
		for (int j = 0; j < NumberOfHospitals; j++) {
			inputFile >> Hospitalsdistances[i][j];
		}
	}

	//Geting the number of cars of each type to its hospial
	for (int i = 0; i < NumberOfHospitals; i++) {
		for (int j = 0; j < 2; j++) {
			inputFile >> Cars[i][j];
		}
	}

	//Geting the number of reqquists
	inputFile >> NumOfRequests;


	for (int i = 0; i < NumOfRequests; i++) {

		//inputFile >> R.type >> R.TimeStep >> R.PatientID >> R.HospitalID >> R.DistanceFromHospital;
	}

	inputFile >> NumOfReqCancellation;

	for (int i = 0; i < NumOfReqCancellation; i++) {
		//inputFile >> CR.TimeStep >> CR.PatientID;
	}

	H = NumberOfHospitals;
	inputFile.close();
};
