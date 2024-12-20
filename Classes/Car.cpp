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

string Car::getStatus()
{
	return carStatus;
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

void Car::SetTimeToBack(int t)
{
	TimeToBack = t;
}

int Car::GetTimeToBack()
{
	return TimeToBack;
}


Car::Car()
{
	TimeToBack = 0;
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

ostream& operator<<(ostream& out, const Car& c)
{
	if (c.isSpecial)
	{
		out << "S" << c.carID << "_H" << c.hospitalID << "_P";
		if (c.ptr) {
			out << *c.ptr;
		}
		else {
			out << "X";
		}
	}
	else
	{
		out << "N" << c.carID << "_H" << c.hospitalID << "_P";
		if (c.ptr) {
			out << *c.ptr;
		}
		else {
			out << "X";
		}
	}
	return out;
	// TODO: insert return statement here
}
