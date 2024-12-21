#include "Hospital.h"

Hospital::Hospital(int HID, int SpecialCarCount, int NormalCarCount) {
		numScars = SpecialCarCount;
		numNcars = NormalCarCount;
		hospitalID = HID;
		NRCount = 0;
		SRCount = 0;
		ERCount = 0;
		NRCountPrint = 0;
		SRCountPrint = 0;
		ERCountPrint = 0;
}

void Hospital::addCar(Car* ptr)
{
	if (ptr->checkSpecial()) {
		carS.enqueue(ptr);
	}
	else
	{
		carN.enqueue(ptr);
	}
	return;
}

void Hospital::setRequest(Request* rq)
{
	if(rq->getType() == "SP") { // the function need to implemented in request file
		specialRequest.enqueue(rq);
		SRCount++;
		SRIDPrint[SRCountPrint] = rq->getpid();
		SRCountPrint++;
	}
	else if(rq->getType() == "NP")
	{
		normalRequest.enqueue(rq);
		NRCount++;
		NRIDPrint[NRCountPrint] = rq->getpid();
		NRCountPrint++;
	}
	else {
		emergencyRequest.enqueue(rq, ((EPRequest*)rq)->getSeverity());
		ERCount++;
		ERIDPrint[ERCountPrint] = rq->getpid();
		ERCountPrint++;
	}
	return;
}

void Hospital::setCarsandID(int special_cars, int normal_cars, int ID)
{
	numScars = special_cars;
    numNcars = normal_cars;
    hospitalID = ID;
}


Request* Hospital::FinishRequest(string type)
{
	Request *R = NULL;
	int i = 1;
	if (type == "SP") {
		specialRequest.dequeue(R);
		SRCount--;
	}
	else if (type == "NP") {
		normalRequest.dequeue(R);
		NRCount--;
	}
	else if (type == "EP") {
		int x;
		emergencyRequest.dequeue(R, x);
		ERCount--;
	}
	return R;
}

Car* Hospital::SendCarOut(string type)
{
	Car* C;
	if (type == "SC") {
		if (carS.dequeue(C))
			numScars--;
		else
			return nullptr;
	}
	else {
		if (carN.dequeue(C))
			numNcars--;
		else
			return nullptr;
	}
	return C;
}

int Hospital::getSRC()
{
	return SRCount;
}

int Hospital::getNRC()
{
	return NRCount;
}

int Hospital::getERC()
{
	return ERCount;
}

int Hospital::getNcars()
{
	return numNcars;
}

int Hospital::getScars()
{
	return numScars;
}

int Hospital::getHospitalID()
{
	return hospitalID;
}

Car* Hospital::SendCarToRescue()
{
	Car* C;
	if (numNcars) {
		carN.dequeue(C);
		numNcars--;
		return C;
	}
	if (numScars) {
		carS.dequeue(C);
		numScars--;
		return C;
	}
	return nullptr;
}

bool Hospital::checkCancel(Request*& Patient, int timestep)
{
	if (normalRequest.peek(Patient) && Patient->getQT() == timestep)
	{
		normalRequest.dequeue(Patient);
		NRCount--;
		return true;
	}
	return false;
}

void Hospital::printEP()
{
	Request* R;
	priQueue <Request*> Temp; int X = 0;
	int E = ERCount;
	cout << E << " EP requests: ";
	//for (int i = 0; i < E; i++)
	//{
	//	emergencyRequest.dequeue(R, X);
	///*	cout << *R;
	//	if (i != E - 1)
	//	{
	//		cout << ", ";
	//	}
	//	Temp.enqueue(R, X);*/
	//	cout << ERIDPrint[i] << ", ";
	//}
	//while (Temp.dequeue(R, X)) {
	//	emergencyRequest.enqueue(R, X);
	//}
	emergencyRequest.print();
	cout << endl;
}

void Hospital::printSP()
{
	Request* R;
	int S = SRCount;
	cout << S << " SP requests: ";
	//for (int i = 0; i < S; i++)
	//{
	//	/*specialRequest.dequeue(R);
	//	cout << *R;
	//	if (i != S - 1)
	//	{
	//		cout << ",	";
	//	}
	//	specialRequest.enqueue(R);*/
	//	cout << SRIDPrint[i] << ", ";
	//}
	specialRequest.print();
	cout << endl;
}

