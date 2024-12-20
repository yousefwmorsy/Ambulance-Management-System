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

bool Hospital::checkCancel(Request*& Patient, int timestep)
{
	if (normalRequest.peek(Patient) && Patient->getQT() == timestep)
	{
		normalRequest.dequeue(Patient);
		return true;
	}
	return false;
}

void Hospital::printEP()
{
	Request* R;
	priQueue <Request*> Temp; int X = 0;
	int E = ERCountPrint;
	cout << E << " EP requests: ";
	for (int i = 0; i < E; i++)
	{
		/*emergencyRequest.dequeue(R, X);
		cout << *R;
		if (i != E - 1)
		{
			cout << ", ";
		}
		Temp.enqueue(R, X);*/
		cout << ERIDPrint[i] << ", ";

	}
	/*while (Temp.dequeue(R, X)) {
		emergencyRequest.enqueue(R, X);
	}*/
	cout << endl;
}

void Hospital::printSP()
{
	Request* R;
	int S = SRCountPrint;
	cout << S << " SP requests: ";
	for (int i = 0; i < S; i++)
	{
		/*specialRequest.dequeue(R);
		cout << *R;
		if (i != S - 1)
		{
			cout << ", ";
		}
		specialRequest.enqueue(R);*/
		cout << SRIDPrint[i] << ", ";
	}
	cout << endl;
}

void Hospital::printNP()
{
	Request* R;
	int N = NRCountPrint;
	cout << N << " NP requests: ";
	for (int i = 0; i < N; i++)
	{
		/*normalRequest.dequeue(R);
		cout << *R;
		if (i != N - 1)
		{
			cout << ", ";
		}
		normalRequest.enqueue(R);*/

		cout << NRIDPrint[i] << ", ";
	}
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
	if (emergencyRequest.peek(temp, x) && timestep <= temp->getQT())
	{
		return true;
	}
	return false;
}

const bool Hospital::checkNPatient(int& timestep)
{
	Request* temp = nullptr; //Hospital 2
	bool b = normalRequest.peek(temp);
	if (b && timestep <= temp->getQT())
	{
		return true;
	}
	return false;
}

const bool Hospital::checkSPatient(int& timestep)
{
	Request* temp = nullptr;
	bool b = specialRequest.peek(temp);
	if (b && timestep <= temp->getQT())
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
		pr.enqueue(temp, severity);
	}
	return;
}

Car* Hospital::assiNP()
{
	Request* pt = nullptr;
	normalRequest.dequeue(pt);
	NRCount--;
	Car* assiCar = nullptr;
	if (carN.peek(assiCar))
	{
		carN.dequeue(assiCar);
		assiCar->setPatient(pt);
	}
	return assiCar;
}

Car* Hospital::assiSP()
{
	Request* pt = nullptr;
	specialRequest.dequeue(pt);
	SRCount--;
	Car* assiCar = nullptr;
	if (carS.peek(assiCar))
	{
		carS.dequeue(assiCar);
		assiCar->setPatient(pt);
	}
	return nullptr;

}

Car* Hospital::assiEP()
{
	Request* pt = nullptr;
	int x;
	emergencyRequest.dequeue(pt, x);
	ERCount--;
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

Car* Hospital::assiEP(Request* pt)
{
	pt->setHospitalID(hospitalID);
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
		LeavableQueue temp;
		temp.enqueue(R);
		while (NRCount && normalRequest.dequeue(R)) {
			temp.enqueue(R);
		}
		normalRequest = temp;
	}
	else if (R->getType() == "SP") {
		LinkedQueue <Request*> temp;
		temp.enqueue(R);
		while (SRCount && specialRequest.dequeue(R)) {
			temp.enqueue(R);
		}
		specialRequest = temp;
	}
	else {
		emergencyRequest.enqueue(R, ((EPRequest*)R)->getSeverity());
	}
}

int Hospital::AssignRequests(int t, LeavablePriQueue &Ocars){
	int OutCars = 0;
	Car* C = nullptr;
	while (checkEPatient(t) && (CarSCount() || CarNCount() )) {
		C = assiEP();
		Ocars.enqueue(C, C->GetBusyTime() / 2);
		OutCars++;
	}
	while (checkSPatient(t) && (CarSCount())) {
		C = assiSP();
		Ocars.enqueue(C, C->GetBusyTime() / 2);
		OutCars++;
	}
	while (checkNPatient(t) && (CarNCount())) {
		C = assiNP();
		Ocars.enqueue(C, C->GetBusyTime() / 2);
		OutCars++;
	}
	return OutCars;
}


ostream& operator<<(ostream& out,  Hospital& h)
{
	out << h.getHospitalID();
	return out;
}
