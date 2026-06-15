#ifndef __INVITATIONSMANAGER_HPP__
#define __INVITATIONSMANAGER_HPP__

#include <iostream>
#include <map>
#include <memory>
#include "Player.hpp"
#include "MatchType.hpp"
#include "Invitation.hpp"
#include "ReceivedInvitationView.hpp"

class InvitationsManager{
    public:
    InvitationsManager() = default; //Generate the normal default constructor.
    // vector constructor already ran before this 
    void AddInvitation(std::string senderUsername, std::string receiverUsername, MatchType type);
    void Delete(int id);
    Invitation& Find(int id);
    std::map<int, ReceivedInvitationView> GetReceivedInvitations(std::string username) const;

    private:
    std::map<int, Invitation> invitations_; 
};

#endif