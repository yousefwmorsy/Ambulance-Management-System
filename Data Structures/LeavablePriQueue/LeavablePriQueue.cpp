#include "LeavablePriQueue.h"

void LeavablePriQueue::LeaveQueue(int x, int PID)
{
	priNode<Car>* ptr = head;
	while (ptr && ptr->getNext()->getItem(x).getPID() != PID) {
		ptr = ptr->getNext();
	}
	if (ptr) {
		priNode<Car>* temp = ptr->getNext();
		ptr->setNext(temp->getNext());
		delete temp;
		temp = nullptr;
	}
}
