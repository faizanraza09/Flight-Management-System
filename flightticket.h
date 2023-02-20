#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include <iostream>
using namespace std;

class Flight_Ticket
{
private:
	// initial declarations for the ticket
	string companyName;
	int flightNumber;
	string country_of_origin;
	string country_of_destination;
	string stopOver;
	string price;
	string time_of_departure;
	string time_of_arrival;
	string date;

public:
	Flight_Ticket() {}
	Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
	// functions for accessing attributes
	string getCompanyName();
	int getFlightNumber();
	string getCountryOfOrigin();
	string getCountryofDestination();
	string getStopOver();
	string getPrice();
	string getTimeOfDeparture();
	string getTimeOfArrival();
	string getDate();
};

#endif
