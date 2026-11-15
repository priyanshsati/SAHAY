#ifndef LOCATION_H
#define LOCATION_H

#include<iostream>
#include<string>
using namespace std;

class Location{
public:
    int id;
    string name;
    string type;
    double latitude;
    double longitude;
    int population;

    Location(){
        id = 0;
        name = "";
        type = "";
        latitude = 0.0;
        longitude = 0.0;
        population = 0;
    }
};

#endif
