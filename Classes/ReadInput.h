//#pragma once
//
//#include <iostream>
//#include <fstream>
//#include <string>
//#include "ReadInput.h"
//#include "Organiser.h"
//using namespace std;
//
///*Abbreviations List:
//HN: Hospitals Number.
//NCS: Normal Car's Speed
//SCS: Special Car's Speed
//D: The distances matrix
//*/
//int ReadInput(int &HN, int &NCS, int &SCS,int **D) {
//	//Reading input file
//	fstream inputFile;
//	
//	inputFile.open("./Requests.txt");
//	//If there exist a problem when reading the file 
//	if (inputFile.fail()) {
//		cout << "Can't read the file........";
//		return 1;
//	}
//
//	//Variables where the data will be stored
//	struct Request { // Dummy
//		string type = "";
//		int TimeStep = 0;
//		int PatientID = 0;
//		int HospitalID = 0;
//		int DistanceFromHospital = 0;
//	};
//
//	struct CancelReq { // Dummy
//		int PatientID = 0;
//		int TimeStep = 0;
//	};
//	//Hospital-->
//	int NumberOfHospitals = 0, NCSpeed = 0, SCSpeed = 0, distance = 0, NumOfRequests = 0, NumOfReqCancellation = 0;
//
//
//	//Reading number of hospitals and speed of normal and special cars.
//	inputFile >> NumberOfHospitals;
//	HN = NumberOfHospitals;
//	inputFile >> NCSpeed >> SCSpeed;
//	NCS = NCSpeed;
//	SCS = SCSpeed;
//
//	//Creating Matrecies to sotre distances of hospitals and its number of cars of each type
//	int** Hospitalsdistances = new int* [NumberOfHospitals];
//	int** Cars = new int* [2];
//
//	//Allocate the Matrices
//	for (int i = 0; i < NumberOfHospitals; i++) {
//		Hospitalsdistances[i] = new int[NumberOfHospitals];
//		Cars[i] = new int[2];
//	}
//
//	//------------------------------ / Storing Data / -----------------------------------
//
//	//Get the distances of hospitals in a matrix[n][n]
//	for (int i = 0; i < NumberOfHospitals; i++) {
//		for (int j = 0; j < NumberOfHospitals; j++) {
//			inputFile >> Hospitalsdistances[i][j];
//		}
//	}
//	D = Hospitalsdistances;
//
//	//Geting the number of cars of each type to its hospial
//	for (int i = 0; i < NumberOfHospitals; i++) {
//		for (int j = 0; j < 2; j++) {
//			inputFile >> Cars[i][j];
//		}
//	}
//
//	//Geting the number of reqquists
//	inputFile >> NumOfRequests;
//
//
//	for (int i = 0; i < NumOfRequests; i++) {
//		Request R;
//		inputFile >> R.type >> R.TimeStep >> R.PatientID >> R.HospitalID >> R.DistanceFromHospital;
//	}
//
//	inputFile >> NumOfReqCancellation;
//
//	for (int i = 0; i < NumOfReqCancellation; i++) {
//		CancelReq CR;
//		inputFile >> CR.TimeStep >> CR.PatientID;
//	}
//}