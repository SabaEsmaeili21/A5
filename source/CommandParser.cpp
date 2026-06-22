#include <iostream>
#include <map>
#include <sstream>
#include "Command.hpp"
#include "CommandParser.hpp"
#include "Exception.hpp"

using namespace std;

Command CommandParser::parse(const std::string& line){
    stringstream cmdin(line);

    string methodWord;
    string typeWord;
    string questionMark;
    string argumentsPart;

    if (!(cmdin >> methodWord))
        throw BadRequest();

    const CommandMethod method = parseMethod(methodWord);

    if (!(cmdin >> typeWord))
        throw BadRequest();

    const CommandType type = parseType(typeWord, method);

    if (!(cmdin >> questionMark) || questionMark != "?")
        throw BadRequest();

    getline(cmdin, argumentsPart);

    return {method, type, parseArguments(argumentsPart)};
}

CommandMethod CommandParser::parseMethod(const std::string& word){
    if(word == "PUT")
        return CommandMethod::PUT;
    if(word == "GET")
        return CommandMethod::GET;
    if(word == "POST")
        return CommandMethod::POST;
    if(word == "DELETE")
        return CommandMethod::DELETE;
    throw BadRequest();
}

CommandType CommandParser::parseType(const std::string& word, CommandMethod method){
    const map<string, CommandType>* commands = nullptr;

    switch (method)
    {
    case CommandMethod::POST:
        commands = &postCommands;
        break;
    case CommandMethod::GET:
        commands = &getCommands;
        break;
    case CommandMethod::PUT:
        commands = &putCommands;
        break;
    case CommandMethod::DELETE:
        commands = &deleteCommands;
        break;
    }

    auto it = commands->find(word);

    if (it == commands->end())
        throw NotFound();

    return it->second;
}

std::map<std::string, std::string> CommandParser::parseArguments(const std::string& argumentsPart){
    stringstream ss(argumentsPart);

    string key, value;
    map<string, string> arguments;
    string ignored;
    while (ss >> key)
    {
        if (!getline(ss, ignored, '"'))
            throw BadRequest();

        if (!getline(ss, value, '"'))
            throw BadRequest();

        arguments[key] = value;
    }
    return arguments;
}

