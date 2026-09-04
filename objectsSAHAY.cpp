#include <iostream>
#include <string>
using namespace std;

// =====================================================
// 1. PERSON
// =====================================================
class Person {
protected:
    string name;
    int age;
    string phone;

public:
    Person(string n, int a, string p) {
        name = n;
        age = a;
        phone = p;
    }

    void displayPerson() {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Phone: " << phone << endl;
    }
};


// =====================================================
// 2. VICTIM
// =====================================================
class Victim : public Person {
private:
    int victimID;
    string injuryStatus;
    int priority;

public:
    Victim(int id, string n, int a, string p, string injury, int pr)
        : Person(n, a, p) {
        victimID = id;
        injuryStatus = injury;
        priority = pr;
    }

    void displayVictim() {
        cout << "\n--- Victim ---" << endl;
        cout << "Victim ID: " << victimID << endl;
        displayPerson();
        cout << "Injury Status: " << injuryStatus << endl;
        cout << "Priority: " << priority << endl;
    }
};


// =====================================================
// 3. RESCUER
// =====================================================
class Rescuer : public Person {
private:
    int rescuerID;
    string team;
    string location;
    bool available;

public:
    Rescuer(int id, string n, int a, string p, string t, string l, bool av)
        : Person(n, a, p) {
        rescuerID = id;
        team = t;
        location = l;
        available = av;
    }

    void displayRescuer() {
        cout << "\n--- Rescuer ---" << endl;
        cout << "Rescuer ID: " << rescuerID << endl;
        displayPerson();
        cout << "Team: " << team << endl;
        cout << "Location: " << location << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
    }
};


// =====================================================
// 4. DISASTER
// =====================================================
class Disaster {
protected:
    int disasterID;
    string type;
    string location;
    int severity;

public:
    Disaster(int id, string t, string l, int s) {
        disasterID = id;
        type = t;
        location = l;
        severity = s;
    }

    void displayDisaster() {
        cout << "\n--- Disaster ---" << endl;
        cout << "Disaster ID: " << disasterID << endl;
        cout << "Type: " << type << endl;
        cout << "Location: " << location << endl;
        cout << "Severity: " << severity << "/10" << endl;
    }
};


// =====================================================
// 5. FLOOD
// =====================================================
class Flood : public Disaster {
private:
    float waterLevel;
    float rainfall;

public:
    Flood(int id, string l, int s, float w, float r)
        : Disaster(id, "Flood", l, s) {
        waterLevel = w;
        rainfall = r;
    }

    void displayFlood() {
        displayDisaster();
        cout << "Water Level: " << waterLevel << " meters" << endl;
        cout << "Rainfall: " << rainfall << " mm" << endl;
    }
};


// =====================================================
// 6. EARTHQUAKE
// =====================================================
class Earthquake : public Disaster {
private:
    float magnitude;
    float depth;

public:
    Earthquake(int id, string l, int s, float m, float d)
        : Disaster(id, "Earthquake", l, s) {
        magnitude = m;
        depth = d;
    }

    void displayEarthquake() {
        displayDisaster();
        cout << "Magnitude: " << magnitude << endl;
        cout << "Depth: " << depth << " km" << endl;
    }
};


// =====================================================
// 7. LOCATION
// =====================================================
class Location {
private:
    int locationID;
    string name;
    double latitude;
    double longitude;

public:
    Location(int id, string n, double lat, double lon) {
        locationID = id;
        name = n;
        latitude = lat;
        longitude = lon;
    }

    void displayLocation() {
        cout << "\n--- Location ---" << endl;
        cout << "Location ID: " << locationID << endl;
        cout << "Name: " << name << endl;
        cout << "Latitude: " << latitude << endl;
        cout << "Longitude: " << longitude << endl;
    }
};


// =====================================================
// 8. NODE
// =====================================================
class Node {
private:
    int nodeID;
    string name;

public:
    Node(int id, string n) {
        nodeID = id;
        name = n;
    }

    int getNodeID() {
        return nodeID;
    }

    void displayNode() {
        cout << "Node ID: " << nodeID
             << " | Name: " << name << endl;
    }
};


// =====================================================
// 9. ROAD
// =====================================================
class Road {
private:
    int roadID;
    Node* startNode;
    Node* endNode;
    double distance;
    bool blocked;

public:
    Road(int id, Node* start, Node* end, double d, bool b) {
        roadID = id;
        startNode = start;
        endNode = end;
        distance = d;
        blocked = b;
    }

    void displayRoad() {
        cout << "\n--- Road ---" << endl;
        cout << "Road ID: " << roadID << endl;
        cout << "From Node: " << startNode->getNodeID() << endl;
        cout << "To Node: " << endNode->getNodeID() << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Status: " << (blocked ? "Blocked" : "Open") << endl;
    }
};


