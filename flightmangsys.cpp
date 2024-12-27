
//Flight Management system 
#include<iostream>
using namespace std;
#include<string>
#include<algorithm>
#include<vector>
#include<sstream>
#include<iomanip>
#include<ctime>
class Flight{
    protected:
        string name;
        string id;
        int capacity;
        string arrival_time;
        string departure_time;
        string class_of_travel;
        string destination;
        string operator_name;

        int duration(const string& arrival_time, const string& departure_time) const {
            tm arrivalTm={};    
            tm departureTm={};

            // Parse arrival time
            istringstream(arrival_time) >> get_time(&arrivalTm, "%Y-%m-%d %H:%M");
            // Parse departure time
            istringstream(departure_time) >> get_time(&departureTm, "%Y-%m-%d %H:%M");

            // Convert to seconds
            time_t arrivalSeconds = mktime(&arrivalTm);
            time_t departureSeconds = mktime(&departureTm);

            // Calculate the difference in seconds and convert to hours
            return static_cast<int>(difftime(departureSeconds, arrivalSeconds) / 3600);
        }

    public:
        Flight(const string& flightname, const string& flightid, int flightcapacity, 
       const string& flightarrival_time, const string& flightdeparture_time, 
       const string& flightclass_of_travel, const string& flightdestination, 
       const string& flightoperator_name) {
            name = flightname;
            id = flightid;
            capacity = flightcapacity;
            arrival_time = flightarrival_time;
            departure_time = flightdeparture_time;
            class_of_travel = flightclass_of_travel;
            destination = flightdestination;
            operator_name = flightoperator_name;
        }


        string getname() const {
            return name;
        }
        string getid() const {
            return id;
        }
        int getcapacity() const {
            return capacity;
        }
        string getdeparturetime() const {
            return departure_time;
        }
        string getarrivaltime() const {
            return arrival_time;
        }
        string getdestination() const {
            return destination;
        }
        string getoperator_name() const {
            return operator_name;
        }
        string getclass_of_travel() const{
            return class_of_travel;
        }
        

        // Key for sorting
        string key() const {    
            return id+arrival_time;
        }

        
        void sortFlights(vector<Flight>& flights){
            sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
                return a.key() < b.key();
            });
        }

        
        int getstayduration() const{
            return duration(arrival_time, departure_time);
        }

        
        //Functions
        bool insertorupdate(vector<Flight>& flights, const Flight& newFlight);
        bool deleteFlight(vector<Flight>& flights, const string& flightId);
        int getNumFlights(const vector<Flight>& flights);
        bool isEmpty(const vector<Flight>& flights);
        bool isFull(const vector<Flight>& flights, size_t max);
        Flight getLongestStay(const vector<Flight>& flights);
        void listUnique(vector<Flight>& flights);
        void listUnion(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3);
        void listIntersection(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3);
        void listDifference(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3);
        void listSymmetricDifference(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3);
        void displayFlights(const vector<Flight>& flights);
};

/* ===== Inserting a new flights details or update existing flight details ===== */
bool Flight::insertorupdate(vector<Flight>& flights, const Flight& newFlight) {
    auto itr = find_if(flights.begin(), flights.end(), [&](const Flight& f) {
        return f.key() == newFlight.key();
    });

    if (itr != flights.end()) {
        *itr = newFlight;  
    } else {
        flights.push_back(newFlight);  
    }

    sortFlights(flights);  
    return true;  
}


/* ===== Deleting an existing flights details ===== */
bool Flight::deleteFlight(vector<Flight>& flights, const string& flightId){
    for (auto itr = flights.begin() ; itr != flights.end(); ){
        if (itr -> getid() == flightId){
            itr = flights.erase(itr);
            return true;
        }
        else{
            ++itr;
        }
    }

    return false;
}

/* ===== Number of Flights ===== */
int Flight::getNumFlights(const vector<Flight>& flights) {
    return flights.size();
}

/* ===== To check if the flights data is empty*/
bool Flight::isEmpty(const vector<Flight>& flights){
    return flights.empty();
}

/* ===== To check if the flights data is full*/
bool Flight::isFull(const vector<Flight>& flights, size_t max){
    return flights.size() > max;
}

/* ===== Longest stay ===== */
Flight Flight::getLongestStay(const vector<Flight>& flights){
    if (isEmpty(flights)){
        throw runtime_error("Warning: No flights available!");//Displays text similar to cout but doesnt mess flow of execution
    }

    Flight longest = flights[0];
    
    for (const auto& flight : flights){// Similar to 'for i in list' syntax of python
        if (flight.getstayduration()>longest.getstayduration()){
            longest = flight;
        }
    }

    return longest;
}

