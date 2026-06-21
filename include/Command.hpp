#ifndef __COMMAND_HPP__
#define __COMMAND_HPP__
#include <map>
#include <iostream>
enum class CommandMethod {
    GET,
    POST,
    PUT,
    DELETE
};

enum class CommandType {
    Register,
    Login,
    Logout,
    CasualMatchReady,
    CasualMatchOpponents,
    Invitation,
    StartMatch,
    RejectInvitation,
    Action,
    MatchStatus,
    Report,
    Profile,
    ReceivedInvitations,
    Reports,
    RankedMatchOpponents, 
    Block, 
    Penalty, 
    DismissReport
};

inline const std::map<std::string, CommandType> postCommands {
    {"register", CommandType::Register},
    {"login", CommandType::Login},
    {"logout", CommandType::Logout},
    {"casual_match_ready", CommandType::CasualMatchReady},
    {"invitation", CommandType::Invitation},
    {"start_match", CommandType::StartMatch},
    {"reject_invitation", CommandType::RejectInvitation},
    {"action", CommandType::Action},
    {"report", CommandType::Report},
    {"block", CommandType::Block},
    {"penalty", CommandType::Penalty},
    {"dismiss_report", CommandType::DismissReport}
};

inline const std::map<std::string, CommandType> getCommands {
    {"casual_match_opponents", CommandType::CasualMatchOpponents},
    {"match_status", CommandType::MatchStatus},
    {"profile", CommandType::Profile},
    {"received_invitations", CommandType::ReceivedInvitations},
    {"reports", CommandType::Reports}, 
    {"ranked_match_opponents", CommandType::RankedMatchOpponents},
};

inline const std::map<std::string, CommandType> putCommands {
};

inline const std::map<std::string, CommandType> deleteCommands {
};

struct Command{
    CommandMethod method;
    CommandType type;
    std::map<std::string, std::string> arguments;
};
#endif