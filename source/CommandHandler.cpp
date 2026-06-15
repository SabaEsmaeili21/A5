#include <iostream>
#include <map>
#include <string>
#include "CommandHandler.hpp"
#include "Command.hpp"
#include "CommandParser.hpp"
#include "Exception.hpp"
#include "GameSystem.hpp"
#include "OutputFormatter.hpp"
#include "SortOrder.hpp"
#include "MatchType.hpp"
using namespace std;

void CommandHandler::Run(){
    string commandLine;
    Command command;
    while(getline(cin, commandLine)){
        try{
            command = CommandParser::parse(commandLine);
            cout << HandleCommand(command);
        }
        catch(const AppException &ex){
            cout << ex.GetError() + "\n";
        }
    }
}

string CommandHandler::HandleCommand(const Command& command){
    switch (command.method){
        case CommandMethod::POST:
            return HandlePost(command);
        case CommandMethod::GET:
            return HandleGet(command);
        case CommandMethod::PUT:
            return HandlePut(command);
        case CommandMethod::DELETE:
            return HandleDelete(command);
        default:
            throw BadRequest();
    }
}

string CommandHandler::HandlePost(const Command& command) {

    switch (command.type) {
        case CommandType::Register:

            game_.Register(RequireArgument(command, "username"), RequireArgument(command, "password"));
            return OutputFormatter::Ok();

        case CommandType::Login:
            game_.Login(RequireArgument(command, "username"), RequireArgument(command, "password"));
            return OutputFormatter::Ok();

        case CommandType::Logout:
            game_.Logout();
            return OutputFormatter::Ok();
           

        case CommandType::CasualMatchReady:
            game_.CasualMatchReady(RequireArgument(command, "status"));
            return OutputFormatter::Ok();

        case CommandType::Invitation:
            game_.PostInvitation(RequireArgument(command, "username"), RequireArgument(command, "match_type"));
            return OutputFormatter::Ok();
          

        case CommandType::StartMatch:
            game_.StartMatch(stoi(RequireArgument(command, "invitation_id")));
            return OutputFormatter::Ok();
            
        case CommandType::RejectInvitation:
            game_.RejectInvitation(stoi(RequireArgument(command, "invitation_id")));
            return OutputFormatter::Ok();    

        case CommandType::Action:
            game_.ProcessMove(RequireArgument(command, "action"));
            return OutputFormatter::Ok();

        case CommandType::Report:
            game_.Report(RequireArgument(command, "username"), RequireArgument(command, "reason"));
            return OutputFormatter::Ok();

        default:
            throw NotFound();
    }
}

std::string CommandHandler::HandleGet(const Command& command){
    switch(command.type){
        case CommandType::CasualMatchOpponents:{

            vector<CasualOpponent> casualOpponent = game_.CasualMatchOpponents();

            if(command.arguments.find("sort_order") == command.arguments.end())
                return OutputFormatter::CasualMatchOpponents(casualOpponent, SortOrder::DESC);

            if(command.arguments.at("sort_order") != "asc" &&
            command.arguments.at("sort_order") != "desc")
                throw BadRequest();
            
            
            return OutputFormatter::CasualMatchOpponents
            (casualOpponent, getSortOrder.at(command.arguments.at("sort_order")));
        }

        case CommandType::MatchStatus:{
            return OutputFormatter::MatchStatus(game_.MatchStatus());
        }
        
        case CommandType::Profile:{
            string username;
            if(command.arguments.find("username") != command.arguments.end())
                username = command.arguments.at("username");
            return OutputFormatter::Profile(game_.GetProfile(username));
        }

        case CommandType::ReceivedInvitations:
            return OutputFormatter::ReceivedInvitations(game_.GetReceivedInvitations());

        case CommandType::Reports:
            return OutputFormatter::Reports(game_.GetReports());

        default:
            throw NotFound();
    }
}

std::string CommandHandler::HandlePut(const Command& command){
    throw NotFound();
}
std::string CommandHandler::HandleDelete(const Command& command){
    throw NotFound();
}

std::string CommandHandler::RequireArgument(const Command& command, std::string key){
    const auto it = command.arguments.find(key);

    if (it == command.arguments.end())
        throw BadRequest();

    return it->second;
}