#include "Car.h"
int Car::speedN;
int Car::speedS;

void Car::setSpeed(int s,int n){
	speedN = n;
	speedS = s;
	return;
}
void Car::setPatient(Request* pt)
{
	ptr = pt;
	return;
}
void Car::dropPatient()
{
	if (getPatient())
	{
		ptr = nullptr;
	}
}
Request* Car::getPatient()
{
	return ptr;
}
bool Car::checkSpecial()
{
	return isSpecial;
}
Car::Car(int hid, int cid, bool isS) {
	hospitalID = hid;
	carID = cid;
	isSpecial = isS;
	ptr = nullptr;
}

ostream& operator<<(ostream& out, const Car& c)
{
	string type = "Normal";
	if (c.isSpecial) {
		type = "Special";
	}
	out << "Car " << c.carID << "info :\n"
		<< "Hospital ID: " << c.hospitalID << endl
		<< "Type: " << type << endl
		<< "Patient ID: " << c.ptr;
	return out;
}
