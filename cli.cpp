#include<iostream>
#include<string>
#include<cstdlib>
#include "Sahay.h"
#include "Entities.h"

using namespace std;

void deployHelicopter(const string &destName, int dest, int peopleCount = 0){
    cout << "\n[Aerial Search and Rescue Mission Authorized]" << endl;
    cout << "Mission Type:   Emergency Air Evacuation & Supply Airdrop" << endl;
    cout << "Target Zone:    " << destName << " (Location ID: " << dest << ")" << endl;
    cout << "Air Wing:       SDRF Air Wing / Indian Air Force" << endl;
    cout << "Aircraft:       Mi-17 Helicopter" << endl;
    cout << "Launch Base:    Jolly Grant Airport Helipad" << endl;
    cout << "Ground Status:  All ground access destroyed - Bypassing terrain" << endl;
    cout << "Estimated ETA:  12 - 15 minutes" << endl;
    if(peopleCount > 0){
        int food = peopleCount * 2;
        int water = peopleCount * 3;
        int medKits = (peopleCount + 19) / 20;
        int sorties = (peopleCount + 39) / 40;
        if(sorties < 1) sorties = 1;
        cout << "\nAerial Relief Cargo Payload:" << endl;
        cout << "Victims Tracked:    " << peopleCount << " people stranded" << endl;
        cout << "Food Airdrop:       " << food << " ration packets (ready-to-eat meals)" << endl;
        cout << "Drinking Water:     " << water << " liters" << endl;
        cout << "Emergency Med Kits: " << medKits << " trauma packs" << endl;
        cout << "Helicopter Sorties: " << sorties << " flights needed" << endl;
    }
    cout << "Mission Status: Airborne - Rescue in Progress\n" << endl;
}

void showLocations(SahaySystem &sahay){
    Location list[MAX_RECORDS];
    int count = sahay.db.getLocations(list, MAX_RECORDS);

    cout << "\nLocations in Dehradun:\n" << endl;
    cout << "ID   | Name                                | Type       | Pop." << endl;

    for(int i = 0; i < count; i++){
        cout << list[i].id;
        if(list[i].id < 10) cout << "    | ";
        else cout << "   | ";

        cout << list[i].name;
        int spaces = 36 - list[i].name.length();
        for(int s = 0; s < spaces; s++) cout << " ";
        cout << "| ";

        cout << list[i].type;
        spaces = 11 - list[i].type.length();
        for(int s = 0; s < spaces; s++) cout << " ";
        cout << "| " << list[i].population << endl;
    }
    cout << endl;
}

void showRoads(SahaySystem &sahay){
    Location locs[MAX_RECORDS];
    int locCount = sahay.db.getLocations(locs, MAX_RECORDS);

    Road roads[MAX_RECORDS];
    int roadCount = sahay.db.getRoads(roads, MAX_RECORDS);

    RoadCondition conds[MAX_RECORDS];
    int condCount = sahay.db.getRoadConditions(conds, MAX_RECORDS);

    cout << "\nRoad Network and Current Conditions:\n" << endl;
    cout << "ID  | From -> To                    | Dist(km) | Traffic | Flood | Slide | Status" << endl;

    for(int i = 0; i < roadCount; i++){
        string fromName = "Loc " + to_string(roads[i].from_id);
        string toName = "Loc " + to_string(roads[i].to_id);

        for(int j = 0; j < locCount; j++){
            if(locs[j].id == roads[i].from_id) fromName = locs[j].name;
            if(locs[j].id == roads[i].to_id) toName = locs[j].name;
        }

        string routeStr = fromName + " -> " + toName;
        if(routeStr.length() > 29){
            routeStr = routeStr.substr(0, 26) + "...";
        }

        int traffic = 0;
        int flood = 0;
        int slide = 0;
        int blocked = 0;

        for(int k = 0; k < condCount; k++){
            if(conds[k].road_id == roads[i].id){
                traffic = conds[k].traffic;
                flood = conds[k].flood_severity;
                slide = conds[k].landslide_risk;
                blocked = conds[k].blocked;
                break;
            }
        }

        cout << roads[i].id;
        if(roads[i].id < 10) cout << "   | ";
        else cout << "  | ";

        cout << routeStr;
        int spaces = 30 - routeStr.length();
        for(int s = 0; s < spaces; s++) cout << " ";
        cout << "| " << roads[i].distance;
        if(roads[i].distance < 10.0) cout << "     | ";
        else cout << "    | ";

        cout << traffic << "%";
        if(traffic < 10) cout << "     | ";
        else if(traffic < 100) cout << "    | ";
        else cout << "   | ";

        cout << flood << "%";
        if(flood < 10) cout << "   | ";
        else if(flood < 100) cout << "  | ";
        else cout << " | ";

        cout << slide << "%";
        if(slide < 10) cout << "   | ";
        else if(slide < 100) cout << "  | ";
        else cout << " | ";

        if(blocked == 1){
            cout << "BLOCKED" << endl;
        }
        else{
            cout << "OPEN" << endl;
        }
    }
    cout << endl;
}

