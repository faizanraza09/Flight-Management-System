#include "flighthashtable.h"
#include "flightticket.h"

// overload for comparing flight ticket
bool operator==(Flight_Ticket ticket1, Flight_Ticket ticket2)
{
    if (ticket1.getCompanyName() == ticket2.getCompanyName() && ticket1.getFlightNumber() == ticket2.getFlightNumber() && ticket1.getCountryOfOrigin() == ticket2.getCountryOfOrigin() && ticket1.getCountryofDestination() == ticket2.getCountryofDestination() && ticket1.getStopOver() == ticket2.getStopOver() && ticket1.getPrice() == ticket2.getPrice() && ticket1.getTimeOfDeparture() == ticket2.getTimeOfDeparture() && ticket1.getTimeOfArrival() == ticket2.getTimeOfArrival() && ticket1.getDate() == ticket2.getDate())
    {
        return true;
    }
    else
    {
        return false;
    }
}

FlightHASHTABLE::FlightHASHTABLE()
{
    this->size = 0;
    this->capacity = SIZE;
    buckets = new MyList<HashNode>[capacity];
}

FlightHASHTABLE::~FlightHASHTABLE()
{
    delete[] buckets;
}

// testing all the hashcode functions and then cyclic as default
long FlightHASHTABLE::hashCode(string key)
{
    // cyclic shift hash code
    unsigned int h = 0;
    int l = key.length();
    for (int i = 0; i < l; i++)
    {
        h = (h << 5) | (h >> 27);
        h += (unsigned int)key[i];
    }

    return h % capacity;
}

// summation hash code
// for (int i=0;i<key.length();i++) {
//     h += (unsigned int) key[i];
// }

// polynomial summation hash code
// for (int i=0;i<key.length();i++) {
//     h = h*29+(unsigned int) key[i];
// }

// Xor based hash code
//  for (int i=0;i<key.length();i++) {
//      h += h^((unsigned int) key[i]);
//  }

// modular multiplication hash code
//  for (int i=0;i<key.length();i++) {
//      h = (h*29)%101+(unsigned int) key[i];
//  }

// combined xor cyclic based hash code
//  for (int i=0;i<key.length();i++) {
//      h = (h<<5)^((unsigned int) key[i]);
//  }

// add data to the hashtable
int FlightHASHTABLE::add(Flight_Ticket *data)
{
    string key = data->getCompanyName() + "," + to_string(data->getFlightNumber());
    long hash = hashCode(key);

    HashNode *inf = new HashNode(key, *data);

    bool same_key = false;

    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        string temp_key = temp->getElem().getKey();
        if (*data == temp->getElem().getValue())
        {
            return -1;
        }

        else if (temp_key == key)
        {
            same_key = true;

            if (data->getCountryofDestination() <= temp->getElem().getValue().getCountryofDestination())
            { // check ascending order
                buckets[hash].addBefore(temp, *inf);
                size++;
                buckets[hash].incrementSize();
                return 1;
            }
        }

        else if (same_key == true)
        {
            buckets[hash].addBefore(temp, *inf);
            size++;
            buckets[hash].incrementSize();
            return 1;
        }

        temp = temp->getNext();
    }

    buckets[hash].addBack(*inf);
    size++;
    buckets[hash].incrementSize();

    if (same_key == false && buckets[hash].getSize() > 1)
    {
        buckets[hash].incrementCollisions();
    }
    return 1;
}

// add into the date hashtable
int FlightHASHTABLE::date_add(Flight_Ticket *data)
{
    string key = data->getDate();
    long hash = hashCode(key);

    HashNode *inf = new HashNode(key, *data);

    bool same_key = false;

    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        string temp_key = temp->getElem().getKey();
        if (*data == temp->getElem().getValue())
        {
            return -1;
        }

        else if (temp_key == key)
        {
            same_key = true;

            if (data->getTimeOfDeparture() <= temp->getElem().getValue().getTimeOfDeparture())
            { // check ascending order
                buckets[hash].addBefore(temp, *inf);
                size++;
                buckets[hash].incrementSize();
                return 1;
            }
        }

        else if (same_key == true)
        {
            buckets[hash].addBefore(temp, *inf);
            size++;
            buckets[hash].incrementSize();
            return 1;
        }

        temp = temp->getNext();
    }

    buckets[hash].addBack(*inf);
    size++;
    buckets[hash].incrementSize();

    if (same_key == false && buckets[hash].getSize() > 1)
    {
        buckets[hash].incrementCollisions();
    }
    return 1;
}

