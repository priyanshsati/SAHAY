#include <iostream>
#include <string>
using namespace std;

// ================= ROAD CLASS =================
class Road {
private:
    int distance;
    bool blocked;

public:
    Road(int d = 0, bool b = false) {
        distance = d;
        blocked = b;
    }

    int getDistance() {
        return distance;
    }

    bool isBlocked() {
        return blocked;
    }

    void blockRoad() {
        blocked = true;
    }

    void unblockRoad() {
        blocked = false;
    }

    void displayRoad() {
        cout << "Distance: " << distance << " km";

        if (blocked)
            cout << " | BLOCKED";

        cout << endl;
    }
};


// ================= LOCATION CLASS =================
class Location {
private:
    int id;
    string name;

public:
    Location(int i = 0, string n = "Unknown") {
        id = i;
        name = n;
    }

    void displayLocation() {
        cout << "Location ID: " << id << endl;
        cout << "Location Name: " << name << endl;
    }

    int getId() {
        return id;
    }

    string getName() {
        return name;
    }
};


// ================= EMERGENCY CLASS =================
class Emergency {
private:
    int emergencyId;
    string type;
    int severity;

public:
    Emergency(int id, string t, int s) {
        emergencyId = id;
        type = t;
        severity = s;
    }

    void displayEmergency() {
        cout << "\nEmergency ID: " << emergencyId << endl;
        cout << "Type: " << type << endl;
        cout << "Severity: " << severity << endl;
    }
};


// ================= RESCUE TEAM CLASS =================
class RescueTeam {
private:
    int teamId;
    string teamName;
    int members;

public:
    RescueTeam(int id, string name, int m) {
        teamId = id;
        teamName = name;
        members = m;
    }

    void displayTeam() {
        cout << "\nTeam ID: " << teamId << endl;
        cout << "Team Name: " << teamName << endl;
        cout << "Members: " << members << endl;
    }
};


// ================= SAHAY CLASS =================
class Sahay {
private:
    string systemName;
    string purpose;

public:
    Sahay(string name, string p) {
        systemName = name;
        purpose = p;
    }

    void displaySystem() {
        cout << "\n===== SAHAY DISASTER MANAGEMENT SYSTEM =====\n";
        cout << "System: " << systemName << endl;
        cout << "Purpose: " << purpose << endl;
    }
};


// ================= MAIN =================
int main() {

    // Object of Sahay
    Sahay system(
        "SAHAY",
        "Optimal route selection during disasters"
    );

    // Location objects
    Location location1(0, "Hospital");
    Location location2(1, "Fire Station");
    Location location3(2, "Disaster Site");

    // Road objects
    Road road1(5, false);
    Road road2(3, false);
    Road road3(4, true);

    // Emergency object
    Emergency emergency(
        101,
        "Building Collapse",
        5
    );

    // Rescue team object
    RescueTeam team(
        1,
        "Rapid Rescue Team",
        8
    );


    // Display everything
    system.displaySystem();

    cout << "\n--- LOCATIONS ---\n";
    location1.displayLocation();
    location2.displayLocation();
    location3.displayLocation();

    cout << "\n--- ROADS ---\n";
    cout << "Road 1: ";
    road1.displayRoad();

    cout << "Road 2: ";
    road2.displayRoad();

    cout << "Road 3: ";
    road3.displayRoad();

    emergency.displayEmergency();

    team.displayTeam();

    return 0;
}