#include "Organiser.h"
#include <iostream>
#include "time.h"
#include "random"
#include "UI.h"
#include <fstream>
using namespace std;

Organiser::Organiser()
{
	timestep = 0;
	OCarCount = 0;
	BCarCount = 0;
	CheckUpTime = 0;
}

bool Organiser::notEnd()
{
	//checks if all requests were served
	return (FinishedRequestsCount != TotalRequestsCount);
}

void Organiser::sendRequests()
{
	//sends request to suitable hospital in the suitable list
	//called every timestep
	Request* R;
	while (AllRequests.peek(R) && R->getQT() == timestep) {
		AllRequests.dequeue(R);
		HospitalList[R->getHospitalID() - 1].setRequest(R);
	}
}

void Organiser::Simulation(){
	LeavablePriQueue temp;
	ReadInputFile();
	cout << "Select Mode: " << endl;
	cout << "Type ""i"" for Interactive Mode" << endl;
	cout << "Type ""s"" for Silent Mode" << endl;
	bool m = I.SelectMode();
	if (!m)
	{
		I.PrintSilent();
	}
	Car* C; int i;
	int EnteredRequests = 0;

	while (notEnd()) {
		//Request* R = new Request;
		//Car* FailedCar = NULL;
		//Step1: Send each request to it's hospital at it's request time
		sendRequests();

		//Step2: Assigns Hospitals' patients to it's APPROPRIATE FREE cars
		serveRequests();
		checkCancelRequests();
		//Step4: Random on OutCats for choose a car and start OutCar failure Action
		
		//if (!OutCars.isEmpty()) {
		//	int t = 0;
		//	Car* FailedCar = CarFailure(1, t); //After this point OutCars set t NULL
		//	if (FailedCar) {
		//		OutCarFailureAction(FailedCar, t); 
		//		cout << "\nCar failed id: " << FailedCar->GetCarID() << " " << t << endl;
		//	}
		//}
		OutCars;
		BackCars;
		//Step5: If the car reached the patient put it in BackCars from OutCars
		checkOutCarsReached();


		//Step6: Random on BackCars for choose a car and start BackCar failure Action
		if (!BackCars.isEmpty()) {
			int t = 0;
			Car* FailedCar = CarFailure(0, t);
			if (FailedCar) {
				BackCarFailureAction(FailedCar, t); //Not Finished
			}
		}
		
		//Step7: When the time of reaching car to its hospital comes,
		//the car should return to its Hospital and drop the patient.
		checkBackCarsReached();

		//checkCancelRequests();

		//Step8: Check for returned cars from the checkup list
		while (CheckupList.peek(C,i) && -1*i == timestep) {
			CheckupList.dequeue(C, i);
			C->SetCarToFail(false);
			HospitalList[C->GetHospitalID() - 1].addCar(C);
		}
    
		if (m)
		{
			for (int i = 0; i < HospitalCount; i++)
			{
				I.PrintInteractive(HospitalList[i], timestep, FinishList, FinishedRequestsCount, OCarCount, BCarCount, OutCars, BackCars, CheckUpCarC(), CheckupList);
				cin.ignore();
			}
		}


		timestep++;
	}
	CreateOutputFile();
}

Car* Organiser::CarFailure(int x, int &t)
{
	/*
	Generate a number and chick if the number is within the Failure Probability
	make a copy of the OutCars and Generate a number within the num of OutCars
	then Bick the car from the list; 
	*/

	//&t .....
	srand(time(0));
	Car* RandCar = nullptr;
	if (x) {   // 1: OutCars, 0: BackCars;
		int randProb = rand() % 100 + 1;
		if (randProb <= OutCarsFailureProbability) {
			int x = rand() % OCarCount;
			OutCars.GetNext(RandCar, x);
			RandCar->SetCarToFail(true);
			t = timestep - RandCar->getPatient()->getAT();
			return RandCar;
		}
	}

	else {
		int randProb = rand() % 100 + 1;
		if (randProb <= BackCarsFailureProbability) {
			int x = rand() % BCarCount;
			BackCars.GetNext(RandCar, x);
			RandCar->SetCarToFail(true);
			t = RandCar->GetTimeToBack();
			return RandCar;
		}
	}

	return RandCar;
}

void Organiser::OutCarFailureAction(Car* C, int t)
{// t negative - timestep = - int -> enqueue in BackCars 
	int id = C->GetCarID();
	Request* R = C->getPatient();
	int TimeToBack = t + timestep; // Get the time to return to the hospital
	R = C->dropPatient();
	HospitalList[C->GetHospitalID() - 1].SetFailurePatient(R); //Return the request to the hospital
	BackCars.enqueue(C, -1*TimeToBack); // Put the car in the BackCars from its frailer position
	OCarCount--;
	BCarCount++;
}
//NOT FINISHED
void Organiser::BackCarFailureAction(Car*C, int t)
{
	FailedBackCars.enqueue(C,t);
	Car* FBC; int StopedBackTime;
	int CarsCount = HospitalList[C->GetHospitalID() - 1].getNcars() + HospitalList[C->GetHospitalID() - 1].getScars();
	if (CarsCount) {
		//Assign new car from the same hospital to pick the patient and come with the car
		// Waiting for Assigns functions.....
		if (/*Assigning is */true) {
			// Set the Car to BackCars
		}
	}
	while (FailedBackCars.dequeue(FBC, StopedBackTime)) {
		StopedBackTime--;
		FailedBackCars.enqueue(FBC, StopedBackTime);
	}
}

