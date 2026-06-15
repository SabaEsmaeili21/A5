#include <iostream>
#include <map>
#include <algorithm>
#include "User.hpp"
#include "GameSystem.hpp"
#include "Exception.hpp"

using namespace std;

void GameSystem::Register(string username, string password){
    if(login_.IsLoggedIn())
        throw PermissionDenied();
    Player& player = usersManager_.RegisterPlayer(username, password);
    login_.Login(player);
}

void GameSystem::Login(string username, string password){
    if(login_.IsLoggedIn())
        throw PermissionDenied();
    User* user = usersManager_.FindUser(username);
    if(!(user->CheckPassword(password)))
        throw PermissionDenied();
    login_.Login(*user);
}

void GameSystem::Logout(){
    login_.Logout();
}

void GameSystem::CasualMatchReady(std::string status){
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();

    if(status != "false" && status != "true")
        throw BadRequest();

    Player& player = login_.CurrentPlayer();

    if(status == "true")
        player.SetCasualMatchReady(true);
    else 
        player.SetCasualMatchReady(false);
}

vector<OpponentView> GameSystem::CasualMatchOpponents() const{
    if (!login_.IsPlayerLoggedIn()) 
        throw PermissionDenied();
    
    return usersManager_.CasualMatchOpponents(login_.CurrentPlayer().Username());
}

void GameSystem::PostInvitation(std::string username, std::string matchTypeStr){
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();
    Player* player = dynamic_cast<Player*>(usersManager_.FindUser(username));
    if(!player)
        throw PermissionDenied();
    if(matchTypeStr != "casual")
        throw BadRequest();
    invitationsManager_.AddInvitation(login_.CurrentPlayer().Username(), username, GetMatchType.at(matchTypeStr));
}

void GameSystem::StartMatch(int id){
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();
    Invitation& invitation = invitationsManager_.Find(id);
    Player& sender = usersManager_.FindPlayer(invitation.GetSenderUsername());
    Player& receiver = login_.CurrentPlayer();
    StartMatchBetween(sender, receiver);
    invitationsManager_.Delete(id);
}

void GameSystem::StartMatchBetween(Player& sender, Player& receiver){

    if(receiver.IsInGame() || sender.IsInGame())
        throw PermissionDenied();

    int matchId = matchesManager_.AddMatch(Match(sender.Username(), receiver.Username()));
    sender.StartMatch(matchId);
    receiver.StartMatch(matchId);
}

void GameSystem::RejectInvitation(int id){
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();
    invitationsManager_.Delete(id);
}

void GameSystem::ProcessMove(string actionStr){
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();
    if(actionStr != "defend" && actionStr != "reload" && actionStr != "shoot")
        throw BadRequest();

    Player& player = login_.CurrentPlayer();

    if(!player.IsInGame())
        throw NotFound();

    Match& match = matchesManager_.Find(player.CurrentMatchId());
    match.ProcessMove(GetMove.at(actionStr), player.Username());
    if(match.IsFinished())
        FinishMatch(match);

}

void GameSystem::FinishMatch(const Match& match){

    Player& winner = usersManager_.FindPlayer(match.WinnerUsername());
    Player& loser = usersManager_.FindPlayer(match.LoserUsername());

    int deltaXp = CalculateXpChange(winner.Xp(), loser.Xp());
    winner.ApplyWin(deltaXp);
    loser.ApplyLoss(deltaXp);

    winner.FinishMatch();
    loser.FinishMatch();
}

int GameSystem::CalculateXpChange(int xp1, int xp2){
    double deltaXp = 50.0 - 0.1 * (xp1 - xp2);
    return std::max(5, static_cast<int>(deltaXp));
}

MatchStatusView GameSystem::MatchStatus(){
    if (!login_.IsPlayerLoggedIn()) 
        throw PermissionDenied();
    Player& player = login_.CurrentPlayer();
    if(!player.IsInGame())
        throw NotFound();

    Match& match = matchesManager_.Find(player.CurrentMatchId());
    return match.MatchStatus(player.Username());
}

void GameSystem::Report(std::string username, std::string reason){
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();
    if(reason.empty())
        throw BadRequest();
    usersManager_.FindPlayer(username); //checking whether the player exists
    reportsManager_.AddReport(login_.CurrentPlayer().Username(), username, reason);
}

ProfileView GameSystem::GetProfile(std::string username) const{
    if(!login_.IsLoggedIn())
        throw PermissionDenied();
    if(login_.IsAdminLoggedIn() && username == "")
        throw PermissionDenied();
    if(login_.IsPlayerLoggedIn() && username == "")
        return login_.CurrentPlayer().GetProfile();
    Player* player = dynamic_cast<Player*>(usersManager_.FindUser(username));
    if(!player)
        throw PermissionDenied();

    return player->GetProfile();
}

std::map<int, ReceivedInvitationView> GameSystem::GetReceivedInvitations() const{
    if (!login_.IsPlayerLoggedIn()) 
        throw PermissionDenied();
    Player& player = login_.CurrentPlayer();
    return invitationsManager_.GetReceivedInvitations(player.Username());
}

std::map<int, ReportView> GameSystem::GetReports() const{
    if(!login_.IsAdminLoggedIn())
        throw PermissionDenied();
    return reportsManager_.GetReports();
}

std::vector<OpponentView> GameSystem::RankedMatchOpponents() const{
    if (!login_.IsPlayerLoggedIn()) 
        throw PermissionDenied();
    
    return usersManager_.RankedMatchOpponents(login_.CurrentPlayer().Username(), login_.CurrentPlayer().GetRank());
}
