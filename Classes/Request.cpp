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
	AT = 0; //Assign time
	FT = 0; //Finish time
	WT = 0; //Waiting time
	PT = 0; //Pick-Up time
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

int Request::getFT()
{
	return FT;
}

int Request::getQT()
{
	return QT;
}

int Request::getWT()
{
	return WT;
}

int Request::getPT()
{
	return PT;
}

int Request::getAT()
{
	//Getting Assign Time
	return AT;
}

int Request::getpid()
{
	return Pid;
}

void Request::setWT(int t)
{
	WT = t;
}

void Request::setdistance(int x)
{
	distance = x;
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
