#ifndef __GAMESYSTEM_HPP__
#define __GAMESYSTEM_HPP__

#include <iostream>
#include <map>
#include <memory>
#include "UsersManager.hpp"
#include "LoginManager.hpp"
#include "SortOrder.hpp"
#include "InvitationsManager.hpp"
#include "MatchesManager.hpp"
#include "MatchStatusView.hpp"
#include "ReportsManager.hpp"
#include "ProfileView.hpp"
#include "ReceivedInvitationView.hpp"
#include "ReportView.hpp"

class GameSystem{
    public:
    GameSystem(std::map<std::string, Player>& players, std::map<std::string, Admin>& admins)
        : usersManager_(players, admins) {}
    void Register(std::string username, std::string password);
    void Login(std::string username, std::string password);
    void Logout();
    void CasualMatchReady(std::string status);
    std::vector<CasualOpponent> CasualMatchOpponents() const;
    void PostInvitation(std::string username, std::string matchType);
    void StartMatch(int id);
    void RejectInvitation(int id);
    void ProcessMove(std::string actionStr);
    MatchStatusView MatchStatus();
    void Report(std::string username, std::string reason);
    ProfileView GetProfile(std::string username) const;
    std::map<int, ReceivedInvitationView> GetReceivedInvitations() const;
    std::map<int, ReportView> GetReports() const;

    private:
    void StartMatchBetween(Player& sender, Player& receiver);
    void FinishMatch(const Match& match);
    int CalculateXpChange(int xp1, int xp2);
    LoginManager login_;
    UsersManager usersManager_;
    InvitationsManager invitationsManager_;
    MatchesManager matchesManager_;
    ReportsManager reportsManager_;

};

#endif