#pragma once
#include "Data Structures/Queue/LinkedQueue.h"
#include "Classes//Request.h"

class MyClass : public LinkedQueue<Request*>
{
public:
	MyClass();

	Node<Request*>* GetBeforeLast() {
		Node<Request*>* temp = backPtr;
		Node<Request*>* target = backPtr;
		while (temp->getItem() != frontPtr->getItem()) {
			target = temp;
			temp = temp->getNext();
		}
	} 

	bool InsertAtBegin(Request* R) {
		Node<Request*>* newElement = new Node<Request*>;
		newElement->setItem(R);
		newElement->setNext(NULL);
		if (place == 0) {
		if (isEmpty()) {
				enqueue(R);
		}
		else {
			newElement->setNext(frontPtr);
			frontPtr = newElement;
		}
	}
	~MyClass();

private:
	
};