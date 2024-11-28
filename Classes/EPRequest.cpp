#include"EPRequest.h"
#include <iostream>
using namespace std;

EPRequest::EPRequest(int q, int p, int hi, int d, int s) : Request("EP", q, p, hi, d)
{
	Severity = s;
}

int EPRequest::getSeverity()
{
	return Severity;
}