void showRescueTeams(SahaySystem &sahay){
    Location locs[MAX_RECORDS];
    int locCount = sahay.db.getLocations(locs, MAX_RECORDS);

    RescueTeam teams[MAX_RECORDS];
    int count = sahay.db.getRescueTeams(teams, MAX_RECORDS);

    cout << "\nActive Rescue Teams:\n" << endl;
    cout << "ID  | Team Name              | Specialization     | Base Location" << endl;

    for(int i = 0; i < count; i++){
        string baseLoc = "Loc " + to_string(teams[i].current_location_id);
        for(int j = 0; j < locCount; j++){
            if(locs[j].id == teams[i].current_location_id){
                baseLoc = locs[j].name;
                break;
            }
        }

        cout << teams[i].id;
        if(teams[i].id < 10) cout << "   | ";
        else cout << "  | ";

        cout << teams[i].name;
        int spaces = 23 - teams[i].name.length();
        for(int s = 0; s < spaces; s++) cout << " ";
        cout << "| ";

        cout << teams[i].team_type;
        spaces = 19 - teams[i].team_type.length();
        for(int s = 0; s < spaces; s++) cout << " ";
        cout << "| " << baseLoc << endl;
    }
    cout << endl;
}

void updateCondition(SahaySystem &sahay){
    showRoads(sahay);

    int roadId = 0;
    cout << "Enter Road ID to update (1-26, or 0 to cancel): ";
    if(!(cin >> roadId) || roadId <= 0){
        return;
    }

    Road roads[MAX_RECORDS];
    int roadCount = sahay.db.getRoads(roads, MAX_RECORDS);
    Location locs[MAX_RECORDS];
    int locCount = sahay.db.getLocations(locs, MAX_RECORDS);

    if(roadId > roadCount){
        cout << "Invalid road ID!" << endl;
        return;
    }

    string fromName = "Loc " + to_string(roads[roadId - 1].from_id);
    string toName = "Loc " + to_string(roads[roadId - 1].to_id);
    for(int j = 0; j < locCount; j++){
        if(locs[j].id == roads[roadId - 1].from_id) fromName = locs[j].name;
        if(locs[j].id == roads[roadId - 1].to_id) toName = locs[j].name;
    }

    cout << "\nUpdating Conditions for Road #" << roadId << ": " << fromName << " to " << toName << endl;

    int traffic, flood, landslide, blocked;
    cout << "Enter Traffic Severity (0 - 100): ";
    cin >> traffic;
    cout << "Enter Flood Severity (0 - 100): ";
    cin >> flood;
    cout << "Enter Landslide Risk (0 - 100): ";
    cin >> landslide;
    cout << "Is road blocked? (1 for YES, 0 for NO): ";
    cin >> blocked;

    try{
        sql::Statement *stmt = sahay.db.con->createStatement();
        string query = "UPDATE road_conditions SET traffic=" + to_string(traffic) +
                       ", flood_severity=" + to_string(flood) +
                       ", landslide_risk=" + to_string(landslide) +
                       ", blocked=" + to_string(blocked) +
                       " WHERE road_id=" + to_string(roadId);
        stmt->executeUpdate(query);
        delete stmt;
        cout << "\nRoad #" << roadId << " (" << fromName << " to " << toName << ") updated successfully!\n" << endl;
    }
    catch(sql::SQLException &e){
        cout << "Database update error: " << e.what() << endl;
    }
}

void resetConditions(SahaySystem &sahay){
    try{
        sql::Statement *stmt = sahay.db.con->createStatement();
        stmt->executeUpdate("UPDATE road_conditions SET traffic=10, flood_severity=0, landslide_risk=0, road_damage=0, blocked=0");
        delete stmt;
        cout << "\nAll road conditions reset back to normal baseline!\n" << endl;
    }
    catch(sql::SQLException &e){
        cout << "Database update error: " << e.what() << endl;
    }
}