void Hospital::printNP()
{
	Request* R;
	int N = NRCount;
	cout << N << " NP requests: ";
	//for (int i = 0; i < N; i++)
	//{
	//	/*normalRequest.dequeue(R);
	//	cout << *R;
	//	if (i != N - 1)
	//	{
	//		cout << ", ";
	//	}
	//	normalRequest.enqueue(R);*/

	//	cout << NRIDPrint[i] << ", ";
	//}
	normalRequest.print();
	cout << endl;
}


int Hospital::CarNCount()
{
	LinkedQueue <Car*> Ncar = carN;
	int c = 0;
	Car* car;
	while (Ncar.dequeue(car))
	{
		c++;
	}
	return c;
}

int Hospital::CarSCount()
{
	LinkedQueue <Car*> SCar = carS;
	int c = 0;
	Car* car;
	while (SCar.dequeue(car))
	{
		c++;
	}
	return c;
}


bool Hospital::canAssign()
{
	Car* assiCar = nullptr;
	if (carN.peek(assiCar)||carS.peek(assiCar))
	{
		return true;
	}

	return false;
}

const bool Hospital::checkEPatient(int& timestep)
{
	Request* temp = nullptr;
	int x;
	if (emergencyRequest.peek(temp, x) && timestep >= temp->getQT())
	{
		return true;
	}
  	return false;
}

const bool Hospital::checkNPatient(int& timestep)
{
	Request* temp = nullptr; 
	bool b = normalRequest.peek(temp);
	if (b && timestep >= temp->getQT())
	{
		return true;
	}
	return false;
}

const bool Hospital::checkSPatient(int& timestep)
{
	Request* temp = nullptr;
	bool b = specialRequest.peek(temp);
	if (b && timestep >= temp->getQT())
	{
		return true;
	}
	return false;
}

void Hospital::EPtowait(priQueue<Request*>& pr,int timestep )
{
	Request* temp = nullptr;
	int severity;
	while (checkEPatient(timestep))
	{
		emergencyRequest.dequeue(temp, severity);
		ERCount--;
		pr.enqueue(temp, severity);
	}
	return;
}

Car* Hospital::assiNP()
{
	Request* pt = nullptr;
	normalRequest.peek(pt);
	Car* assiCar = nullptr;
	if (carN.peek(assiCar))
	{
		normalRequest.dequeue(pt);
		carN.dequeue(assiCar);
		assiCar->setPatient(pt);
		NRCount--;
	}
	return assiCar;
}


Car* Hospital::assiSP()
{
	Request* pt = nullptr;
	specialRequest.peek(pt);
	Car* assiCar = nullptr;
	if (carS.peek(assiCar))
	{
		carS.dequeue(assiCar);
		specialRequest.dequeue(pt);
		SRCount--;
		assiCar->setPatient(pt);
	}
	return assiCar;
}

Car* Hospital::assiEP()
{
	Request* pt = nullptr;
	int x;
	emergencyRequest.peek(pt, x);
	Car* assiCar = nullptr;
	if (carN.peek(assiCar))
	{
		emergencyRequest.dequeue(pt, x);
		ERCount--;
		carN.dequeue(assiCar);
		assiCar->setPatient(pt);
	}
	else if (carS.peek(assiCar))
	{
		emergencyRequest.dequeue(pt, x);
		ERCount--;
		carS.dequeue(assiCar);
		assiCar->setPatient(pt);
	}
	return assiCar;
}

Car* Hospital::assiEP(Request* pt)
{
	int x;
	Car* assiCar = nullptr;
	if (carN.peek(assiCar))
	{
		carN.dequeue(assiCar);
		assiCar->setPatient(pt);
	}
	else if (carS.peek(assiCar))
	{
		carS.dequeue(assiCar);
		assiCar->setPatient(pt);
	}
	return assiCar;
}


void Hospital::SetFailurePatient(Request* R)
{
	if (R->getType() == "NP") {
		normalRequest.InsertAtBegin(R);
		NRCount++;
	}
	else if (R->getType() == "SP") {
		specialRequest.InsertAtBegin(R);
		SRCount++;
	}
	else {
		emergencyRequest.enqueue(R, ((EPRequest*)R)->getSeverity()); //Logical Error
		ERCount++;
	}
}

void Hospital::addEPfromDiffHospital(Request* ptr)
{
	if (ptr != nullptr)
	{
		emergencyRequest.enqueue(ptr, ((EPRequest*)ptr)->getSeverity());
		ERCount++;
	}
}

ostream& operator<<(ostream& out,  Hospital& h)
{
	out << h.getHospitalID();
	return out;
}
