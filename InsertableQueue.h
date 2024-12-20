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

	bool InsertAtPlace(int place, Request* R) {
		Node<Request*>* newElement = new Node<Request*>;
		newElement->setItem(R);
		newElement->setNext(NULL);
		if (place == 0) {
			if (isEmpty()) {
				enqueue(R);
			}
			else {
				GetBeforeLast()->setNext(newElement);
				frontPtr = newElement;//back->1->2->3->4()->NULL
				
			}
		}
	}
	~MyClass();

private:
	
};