int main(){
    SahaySystem sahay;
    if(!sahay.initialize("config/db_credentials.env")){
        cout << "Failed to connect to MySQL database at 127.0.0.1:3306" << endl;
        return 1;
    }

    int choice = 0;

    do{
        cout << "\nSAHAY - Disaster Route Optimization System (Dehradun)\n" << endl;
        cout << "1. View All Locations" << endl;
        cout << "2. View Road Network & Live Conditions" << endl;
        cout << "3. Emergency Incident Response & Dispatch" << endl;
        cout << "4. View Active Rescue Teams" << endl;
        cout << "5. Simulate Disaster / Update Road Condition" << endl;
        cout << "6. Reset Road Conditions to Clean Baseline" << endl;
        cout << "7. Run 7 Automated Demonstration Scenarios" << endl;
        cout << "8. Exit" << endl;
        cout << "\nEnter your choice (1-8): ";
        if(!(cin >> choice)){
            cin.clear();
            string discard;
            cin >> discard;
            continue;
        }

        switch(choice){
            case 1:
                showLocations(sahay);
                break;

            case 2:
                showRoads(sahay);
                break;

            case 3: {
                Location locs[MAX_RECORDS];
                int locCount = sahay.db.getLocations(locs, MAX_RECORDS);

                cout << "\nEmergency Incident Response & Dispatch" << endl;
                cout << "Enter Disaster / Destination Location ID (1-" << locCount << ", or 0 to view locations): ";
                int dest = 0;
                cin >> dest;

                if(dest == 0){
                    showLocations(sahay);
                    cout << "Enter Disaster / Destination Location ID: ";
                    cin >> dest;
                }

                if(dest <= 0 || dest > locCount){
                    cout << "Invalid location ID!" << endl;
                    break;
                }

                string destName = "Location " + to_string(dest);
                for(int j = 0; j < locCount; j++){
                    if(locs[j].id == dest){
                        destName = locs[j].name;
                        break;
                    }
                }
                cout << "\n>> Target Incident Location: " << destName << " (ID: " << dest << ")" << endl;

                int people = 0;
                cout << "Enter estimated number of stranded people / victims: ";
                cin >> people;
                if(people < 0) people = 0;

                ReliefSupply supply;
                supply.calculate(people);

                RescueTeam teams[MAX_RECORDS];
                int teamCount = sahay.db.getRescueTeams(teams, MAX_RECORDS);

                cout << "\nSelect Rescue Team to Dispatch:\n" << endl;
                for(int i = 0; i < teamCount; i++){
                    string baseName = "Location " + to_string(teams[i].current_location_id);
                    for(int j = 0; j < locCount; j++){
                        if(locs[j].id == teams[i].current_location_id){
                            baseName = locs[j].name;
                            break;
                        }
                    }
                    cout << teams[i].id << ". " << teams[i].name << " (" << teams[i].team_type << ") [Base: " << baseName << "]" << endl;
                }
                cout << "\nSelect Team ID (1-" << teamCount << "): ";
                int teamId = 1;
                cin >> teamId;
                if(teamId < 1 || teamId > teamCount) teamId = 1;

                int teamIdx = teamId - 1;
                int src = teams[teamIdx].current_location_id;
                string srcName = "Location " + to_string(src);
                for(int j = 0; j < locCount; j++){
                    if(locs[j].id == src){
                        srcName = locs[j].name;
                        break;
                    }
                }

                cout << "\n>> Assigned Unit: " << teams[teamIdx].name << endl;
                cout << ">> Starting Base Location: " << srcName << " (ID: " << src << ")" << endl;

                Road roads[MAX_RECORDS];
                int roadCount = sahay.db.getRoads(roads, MAX_RECORDS);
                RoadCondition conds[MAX_RECORDS];
                int condCount = sahay.db.getRoadConditions(conds, MAX_RECORDS);

                cout << "\nCorridor Roads around " << srcName << " and " << destName << ":\n" << endl;
                cout << "ID  | From -> To                    | Dist(km) | Traffic | Flood | Slide | Status" << endl;

                for(int i = 0; i < roadCount; i++){
                    if(roads[i].from_id == src || roads[i].to_id == src ||
                       roads[i].from_id == dest || roads[i].to_id == dest){
                        string fromStr = "Loc " + to_string(roads[i].from_id);
                        string toStr = "Loc " + to_string(roads[i].to_id);
                        for(int j = 0; j < locCount; j++){
                            if(locs[j].id == roads[i].from_id) fromStr = locs[j].name;
                            if(locs[j].id == roads[i].to_id) toStr = locs[j].name;
                        }

                        string routeStr = fromStr + " -> " + toStr;
                        if(routeStr.length() > 29) routeStr = routeStr.substr(0, 26) + "...";

                        int traffic = 0, flood = 0, slide = 0, blocked = 0;
                        for(int k = 0; k < condCount; k++){
                            if(conds[k].road_id == roads[i].id){
                                traffic = conds[k].traffic;
                                flood = conds[k].flood_severity;
                                slide = conds[k].landslide_risk;
                                blocked = conds[k].blocked;
                                break;
                            }
                        }

                        cout << roads[i].id;
                        if(roads[i].id < 10) cout << "   | ";
                        else cout << "  | ";

                        cout << routeStr;
                        int spaces = 30 - routeStr.length();
                        for(int s = 0; s < spaces; s++) cout << " ";
                        cout << "| " << roads[i].distance;
                        if(roads[i].distance < 10.0) cout << "     | ";
                        else cout << "    | ";

                        cout << traffic << "%";
                        if(traffic < 10) cout << "     | ";
                        else if(traffic < 100) cout << "    | ";
                        else cout << "   | ";

                        cout << flood << "%";
                        if(flood < 10) cout << "   | ";
                        else if(flood < 100) cout << "  | ";
                        else cout << " | ";

                        cout << slide << "%";
                        if(slide < 10) cout << "   | ";
                        else if(slide < 100) cout << "  | ";
                        else cout << " | ";

                        if(blocked == 1) cout << "BLOCKED" << endl;
                        else cout << "OPEN" << endl;
                    }
                }

                cout << "\nDispatch Decision for this Mission:" << endl;
                cout << "0. No, Proceed with Ground Convoy (Calculate Dijkstra Route)" << endl;
                cout << "1. Yes, Update/Change a Road Condition" << endl;
                cout << "2. All Roads Destroyed / Cut Off -> Send Helicopter Immediately (Air Rescue)!" << endl;
                cout << "Enter your choice (0, 1, or 2): ";
                int wantChange = 0;
                cin >> wantChange;

                if(wantChange == 2){
                    deployHelicopter(destName, dest, people);
                    break;
                }
                else if(wantChange == 1){
                    updateCondition(sahay);
                }

                bool routeFound = sahay.displayRoute(src, dest, teamId);

                if(routeFound && people > 0){
                    cout << "Emergency Relief & Food Supply Logistics:" << endl;
                    cout << "Stranded People:     " << supply.people_count << " victims" << endl;
                    cout << "Food Ration Packets: " << supply.food_packets << " meals (ready-to-eat packages)" << endl;
                    cout << "Clean Drinking Water:" << supply.water_liters << " liters" << endl;
                    cout << "Medical First-Aid:   " << supply.medical_kits << " trauma kits" << endl;
                    cout << "Convoy Logistics:    " << supply.vehicles_needed << " relief supply trucks dispatched with team\n" << endl;
                }

                if(!routeFound){
                    cout << "\n[Alert] All ground routes are impassable!" << endl;
                    cout << "Vehicular convoy cannot reach " << destName << "." << endl;
                    cout << "Do you want to authorize Aerial Helicopter Rescue (IAF / SDRF Chopper)? (1 for YES, 0 for NO): ";
                    int sendHeli = 0;
                    cin >> sendHeli;

                    if(sendHeli == 1){
                        deployHelicopter(destName, dest, people);
                    }
                    else {
                        cout << "\nGround routes remain blocked. Please clear road debris or reconsider air support.\n" << endl;
                    }
                }
                break;
            }

            case 4:
                showRescueTeams(sahay);
                break;

            case 5:
                updateCondition(sahay);
                break;

            case 6:
                resetConditions(sahay);
                break;

            case 7: {
                int ret = system("./tests/test_scenarios.sh");
                (void)ret;
                break;
            }

            case 8:
                cout << "\nExiting SAHAY system. Stay safe!\n" << endl;
                break;

            default:
                cout << "\nInvalid option. Please enter a number between 1 and 8.\n" << endl;
                break;
        }

    } while(choice != 8);

    return 0;
}
