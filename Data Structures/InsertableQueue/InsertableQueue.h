#pragma once
#include "..//Queue//LinkedQueue.h"
#include "..//..//Classes/Request.h"

class InsertableQueue : public LinkedQueue<Request*>
{
public:

	void InsertAtBegin(Request* R) {
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
	
};