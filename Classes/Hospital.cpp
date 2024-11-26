#include "Hospital.h"

Hospital::Hospital(){}

Hospital::Hospital(int SpecialCarCount, int NormalCarCount,Organiser *orga) {
		numScars = SpecialCarCount;
		numNcars = NormalCarCount;
		org = orga;
}

void Hospital::addCar(Car* ptr)
{
	if (ptr->checkSpecial()) {
		carS->enqueue(ptr);
	}
	else
	{
		carN->enqueue(ptr);
	}
	return;
}

void Hospital::setRequest(Request* rq)
{
	/*if (rq->isSpecial()) { // the function need to implemented in request file
		specialRequest->enqueue(rq);
	}
	else
	{
		normalRequest->enqueue(rq);
	}*/
	return;
}

ostream& operator<<(ostream& out, const Hospital& h)
{
	out << "Hospital " << h.hospitalID << "Info "
		<< "Number of normal cars: " << h.numNcars << endl;
	for (int i = 0; i < h.numNcars; i++)
	{
		Car c;
		h.carN->peek(c);
		out << c << endl;
	}
	out << "Number of special cars: " << h.numScars << endl;
	for (int i = 0; i < h.numScars; i++)
	{
		Car c;
		h.carS->peek(c);
		out << c << endl;
	}
	return out;
}
