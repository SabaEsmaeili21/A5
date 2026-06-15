#ifndef __INVITATION_HPP__
#define __INVITATION_HPP__

#include <iostream>
#include <MatchType.hpp>
#include "IdGenerator.hpp"
#include "ReceivedInvitationView.hpp"

class Invitation{
    public:
    Invitation(std::string senderUsername, std::string receiverUsername, MatchType type):
    senderUsername_(senderUsername), receiverUsername_(receiverUsername), matchType_(type){}

    std::string GetSenderUsername() const;
    bool IsReceiver(std::string username) const;
    ReceivedInvitationView ToReceivedInvitationView() const;
    private:
    std::string senderUsername_;
    std::string receiverUsername_;
    MatchType matchType_;
};

#endif