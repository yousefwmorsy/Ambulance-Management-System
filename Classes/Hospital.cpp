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

