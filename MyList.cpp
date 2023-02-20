#include "MyList.h"
#include "flighthashtable.h"

template <typename T>
inline MyList<T>::MyList()
{
	head = new Node<T>;
	tail = new Node<T>;
	this->collisions = 0;
	this->size = 0;
	head->next = tail;
	tail->prev = head;
}
//============================================================
template <typename T>
inline MyList<T>::~MyList() // destructor to clean up all nodes
{
	while (!empty())
	{
		removeFront();
	}

	delete head;
	delete tail;
}
//============================================================
template <typename T>
bool MyList<T>::empty() const // is list empty?
{
	return (head->next == tail);
}
//============================================================
template <typename T>
T &MyList<T>::front() const // get front element
{
	if (!empty())
	{
		return head->next->elem;
	}
	else
	{
		throw runtime_error("List is Empty...!");
	}
}
//============================================================
template <typename T>
const T &MyList<T>::back() const // get front element
{
	if (!empty())
	{
		return tail->prev->elem;
	}
	else
	{
		throw runtime_error("List is Empty...!");
	}
}
//============================================================
template <typename T>
void MyList<T>::addBefore(Node<T> *ptr, const T &elem) // add before a certain element
{
	Node<T> *temp = head;

	while (temp != tail)
	{
		if (temp == ptr)
		{
			Node<T> *n = new Node<T>(elem);
			n->prev = temp->prev;
			n->next = temp;
			temp->prev->next = n;
			temp->prev = n;
			break;
		}
		else
		{
			temp = temp->next;
		}
	}
}
//============================================================
template <typename T>
void MyList<T>::addFront(T &elem) // add to front of list
{
	Node<T> *n = new Node<T>(elem);
	Node<T> *a = head->next;
	head->next = n;
	n->prev = head;
	n->next = a;
	a->prev = n;
}
//============================================================
template <typename T>
void MyList<T>::addBack(const T &elem) // add to Back of the list
{
	Node<T> *n = new Node<T>(elem);
	Node<T> *a = tail->prev;
	tail->prev = n;
	n->prev = a;
	n->next = tail;
	a->next = n;
}
//============================================================
template <typename T>
void MyList<T>::removeFront() // remove front item from list
{
	if (!empty())
	{
		Node<T> *a = head->next;
		head->next = a->next;
		a->next->prev = head;
		delete a;
	}

	else
	{
		throw runtime_error("List is Empty...!");
	}
}
//============================================================
template <typename T>
void MyList<T>::removeBack() // remove last item from list
{
	if (!empty())
	{
		Node<T> *a = tail->prev;
		tail->prev = a->prev;
		a->prev->next = tail;
		delete a;
	}

	else
	{
		throw runtime_error("List is Empty...!");
	}
}

template <typename T>
void MyList<T>::remove(Node<T> *ptr)
{ // remove a specific element from the list
	Node<T> *temp = head;

	while (temp != tail)
	{
		if (temp == ptr)
		{
			Node<T> *a = temp->next;
			a->prev = temp->prev;
			temp->prev->next = a;
		}
		temp = temp->next;
	}
}

template class MyList<HashNode>;
