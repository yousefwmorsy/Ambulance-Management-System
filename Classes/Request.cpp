#include "Request.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const Request& r)
{
	string type = "Normal";
	if (r.type == 'S') {
		type = "Special";
	}
	out << "Patient ID: " << r.Pid << " Info\n"
		<< "Nearest Hospital: Hospital " << r.nearestHid << endl
		<< "Distance: " << r.distance;
	return out;
}

Request::Request(char t, int q, int p, int hi, int d)
{
	type = t;
	QT = q;
	Pid = p;
	nearestHid = hi;
	distance = d;
}

int Request::getQT()
{
	return QT;
}

int Request::getpid()
{
	return Pid;
}

int Request::gethid()
{
	return nearestHid;
}

char Request::getType()
{
	return type;
}