void Organiser::ReturnRepairedCars()
{
}

void Organiser::linkCarToPatient(Car*& Car)
{
	Request * Patient = Car->getPatient();
	int timeToReach = ceil((Patient->getDistance()) / Car->getSpeed());
	Car->SetTimeToBack((2*timeToReach) + timestep); //Save the time to get patient from request point to the hospital.
	int pickupTime = timestep + timeToReach;
	OutCars.enqueue(Car, -1 * pickupTime); //add to outcars, priority is the absolute reach time [timestep + distance/speed]
	OCarCount++;
	Patient->setAT(timestep); //sets the assignment time of patient to current timestep
	Car->setPatient(Patient); //links patient to car and sets status as "Assigned"
	Car->incBusyTime(timeToReach); //increments busy time
}

void Organiser::finishRequest(Request*& Patient)
{
	FinishList.enqueue(Patient);
	FinishedRequestsCount++;
}

void Organiser::carReachedPatient(Car*& Car)
{
	Request* Patient = Car->getPatient();
	int timeToReach = ceil((Patient->getDistance()) / Car->getSpeed());
	int returnTime = timestep + timeToReach;
	Patient->setPT(timestep); //sets the pickup time of patient to current timestep
	Car->setStatus("Loaded"); //sets status of car to "Loaded"
	Car->incBusyTime(timeToReach); //increments busy time
	OCarCount--;
	BCarCount++;
	BackCars.enqueue(Car, -1 * returnTime); //add to backcars, priority is absolute reach time
}

void Organiser::carReachedHospital(Car*& Car)
{
	if (Car->GetFailingCondition()) {
		CheckupList.enqueue(Car,-1*(timestep + CheckUpTime));
		BCarCount--;
		return;
	}
	if (Car->getPatient())
	{
		Request* Patient = Car->dropPatient();//car drops patient and status set to free
		Patient->setFT(timestep); //finish time is set to current timestep
		finishRequest(Patient); //patient sent to finished request list
	}
	HospitalList[Car->GetHospitalID() - 1].addCar(Car); //car is added to free list of hospital
	BCarCount--;
}

void Organiser::checkCancelRequests()
{
	CancelRequest* CancelReq;
	Request* Patient = nullptr;
	Car* Car = nullptr;
	while (CancellationRequests.peek(CancelReq) && timestep == CancelReq->CancelTime)
	{
		CancellationRequests.dequeue(CancelReq);
		Request* Patient;
		int timetoreach = 0;
		for (int i = 0; i < HospitalCount; i++) //loops on hospitals and check np list
		{
			while (HospitalList[i].checkCancel(Patient, timestep)) {
				finishRequest(Patient); //patient sent to finished request list
			}
		}
		if (OutCars.LeaveQueue(Car, timetoreach, CancelReq->PID)) {
			Patient = Car->dropPatient();
			int timetoreturn = timestep + ceil((Patient->getDistance()) / Car->getSpeed()) - (timetoreach - timestep);
			BackCars.enqueue(Car, -1 * timetoreturn);
			OCarCount--;
			BCarCount++;
			finishRequest(Patient); //patient sent to finished request list
		}
		if (AllRequests.LeaveQueue(Patient, CancelReq->PID)) {
			finishRequest(Patient); //patient sent to finished request list
		}
	}
}

void Organiser::checkOutCarsReached()
{
	Car* Car;
	int priority;
	while (OutCars.peek(Car, priority) && timestep == priority*-1)
	{
		OutCars.dequeue(Car, priority);
		carReachedPatient(Car);
	}
}

void Organiser::checkBackCarsReached()
{
	Car* Car;
	int priority;
	while (BackCars.peek(Car, priority) && timestep == priority * -1)
	{
		BackCars.dequeue(Car, priority);
		carReachedHospital(Car);
	}
}

void Organiser::handlingEP()
{
	if (waitEP.isEmpty())
	{
		return;
	}
	Car* assignCar = nullptr;
	Request* eP = nullptr;
	int x;
	while (thereIsHospitalCanServe() && !waitEP.isEmpty()) {
	int* hospital_arr = new int[HospitalCount - 1];
		for (int i = 0; i < HospitalCount; i++)
		{
			if (HospitalList[i].canAssign())
			{
				hospital_arr[i] = i; //stores index of hospital able to serve
			}
			else {
				hospital_arr[i] = -1;
			}
		}
		srand(time(NULL));
		int random = rand() % HospitalCount;
		for (int i = 0; i < HospitalCount - 1; i++)
		{
			if (hospital_arr[random] != -1 && HospitalList[hospital_arr[random]].canAssign())
			{
				waitEP.peek(eP, x);
				int prevhospital = eP->getHospitalID() - 1;
				assignCar = HospitalList[hospital_arr[random]].assiEP(eP);
				if (assignCar != nullptr) //there is a car
				{
					waitEP.dequeue(eP, x);
					eP->setdistance(eP->getDistance() + HospitalsDistances[prevhospital][random]);
					eP->setHospitalID(random+1);
					linkCarToPatient(assignCar);
					break;
				}
			}
			random = (++random) % (HospitalCount - 1);
		}
	}
	while (!waitEP.isEmpty())
	{
		waitEP.dequeue(eP, x);
		HospitalList[eP->getHospitalID() - 1].addEPfromDiffHospital(eP);
	}
	return;
}

