#ifndef __RECEIVEDINVITATIONVIEW_HPP__
#define __RECEIVEDINVITATIONVIEW_HPP__

#include <iostream>
#include "MatchType.hpp"

struct ReceivedInvitationView{
    std::string senderUsername;
    MatchType matchType;
};

#endif