/* ===== To list all Unique entries ===== */
void Flight::listUnique(vector<Flight>& flights) {
    sort(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
        return a.key() < b.key();
    });

    auto last = unique(flights.begin(), flights.end(), [](const Flight& a, const Flight& b) {
        return a.key() == b.key(); 
    });

    flights.erase(last, flights.end()); 
}

/* ===== To list union of 2 list of entries ===== */
void Flight::listUnion(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3){
    list3 = list1;

    for (const auto& flight : list2) {
        if (none_of(list3.begin(), list3.end(), [&](const Flight& f) {
            return f.key() == flight.key();
        })) {
            list3.push_back(flight);
        }
    }

    sortFlights(list3);
}

/* ===== To list intersection of 2 list of entries ===== */
void Flight::listIntersection(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3){
    list3.clear(); 

    for (const auto& flight1 : list1) {
        auto it = find_if(list2.begin(), list2.end(), [&](const Flight& flight2) {
            return flight1.key() == flight2.key();
        });

        if (it != list2.end()) {
            list3.push_back(flight1); 
        }
    }

    sortFlights(list3); 
}

/* ===== To list Difference of 2 list of entries ===== */
void Flight::listDifference(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3){
    list3.clear(); 

    for (const auto& flight1 : list1) {
        if (std::none_of(list2.begin(), list2.end(), [&](const Flight& flight2) {
            return flight1.key() == flight2.key();
        })) {
            list3.push_back(flight1); 
        }
    }

    sortFlights(list3);
}

/* ===== To list the symmetric difference of 2 list of entries ===== */
void Flight::listSymmetricDifference(const vector<Flight>& list1, const vector<Flight>& list2, vector<Flight>& list3){
    list3.clear(); 
    vector<Flight> temp1, temp2;

    // List Difference Displays what are in first parameter list but not the second parameter list 
    listDifference(list1, list2, temp1); 
    listDifference(list2, list1, temp2); 

    list3.insert(list3.end(), temp1.begin(), temp1.end());
    list3.insert(list3.end(), temp2.begin(), temp2.end());

    sortFlights(list3); 
}
  
/* ===== Display details ===== */
void Flight::displayFlights(const vector<Flight>& flights) {
    cout << left << setw(20) << "Flight Name" 
         << setw(15) << "Flight ID" 
         << setw(10) << "Capacity" 
         << setw(20) << "Arrival Time" 
         << setw(20) << "Departure Time" 
         << setw(15) << "Class" 
         << setw(20) << "Destination" 
         << setw(20) << "Operator" << endl;
    
    cout << string(130, '-') << endl;

    for (const auto& flight : flights) {
        cout << left << setw(20) << flight.getname() 
             << setw(15) << flight.getid() 
             << setw(10) << flight.getcapacity() 
             << setw(20) << flight.getarrivaltime() 
             << setw(20) << flight.getdeparturetime() 
             << setw(15) << flight.getclass_of_travel() 
             << setw(20) << flight.getdestination() 
             << setw(20) << flight.getoperator_name() << endl;
    }
}


class Display : public Flight {
public:
    
    Display(const Flight& obj) : Flight(obj) {}//initializing Display with a Flight object’s data

    void display() {
        
        cout << left << setw(20) << "Flight Name" 
             << setw(15) << "Flight ID" 
             << setw(10) << "Capacity" 
             << setw(20) << "Arrival Time" 
             << setw(20) << "Departure Time" 
             << setw(15) << "Class" 
             << setw(20) << "Destination" 
             << setw(20) << "Operator" << endl;
        cout << string(130, '-') << endl;
        
        cout << left << setw(20) << name 
             << setw(15) << id 
             << setw(10) << capacity 
             << setw(20) << arrival_time 
             << setw(20) << departure_time 
             << setw(15) << class_of_travel 
             << setw(20) << destination 
             << setw(20) << operator_name << endl;
    }
};



