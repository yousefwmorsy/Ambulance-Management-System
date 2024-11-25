#include "Request.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const Request& r)
{
	string type = "Normal";
	if (r.isSpecial) {
		type = "Special";
	}
	out << "Patient ID: " << r.Pid << " Info\n"
		<< "Nearest Hospital: Hospital " << r.nearestHid << endl
		<< "Distane: " << r.distance;
	return out;
}

int Request::getQT()
{
	return QT;
}
