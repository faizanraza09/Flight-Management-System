
//=================================================================================
// Name         : DS Assignment#4
// Author       :
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified:
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include <iostream>
#include <cstdlib>
#include <sstream>
// #include <chrono>

#include "flightticket.h"
#include "flighthashtable.h"

using namespace std;

int addEntry(FlightHASHTABLE &myFlightHashtable, FlightHASHTABLE &dateHashtable); // taking input and calling add function
string lowerString(string st);													   // lowercase the string
//==========================================================
void listCommands()
{
	cout << "\n----------------------------------" << endl;
	cout << "import <path>      	:Import flight-tickets from a CSV file" << endl
		 << "export <path>      	:Export flight-tickets to a CSV file" << endl
		 << "count_collisions   	:Print number of collisions" << endl
		 << "add                	:Add a new flight-ticket" << endl
		 << "delete <key>       	:Delete a flight-ticket" << endl
		 << "find <key>         	:Find a flight-ticket's details" << endl
		 << "allinday <date>    	:Display all flight-tickets in a day" << endl
		 << "printASC <key>     	:Print flight-tickets in ascending order" << endl
		 << "exit               	:Exit the program" << endl;
}
//==========================================================

//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	FlightHASHTABLE dateHASHTABLE; // hashtable for date as key

	string user_input;
	string command;
	string parameter;

	while (true)
	{
		listCommands();
		cout << ">";

		getline(cin, user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter);

		command = lowerString(command);
		parameter = lowerString(parameter);

		if (command == "import")
		{
			int num1 = myFlightHASHTABLE.importCSV(parameter);
			int num2 = dateHASHTABLE.dateImportCSV(parameter);
			cout << num1 << endl;
		}

		else if (command == "export")
		{
			cout << myFlightHASHTABLE.exportCSV(parameter);
		}

		else if (command == "count_collisions")
		{
			cout << "Total number of collisions is " << myFlightHASHTABLE.count_collisions() << endl;
		}

		else if (command == "add")
		{
			if (addEntry(myFlightHASHTABLE, dateHASHTABLE)==1){
				cout<<"Entry has been successfully added"<<endl;
			}
		}

		else if (command == "delete")
		{
			string company;
			string plane;
			bool searched = false;
			for (int i = 0; i < parameter.length(); i++)
			{
				if (parameter[i] == ',')
				{
					searched = true;
					continue;
				}

				if (searched == false)
				{
					company += parameter[i];
				}
				else
				{
					plane += parameter[i];
				}
			}
			Flight_Ticket ticket1 = myFlightHASHTABLE.removedate;
			
			myFlightHASHTABLE.removeRecord(company, stoi(plane));
			Flight_Ticket ticket2 = myFlightHASHTABLE.removedate;
			if (!(ticket1==ticket2)){
				dateHASHTABLE.dateRemove(myFlightHASHTABLE.removedate);
			}
			
		}

		else if (command == "find")
		{
			string company;
			string plane;
			bool searched = false;
			for (int i = 0; i < parameter.length(); i++)
			{
				if (parameter[i] == ',')
				{
					searched = true;
					continue;
				}

				if (searched == false)
				{
					company += parameter[i];
				}
				else
				{
					plane += parameter[i];
				}
			}
			myFlightHASHTABLE.find(company, stoi(plane));
		}

		else if (command == "allinday")
		{
			dateHASHTABLE.allinday(parameter);
		}

		else if (command == "printasc")
		{
			string company;
			string plane;
			bool searched = false;
			for (int i = 0; i < parameter.length(); i++)
			{
				if (parameter[i] == ',')
				{
					searched = true;
					continue;
				}

				if (searched == false)
				{
					company += parameter[i];
				}
				else
				{
					plane += parameter[i];
				}
			}
			myFlightHASHTABLE.printASC(company, stoi(plane));
		}

		else if (command == "exit" or command == "quit")
		{
			break;
		}
		else
		{
			cout << "Invalid Command!!!" << endl;
		}
		fflush(stdin);
	}
	return 0;
}

string lowerString(string str)
{
	string temp;

	for (int i = 0; i < str.length(); i++)
	{
		temp += tolower(str[i]);
	}
	return temp;
}

int addEntry(FlightHASHTABLE &myFlightHashtable, FlightHASHTABLE &dateHashtable)
{
	string companyName;
	string flightNumber;
	string country_of_origin;
	string country_of_destination;
	string stopOver;
	string price;
	string time_of_departure;
	string time_of_arrival;
	string date;

	cout << "Please enter the details of the flight-ticket:\n";

	cout << "Company Name: ";
	getline(cin, companyName);
	companyName = lowerString(companyName);

	cout << "Flight Number: ";
	getline(cin, flightNumber);
	flightNumber = lowerString(flightNumber);

	cout << "Country of Origin: ";
	getline(cin, country_of_origin);
	country_of_origin = lowerString(country_of_origin);

	cout << "Country of Destination: ";
	getline(cin, country_of_destination);
	country_of_destination = lowerString(country_of_destination);

	cout << "Stop Over: ";
	getline(cin, stopOver);
	stopOver = lowerString(stopOver);

	cout << "Price: ";
	getline(cin, price);
	price = lowerString(price);

	cout << "Time of Departure: ";
	getline(cin, time_of_departure);
	time_of_departure = lowerString(time_of_departure);

	cout << "Time of Arrival: ";
	getline(cin, time_of_arrival);
	time_of_arrival = lowerString(time_of_arrival);

	cout << "Date: ";
	getline(cin, date);
	date = lowerString(date);

	// cout<<companyName<<stoi(flightNumber)<<country_of_origin<<country_of_destination<<stopOver<<price<<time_of_departure<<time_of_arrival<<date<<endl;
	Flight_Ticket *data = new Flight_Ticket(companyName, stoi(flightNumber), country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
	int status = myFlightHashtable.add(data);
	dateHashtable.date_add(data);

	return status;
}