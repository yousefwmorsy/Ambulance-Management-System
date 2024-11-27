#include "LeavablePriQueue.h"

void LeavablePriQueue::LeaveQueue(Car* &Removed, int PID)
{
	priNode<Car*>* ptr = head; 
	int x;
	while (ptr && ptr->getNext()->getItem(x)->getPatient()->getpid() != PID) {
		ptr = ptr->getNext();
	} //traversal until it reaches null or ptr before the one to be deleted
	if (ptr) {
		Removed = ptr->getNext()->getItem(x); //sets temp to ptr to be deleted
		ptr->setNext(ptr->getNext()->getNext()); //sets the next of ptr to the next of deleted 
	
	}
}
