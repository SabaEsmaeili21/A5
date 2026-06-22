#include <iostream>
#include <algorithm>
#include "InvitationsManager.hpp"
#include "Exception.hpp"
using namespace std;

void InvitationsManager::AddInvitation(std::string senderUsername,
    std::string receiverUsername, MatchType type){
    
    int id = IdGenerator::GenerateInvitationId();
    invitations_.emplace(id, Invitation(senderUsername, receiverUsername, type));
}

void InvitationsManager::Delete(int id){
    if (invitations_.erase(id) == 0)
        throw NotFound();
}

const Invitation& InvitationsManager::Find(int id) const{
    auto it = invitations_.find(id);
    if (it == invitations_.end())
        throw NotFound();
    return it->second;
}

std::map<int, ReceivedInvitationView> InvitationsManager::GetReceivedInvitations(std::string username) const{
    std::map<int, ReceivedInvitationView> invitations;
    for(const auto& [id, invitation] : invitations_){
        if(invitation.IsReceiver(username))
            invitations.emplace(id, invitation.ToReceivedInvitationView());
    }
    if(invitations.empty())
        throw Empty();
    return invitations;
}
