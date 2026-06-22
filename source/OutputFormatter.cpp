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
        return FormatOpponents(opponents,sortOrder,"XP");
    }

string OutputFormatter::MatchStatus(const MatchStatusView& matchStatus){
    ostringstream out;

    out << "Turn " << matchStatus.turnNum << '\n';
    out << "You: " << MoveToString(matchStatus.yourMove) << '\n';
    out << "Your opponent: " << (matchStatus.opponentHasPlayed ? "played" : "pending") << '\n';
    out << "History:\n";
    out << left << setw(20) << "Opponent's moves:" << "Your moves:\n";

    for(const auto& [opponentMove, yourMove] : matchStatus.history)
        out << left << setw(20) << MoveToString(opponentMove) << MoveToString(yourMove) << '\n';

    out << "Your remaining bullets: " << matchStatus.yourRemainingBullets << '\n';

    if (matchStatus.yourRemainingHealth.has_value()) {
        out << "Your remaining health: "
            << matchStatus.yourRemainingHealth.value()
            << '\n';
    }

    return out.str();
}

string OutputFormatter::MoveToString(Move move){
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

string OutputFormatter::Profile(const ProfileView& profile){
    return "username: \"" + profile.username + "\"\n"
    + "Level: " + RankToString(profile.rank) + "\n"
    + "RP: " + to_string(profile.rp) + "\n"
    + "XP: " + to_string(profile.xp) + "\n"
    + "Total wins: " + to_string(profile.totalWins) + "\n"
    + "Total losses: " + to_string(profile.totalLosses) + "\n";
}

string OutputFormatter::ReceivedInvitations(const map<int, ReceivedInvitationView>& invitations){
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

string OutputFormatter::MatchTypeToString(MatchType matchType){
    if(matchType == MatchType::CASUAL)
        return "casual";

    if(matchType == MatchType::RANKED)
        return "ranked";

    throw BadRequest();
}

string OutputFormatter::Reports(const map<int, ReportView>& reports){
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
        return FormatOpponents(opponents,sortOrder,"RP");
}

string OutputFormatter::RankToString(Rank rank)
{
    switch (rank) {
        case Rank::Bronze:
            return "Bronze";

        case Rank::Silver:
            return "Silver";

        case Rank::Gold:
            return "Golden";

        case Rank::Platinum:
            return "Platinum";
    }

    throw BadRequest();
}

string OutputFormatter::FormatOpponents(vector<OpponentView>& opponents,
    const SortOrder& sortOrder,string pointName) {
    sort(
        opponents.begin(),
        opponents.end(),
        [sortOrder](const OpponentView& first,
                    const OpponentView& second) {
            if (first.point != second.point) {
                if (sortOrder == SortOrder::ASC) {
                    return first.point < second.point;
                }

                return first.point > second.point;
            }

            return first.username < second.username;
        }
    );

    ostringstream out;

    for (size_t index = 0; index < opponents.size(); ++index) {
        out << index + 1
            << ". "
            << opponents[index].username
            << " with "
            << opponents[index].point
            << ' '
            << pointName
            << '\n';
    }

    return out.str();
}