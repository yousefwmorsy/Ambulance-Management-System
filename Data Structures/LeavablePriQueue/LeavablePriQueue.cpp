#include "LeavablePriQueue.h"

bool LeavablePriQueue::LeaveQueue(Car*& Removed, int timetoreach, int PID)
{
	priNode<Car*>* prevptr = NULL;
	priNode<Car*>* ptr = head;
	int x;
	while (ptr && ptr->getItem(x)->getPatient()->getpid() != PID)
	{
		prevptr = ptr;
		ptr = ptr->getNext();
	}
	if (ptr) {
		Removed = ptr->getItem(timetoreach); //pointer assigned to the removed car
		timetoreach *= -1;
		prevptr->setNext(ptr->getNext()); //sets the next of ptr to the next of deleted 
		return true;
	}
	return false;
}

bool LeavablePriQueue::GetPlacedItem(Car*&randCar, int randPlace)
{
	priNode<Car*>* kyle_walker = head;
	priNode<Car*>* dltItem = head;
	priNode<Car*>* BeforedltItem = nullptr;
	if (kyle_walker) {
		for (int i = 0; i < randPlace; i++) {
			kyle_walker = kyle_walker->getNext();
		}
		while (dltItem->getItem(randPlace) != kyle_walker->getItem(randPlace)) {
			BeforedltItem = dltItem;
			dltItem = dltItem->getNext();
		}
		if (BeforedltItem) {
			BeforedltItem->setNext(dltItem->getNext());
		}
		else {
			head = head->getNext();
		}
		randCar = kyle_walker->getItem(randPlace); 
		return true;
	}
	return false;
}



/*
Case1: 1 OC and x = 0 (1) then randCar = 1 -> dequeue()
Case2: 2 OC and x = 0 (1,2) then randCar = 1 -> 
case3: 5 OC and x = 2 (1,2,3,4,5) then randCar = 3 -> 
*/