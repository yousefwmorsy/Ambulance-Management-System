#include "LeavablePriQueue.h"

bool LeavablePriQueue::LeaveQueue(Car* &Removed, int timetoreach, int PID)
{
	priNode<Car*>* ptr = head; 
	int x;
	while (ptr && ptr->getNext() && ptr->getNext()->getItem(x)->getPatient()->getpid() != PID) {
		ptr = ptr->getNext();
	} //traversal until it reaches null or ptr before the one to be deleted
	if (ptr && ptr->getNext() && ptr->getNext()->getItem(x)->getPatient()->getpid() == PID) {
		priNode<Car*>* temp = ptr->getNext();//sets temp to ptr to be removed
		Removed = temp->getItem(timetoreach); //pointer assigned to the removed car
		timetoreach *= -1;
		ptr->setNext(temp->getNext()); //sets the next of ptr to the next of deleted 
		return true;
	}
	return false;
}

bool LeavablePriQueue::GetNext(Car*randCar, int randPlace)
{
	priNode<Car*>* kyle_walker = head;
	if (kyle_walker) {
		for (int i = 0; i < randPlace; i++) {
			kyle_walker = kyle_walker->getNext();
		}
		randCar = kyle_walker->getItem(randPlace); 
		return true;
	}
	return false;
}