// import into csv
int FlightHASHTABLE::importCSV(string path)
{
    ifstream myFile(path);

    int cnt = 0;

    if (!myFile)
    {
        return -1;
    }
    string myText;

    // parse the incoming text into the variables
    while (getline(myFile, myText))
    {
        if (cnt == 0)
        {
            cnt++;
            continue;
        }
        string companyName;
        string flightNumber;
        string country_of_origin;
        string country_of_destination;
        string stopOver;
        string price;
        string time_of_departure;
        string time_of_arrival;
        string date;

        bool activation = false;
        myText = lowerString(myText);
        int cnt2 = 0;
        for (int i = 0; i < myText.length(); i++)
        {
            if (myText[i] == '"')
            { // take care of apostrophes
                if (activation == true)
                {
                    activation = false;
                }
                else
                {
                    activation = true;
                }
                continue;
            }
            if (myText[i] == ',' && activation == false)
            {
                cnt2 += 1;
                continue;
            }
            if (cnt2 == 0)
            {
                companyName += myText[i];
            }
            else if (cnt2 == 1)
            {
                flightNumber += myText[i];
            }
            else if (cnt2 == 2)
            {
                country_of_origin += myText[i];
            }
            else if (cnt2 == 3)
            {
                country_of_destination += myText[i];
            }
            else if (cnt2 == 4)
            {
                stopOver += myText[i];
            }
            else if (cnt2 == 5)
            {
                price += myText[i];
            }
            else if (cnt2 == 6)
            {
                time_of_departure += myText[i];
            }
            else if (cnt2 == 7)
            {
                time_of_arrival += myText[i];
            }
            else if (cnt2 == 8)
            {
                date += myText[i];
            }
        }

        Flight_Ticket *data = new Flight_Ticket(companyName, stoi(flightNumber), country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);

        if (add(data) == 1)
        {
            cnt++;
        }
    }

    return cnt - 1;
}

// import csv for date hashtable
int FlightHASHTABLE::dateImportCSV(string path)
{
    ifstream myFile(path);

    int cnt = 0;

    if (!myFile)
    {
        return -1;
    }
    string myText;

    // parse the incoming text into the variables
    while (getline(myFile, myText))
    {
        if (cnt == 0)
        {
            cnt++;
            continue;
        }
        string companyName;
        string flightNumber;
        string country_of_origin;
        string country_of_destination;
        string stopOver;
        string price;
        string time_of_departure;
        string time_of_arrival;
        string date;

        bool activation = false;
        myText = lowerString(myText);
        int cnt2 = 0;
        for (int i = 0; i < myText.length(); i++)
        {
            if (myText[i] == '"')
            {
                if (activation == true)
                {
                    activation = false;
                }
                else
                {
                    activation = true;
                }
                continue;
            }
            if (myText[i] == ',' && activation == false)
            {
                cnt2 += 1;
                continue;
            }
            if (cnt2 == 0)
            {
                companyName += myText[i];
            }
            else if (cnt2 == 1)
            {
                flightNumber += myText[i];
            }
            else if (cnt2 == 2)
            {
                country_of_origin += myText[i];
            }
            else if (cnt2 == 3)
            {
                country_of_destination += myText[i];
            }
            else if (cnt2 == 4)
            {
                stopOver += myText[i];
            }
            else if (cnt2 == 5)
            {
                price += myText[i];
            }
            else if (cnt2 == 6)
            {
                time_of_departure += myText[i];
            }
            else if (cnt2 == 7)
            {
                time_of_arrival += myText[i];
            }
            else if (cnt2 == 8)
            {
                date += myText[i];
            }
        }

        Flight_Ticket *data = new Flight_Ticket(companyName, stoi(flightNumber), country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);

        if (date_add(data) == 1)
        {
            cnt++;
        }
    }

    return cnt - 1;
}

// exporting to csv
int FlightHASHTABLE::exportCSV(string path)
{

    ofstream myFile(path);

    string str;

    if (!myFile)
    {
        return -1;
    }
    int cnt = 0;

    for (int i = 0; i < capacity; i++)
    {
        str = exportHelper(i);
        if (str.length() >= 1)
        {
            myFile << str;
        }
        cnt += buckets[i].getSize();
    }

    myFile.close();
    return cnt;
}

// helper for exportCSV
string FlightHASHTABLE::exportHelper(int index)
{
    Node<HashNode> *temp = buckets[index].getHead()->getNext();

    string str;

    while (temp != buckets[index].getTail())
    {

        Flight_Ticket data = temp->getElem().getValue();
        str = str + data.getCompanyName() + "," + to_string(data.getFlightNumber()) + ",";

        bool comma_check = false;
        string country_of_origin = data.getCountryOfOrigin();
        for (int i = 0; i < country_of_origin.length(); i++)
        {
            if (country_of_origin[i] == ',')
            {
                comma_check = true;
                break;
            }
        }

        bool comma_check2 = false;
        string country_of_destination = data.getCountryofDestination();
        for (int i = 0; i < country_of_origin.length(); i++)
        {
            if (country_of_destination[i] == ',')
            {
                comma_check2 = true;
                break;
            }
        }

        if (comma_check)
        {
            str = str + "\"" + data.getCountryOfOrigin() + "\"";
        }
        else
        {
            str = str + data.getCountryOfOrigin();
        }

        str += ",";

        if (comma_check2)
        {
            str = str + "\"" + data.getCountryofDestination() + "\"";
        }

        else
        {
            str += data.getCountryofDestination();
        }

        str += ",";

        str = str + data.getStopOver() + "," + data.getPrice() + "," + data.getTimeOfDeparture() + "," + data.getTimeOfArrival() + "," + data.getDate() + "\n";
        temp = temp->getNext();
    }

    return str;
}

