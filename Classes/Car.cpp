#include "Car.h"
int Car::speedN;
int Car::speedS;
void Car::setSpeed(int s,int n){
	speedN = n;
	speedS = s;
	return;
}
void Car::setPID(int id) {
	patient_ID = id;
}
int Car::getPID() {
	return patient_ID;
}
Car::Car(int hid, int cid, bool isS) {
	hospitalID = hid;
	carID = cid;
	isSpecial = isS;
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
		<< "Patient ID: " << c.patient_ID;
	return out;
}
