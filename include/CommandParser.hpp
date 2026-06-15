#ifndef __COMMANDPARSER_HPP__
#define __COMMANDPARSER_HPP__

#include <iostream>
#include <map>
#include "Command.hpp"

class CommandParser{
    public:
    Command static parse(const std::string& line);

    private:
    CommandMethod static parseMethod(const std::string& word);
    CommandType static parseType(const std::string& word, CommandMethod method);
    std::map<std::string, std::string> static parseArguments(const std::string& argumentsPart);
};
#endif