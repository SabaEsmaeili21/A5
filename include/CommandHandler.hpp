#ifndef __COMMANDHANDLER_HPP__
#define __COMMANDHANDLER_HPP__
#include <iostream>
#include "Command.hpp"
#include "GameSystem.hpp"
#include "CasualOpponent.hpp"

class CommandHandler{
    public:
    CommandHandler(GameSystem& game): game_(game){}
    void Run();
    private:
    GameSystem& game_;
    std::string HandleCommand(const Command& command);
    std::string HandlePut(const Command& command);
    std::string HandlePost(const Command& command);
    std::string HandleGet(const Command& command);
    std::string HandleDelete(const Command& command);
    std::string RequireArgument(const Command& command, std::string key);

};
#endif