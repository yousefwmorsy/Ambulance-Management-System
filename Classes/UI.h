#pragma once
#include "Hospital.h"
class UI{
private:

public:
	void PrintHospital(Hospital H, int timeStep, LinkedQueue<Request*> F, int FinishRCount);
};

