#ifndef ENTITIES_H
#define ENTITIES_H

#include<iostream>
#include<string>
using namespace std;

class Hospital{
public:
    int id;
    int location_id;
    string name;
    int available_beds;
    string contact;

    Hospital(){
        id = 0;
        location_id = 0;
        name = "";
        available_beds = 0;
        contact = "";
    }
};

class Shelter{
public:
    int id;
    int location_id;
    string name;
    int capacity;
    int occupied;

    Shelter(){
        id = 0;
        location_id = 0;
        name = "";
        capacity = 0;
        occupied = 0;
    }
};

class Disaster{
public:
    int id;
    string disaster_type;
    int location_id;
    int severity;
    string description;
    string status;
    string created_at;

    Disaster(){
        id = 0;
        disaster_type = "";
        location_id = 0;
        severity = 0;
        description = "";
        status = "Active";
        created_at = "";
    }
};

class RouteLog{
public:
    int id;
    int source_location_id;
    int dest_location_id;
    int rescue_team_id;
    string path_taken;
    double total_weight;
    double total_distance;
    string algorithm_used;
    string calculated_at;

    RouteLog(){
        id = 0;
        source_location_id = 0;
        dest_location_id = 0;
        rescue_team_id = 0;
        path_taken = "";
        total_weight = 0.0;
        total_distance = 0.0;
        algorithm_used = "Dijkstra";
        calculated_at = "";
    }
};

class ReliefSupply{
public:
    int people_count;
    int food_packets;
    int water_liters;
    int medical_kits;
    int vehicles_needed;

    ReliefSupply(){
        people_count = 0;
        food_packets = 0;
        water_liters = 0;
        medical_kits = 0;
        vehicles_needed = 0;
    }

    void calculate(int people){
        people_count = people;
        food_packets = people * 2;
        water_liters = people * 3;
        medical_kits = (people + 19) / 20;
        vehicles_needed = (people + 49) / 50;
        if(vehicles_needed < 1) vehicles_needed = 1;
    }
};

#endif
