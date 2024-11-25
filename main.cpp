#include <iostream>
#include "Classes/Organiser.h"
using namespace std;

int main() {
	Organiser* pOrg = new Organiser(); 

	while (pOrg->notEnd()) {
		//code to run while program is active
	}

	delete pOrg;
}