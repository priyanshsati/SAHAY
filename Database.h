#ifndef DATABASE_H
#define DATABASE_H

#include<iostream>
#include<string>
#include<mysql_driver.h>
#include<mysql_connection.h>
#include<cppconn/statement.h>
#include<cppconn/resultset.h>

#include "Location.h"
#include "Road.h"
#include "RoadCondition.h"
#include "RescueTeam.h"

using namespace std;

#define MAX_RECORDS 200

class Database{
public:
    string host;
    string port;
    string dbName;
    string user;
    string pass;

    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    Database();
    ~Database();

    bool loadConfigFile(const string &filename);
    bool connectToDatabase(const string &configPath = "config/db_credentials.env");
    bool isConnected();

    int getLocations(Location list[], int maxLimit);
    int getRoads(Road list[], int maxLimit);
    int getRoadConditions(RoadCondition list[], int maxLimit);
    int getRescueTeams(RescueTeam list[], int maxLimit);

    void close();
};

#endif
