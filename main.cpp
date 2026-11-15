#include<iostream>
#include<string>
#include "Sahay.h"

using namespace std;

int toInt(const char* str){
    int val = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= '0' && str[i] <= '9'){
            val = val * 10 + (str[i] - '0');
        }
    }
    return val;
}

int main(int argc, char* argv[]){
    if(argc < 3){
        cout << "Usage: " << argv[0] << " <source_id> <dest_id> [team_id] [config_path]" << endl;
        cout << "{\"status\":\"error\",\"message\":\"Source and destination IDs are required.\"}" << endl;
        return 1;
    }

    int src = toInt(argv[1]);
    int dest = toInt(argv[2]);
    int teamId = 0;
    if(argc >= 4){
        teamId = toInt(argv[3]);
    }

    string configPath = "config/db_credentials.env";
    if(argc >= 5){
        configPath = argv[4];
    }

    SahaySystem sahay;
    if(!sahay.initialize(configPath)){
        cout << "{\"status\":\"error\",\"message\":\"Failed to connect to MySQL database at 127.0.0.1:3306.\"}" << endl;
        return 2;
    }

    string result = sahay.findRescueRoute(src, dest, teamId);
    cout << result << endl;

    return 0;
}
