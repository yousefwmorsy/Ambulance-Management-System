#include "LeavablePriQueue.h"

void LeavablePriQueue::LeaveQueue(int x, int PID)
{
	priNode<Car>* ptr = head; 
	while (ptr && ptr->getNext()->getItem(x).getPID() != PID) {
		ptr = ptr->getNext();
	} //traversal until it reaches null or ptr before the one to be deleted
	if (ptr) {
		priNode<Car>* temp = ptr->getNext(); //sets temp to ptr to be deleted
		ptr->setNext(temp->getNext()); //sets the next of ptr to the next of deleted 
		delete temp; 
		temp = nullptr;
	}
}
