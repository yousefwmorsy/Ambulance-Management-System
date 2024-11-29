#include "Hospital.h"

Hospital::Hospital(int HID, int SpecialCarCount, int NormalCarCount) {
		numScars = SpecialCarCount;
		numNcars = NormalCarCount;
		hospitalID = HID;
		NRCount = 0;
		SRCount = 0;
		ERCount = 0;

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
	}
	else if(rq->getType() == "NP")
	{
		normalRequest.enqueue(rq);
		NRCount++;
	}
	else {
		emergencyRequest.enqueue(rq, ((EPRequest*)rq)->getSeverity());
		ERCount++;
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
		carS.dequeue(C);
		numScars--;
	}
	else {
		carS.dequeue(C);
		numNcars--;
	}
	return C;
}

void Hospital::SetCarFree(Car*c)
{
	if (c->checkSpecial()) {
		carS.enqueue(c);
	}
	else {
		carN.enqueue(c);
	}
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

void Hospital::printEP()
{
	Request* R;
	priQueue <Request*> Temp; int X = 0;
	int E = ERCount;
	cout << ERCount << " EP requests: ";
	for (int i = 0; i < E; i++)
	{
		emergencyRequest.dequeue(R, X);
		cout << *R;
		if (i != E - 1)
		{
			cout << ", ";
		}
		Temp.enqueue(R, X);

	}
	while (Temp.dequeue(R, X)) {
		emergencyRequest.enqueue(R, X);
	}
	cout << endl;
}

void Hospital::printSP()
{
	Request* R;
	int S = SRCount;
	cout << SRCount << " SP requests: ";
	for (int i = 0; i < S; i++)
	{
		specialRequest.dequeue(R);
		cout << *R;
		if (i != S - 1)
		{
			cout << ", ";
		}
		specialRequest.enqueue(R);
	}
	cout << endl;
}

void Hospital::printNP()
{
	Request* R;
	int N = NRCount;
	cout << NRCount << " NP requests: ";
	for (int i = 0; i < N; i++)
	{
		normalRequest.dequeue(R);
		cout << *R;
		if (i != N - 1)
		{
			cout << ", ";
		}
		normalRequest.enqueue(R);
	}
	cout << endl;
}

ostream& operator<<(ostream& out,  Hospital& h)
{
	out << h.getHospitalID();
	
	//Request *R;
	//int Y = 0;
	//out << "================== Hospital #" << h.hospitalID << " data ====================" << endl;
		/*<< "Number of normal cars: " << h.numNcars << endl;
	for (int i = 0; i < h.numNcars; i++)
	{
		for (int i = 0; i < h.numNcars; i++) {
			Car* c;
			h.carN.dequeue(c);
			cout << *c << endl;
			h.carN.enqueue(c);
		}
	}
	out << "Number of special cars: " << h.numScars << endl;
	for (int i = 0; i < h.numScars; i++)
	{
		for (int i = 0; i < h.numScars; i++) {
			Car* c;
			h.carS.dequeue(c);
			cout << *c << endl;
			h.carS.enqueue(c);
		}
	}*/
	/*h.printEP();
	h.printNP();
	h.printSP();*/


	//out << "Free cars: " << h.numScars << " Scars, " << h.numNcars << " Ncars";
	//out << "\n================== Hospital #" << h.hospitalID << " end data =================";
	

	return out;
}
