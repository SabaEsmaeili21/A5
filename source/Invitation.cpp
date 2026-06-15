#include <iostream>
#include "Invitation.hpp"
using namespace std;

string Invitation::GetSenderUsername() const{
    return senderUsername_;
}

bool Invitation::IsReceiver(std::string username) const{
    return username == receiverUsername_;
}

ReceivedInvitationView Invitation::ToReceivedInvitationView() const{
    return ReceivedInvitationView{senderUsername_, matchType_};
}
