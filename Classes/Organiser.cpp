#include "Organiser.h"

Organiser::Organiser()
{
	timestep = 0;
}

int Organiser::getTime()
{
	return timestep;
}

void Organiser::incTime()
{
	timestep++;
}
