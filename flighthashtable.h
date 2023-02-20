#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include <fstream>
#include <iostream>
#include "flightticket.h"
#include "MyList.h"
// include additional header files as needed

using namespace std;

const int SIZE = 125003; // first prime number after 100000*1.25=125000 which is the size of the largest dataset

bool operator==(Flight_Ticket ticket1, Flight_Ticket ticket2);

class HashNode
{
private:
	string key;			 // key = companyName+flightNumber
	Flight_Ticket value; // value = flight ticket
public:
	HashNode(){};
	HashNode(string key, Flight_Ticket value)
	{
		this->key = key;
		this->value = value;
	}

	Flight_Ticket getValue() { return value; } // get the flight ticket
	string getKey() { return key; }			   // get the key
	friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
private:
	MyList<HashNode> *buckets; // List of Buckets, Please create your own List Class called MyList
	int size;				   // Current Size of HashTable
	int capacity;			   // Total Capacity of HashTable
public:
	FlightHASHTABLE();										 // constructor
	~FlightHASHTABLE();										 // destructor
	long hashCode(string key);								 // implement and test different hash functions
	Flight_Ticket removedate;								 // save flight ticket with the date that needs to be removed
	int importCSV(string path);								 // Load all the flight-tickets from the CSV file to the HashTable
	int dateImportCSV(string path);							 // import csv for date key
	int exportCSV(string path);								 // Export all the flight-tickets from the HashTable to a CSV file in an ascending order
	string exportHelper(int index);							 // helper for exportCSV
	int count_collisions();									 // return the number of collisions on the HashTable
	int add(Flight_Ticket *data);							 // add new flight to the HashTable
	int date_add(Flight_Ticket *data);						 // add date based enteries in the hashtable
	void removeRecord(string companyName, int flightNumber); // Delete a record with key from the hashtable
	void dateRemove(Flight_Ticket rdate);
	void find(string companyName, int flightNumber);		// Find and Display records with same key entered
	void allinday(string date);								// Find and Display records with same day entered
	void printASC(string companyName, int flightNumber);	// display the collisions for the entered key in an ascending order
	void displayRecord(Flight_Ticket data, int counter);	// display a record
	string lowerString(string str);							// lowercase the string
	int removeHelper(string companyName, int flightNumber); // helper for remove
};

#endif