// count total collisions
int FlightHASHTABLE::count_collisions()
{
    int total = 0;

    for (int i = 0; i < SIZE; i++)
    {
        total += buckets[i].getCollisions();
    }

    return total;
}

// remove from hashtable
void FlightHASHTABLE::removeRecord(string companyName, int flightNumber)
{

    int num_records = removeHelper(companyName, flightNumber);

    string key = companyName + "," + to_string(flightNumber);
    long hash = hashCode(key);

    if (num_records == 0)
    {
        cout << "ERROR: Record doesnt exist in the hashtable" << endl;
        return;
    }

    else if (num_records == 1)
    {
        buckets[hash].decrementCollisions();
    }

    string op;

    do
    {
        cout << "Please select the record you want to delete: ";
        getline(cin, op);
    } while (stoi(op) > num_records);

    int opt = stoi(op);

    int counter = 1;

    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        if (temp->getElem().getKey() == key)
        {
            if (opt == counter)
            {
                removedate = temp->getElem().getValue();
                buckets[hash].remove(temp);
                size--;
                buckets[hash].decrementSize();
                return;
            }
            counter += 1;
        }
        temp = temp->getNext();
    }
}

// helper for remove
int FlightHASHTABLE::removeHelper(string companyName, int flightNumber)
{
    string key = companyName + "," + to_string(flightNumber);
    long hash = hashCode(key);

    int num_records = 0;

    int counter = 1;

    string temp_key;

    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        temp_key = temp->getElem().getKey();
        if (temp_key == key)
        {
            num_records += 1;
        }
        temp = temp->getNext();
    }

    cout << num_records << " records found: " << endl;

    temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        temp_key = temp->getElem().getKey();

        if (temp_key == key)
        {
            Flight_Ticket data = temp->getElem().getValue();
            cout << " " << counter << ". ";
            cout << data.getCompanyName() << "," << data.getFlightNumber() << ",";

            bool comma_check = false;
            string country_of_origin = data.getCountryOfOrigin();
            for (int i = 0; i < country_of_origin.length(); i++)
            {
                if (country_of_origin[i] == ',')
                {
                    comma_check = true;
                    break;
                }
            }

            bool comma_check2 = false;
            string country_of_destination = data.getCountryofDestination();
            for (int i = 0; i < country_of_origin.length(); i++)
            {
                if (country_of_destination[i] == ',')
                {
                    comma_check2 = true;
                    break;
                }
            }

            if (comma_check)
            {
                cout << "\"" << data.getCountryOfOrigin() << "\"";
            }
            else
            {
                cout << data.getCountryOfOrigin();
            }

            cout << ",";

            if (comma_check2)
            {
                cout << "\"" << data.getCountryofDestination() << "\"";
            }

            else
            {
                cout << data.getCountryofDestination();
            }

            cout << ",";

            cout << data.getStopOver() << "," << data.getPrice() << "," << data.getTimeOfDeparture() << "," << data.getTimeOfArrival() << "," << data.getDate() << endl;
            counter += 1;
        }

        temp = temp->getNext();
    }

    return num_records;
}

// remove entry with given date
void FlightHASHTABLE::dateRemove(Flight_Ticket rdate)
{
    string date = rdate.getDate();
    long hash = hashCode(date);
    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        if (temp->getElem().getValue() == rdate)
        {
            buckets[hash].remove(temp);
            size--;
            buckets[hash].decrementSize();
            return;
        }
        temp = temp->getNext();
    }
}

// find an entry in the hashtable
void FlightHASHTABLE::find(string companyName, int flightNumber)
{
    string key = companyName + "," + to_string(flightNumber);
    long hash = hashCode(key);

    int num_records = 0;

    int counter = 0;

    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        string temp_key = temp->getElem().getKey();
        if (temp_key == key)
        {
            num_records += 1;
        }
        temp = temp->getNext();
    }

    cout << num_records << " records found: " << endl;
    Node<HashNode> *temp2 = buckets[hash].getHead()->getNext();

    while (temp2 != buckets[hash].getTail())
    {
        string temp2_key = temp2->getElem().getKey();
        if (temp2_key == key)
        {
            counter += 1;
            displayRecord(temp2->getElem().getValue(), counter);
        }
        temp2 = temp2->getNext();
    }
}

