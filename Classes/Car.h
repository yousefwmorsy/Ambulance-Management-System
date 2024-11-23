#pragma once
class Car
{
private:
	static int speedS;
	static int speedN;
	int carID;
	int hospitalID;
	bool isSpecial;
	int patient_ID = -1; //negative one is when there is no patient in the car 
public:
	Car(){}
	Car(int hospitalID,int carID,bool isSpecial);
	static void setSpeed(int speed_special, int speed_normal);
	void setPID(int ID);
	int getPID();       //I don't think we will use it but I am leaving it incase it was needed for debugging
};

