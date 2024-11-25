#pragma once
#include <iostream>
using namespace std;
#include "Request.h"
class EPRequest : public Request
{
private:
	int Severity;
public:
	EPRequest(int q, int p, int hi, int d, int s);
};

