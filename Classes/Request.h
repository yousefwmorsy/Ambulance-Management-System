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
	void setFT(int x);
	int getFT();
	int getQT();
	int getWT();
	int getPT();
	int getAT(); //Getting Assign Time
	int getpid();
	void setWT(int);
	void setdistance(int x);
	string getType();
	void setHospitalID(int); //only used for EP 
	int getHospitalID();
	int getDistance();
	friend ostream& operator << (ostream& out,const Request& r);
	//Make operator (=) overloading
};

