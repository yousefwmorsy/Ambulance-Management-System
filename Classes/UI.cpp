#include "UI.h"
#include "Hospital.h"

void UI::PrintHospital(Hospital H, int timeStep, LinkedQueue<Request*> F, int FinishRCount)
{
	cout <<"Current Time Step: " << timeStep << endl;
	cout << H;
	cout << endl << FinishRCount << " finished patients: ";
	Request* R;
	for (int i = 0; i < FinishRCount; i++) {
		F.dequeue(R);
		cout << R->getpid() << ", ";
	}
	cout << endl;
}
