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

void Request::setAT(int x)
{
	AT = x;
}

void Request::setPT(int x)
{
	PT = x;
}

void Request::setFT(int x)
{
	FT = x;
}

int Request::getQT()
{
	return QT;
}

int Request::getpid()
{
	return Pid;
}


string Request::getType()
{
	return type;
}

void Request::setHospitalID(int HID)
{
	nearestHid = HID;
	return;
}

int Request::getHospitalID()
{
	return nearestHid;
}

int Request::getDistance()
{
	return distance;
}
