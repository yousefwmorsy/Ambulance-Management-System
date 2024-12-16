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
	setStatus("Assigned");
	return;
}

void Car::setStatus(string status)
{
	carStatus = status;
}

void Car::incBusyTime(int x)
{
	busyTime += x;
}

Request* Car::dropPatient()
{
	setStatus("Ready");
	if (ptr)
	{
		Request* x = ptr;
		ptr = nullptr;
		return x;
	}
	return nullptr;
}
Request* Car::getPatient()
{
	return ptr;
}
int Car::getSpeed()
{
	return (!isSpecial) ? speedN: speedS;
}

bool Car::checkSpecial()
{
	return isSpecial;
}
int Car::GetHospitalID()
{
	return hospitalID;
}
int Car::GetCarID()
{
	return carID;
}
bool Car::GetFailingCondition()
{
	return isFail;
}
void Car::SetCarToFail(bool fail)
{
	isFail = fail;
}

int Car::GetBusyTime()
{
	return busyTime;
}


Car::Car()
{
	isFail = false;
}

Car::Car(int hid, int cid, bool isS) {
	hospitalID = hid;
	carID = cid;
	isSpecial = isS;
	carStatus = "Ready";
	busyTime = 0;
	ptr = nullptr;
	isFail = false;
}

