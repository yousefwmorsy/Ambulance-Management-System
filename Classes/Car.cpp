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