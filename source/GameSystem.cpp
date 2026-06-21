#include <iostream>
#include <map>
#include <algorithm>
#include "User.hpp"
#include "GameSystem.hpp"
#include "Exception.hpp"
#include "Penalty.hpp"
using namespace std;

void GameSystem::EnsurePlayerLoggedIn() const {
    if(!login_.IsPlayerLoggedIn())
        throw PermissionDenied();
    
}

void GameSystem::EnsureLoggedIn() const {
    if(!login_.IsLoggedIn())
        throw PermissionDenied();
}

void GameSystem::EnsureAdminLoggedIn() const {
    if(!login_.IsAdminLoggedIn())
        throw PermissionDenied();
}

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
    EnsurePlayerLoggedIn();

    if(status != "false" && status != "true")
        throw BadRequest();

    Player& player = login_.CurrentPlayer();

    player.SetCasualMatchReady(status == "true");
}

vector<OpponentView> GameSystem::CasualMatchOpponents() const{
    EnsurePlayerLoggedIn();
    return usersManager_.CasualMatchOpponents(login_.CurrentPlayer().Username());
}

void GameSystem::PostInvitation(std::string username, std::string matchTypeStr){
    EnsurePlayerLoggedIn();

    if(usersManager_.AdminExists(username))
        throw PermissionDenied();

    /*if(!usersManager_.PlayerExists(username))
        throw NotFound();*/

    if(matchTypeStr != "casual" && matchTypeStr != "ranked")
        throw BadRequest();
    
    Player& sender = login_.CurrentPlayer();
    Player& receiver = usersManager_.FindPlayer(username);
    if(receiver.HasBlocked(sender.Username()))
        return;

    invitationsManager_.AddInvitation(sender.Username(), username, GetMatchType.at(matchTypeStr));
}

void GameSystem::StartMatch(int invitationId){
    EnsurePlayerLoggedIn();
    Invitation& invitation = invitationsManager_.Find(invitationId);
    MatchType matchType = invitation.GetMatchType();

    Player& sender = usersManager_.FindPlayer(invitation.GetSenderUsername());
    Player& receiver = login_.CurrentPlayer();

    ValidateMatchStart(sender, receiver, invitation.GetMatchType(), invitationId);

    int matchId = CreateMatch(sender, receiver, matchType);
    MarkPlayersInMatch(sender, receiver, matchId);
    invitationsManager_.Delete(invitationId);
}

void GameSystem::ValidateMatchStart(const Player& sender, const Player& receiver,
MatchType matchType, int invitationId){
    if(receiver.IsInGame() || sender.IsInGame())
        throw PermissionDenied();
    if(!sender.IsRank(receiver.GetRank()) && matchType == MatchType::RANKED){
        invitationsManager_.Delete(invitationId);
        throw LevelMismatch();
    }
}

int GameSystem::CreateMatch(Player& sender, Player& receiver, MatchType matchType){
    switch(matchType){
        case(MatchType::CASUAL):
            return matchesManager_.AddCasualMatch(sender.Username(), receiver.Username());
        case(MatchType::RANKED):{

            const PlayerMatchStartState senderState =
                sender.GetRankedMatchStartState();

            const PlayerMatchStartState receiverState =
                receiver.GetRankedMatchStartState();

            int matchId = matchesManager_.AddRankedMatch(sender.Username(), receiver.Username(),
            senderState, receiverState);

            sender.ConsumeRankedMatchPenalties();
            receiver.ConsumeRankedMatchPenalties();

            return matchId;
        }
    }
    throw BadRequest();
}

void GameSystem::MarkPlayersInMatch(Player& sender, Player& receiver, int matchId){
    sender.StartMatch(matchId);
    receiver.StartMatch(matchId);
}

void GameSystem::RejectInvitation(int id){
    EnsurePlayerLoggedIn();
    invitationsManager_.Delete(id);
}

void GameSystem::ProcessMove(string actionStr){
    EnsurePlayerLoggedIn();
    if(actionStr != "defend" && actionStr != "reload" && actionStr != "shoot")
        throw BadRequest();

    Player& player = login_.CurrentPlayer();

    if(!player.IsInGame())
        throw NotFound();

    Match& match = matchesManager_.Find(player.CurrentMatchId());
    // Even if Match is abstract, you can still use a reference or pointer to Match.
    match.ProcessMove(GetMove.at(actionStr), player.Username());
    if(match.IsFinished())
        FinishMatch(match);

}

