#pragma once
#include <iostream>
using namespace std;
class Request
{
protected:
	char type;
	int QT;
	int Pid;
	int nearestHid;
	int distance;
public:
	Request() {}
	Request(char t , int q, int p, int hi, int d);
	int getQT();
	int getpid();
	char getType();
	friend ostream& operator << (ostream& out, const Request& r);
	//Make operator (=) overloading
};

