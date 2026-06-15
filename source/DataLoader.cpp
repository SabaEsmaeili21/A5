#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include "Player.hpp"
#include "Admin.hpp"
#include "DataLoader.hpp"
using namespace std;

std::map<std::string, Player> DataLoader::LoadPlayers(std::string playersFileName){
    map<string, Player> players;
    ifstream file(playersFileName);
    if (!file.is_open()){
        cerr << "Error opening the Players.csv file.\n";
        return players;
    }
    string header, line;
    getline(file, header);
    while(getline(file, line)){
        string username, password, xpStr, rpStr;
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, xpStr, ',');
        getline(ss, rpStr, ',');

        int xp = stoi(xpStr);
        int rp = stoi(rpStr);
        players.emplace(username, Player(username, password, xp, rp));   
    }
    return players;

}
std::map<std::string, Admin> DataLoader::LoadAdmins(std::string adminsFileName){
    map<string, Admin> admins;
    ifstream file(adminsFileName);
    if (!file.is_open()){
        cerr << "Error opening the Admins.csv file.\n";
        return admins;
    }
    string header, line;
    getline(file, header);
    while(getline(file, line)){
        string username, password;
        stringstream ss(line);
        getline(ss, username, ',');
        getline(ss, password, ',');
        admins.emplace(username, Admin(username, password));
    }
    return admins;

}