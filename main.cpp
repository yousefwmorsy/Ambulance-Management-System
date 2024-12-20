#include <iostream>
#include "Classes/Organiser.h"
using namespace std;

int main() {
	Organiser* pOrg = new Organiser(); 

	pOrg->Simulation();
	
	delete pOrg;
	//while (true) {}
	int x;
	cin >> x;
}