#include "LeavableQueue.h"

bool LeavableQueue::LeaveQueue(Request*& Removed, int PID)
{
    Node<Request*>* ptr = frontPtr;
    Node<Request*>* prevPtr = frontPtr;
    while (ptr && ptr->getItem()->getpid() != PID)
    {
        if (ptr != frontPtr) {
            prevPtr = prevPtr->getNext();
        }
        ptr = ptr->getNext();
    }
    if (ptr)
    {
        Removed = ptr->getItem();
        if (ptr == prevPtr) frontPtr = frontPtr->getNext();
        prevPtr->setNext(ptr->getNext());
        ptr->setNext(nullptr);
        if (ptr == backPtr) backPtr = prevPtr;
        return true;
    }
    return false;
}

void LeavableQueue::InsertAtBegin(Request* R){
    Node<Request*>* newElement = new Node<Request*>;
    newElement->setItem(R);
    newElement->setNext(NULL);
    if (isEmpty()) {
       enqueue(R);
    }
    else {
       newElement->setNext(frontPtr);
       frontPtr = newElement;
    }
}