int main() {
    vector<Flight> flights;

    // Creating some flight instances
    Flight flight1("Airline A", "A001", 150, "2024-11-06 10:00", "2024-11-06 14:00", "Economy", "New York", "Airline A");
    Flight flight2("Airline B", "B001", 180, "2024-11-06 09:00", "2024-11-06 13:00", "Business", "Los Angeles", "Airline B");
    Flight flight3("Airline C", "C001", 200, "2024-11-06 11:00", "2024-11-06 15:00", "First", "Chicago", "Airline C");
    Flight flight4("Airline A", "A002", 120, "2024-11-07 08:00", "2024-11-07 12:00", "Economy", "Miami", "Airline A");

    // Inserting flights
    flight1.insertorupdate(flights, flight1);
    flight2.insertorupdate(flights, flight2);
    flight3.insertorupdate(flights, flight3);
    flight4.insertorupdate(flights, flight4);

    // Displaying the flights after insertion
    cout << "Flights after insertion:" << endl;
    Display Obj1(flight1);
    Obj1.display();
    cout << endl;
    
    Display Obj2(flight2);
    Obj2.display();
    cout << endl;
    
    Display Obj3(flight3);
    Obj3.display();
    cout << endl;

    // Updating a flight (updating flight2 details)
    Flight updatedFlight2("Airline B", "B001", 180, "2024-11-06 09:00", "2024-11-06 16:00", "Business", "Los Angeles", "Airline B");
    flight1.insertorupdate(flights, updatedFlight2);

    // Displaying the flights after update
    cout << "Flights after update:" << endl;
    Display updatedDisplayObj2(updatedFlight2);
    updatedDisplayObj2.display();
    cout << endl;

    // Deleting a flight (delete flight with id B001)
    if (flight1.deleteFlight(flights, "B001")) {
        cout << "Flight B001 deleted successfully." << endl;
    } else {
        cout << "Failed to delete flight B001." << endl;
    }

    // Displaying the flights after deletion
    cout << "Flights after deletion:" << endl;
    flight1.displayFlights(flights);
    cout << endl;

    // Checking if the list is empty or full
    cout << "Number of flights: " << flight1.getNumFlights(flights) << endl;

    // Checking the longest stay (duration between arrival and departure)
    try {
        Flight longestStayFlight = flight1.getLongestStay(flights);
        cout << "Longest Stay Flight: " << longestStayFlight.getname() 
             << " (" << longestStayFlight.getid() << ")" << endl;
    } catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    // Listing unique flights (if there are duplicates, it will remove them)
    cout << "Unique Flights:" << endl;
    flight1.listUnique(flights);
    flight1.displayFlights(flights);
    cout << endl;

    // Demonstrating union of two flight lists
    vector<Flight> flights2 = {flight2, flight3}; // Another list
    vector<Flight> unionFlights;
    flight1.listUnion(flights, flights2, unionFlights);
    cout << "Union of Flights:" << endl;
    flight1.displayFlights(unionFlights);
    cout << endl;

    // Demonstrating intersection of two flight lists
    vector<Flight> intersectionFlights;
    flight1.listIntersection(flights, flights2, intersectionFlights);
    cout << "Intersection of Flights:" << endl;
    flight1.displayFlights(intersectionFlights);
    cout << endl;

    // Demonstrating difference of two flight lists
    vector<Flight> differenceFlights;
    flight1.listDifference(flights, flights2, differenceFlights);
    cout << "Difference of Flights (in flights but not in flights2):" << endl;
    flight1.displayFlights(differenceFlights);
    cout << endl;

    // Demonstrating symmetric difference of two flight lists
    vector<Flight> symmetricDifferenceFlights;
    flight1.listSymmetricDifference(flights, flights2, symmetricDifferenceFlights);
    cout << "Symmetric Difference of Flights:" << endl;
    flight1.displayFlights(symmetricDifferenceFlights);
    cout << endl;






    /* === For Manual Usage === */
    /*
    int choice;
        string flight_name, flight_id, arrival_time, departure_time, class_of_travel, destination, operator_name;
        int capacity;
    do {
        // Display menu options
        cout << "\n===== Flight Management System =====\n";
        cout << "1. Add or Update Flight\n";
        cout << "2. Delete Flight\n";
        cout << "3. Display All Flights\n";
        cout << "4. Sort Flights\n";
        cout << "5. Get Number of Flights\n";
        cout << "6. Check if Flight Data is Empty\n";
        cout << "7. Check if Flight Data is Full\n";
        cout << "8. Get Longest Stay Flight\n";
        cout << "9. List Unique Flights\n";
        cout << "10. List Union of Two Flight Lists\n";
        cout << "11. List Intersection of Two Flight Lists\n";
        cout << "12. List Difference of Two Flight Lists\n";
        cout << "13. List Symmetric Difference of Two Flight Lists\n";
        cout << "14. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: // Add or Update Flight
                cout << "Enter Flight Name: ";
                getline(cin, flight_name);  // Read the flight name
                cout << "Enter Flight ID: ";
                getline(cin, flight_id);  // Read the flight ID
                cout << "Enter Capacity: ";
                cin >> capacity;
                cin.ignore();  // Ignore the newline left by cin >> capacity
                cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                getline(cin, arrival_time);  // Read the arrival time
                cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                getline(cin, departure_time);  // Read the departure time
                cout << "Enter Class of Travel: ";
                getline(cin, class_of_travel);  // Read the class of travel
                cout << "Enter Destination: ";
                getline(cin, destination);  // Read the destination
                cout << "Enter Operator Name: ";
                getline(cin, operator_name);  // Read the operator name

                {
                    Flight newFlight(flight_name, flight_id, capacity, arrival_time, departure_time, class_of_travel, destination, operator_name);
                    newFlight.insertorupdate(flights, newFlight);
                }

                break;


            case 2: // Delete Flight
                cout << "Enter Flight ID to Delete: ";
                getline(cin, flight_id);
                {
                    Flight tempFlight("", flight_id, 0, "", "", "", "", "");
                    if (tempFlight.deleteFlight(flights, flight_id)) {
                        cout << "Flight deleted successfully.\n";
                    } else {
                        cout << "Flight ID not found.\n";
                    }
                }
                break;

            case 3: // Display All Flights
                {
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.displayFlights(flights);
                }
                break;

            case 4: // Sort Flights
                {
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.sortFlights(flights);
                    cout << "Flights sorted by ID and Arrival Time.\n";
                }
                break;

            case 5: // Get Number of Flights
                {
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    cout << "Total number of flights: " << tempFlight.getNumFlights(flights) << endl;
                }
                break;

            case 6: // Check if Flight Data is Empty
                {
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    if (tempFlight.isEmpty(flights)) {
                        cout << "No flights available.\n";
                    } else {
                        cout << "There are flights available.\n";
                    }
                }
                break;

            case 7: // Check if Flight Data is Full
                {
                    size_t max_capacity;
                    cout << "Enter maximum capacity: ";
                    cin >> max_capacity;
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    if (tempFlight.isFull(flights, max_capacity)) {
                        cout << "Flight data is full.\n";
                    } else {
                        cout << "Flight data is not full.\n";
                    }
                }
                break;

            case 8: // Get Longest Stay Flight
                {
                    try {
                        Flight tempFlight("", "", 0, "", "", "", "", "");
                        Flight longestStayFlight = tempFlight.getLongestStay(flights);
                        cout << "Longest Stay Flight: " << longestStayFlight.getname() << " (ID: " << longestStayFlight.getid() << ")\n";
                    } catch (const runtime_error& e) {
                        cout << e.what() << endl;
                    }
                }
                break;

            case 9: // List Unique Flights
                {
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.listUnique(flights);
                    cout << "Unique flights listed.\n";
                }
                break;

            case 10: // List Union of Two Flight Lists
                {
                    vector<Flight> list2;
                    string id, name, arrival, departure;
                    int capacity;
                    cout << "Enter 2nd Flight Data:\n";
                    cout << "Enter Flight Name: ";
                    getline(cin, name);
                    cout << "Enter Flight ID: ";
                    getline(cin, id);
                    cout << "Enter Capacity: ";
                    cin >> capacity;
                    cin.ignore();
                    cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, arrival);
                    cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, departure);
                    list2.push_back(Flight(name, id, capacity, arrival, departure, "Economy", "Paris", "Airline Y"));

                    vector<Flight> unionFlights;
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.listUnion(flights, list2, unionFlights);
                    cout << "Union of flights listed.\n";
                    tempFlight.displayFlights(unionFlights);
                }
                break;

            case 11: // List Intersection of Two Flight Lists
                {
                    vector<Flight> list2;
                    string id, name, arrival, departure;
                    int capacity;
                    cout << "Enter 2nd Flight Data:\n";
                    cout << "Enter Flight Name: ";
                    getline(cin, name);
                    cout << "Enter Flight ID: ";
                    getline(cin, id);
                    cout << "Enter Capacity: ";
                    cin >> capacity;
                    cin.ignore();
                    cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, arrival);
                    cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, departure);
                    list2.push_back(Flight(name, id, capacity, arrival, departure, "Economy", "Paris", "Airline Y"));

                    vector<Flight> intersectionFlights;
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.listIntersection(flights, list2, intersectionFlights);
                    cout << "Intersection of flights listed.\n";
                    tempFlight.displayFlights(intersectionFlights);
                }
                break;

            case 12: // List Difference of Two Flight Lists
                {
                    vector<Flight> list2;
                    string id, name, arrival, departure;
                    int capacity;
                    cout << "Enter 2nd Flight Data:\n";
                    cout << "Enter Flight Name: ";
                    getline(cin, name);
                    cout << "Enter Flight ID: ";
                    getline(cin, id);
                    cout << "Enter Capacity: ";
                    cin >> capacity;
                    cin.ignore();
                    cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, arrival);
                    cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, departure);
                    list2.push_back(Flight(name, id, capacity, arrival, departure, "Economy", "Paris", "Airline Y"));

                    vector<Flight> differenceFlights;
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.listDifference(flights, list2, differenceFlights);
                    cout << "Difference of flights listed.\n";
                    tempFlight.displayFlights(differenceFlights);
                }
                break;

            case 13: // List Symmetric Difference of Two Flight Lists
                {
                    vector<Flight> list2;
                    string id, name, arrival, departure;
                    int capacity;
                    cout << "Enter 2nd Flight Data:\n";
                    cout << "Enter Flight Name: ";
                    getline(cin, name);
                    cout << "Enter Flight ID: ";
                    getline(cin, id);
                    cout << "Enter Capacity: ";
                    cin >> capacity;
                    cin.ignore();
                    cout << "Enter Arrival Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, arrival);
                    cout << "Enter Departure Time (YYYY-MM-DD HH:MM): ";
                    getline(cin, departure);
                    list2.push_back(Flight(name, id, capacity, arrival, departure, "Economy", "Paris", "Airline Y"));

                    vector<Flight> symmetricDifferenceFlights;
                    Flight tempFlight("", "", 0, "", "", "", "", "");
                    tempFlight.listSymmetricDifference(flights, list2, symmetricDifferenceFlights);
                    cout << "Symmetric difference of flights listed.\n";
                    tempFlight.displayFlights(symmetricDifferenceFlights);
                }
                break;

            case 14: // Exit
                cout << "Exiting the Flight Management System...\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
                break;
        }

    } while (choice != 14);
    */

    return 0;
}



