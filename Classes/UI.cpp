#include "UI.h"
#include "Hospital.h"
#include <string>

void UI::PrintInteractive(Hospital H, int timeStep, LinkedQueue<Request*> F, int FinishRCount, int OCarC, int BCarC, LeavablePriQueue OCars, priQueue<Car*> BCars)
{
	cout <<"Current Time Step: " << timeStep << endl;
	cout << "================== Hospital #" << H << " data ====================" << endl;
	H.printEP();
	H.printSP();
	H.printNP();
	cout << "Free Cars: " << H.CarSCount() << " SCars, " << H.CarNCount() << " NCars" << endl;
	cout << "================= Hospital #" << H << " end data =================";
	cout << endl << "-------------------------------------------------------------------" << endl;
	cout << OCarC << " ==> Out cars: ";
	OCars.print();
	cout << endl << BCarC << " <== Back cars: ";
	BCars.print();
	cout << endl << "-------------------------------------------------------------------" << endl;
	cout << FinishRCount << " finished patients: ";
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

bool UI::SelectMode()
{
	string m;
	cin >> m;
	if (m == "i")
	{
		//PrintInteractive(H, timestep, F, FinishRcount, OCarC, BCarC, OCars, BCars);
		return true;
	}
	else if (m == "s")
	{
		//PrintSilent();
		return false;
	}
	else
	{
		/*cout << "Please type ""i"" or ""s""" << endl;
		SelectMode(m, H, timestep, F, FinishRcount, OCarC, BCarC, OCars, BCars);*/
		SelectMode();
	}
}

void UI::PrintSilent()
{
	cout << "Silent Mode, Simulation Starts..." << endl;
	cout << "Simulstion ends, Output file Created" << endl;
}
