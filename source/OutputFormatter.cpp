#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "OutputFormatter.hpp"
#include "Exception.hpp"

using namespace std;

string OutputFormatter::Ok(){
    return "OK\n";
}

string OutputFormatter::CasualMatchOpponents(vector<OpponentView> opponents,
    SortOrder sortOrder){
        sort(opponents.begin(), opponents.end(),[sortOrder](const auto& a, const auto& b){
            if (a.point != b.point)
                return sortOrder == SortOrder::ASC ? a.point < b.point
                    : a.point > b.point;

            return a.username < b.username;
        });
        string result;
        int i = 0;
        for(const auto& opponant : opponents){
            i++;
            result += to_string(i) + ". " + opponant.username + " with "
            + to_string(opponant.point) + " XP\n";
            
        }
        return result;
    }

std::string OutputFormatter::MatchStatus(MatchStatusView matchStatus){
    std::ostringstream out;

    out << "Turn " << matchStatus.turnNum << '\n';
    out << "You: " << MoveToString(matchStatus.yourMove) << '\n';
    out << "Your opponent: " << (matchStatus.opponentHasPlayed ? "played" : "pending") << '\n';
    out << "History:\n";
    out << left << setw(20) << "Opponent's moves:" << "Your moves:\n";
    /*setw means The next thing printed should occupy at least 20 characters.*/
    for(const auto& [opponentMove, yourMove] : matchStatus.history)
        out << left << setw(20) << MoveToString(opponentMove) << MoveToString(yourMove) << '\n';
    out << "Your remaining bullets: " << matchStatus.yourRemainingBullets << '\n';

    return out.str();
}

std::string OutputFormatter::MoveToString(Move move){
     switch (move)
    {
        case Move::SHOOT:
            return "shoot";

        case Move::DEFEND:
            return "defend";

        case Move::RELOAD:
            return "reload";

        case Move::PENDING:
            return "pending";
        default:
            throw BadRequest();
    }
}

std::string OutputFormatter::Profile(ProfileView profile){
    return "username: \"" + profile.username + "\"\n"
    + "XP: " + to_string(profile.xp) + "\n"
    + "Total wins: " + to_string(profile.totalWins) + "\n"
    + "Total losses: " + to_string(profile.totallosses) + "\n";
}

std::string OutputFormatter::ReceivedInvitations(std::map<int, ReceivedInvitationView> invitations){
    string result;
    for(const auto& [id, invitation] : invitations)
        result += to_string(id)
        + ": Invitation from \""
        + invitation.senderUsername
        + "\" for a \""
        + MatchTypeToString(invitation.matchType)
        + "\" match\n";
    return result;
}

std::string OutputFormatter::MatchTypeToString(MatchType matchType){
    if(matchType == MatchType::CASUAL)
        return "casual";
    throw BadRequest();
}

std::string OutputFormatter::Reports(std::map<int, ReportView> reports){
    string result;
    for(const auto& [id, report] : reports)
        result += to_string(id)
        + ": \"" + report.senderUsername
        + "\" reported \"" + report.reportedUsername
        + "\" for: \"" + report.reason
        + "\"\n";
    return result;
}

string OutputFormatter::RankedMatchOpponents(vector<OpponentView> opponents,
    SortOrder sortOrder){
        sort(opponents.begin(), opponents.end(),[sortOrder](const auto& a, const auto& b){
            if (a.point != b.point)
                return sortOrder == SortOrder::ASC ? a.point < b.point
                    : a.point > b.point;

            return a.username < b.username;
        });
        string result;
        int i = 0;
        for(const auto& opponant : opponents){
            i++;
            result += to_string(i) + ". " + opponant.username + " with "
            + to_string(opponant.point) + " RP\n";
            
        }
        return result;
    }