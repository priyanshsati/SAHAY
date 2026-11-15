#include "Sahay.h"
#include<sstream>

using namespace std;

extern "C" {
    #include "../c/dijkstra.c"
}

SahaySystem::SahaySystem(){
    locationCount = 0;
    roadCount = 0;
    conditionCount = 0;
    c_graph = (struct Graph*)malloc(sizeof(struct Graph));
    initGraph(c_graph, 0);
}

SahaySystem::~SahaySystem(){
    if(c_graph != NULL){
        freeGraph(c_graph);
        free(c_graph);
        c_graph = NULL;
    }
}

bool SahaySystem::initialize(const string &configPath){
    return db.connectToDatabase(configPath);
}

bool SahaySystem::buildGraphFromDatabase(){
    if(!db.isConnected()) return false;

    locationCount = db.getLocations(locations, MAX_RECORDS);
    roadCount = db.getRoads(roads, MAX_RECORDS);
    conditionCount = db.getRoadConditions(conditions, MAX_RECORDS);

    int maxId = 0;
    for(int i = 0; i < locationCount; i++){
        if(locations[i].id > maxId) maxId = locations[i].id;
    }

    freeGraph(c_graph);
    initGraph(c_graph, maxId);

    for(int i = 0; i < roadCount; i++){
        Road r = roads[i];

        int traffic = 0;
        int flood = 0;
        int landslide = 0;
        int damage = 0;
        int isBlocked = 0;

        for(int j = 0; j < conditionCount; j++){
            if(conditions[j].road_id == r.id){
                traffic = conditions[j].traffic;
                flood = conditions[j].flood_severity;
                landslide = conditions[j].landslide_risk;
                damage = conditions[j].road_damage;
                isBlocked = conditions[j].blocked;
                break;
            }
        }

        if(isBlocked == 1) continue;

        float weight = calculateRoadWeight(r.distance, traffic, flood, landslide, damage);
        addEdge(c_graph, r.from_id, r.to_id, weight, r.distance, r.id, r.is_one_way);
    }

    return true;
}

string SahaySystem::findRescueRoute(int sourceId, int destId, int rescueTeamId){
    if(!buildGraphFromDatabase()){
        return "{\"status\":\"error\",\"message\":\"Failed to read database.\"}";
    }

    string srcName = "Unknown";
    string dstName = "Unknown";
    for(int i = 0; i < locationCount; i++){
        if(locations[i].id == sourceId) srcName = locations[i].name;
        if(locations[i].id == destId) dstName = locations[i].name;
    }

    string teamName = "None";
    if(rescueTeamId > 0){
        RescueTeam teams[MAX_RECORDS];
        int teamCount = db.getRescueTeams(teams, MAX_RECORDS);
        for(int i = 0; i < teamCount; i++){
            if(teams[i].id == rescueTeamId){
                teamName = teams[i].name;
                break;
            }
        }
    }

    struct RouteResult res = findShortestRoute(c_graph, sourceId, destId);

    if(res.found == 0){
        stringstream ss;
        ss << "{"
           << "\"status\":\"no_route\","
           << "\"source_id\":" << sourceId << ","
           << "\"source_name\":\"" << srcName << "\","
           << "\"destination_id\":" << destId << ","
           << "\"destination_name\":\"" << dstName << "\","
           << "\"message\":\"No usable route found between these locations. Roads may be blocked or flooded.\","
           << "\"warnings\":[";
        for(int i = 0; i < res.warningCount; i++){
            ss << "\"" << res.warnings[i] << "\"";
            if(i < res.warningCount - 1) ss << ",";
        }
        ss << "]}";
        return ss.str();
    }

    stringstream ss;
    ss << "{"
       << "\"status\":\"success\","
       << "\"source_id\":" << sourceId << ","
       << "\"source_name\":\"" << srcName << "\","
       << "\"destination_id\":" << destId << ","
       << "\"destination_name\":\"" << dstName << "\","
       << "\"rescue_team_name\":\"" << teamName << "\","
       << "\"total_weight\":" << res.totalWeight << ","
       << "\"total_distance\":" << res.totalDistance << ","
       << "\"road_count\":" << res.roadCount << ","
       << "\"path\":[";

    for(int i = 0; i < res.pathLength; i++){
        int locId = res.path[i];
        string name = "Location " + to_string(locId);

        for(int j = 0; j < locationCount; j++){
            if(locations[j].id == locId){
                name = locations[j].name;
                break;
            }
        }

        ss << "{\"id\":" << locId << ",\"name\":\"" << name << "\"}";
        if(i < res.pathLength - 1) ss << ",";
    }

    ss << "],\"warnings\":[";
    for(int i = 0; i < res.warningCount; i++){
        ss << "\"" << res.warnings[i] << "\"";
        if(i < res.warningCount - 1) ss << ",";
    }
    ss << "]}";

    return ss.str();
}

bool SahaySystem::displayRoute(int sourceId, int destId, int rescueTeamId){
    if(!buildGraphFromDatabase()){
        cout << "\nError: Unable to load data from database." << endl;
        return false;
    }

    string srcName = "Unknown";
    string dstName = "Unknown";
    for(int i = 0; i < locationCount; i++){
        if(locations[i].id == sourceId) srcName = locations[i].name;
        if(locations[i].id == destId) dstName = locations[i].name;
    }

    string teamName = "None";
    if(rescueTeamId > 0){
        RescueTeam teams[MAX_RECORDS];
        int teamCount = db.getRescueTeams(teams, MAX_RECORDS);
        for(int i = 0; i < teamCount; i++){
            if(teams[i].id == rescueTeamId){
                teamName = teams[i].name;
                break;
            }
        }
    }

    struct RouteResult res = findShortestRoute(c_graph, sourceId, destId);

    cout << "\nOptimal Rescue Route:" << endl;
    cout << "Source:      " << srcName << " (ID: " << sourceId << ")" << endl;
    cout << "Destination: " << dstName << " (ID: " << destId << ")" << endl;
    if(rescueTeamId > 0){
        cout << "Rescue Team: " << teamName << " (ID: " << rescueTeamId << ")" << endl;
    }

    if(res.found == 0){
        cout << "\nStatus: No route found" << endl;
        cout << "Reason: All available roads are blocked or severely flooded.\n" << endl;
        return false;
    }

    cout << "\nStatus: Route Found Successfully" << endl;
    cout << "Total Physical Distance: " << res.totalDistance << " km" << endl;
    cout << "Hazard-Weighted Cost:    " << res.totalWeight << endl;
    cout << "Number of Road Segments: " << res.roadCount << endl;

    cout << "\nRecommended Path Sequence:" << endl;
    for(int i = 0; i < res.pathLength; i++){
        int locId = res.path[i];
        string name = "Location " + to_string(locId);
        for(int j = 0; j < locationCount; j++){
            if(locations[j].id == locId){
                name = locations[j].name;
                break;
            }
        }
        cout << "  [" << (i + 1) << "] " << name << " (ID: " << locId << ")" << endl;
        if(i < res.pathLength - 1){
            cout << "       |" << endl;
            cout << "       v" << endl;
        }
    }

    if(res.warningCount > 0){
        cout << "\nActive Hazard Warnings:" << endl;
        for(int i = 0; i < res.warningCount; i++){
            cout << "  ! " << res.warnings[i] << endl;
        }
    }
    else{
        cout << "\nRoad Status: Clear (No hazard penalties active)" << endl;
    }
    cout << endl;
    return true;
}
