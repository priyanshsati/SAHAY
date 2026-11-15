#ifndef ROAD_H
#define ROAD_H

#include<iostream>
#include<string>
using namespace std;

class Road{
public:
    int id;
    int from_id;
    int to_id;
    double distance;
    string road_type;
    int is_one_way;

    Road(){
        id = 0;
        from_id = 0;
        to_id = 0;
        distance = 0.0;
        road_type = "";
        is_one_way = 0;
    }
};

#endif