// =====================================================
// 10. GRAPH
// =====================================================
class Graph {
private:
    string cityName;
    int numberOfNodes;

public:
    Graph(string city, int nodes) {
        cityName = city;
        numberOfNodes = nodes;
    }

    void displayGraph() {
        cout << "\n--- Graph ---" << endl;
        cout << "City: " << cityName << endl;
        cout << "Number of Nodes: " << numberOfNodes << endl;
    }

    void addNode() {
        numberOfNodes++;
        cout << "Node added. Total Nodes: "
             << numberOfNodes << endl;
    }
};


// =====================================================
// 11. ROUTE
// =====================================================
class Route {
private:
    int routeID;
    string source;
    string destination;
    double distance;
    double estimatedTime;
    int safetyScore;

public:
    Route(int id, string s, string d, double dist,
          double time, int safety) {
        routeID = id;
        source = s;
        destination = d;
        distance = dist;
        estimatedTime = time;
        safetyScore = safety;
    }

    void displayRoute() {
        cout << "\n--- Route ---" << endl;
        cout << "Route ID: " << routeID << endl;
        cout << "Source: " << source << endl;
        cout << "Destination: " << destination << endl;
        cout << "Distance: " << distance << " km" << endl;
        cout << "Estimated Time: " << estimatedTime << " minutes" << endl;
        cout << "Safety Score: " << safetyScore << "/100" << endl;
    }
};


// =====================================================
// 12. ROUTE CALCULATOR
// =====================================================
class RouteCalculator {
private:
    string algorithm;

public:
    RouteCalculator(string algo) {
        algorithm = algo;
    }

    void calculateRoute() {
        cout << "\nCalculating optimal route using "
             << algorithm << "..." << endl;
    }

    void displayCalculator() {
        cout << "Route Algorithm: " << algorithm << endl;
    }
};


// =====================================================
// 13. SHELTER
// =====================================================
class Shelter {
private:
    int shelterID;
    string name;
    string location;
    int capacity;
    int availableSpace;

public:
    Shelter(int id, string n, string l, int c, int a) {
        shelterID = id;
        name = n;
        location = l;
        capacity = c;
        availableSpace = a;
    }

    void displayShelter() {
        cout << "\n--- Shelter ---" << endl;
        cout << "Shelter ID: " << shelterID << endl;
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Capacity: " << capacity << endl;
        cout << "Available Space: " << availableSpace << endl;
    }
};


// =====================================================
// 14. HOSPITAL
// =====================================================
class Hospital {
private:
    int hospitalID;
    string name;
    string location;
    int bedsAvailable;
    int emergencyCapacity;

public:
    Hospital(int id, string n, string l, int beds, int emergency) {
        hospitalID = id;
        name = n;
        location = l;
        bedsAvailable = beds;
        emergencyCapacity = emergency;
    }

    void displayHospital() {
        cout << "\n--- Hospital ---" << endl;
        cout << "Hospital ID: " << hospitalID << endl;
        cout << "Name: " << name << endl;
        cout << "Location: " << location << endl;
        cout << "Beds Available: " << bedsAvailable << endl;
        cout << "Emergency Capacity: " << emergencyCapacity << endl;
    }
};


// =====================================================
// 15. AMBULANCE
// =====================================================
class Ambulance {
private:
    int ambulanceID;
    string driver;
    string location;
    bool available;
    int fuelLevel;

public:
    Ambulance(int id, string d, string l, bool a, int fuel) {
        ambulanceID = id;
        driver = d;
        location = l;
        available = a;
        fuelLevel = fuel;
    }

    void displayAmbulance() {
        cout << "\n--- Ambulance ---" << endl;
        cout << "Ambulance ID: " << ambulanceID << endl;
        cout << "Driver: " << driver << endl;
        cout << "Location: " << location << endl;
        cout << "Available: " << (available ? "Yes" : "No") << endl;
        cout << "Fuel Level: " << fuelLevel << "%" << endl;
    }
};


// =====================================================
// 16. EMERGENCY REQUEST
// =====================================================
class EmergencyRequest {
private:
    int requestID;
    string requester;
    string location;
    string emergencyType;
    int priority;
    string status;

public:
    EmergencyRequest(int id, string r, string l,
                     string type, int p, string s) {
        requestID = id;
        requester = r;
        location = l;
        emergencyType = type;
        priority = p;
        status = s;
    }

    void displayRequest() {
        cout << "\n--- Emergency Request ---" << endl;
        cout << "Request ID: " << requestID << endl;
        cout << "Requester: " << requester << endl;
        cout << "Location: " << location << endl;
        cout << "Emergency Type: " << emergencyType << endl;
        cout << "Priority: " << priority << endl;
        cout << "Status: " << status << endl;
    }
};


