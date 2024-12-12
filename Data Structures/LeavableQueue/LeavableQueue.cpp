#include "LeavableQueue.h"

bool LeavableQueue::LeaveQueue(Request* &Removed, int PID)
{
	Node<Request*> *ptr = frontPtr;
	while (ptr && ptr->getNext()->getItem()->getpid() == PID)
	{
		ptr = ptr->getNext();
	}
	if (ptr) {
		Node<Request*>* temp = ptr->getNext();//sets temp to ptr to be removed
		Removed = temp->getItem(); //pointer assigned to the removed car
		ptr->setNext(temp->getNext()); //sets the next of ptr to the next of deleted 
		return true;
	}
	return false;
}