void Organiser::serveRequests()
{
	Car* temp;
	for (int i = 0; i < HospitalCount; i++)
	{
		while (HospitalList[i].checkEPatient(timestep))
		{
			temp = HospitalList[i].assiEP();
			if (temp == nullptr)
			{
				HospitalList[i].EPtowait(waitEP, timestep);// should implement function that takes all the current EP that couldn't be assigned
				break;
			}
			else
			{
				linkCarToPatient(temp);//here you need to assign car to the out and set return time
			}
		}
	}
	handlingEP();//handling the EP that couldn't be assigned
	for (int i = 0; i < HospitalCount; i++)
	{
		while (HospitalList[i].checkSPatient(timestep))
		{
			temp = HospitalList[i].assiSP();
			if (temp == nullptr)
			{
				break;
			}
			else
			{
				linkCarToPatient(temp);//here you need to assign car to the out and set return time
			}
		}
		while (HospitalList[i].checkNPatient(timestep))
		{
			temp = HospitalList[i].assiNP();
			if (temp == nullptr)
			{
				break;
			}
			else
			{
				linkCarToPatient(temp);//here you need to assign car to the out and set return time
			}
		}
	}
}

bool Organiser::thereIsHospitalCanServe()
{
	for (int i = 0; i < HospitalCount; i++)
	{
		if (HospitalList[i].canAssign())
		{
			return true;
		}
	}
	return false;
}

int Organiser::CheckUpCarC()
{
  priQueue <Car*> ChechUpL = CheckupList;
	int c = 0;
	int s;
	Car* car;
	while (ChechUpL.dequeue(car, s))
	{
		c++;
	}
	return c;
}

void Organiser::CreateOutputFile()
{
	ofstream OutputFile("Input&Output//Output//Output.txt");
	if (OutputFile.is_open())
	{
		OutputFile << "FT     PID     QT     WT" << endl;
		Request** FT = new Request * [FinishedRequestsCount];
		LinkedQueue <Request*> FinishL = FinishList;
		Request* r;
		int np = 0, sp = 0, ep = 0;
		for (int i = 0; i < FinishedRequestsCount; i++)
		{
			if (FinishL.dequeue(r))
			{
				FT[i] = r;
				if (r->getType() == "NP")
					np++;
				else if (r->getType() == "SP")
					sp++;
				else
					ep++;
			}
		}
		for (int i = 0; i < FinishedRequestsCount - 1; i++)
		{
			for (int j = 0; j < FinishedRequestsCount - i - 1; j++)
			{
				if (FT[j]->getFT() > FT[j + 1]->getFT())
				{
					Request* temp = FT[j];
					FT[j] = FT[j + 1];
					FT[j + 1] = temp;
				}
			}
		}
		for (int i = 0; i < FinishedRequestsCount; i++)
		{
			OutputFile << FT[i]->getFT() << "    " << FT[i]->getpid() << "    " << FT[i]->getQT() << "    " << FT[i]->getWT() << endl;
			OutputFile << "..............................." << endl;
			OutputFile << "Patients: " << FinishedRequestsCount << "     " << "[NP: " << np << ",SP: " << sp << ",EP: " << ep << "]" << endl;

		}
	}
	else
		cout << "Error loading file" << endl;
}

void Organiser::checkCancelRequests()
{
	CancelRequest* CancelReq;
	Request* Patient = nullptr;
	Car* Car = nullptr;
	while (CancellationRequests.peek(CancelReq) && timestep == CancelReq->CancelTime)
	{
		CancellationRequests.dequeue(CancelReq);
		Request* Patient;
		int timetoreach = 0;
		for (int i = 0; i < HospitalCount; i++) //loops on hospitals and check np list
		{
			while (HospitalList[i].checkCancel(Patient, timestep)) {
				finishRequest(Patient); //patient sent to finished request list
			}
		}
		if (OutCars.LeaveQueue(Car, timetoreach, CancelReq->PID)) {
			Patient = Car->dropPatient();
			int timetoreturn = timestep + ceil((Patient->getDistance()) / Car->getSpeed()) - (timetoreach - timestep);
			BackCars.enqueue(Car, -1 * timetoreturn);
			BCarCount++;
			finishRequest(Patient); //patient sent to finished request list
		}
		if (AllRequests.LeaveQueue(Patient, CancelReq->PID)) {
			finishRequest(Patient); //patient sent to finished request list
		}
	}
}

Organiser::~Organiser()
{
	delete[] HospitalList, HospitalsDistances;
}