// =====================================================
// 17. RESCUE OPERATION
// =====================================================
class RescueOperation {
private:
    int operationID;
    string location;
    string assignedTeam;
    int priority;
    string status;

public:
    RescueOperation(int id, string l, string team,
                     int p, string s) {
        operationID = id;
        location = l;
        assignedTeam = team;
        priority = p;
        status = s;
    }

    void displayOperation() {
        cout << "\n--- Rescue Operation ---" << endl;
        cout << "Operation ID: " << operationID << endl;
        cout << "Location: " << location << endl;
        cout << "Assigned Team: " << assignedTeam << endl;
        cout << "Priority: " << priority << endl;
        cout << "Status: " << status << endl;
    }
};


// =====================================================
// 18. RESOURCE
// =====================================================
class Resource {
private:
    int resourceID;
    string name;
    string type;
    int quantity;
    string location;

public:
    Resource(int id, string n, string t, int q, string l) {
        resourceID = id;
        name = n;
        type = t;
        quantity = q;
        location = l;
    }

    void displayResource() {
        cout << "\n--- Resource ---" << endl;
        cout << "Resource ID: " << resourceID << endl;
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Quantity: " << quantity << endl;
        cout << "Location: " << location << endl;
    }
};


// =====================================================
// MAIN FUNCTION
// =====================================================
int main() {

    // 1. Person
    Person person1("Rahul", 25, "9876543210");

    // 2. Victim
    Victim victim1(101, "Amit", 30, "9876500001",
                   "Injured", 1);

    // 3. Rescuer
    Rescuer rescuer1(201, "Rohit", 28, "9876500002",
                     "Team Alpha", "Haridwar", true);

    // 4. Disaster
    Disaster disaster1(301, "Natural Disaster",
                       "Haridwar", 8);

    // 5. Flood
    Flood flood1(302, "Rishikesh", 9,
                 2.5, 150.0);

    // 6. Earthquake
    Earthquake earthquake1(303, "Dehradun", 7,
                           6.2, 10);

    // 7. Location
    Location location1(401, "Haridwar Railway Station",
                       29.9457, 78.1642);

    // 8. Nodes
    Node node1(1, "Haridwar");
    Node node2(2, "Rishikesh");

    // 9. Road
    Road road1(501, &node1, &node2,
               20.5, false);

    // 10. Graph
    Graph cityGraph("Haridwar", 5);

    // 11. Route
    Route route1(601, "Haridwar",
                 "Rishikesh", 20.5,
                 35.0, 92);

    // 12. Route Calculator
    RouteCalculator calculator1("Dijkstra Algorithm");

    // 13. Shelter
    Shelter shelter1(701, "Community Shelter",
                     "Haridwar", 500, 250);

    // 14. Hospital
    Hospital hospital1(801, "District Hospital",
                       "Haridwar", 100, 30);

    // 15. Ambulance
    Ambulance ambulance1(901, "Suresh",
                         "Haridwar", true, 80);

    // 16. Emergency Request
    EmergencyRequest request1(1001, "Amit",
                              "Haridwar", "Medical Emergency",
                              1, "Pending");

    // 17. Rescue Operation
    RescueOperation operation1(1101, "Haridwar",
                               "Team Alpha", 1,
                               "In Progress");

    // 18. Resource
    Resource resource1(1201, "Drinking Water",
                       "Essential", 1000,
                       "Haridwar Relief Center");


    // =================================================
    // DISPLAYING OBJECT DATA
    // =================================================

    cout << "========================================" << endl;
    cout << "       SAHAY DISASTER MANAGEMENT       " << endl;
    cout << "       OOP CLASS & OBJECT DEMO          " << endl;
    cout << "========================================" << endl;

    person1.displayPerson();

    victim1.displayVictim();

    rescuer1.displayRescuer();

    disaster1.displayDisaster();

    cout << "\n--- Flood Information ---" << endl;
    flood1.displayFlood();

    cout << "\n--- Earthquake Information ---" << endl;
    earthquake1.displayEarthquake();

    location1.displayLocation();

    cout << "\n--- Nodes ---" << endl;
    node1.displayNode();
    node2.displayNode();

    road1.displayRoad();

    cityGraph.displayGraph();
    cityGraph.addNode();

    route1.displayRoute();

    calculator1.displayCalculator();
    calculator1.calculateRoute();

    shelter1.displayShelter();

    hospital1.displayHospital();

    ambulance1.displayAmbulance();

    request1.displayRequest();

    operation1.displayOperation();

    resource1.displayResource();

    cout << "\n========================================" << endl;
    cout << "        SAHAY DEMO COMPLETED            " << endl;
    cout << "========================================" << endl;

    return 0;
}