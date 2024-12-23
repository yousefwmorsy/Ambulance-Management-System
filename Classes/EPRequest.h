#pragma once
#include <iostream>
#include "Request.h"

using namespace std;
class EPRequest : public Request
{
private:
	int Severity;
public:
	EPRequest() {}
	EPRequest(int q, int p, int hi, int d, int s); // Copy constructor
	int getSeverity(); // get severity of the EP request
};

