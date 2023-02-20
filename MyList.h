#pragma once
#ifndef MY_LIST
#define MY_LIST
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <exception>

using namespace std;

template <typename T>
class MyList;

template <typename T>
class Node
{
private:
	T elem;
	Node<T> *next; // Link (pointer) to the next Node
	Node<T> *prev; // Link (pointer) to the previous Node
	friend class MyList<T>;
	friend class FlightHASHTABLE;

public:
	Node() : next(NULL), prev(NULL)
	{
	}
	Node(T elem) : elem(elem), next(NULL), prev(NULL)
	{
	}

	Node<T> *getNext() { return this->next; } // get next node

	T &getElem() { return this->elem; } // get element of node
};
//==============================================================
template <typename T>
class MyList
{
private:
	Node<T> *head;	// pointer to the head of List
	Node<T> *tail;	// pointer to the tail of List
	int collisions; // number of collisions in the list
	int size;		// size of list

public:
	MyList();									 // constructor to create dummy head and tail nodes
	~MyList();									 // destructor to clean up all nodes
	bool empty() const;							 // return true if the list is empty
	T &front() const;							 // return the element from the first valid Node of list, throw an exception if the list is empty
	const T &back() const;						 // get the value (element) from last valid Node of the list, throw an exception if the list is empty
	void addBefore(Node<T> *ptr, const T &elem); // add a new node before a node pointed by ptr
	void addFront(T &elem);						 // add a new node to the front of list (after head)
	void addBack(const T &elem);				 // add a new node to the back of the list (before tail)
	void removeFront();							 // remove front node from list, throw an exception if the list is empty
	void removeBack();							 // remove last node from list, throw an exception if the list is empty
	void remove(Node<T> *ptr);					 // remove a specific node
	// void reverseList();	// reverse the list
	// bool isPalindrome(); //return true if the list is Palindrome, false otherwise
	// void display() const;	// display all element of the list
	Node<T> *getHead() { return this->head; }	 // get the head of the list
	Node<T> *getTail() { return tail; }			 // get the tail of the list
	int getSize() { return size; }				 // get size of the list
	void incrementSize() { size++; }			 // increment size of the list
	void decrementSize() { size--; }			 // decrement size of the list
	int getCollisions() { return collisions; }	 // get collisions of the list
	void incrementCollisions() { collisions++; } // increment collisions of the list
	void decrementCollisions() { collisions--; } // decrement collisions of the list
	friend class FlightHASHTABLE;
};

#endif
