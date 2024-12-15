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

Request* Car::dropPatient()
{
	if (ptr)
	{
		Request* x = ptr;
		ptr = nullptr;
		return x;
	}
}
Request* Car::getPatient()
{
	return ptr;
}
int Car::getSpeed(string Type)
{
	return (Type == "NP") ? speedN: speedS;
}

bool Car::checkSpecial()
{
	return isSpecial;
}
int Car::GetHospitalID()
{
	return hospitalID;
}
Car::Car(int hid, int cid, bool isS) {
	hospitalID = hid;
	carID = cid;
	isSpecial = isS;
	carStatus = "Ready";
	busyTime = 0;
	ptr = nullptr;
}

