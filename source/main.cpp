#include <iostream>
#include <sstream>
#include "Player.hpp"
#include "Admin.hpp"
#include "CommandHandler.hpp"
#include "DataLoader.hpp"
#include "GameSystem.hpp"
#include "CommandParser.hpp"

using namespace std;

int main(int argc, char* argv[]){
    
    if (argc != 3)
    {
        cerr << "Usage: ./UTGame </path/to/players/file> </path/to/admins/file>\n";
        return 1;
    }

    auto players = DataLoader::LoadPlayers(argv[1]);
    auto admins = DataLoader::LoadAdmins(argv[2]);

    GameSystem game(players, admins);
    CommandHandler commandHandler(game);
    commandHandler.Run();
    
}