// display record in the hashtable
void FlightHASHTABLE::displayRecord(Flight_Ticket data, int counter)
{
    cout << " " << counter << ". Company Name: " << data.getCompanyName() << endl;
    cout << "    "
         << "Flight Number: " << data.getFlightNumber() << endl;
    cout << "    "
         << "Country of Origin: " << data.getCountryOfOrigin() << endl;
    cout << "    "
         << "Country of Destination: " << data.getCountryofDestination() << endl;
    cout << "    "
         << "Stop Over: " << data.getStopOver() << endl;
    cout << "    "
         << "Price: " << data.getPrice() << endl;
    cout << "    "
         << "Time of Departure: " << data.getTimeOfDeparture() << endl;
    cout << "    "
         << "Time of Arrival: " << data.getTimeOfArrival() << endl;
    cout << "    "
         << "Date: " << data.getDate() << endl;
}

// print all entries on a specific date
void FlightHASHTABLE::allinday(string date)
{
    long hash = hashCode(date);
    int num_records = 0;

    int counter = 1;

    string temp_key;

    Node<HashNode> *temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        temp_key = temp->getElem().getKey();
        if (temp_key == date)
        {
            num_records += 1;
        }
        temp = temp->getNext();
    }

    cout << num_records << " records found: " << endl;

    temp = buckets[hash].getHead()->getNext();

    while (temp != buckets[hash].getTail())
    {
        temp_key = temp->getElem().getKey();

        if (temp_key == date)
        {
            Flight_Ticket data = temp->getElem().getValue();
            cout << " " << counter << ". ";
            cout << data.getCompanyName() << "," << data.getFlightNumber() << ",";

            bool comma_check = false;
            string country_of_origin = data.getCountryOfOrigin();
            for (int i = 0; i < country_of_origin.length(); i++)
            {
                if (country_of_origin[i] == ',')
                {
                    comma_check = true;
                    break;
                }
            }

            bool comma_check2 = false;
            string country_of_destination = data.getCountryofDestination();
            for (int i = 0; i < country_of_origin.length(); i++)
            {
                if (country_of_destination[i] == ',')
                {
                    comma_check2 = true;
                    break;
                }
            }

            if (comma_check)
            {
                cout << "\"" << data.getCountryOfOrigin() << "\"";
            }
            else
            {
                cout << data.getCountryOfOrigin();
            }

            cout << ",";

            if (comma_check2)
            {
                cout << "\"" << data.getCountryofDestination() << "\"";
            }

            else
            {
                cout << data.getCountryofDestination();
            }

            cout << ",";

            cout << data.getStopOver() << "," << data.getPrice() << "," << data.getTimeOfDeparture() << "," << data.getTimeOfArrival() << "," << data.getDate() << endl;
            counter += 1;
        }

        temp = temp->getNext();
    }
}

// print in ascending order
void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
    string key = companyName + "," + to_string(flightNumber);
    long hash = hashCode(key);
    Node<HashNode> *temp = buckets[hash].getHead()->getNext();
    string temp_key;

    while (temp != buckets[hash].getTail())
    {
        temp_key = temp->getElem().getKey();
        if (temp_key == key)
        {
            Flight_Ticket data = temp->getElem().getValue();
            cout << data.getCompanyName() << "," << data.getFlightNumber() << ",";

            bool comma_check = false;
            string country_of_origin = data.getCountryOfOrigin();
            for (int i = 0; i < country_of_origin.length(); i++)
            {
                if (country_of_origin[i] == ',')
                {
                    comma_check = true;
                    break;
                }
            }

            bool comma_check2 = false;
            string country_of_destination = data.getCountryofDestination();
            for (int i = 0; i < country_of_origin.length(); i++)
            {
                if (country_of_destination[i] == ',')
                {
                    comma_check2 = true;
                    break;
                }
            }

            if (comma_check)
            {
                cout << "\"" << data.getCountryOfOrigin() << "\"";
            }
            else
            {
                cout << data.getCountryOfOrigin();
            }

            cout << ",";

            if (comma_check2)
            {
                cout << "\"" << data.getCountryofDestination() << "\"";
            }

            else
            {
                cout << data.getCountryofDestination();
            }

            cout << ",";

            cout << data.getStopOver() << "," << data.getPrice() << "," << data.getTimeOfDeparture() << "," << data.getTimeOfArrival() << "," << data.getDate() << endl;
        }

        temp = temp->getNext();
    }
}

// lowercase the strings
string FlightHASHTABLE::lowerString(string str)
{
    string temp;

    for (int i = 0; i < str.length(); i++)
    {
        temp += tolower(str[i]);
    }
    return temp;
}
