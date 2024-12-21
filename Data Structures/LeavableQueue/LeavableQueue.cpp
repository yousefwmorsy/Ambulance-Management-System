#include "LeavableQueue.h"

bool LeavableQueue::LeaveQueue(Request*& Removed, int PID)
{
    Node<Request*>* prevptr = backPtr;
    Node<Request*>* ptr = frontPtr;
    while (ptr && prevptr && ptr->getItem()->getpid() != PID)
    {
        prevptr = prevptr->getNext();
        ptr = ptr->getNext();
    }
    if (ptr && prevptr)
    {
        Removed = ptr->getItem();
        prevptr->setNext(ptr->getNext());
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
