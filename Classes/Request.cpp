#include "Request.h"
#include <iostream>
using namespace std;

ostream& operator<<(ostream& out, const Request& r)
{
	out << r.Pid;
	return out;
}


Request::Request(string t, int q, int p, int hi, int d)
{
	type = t;
	QT = q;
	Pid = p;
	nearestHid = hi;
	distance = d;
	AT = 0;
	FT = 0;
	WT = 0;
	PT = 0;
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

string Request::getType()
{
	return type;
}

int Request::getHospitalID()
{
	return nearestHid;
}
