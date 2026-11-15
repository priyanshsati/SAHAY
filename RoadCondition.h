#ifndef ROADCONDITION_H
#define ROADCONDITION_H

#include<iostream>
#include<string>
using namespace std;

class RoadCondition{
public:
    int id;
    int road_id;
    int traffic;
    int flood_severity;
    int landslide_risk;
    int road_damage;
    int blocked;
    string updated_at;

    RoadCondition(){
        id = 0;
        road_id = 0;
        traffic = 0;
        flood_severity = 0;
        landslide_risk = 0;
        road_damage = 0;
        blocked = 0;
        updated_at = "";
    }
};

#endif