void GameSystem::FinishMatch(const Match& match){

    Player& winner = usersManager_.FindPlayer(match.WinnerUsername());
    Player& loser = usersManager_.FindPlayer(match.LoserUsername());

    if(match.Type() == MatchType::CASUAL){
        int deltaXp = CalculateXpChange(winner.Xp(), loser.Xp());
        winner.ApplyCasualWin(deltaXp);
        loser.ApplyCasualLoss(deltaXp);
    }

    else if(match.Type() == MatchType::RANKED){
        int healthBonus = match.GetHealthBonus();
        int deltaRp = winner.CalculateRpChange();
        winner.ApplyRankedWin(deltaRp, healthBonus);
        loser.ApplyRankedLoss(deltaRp);
    }

    winner.FinishMatch();
    loser.FinishMatch();
}

int GameSystem::CalculateXpChange(int xp1, int xp2){
    double deltaXp = 50.0 - 0.1 * (xp1 - xp2);
    return std::max(5, static_cast<int>(deltaXp));
}

MatchStatusView GameSystem::MatchStatus(){
    EnsurePlayerLoggedIn();
    Player& player = login_.CurrentPlayer();
    if(!player.IsInGame())
        throw NotFound();

    Match& match = matchesManager_.Find(player.CurrentMatchId());
    return match.MatchStatus(player.Username());
}

void GameSystem::AddReport(std::string username, std::string reason){
    EnsurePlayerLoggedIn();
    if(reason.empty())
        throw BadRequest();
    usersManager_.FindPlayer(username); //checking whether the player exists
    reportsManager_.AddReport(login_.CurrentPlayer().Username(), username, reason);
}

ProfileView GameSystem::GetProfile(std::string username) const{
    EnsureLoggedIn();
    if(login_.IsAdminLoggedIn() && username == "")
        throw PermissionDenied();
    if(login_.IsPlayerLoggedIn() && username == "")
        return login_.CurrentPlayer().GetProfile();
        
    if(usersManager_.AdminExists(username))
        throw PermissionDenied();

    Player& player = usersManager_.FindPlayer(username);

    return player.GetProfile();
}

std::map<int, ReceivedInvitationView> GameSystem::GetReceivedInvitations() const{
    EnsurePlayerLoggedIn();
    Player& player = login_.CurrentPlayer();
    return invitationsManager_.GetReceivedInvitations(player.Username());
}

std::map<int, ReportView> GameSystem::GetReports() const{
    EnsureAdminLoggedIn();
    return reportsManager_.GetReports();
}

std::vector<OpponentView> GameSystem::RankedMatchOpponents() const{
    EnsurePlayerLoggedIn();
    return usersManager_.RankedMatchOpponents(login_.CurrentPlayer().Username(), login_.CurrentPlayer().GetRank());
}

void GameSystem::Block(std::string username, std::string status){
    EnsurePlayerLoggedIn();

    if(usersManager_.AdminExists(username))
        throw BadRequest();

    Player& player = usersManager_.FindPlayer(username);

    if(status == "blocked")
        player.Block(username);
    
    else if(status == "unblocked")
        player.Unblock(username);

    else
        throw BadRequest();

}

void GameSystem::ApplyPenalty(int reportId, std::string type, int amount, int numOfMatches){
    EnsureAdminLoggedIn();
    
    const Report& report = reportsManager_.FindReport(reportId);
    Player& reportedPlayer = usersManager_.FindPlayer(report.ReportedUsername());

    if(type == "health_penalty")
    {
        reportedPlayer.ApplyHealthPenalty(amount, numOfMatches);
    }
    else if(type == "bullet_penalty")
    {
        reportedPlayer.ApplyBulletPenalty(amount, numOfMatches);
    }
    else
        throw BadRequest();
}

void GameSystem::DismissReport(int reportId){
    EnsureAdminLoggedIn();
    reportsManager_.Delete(reportId);
}

