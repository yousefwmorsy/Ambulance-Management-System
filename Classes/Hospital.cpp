#include "Hospital.h"

Hospital::Hospital(int SpecialCarCount, int NormalCarCount) {
		numScars = SpecialCarCount;
		numNcars = NormalCarCount;

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
	if(rq->getType() == 'S') { // the function need to implemented in request file
		specialRequest.enqueue(rq);
	}
	else
	{
		normalRequest.enqueue(rq);
	}
	return;
}

void Hospital::setRequest(EPRequest* rq, int s)
{
	emergencyRequest.enqueue(rq, s);
}

void Hospital::serveEP()
{
	int x; Request* rq;
	if (emergencyRequest.peek(rq, x))
	{

	}
}

bool Hospital::hasEPRequests()
{
	Request* x;
	int t;
	return emergencyRequest.peek(x,t);
}

bool Hospital::hasSPRequests()
{
	Request* x;
	return specialRequest.peek(x);
}

bool Hospital::hasNPRequests()
{
	Request* x;
	return normalRequest.peek(x);
}

//ostream& operator<<(ostream& out, const Hospital& h)
//{
//	out << "Hospital " << h.hospitalID << "Info "
//		<< "Number of normal cars: " << h.numNcars << endl;
//	for (int i = 0; i < h.numNcars; i++)
//	{
//		Car c;
//		h.carN->peek(c);
//		out << c << endl;
//	}
//	out << "Number of special cars: " << h.numScars << endl;
//	for (int i = 0; i < h.numScars; i++)
//	{
//		Car c;
//		h.carS->peek(c);
//		out << c << endl;
//	}
//	return out;
//}
