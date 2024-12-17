#pragma once
#include "Hospital.h"
class UI{
private:

public:
	void PrintInteractive(Hospital H, int timeStep, LinkedQueue<Request*> F, int FinishRCount, int OCarC, int BCarC, LeavablePriQueue OCars, priQueue<Car*> BCars);
	bool SelectMode();
	void PrintSilent();
};

