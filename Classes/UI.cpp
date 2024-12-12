#include "UI.h"
#include "Hospital.h"

void UI::PrintHospital(Hospital H, int timeStep, LinkedQueue<Request*> F, int FinishRCount)
{
	cout <<"Current Time Step: " << timeStep << endl;
	cout << "================== Hospital #" << H << " data ====================" << endl;
	H.printEP();
	H.printSP();
	H.printNP();
	cout << "================= Hospital #" << H << " end data =================";
	cout << endl << FinishRCount << " finished patients: ";
	Request* R;
	for (int i = 0; i < FinishRCount; i++) {
		F.dequeue(R);
		cout << *R;
		if (i != FinishRCount - 1)
		{
			cout << ", ";
		}
	}
	cout << endl;
}