/*

Flights after insertion:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline A           A001           150       2024-11-06 10:00    2024-11-06 14:00    Economy        New York            Airline A

Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline B           B001           180       2024-11-06 09:00    2024-11-06 13:00    Business       Los Angeles         Airline B

Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline C           C001           200       2024-11-06 11:00    2024-11-06 15:00    First          Chicago             Airline C

Flights after update:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline B           B001           180       2024-11-06 09:00    2024-11-06 16:00    Business       Los Angeles         Airline B

Flight B001 deleted successfully.
Flights after deletion:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline A           A001           150       2024-11-06 10:00    2024-11-06 14:00    Economy        New York            Airline A
Airline A           A002           120       2024-11-07 08:00    2024-11-07 12:00    Economy        Miami               Airline A
Airline C           C001           200       2024-11-06 11:00    2024-11-06 15:00    First          Chicago             Airline C

Number of flights: 3
Longest Stay Flight: Airline A (A001)
Unique Flights:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline A           A001           150       2024-11-06 10:00    2024-11-06 14:00    Economy        New York            Airline A
Airline A           A002           120       2024-11-07 08:00    2024-11-07 12:00    Economy        Miami               Airline A
Airline C           C001           200       2024-11-06 11:00    2024-11-06 15:00    First          Chicago             Airline C

Union of Flights:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline A           A001           150       2024-11-06 10:00    2024-11-06 14:00    Economy        New York            Airline A
Airline A           A002           120       2024-11-07 08:00    2024-11-07 12:00    Economy        Miami               Airline A
Airline B           B001           180       2024-11-06 09:00    2024-11-06 13:00    Business       Los Angeles         Airline B
Airline C           C001           200       2024-11-06 11:00    2024-11-06 15:00    First          Chicago             Airline C

Intersection of Flights:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline C           C001           200       2024-11-06 11:00    2024-11-06 15:00    First          Chicago             Airline C

Difference of Flights (in flights but not in flights2):
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline A           A001           150       2024-11-06 10:00    2024-11-06 14:00    Economy        New York            Airline A
Airline A           A002           120       2024-11-07 08:00    2024-11-07 12:00    Economy        Miami               Airline A

Symmetric Difference of Flights:
Flight Name         Flight ID      Capacity  Arrival Time        Departure Time      Class          Destination         Operator
----------------------------------------------------------------------------------------------------------------------------------
Airline A           A001           150       2024-11-06 10:00    2024-11-06 14:00    Economy        New York            Airline A
Airline A           A002           120       2024-11-07 08:00    2024-11-07 12:00    Economy        Miami               Airline A
Airline B           B001           180       2024-11-06 09:00    2024-11-06 13:00    Business       Los Angeles         Airline B


*/
