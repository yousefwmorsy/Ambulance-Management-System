#pragma once
#include <iostream>
using namespace std;
class Request
{
protected:
	string type;
	int QT;
	int AT;
	int PT;
	int WT;
	int FT;
	int Pid;
	int nearestHid;
	int distance;
public:
	Request() {}
	Request(string t , int q, int p, int hi, int d);
	void setAT(int x);
	void setPT(int x);
	int getQT();
	int getpid();
	string getType();
	int getHospitalID();
	int getDistance();
	friend ostream& operator << (ostream& out, const Request& r);

	//Make operator (=) overloading
};

