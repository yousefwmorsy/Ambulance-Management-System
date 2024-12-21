#include "LeavableQueue.h"

bool LeavableQueue::LeaveQueue(Request*& Removed, int PID)
{
    Node<Request*>* ptr = frontPtr;
    int x;
    while (ptr && ptr->getNext() && ptr->getNext()->getItem()->getpid() != PID) {
        ptr = ptr->getNext();
    } //traversal until it reaches null or ptr before the one to be deleted
    if (ptr && ptr->getNext() && ptr->getNext()->getItem()->getpid() == PID) {
        Node<Request*>* temp = ptr->getNext();//sets temp to ptr to be removed
        Removed = temp->getItem(); //pointer assigned to the removed car
        ptr->setNext(temp->getNext()); //sets the next of ptr to the next of deleted 
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
