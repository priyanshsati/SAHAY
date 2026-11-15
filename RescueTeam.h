#ifndef RESCUETEAM_H
#define RESCUETEAM_H

#include<iostream>
#include<string>
using namespace std;

class RescueTeam{
public:
    int id;
    string name;
    string team_type;
    int current_location_id;
    int available;
    string contact_number;

    RescueTeam(){
        id = 0;
        name = "";
        team_type = "";
        current_location_id = 0;
        available = 1;
        contact_number = "";
    }
};

#endif
