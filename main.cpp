#include <iostream>
#include "Classes/Organiser.h"
using namespace std;

int main() {
	Organiser* pOrg = new Organiser(4);
	cout << endl << pOrg->getTime() << endl;
	pOrg->incTime(); pOrg->incTime();
	cout << pOrg->getTime() << endl;
	delete pOrg;
}