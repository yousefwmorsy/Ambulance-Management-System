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
		ERCount++;
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
		emergencyRequest.dequeue(R,i);
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

ostream& operator<<(ostream& out,  Hospital& h)
{
	Request *R;
	int Y = 0;
	out << "==================Hospital #" << h.hospitalID << " data====================" << endl;
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
	out << h.ERCount << " EP requests: ";
	int E = h.ERCount;
	int S = h.SRCount;
	int N = h.NRCount;
	for (int i = 0; i < E; i++)
	{
		h.emergencyRequest.dequeue(R,Y);
		out << R->getpid() << " ,";
		h.setRequest(R);
	}
	out << endl;
	out << h.ERCount << " SP requests: ";
	for (int i = 0; i < S; i++)
	{
		h.specialRequest.dequeue(R);
		out << R->getpid() << " ,";
		h.setRequest(R);
	}
	out << endl;
	out << h.ERCount << " NP requests: ";
	for (int i = 0; i < N; i++)
	{
		h.normalRequest.dequeue(R);
		out << R->getpid() << " ,";
		h.setRequest(R);
	}
	out << endl;
	out << "Free cars: " << h.numScars << " Scars, " << h.numNcars << "Ncars" << endl;

	return out;
}
