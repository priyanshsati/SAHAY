#ifndef SAHAY_H
#define SAHAY_H

#include<iostream>
#include<string>
#include "Database.h"

using namespace std;

struct Graph;

class SahaySystem{
public:
    Database db;
    struct Graph *c_graph;

    Location locations[MAX_RECORDS];
    int locationCount;

    Road roads[MAX_RECORDS];
    int roadCount;

    RoadCondition conditions[MAX_RECORDS];
    int conditionCount;

    SahaySystem();
    ~SahaySystem();

    bool initialize(const string &configPath = "config/db_credentials.env");
    bool buildGraphFromDatabase();
    string findRescueRoute(int sourceId, int destId, int rescueTeamId = 0);
    bool displayRoute(int sourceId, int destId, int rescueTeamId = 0);
};

#endif
