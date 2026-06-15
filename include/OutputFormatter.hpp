#ifndef __OUTPUTFORMATTER_HPP__
#define __OUTPUTFORMATTER_HPP__
#include <iostream>
#include <vector>
#include <map>
#include "SortOrder.hpp"
#include "OpponentView.hpp"
#include "MatchStatusView.hpp"
#include "ProfileView.hpp"
#include "ReceivedInvitationView.hpp"
#include "MatchType.hpp"
#include "ReportView.hpp"

class OutputFormatter{
    public:
    std::string static Ok();
    std::string static CasualMatchOpponents(std::vector<OpponentView> Opponent, SortOrder sortOrder);
    std::string static MatchStatus(MatchStatusView matchStatus);
    std::string static Profile(ProfileView profile);
    std::string static ReceivedInvitations(std::map<int, ReceivedInvitationView> invitations);
    std::string static Reports(std::map<int, ReportView> reports);
    std::string static RankedMatchOpponents(std::vector<OpponentView> Opponent, SortOrder sortOrder);
    private:
    std::string static MoveToString(Move move);
    std::string static MatchTypeToString(MatchType matchType);

};
#endif