#pragma once
#include <iostream>
using namespace std;
class Request
{
protected:
	string type;
	int QT;
	int Pid;
	int nearestHid;
	int distance;
public:
	Request() {}
	Request(string t , int q, int p, int hi, int d);
	int getQT();
	int getpid();
	string getType();
	int gitHospitalID();
	int gethid();
	friend ostream& operator << (ostream& out, const Request& r);
	//Make operator (=) overloading
};

