#pragma once
#include <iostream>
using namespace std;

template < typename T>
class priNode
{
private :
	T item;		// A data item
	int pri;	//priority of the item
	priNode<T>* next; // Pointer to next node
public :
	priNode(const T& r_Item, int PRI)
	{
		setItem(r_Item, PRI);
		next = nullptr;
	}
	void setItem(const T& r_Item, int PRI)
	{
		item = r_Item;
		pri = PRI;
	}
	void setNext(priNode<T>* nextNodePtr)
	{		next = nextNodePtr; 	}
	
	T getItem(int& PRI) const
	{
		PRI = pri;
		return item;
	}
	
	priNode<T>* getNext() const 
	{		return next;	}
	
	int getPri() const
	{		return pri; 	}
}; // end Node

//This class impelements the priority queue as a sorted list (Linked List)
//The item with highest priority is at the front of the queue
template <typename T>
class priQueue
{
protected:
    priNode<T>* head;
public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        /*T tmp;
        int p;
        while (dequeue(tmp,p));*/
    }

    //insert the new node in its correct position according to its priority
    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {
            
            newNode->setNext(head);
            head = newNode;
            return;
        }
       
        priNode<T>* current = head;        
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext( current->getNext());
        current->setNext( newNode);        
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty())
            return false;

        topEntry = head->getItem(pri);
        pri = head->getPri();
        return true;
    }
    void print()
    {
        int x;
        if (isEmpty())
        {
            return;
        }
        else
        {
            priNode<T>* current = head;
            while (current != nullptr)
            {
                cout << *current->getItem(x) << endl;
                current = current->getNext();
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    /*
    Function: Copy constructor
    To avoid shallow copy,
    copy constructor is provided

    Input: priQueue<T>: The Queue to be copied
    Output: none
    */

    priQueue(const priQueue<T>& LQ) {
        head = nullptr;
        priNode<T>* NodePtr = LQ.head; // start at the head node in LQ
        while (NodePtr) {
            int x;
            enqueue(NodePtr->getItem(x), NodePtr->getPri()); // get data of each node and enqueue it in this queue
            NodePtr = NodePtr->getNext();
        }
    }


    bool isEmpty() const {
        return head == nullptr;
    }
};
