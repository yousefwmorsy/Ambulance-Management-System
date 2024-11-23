#include "Hospital.h"

Hospital::Hospital(){}

Hospital::Hospital(int hID, int SpecialCarCount, int NormalCarCount) {
		for (int i = 0; i < SpecialCarCount; i++)
		{
			Car* temp = new Car(hID, i + 1, true);
			carS->enqueue(*temp);
		}
		for (int i = 0; i < NormalCarCount; i++)
		{
			Car* temp = new Car(hID, i + 1, false);
			carN->enqueue(*temp);
		}
		numScars = SpecialCarCount;
		numNcars = NormalCarCount;
}

ostream& operator<<(ostream& out, const Hospital& h)
{
	out << "Hospital " << h.hospitalID << "Info "
		<< "Number of normal cars: " << h.numNcars << endl;
	for (int i = 0; i < h.numNcars; i++)
	{
		Car c;
		h.carN->peek(c);
		out << c << endl;
	}
	out << "Number of special cars: " << h.numScars << endl;
	for (int i = 0; i < h.numScars; i++)
	{
		Car c;
		h.carS->peek(c);
		out << c << endl;
	}
}