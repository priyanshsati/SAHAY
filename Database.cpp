#include "Database.h"
#include<fstream>
#include<sstream>

using namespace std;

Database::Database(){
    host = "127.0.0.1";
    port = "3306";
    dbName = "sahay";
    user = "sahay_user";
    pass = "";
    driver = NULL;
    con = NULL;
}

Database::~Database(){
    close();
}

void Database::close(){
    if(con != NULL){
        delete con;
        con = NULL;
    }
}

bool Database::loadConfigFile(const string &filename){
    ifstream file(filename.c_str());
    if(!file.is_open()) return false;

    string line;
    while(getline(file, line)){
        if(line.empty() || line[0] == '#') continue;

        size_t pos = line.find('=');
        if(pos != string::npos){
            string key = line.substr(0, pos);
            string val = line.substr(pos + 1);

            while(!val.empty() && (val.back() == '\r' || val.back() == ' ')){
                val.pop_back();
            }

            if(key == "DB_HOST") host = val;
            if(key == "DB_PORT") port = val;
            if(key == "DB_NAME") dbName = val;
            if(key == "DB_USER") user = val;
            if(key == "DB_PASS") pass = val;
        }
    }
    file.close();
    return true;
}

bool Database::connectToDatabase(const string &configPath){
    if(!loadConfigFile(configPath)) return false;

    try{
        driver = sql::mysql::get_mysql_driver_instance();
        string address = "tcp://" + host + ":" + port;
        con = driver->connect(address, user, pass);
        con->setSchema(dbName);
        return true;
    }
    catch(sql::SQLException &e){
        cout << "MySQL Error: " << e.what() << endl;
        con = NULL;
        return false;
    }
}

bool Database::isConnected(){
    return (con != NULL && !con->isClosed());
}

int Database::getLocations(Location list[], int maxLimit){
    int count = 0;
    if(!isConnected()) return 0;

    try{
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *result = stmt->executeQuery("SELECT id, name, type, latitude, longitude, population FROM locations ORDER BY id ASC");

        while(result->next() && count < maxLimit){
            Location loc;
            loc.id = result->getInt("id");
            loc.name = result->getString("name");
            loc.type = result->getString("type");
            loc.latitude = result->getDouble("latitude");
            loc.longitude = result->getDouble("longitude");
            loc.population = result->getInt("population");

            list[count] = loc;
            count++;
        }

        delete result;
        delete stmt;
    }
    catch(sql::SQLException &e){
        cout << "SQL Error: " << e.what() << endl;
    }

    return count;
}

int Database::getRoads(Road list[], int maxLimit){
    int count = 0;
    if(!isConnected()) return 0;

    try{
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *result = stmt->executeQuery("SELECT id, from_id, to_id, distance, road_type, is_one_way FROM roads ORDER BY id ASC");

        while(result->next() && count < maxLimit){
            Road road;
            road.id = result->getInt("id");
            road.from_id = result->getInt("from_id");
            road.to_id = result->getInt("to_id");
            road.distance = (float)result->getDouble("distance");
            road.road_type = result->getString("road_type");
            road.is_one_way = result->getInt("is_one_way");

            list[count] = road;
            count++;
        }

        delete result;
        delete stmt;
    }
    catch(sql::SQLException &e){
        cout << "SQL Error: " << e.what() << endl;
    }

    return count;
}

int Database::getRoadConditions(RoadCondition list[], int maxLimit){
    int count = 0;
    if(!isConnected()) return 0;

    try{
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *result = stmt->executeQuery("SELECT id, road_id, traffic, flood_severity, landslide_risk, road_damage, blocked, last_updated FROM road_conditions");

        while(result->next() && count < maxLimit){
            RoadCondition rc;
            rc.id = result->getInt("id");
            rc.road_id = result->getInt("road_id");
            rc.traffic = result->getInt("traffic");
            rc.flood_severity = result->getInt("flood_severity");
            rc.landslide_risk = result->getInt("landslide_risk");
            rc.road_damage = result->getInt("road_damage");
            rc.blocked = result->getInt("blocked");
            rc.updated_at = result->getString("last_updated");

            list[count] = rc;
            count++;
        }

        delete result;
        delete stmt;
    }
    catch(sql::SQLException &e){
        cout << "SQL Error: " << e.what() << endl;
    }

    return count;
}

int Database::getRescueTeams(RescueTeam list[], int maxLimit){
    int count = 0;
    if(!isConnected()) return 0;

    try{
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *result = stmt->executeQuery("SELECT id, name, team_type, current_location_id, available FROM rescue_teams ORDER BY id ASC");

        while(result->next() && count < maxLimit){
            RescueTeam team;
            team.id = result->getInt("id");
            team.name = result->getString("name");
            team.team_type = result->getString("team_type");
            team.current_location_id = result->getInt("current_location_id");
            team.available = result->getInt("available");

            list[count] = team;
            count++;
        }

        delete result;
        delete stmt;
    }
    catch(sql::SQLException &e){
        cout << "SQL Error: " << e.what() << endl;
    }

    return count;
}
