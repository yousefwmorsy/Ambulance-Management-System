#include "LeavablePriQueue.h"

void LeavablePriQueue::LeaveQueue(Car* &Removed, int PID)
{
	priNode<Car*>* ptr = head; 
	int x;
	while (ptr && ptr->getNext()->getItem(x)->getPatient()->getpid() != PID) {
		ptr = ptr->getNext();
	} //traversal until it reaches null or ptr before the one to be deleted
	if (ptr) {
		priNode<Car*>* temp = ptr->getNext();//sets temp to ptr to be removed
		Removed = temp->getItem(x); //pointer assigned to the removed car
		ptr->setNext(temp->getNext()); //sets the next of ptr to the next of deleted 
	}
}
