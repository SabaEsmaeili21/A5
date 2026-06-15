#include <iostream>
#include "LoginManager.hpp"
#include "Exception.hpp"

using namespace std;

void LoginManager::Login(User& User){
    if(currentUser_ != nullptr)
        throw PermissionDenied();
    currentUser_ = &User;
}

bool LoginManager::IsLoggedIn() const{
    return currentUser_ != nullptr;
}

void LoginManager::Logout(){
    if(currentUser_ == nullptr)
        throw PermissionDenied();
    currentUser_ = nullptr;
}

User* LoginManager::CurrentUser() const{
    if(currentUser_ == nullptr)
        throw PermissionDenied();
    return currentUser_;
}

bool LoginManager::IsPlayerLoggedIn() const {
    return dynamic_cast<Player*>(currentUser_) != nullptr;
}

bool LoginManager::IsAdminLoggedIn() const {
    return dynamic_cast<Admin*>(currentUser_) != nullptr;
}

Player& LoginManager::CurrentPlayer() const {
    User* user = CurrentUser();

    Player* player = dynamic_cast<Player*>(user);
    if (!player)
        throw PermissionDenied();

    return *player;
}
Admin& LoginManager::CurrentAdmin() const{
    User* user = CurrentUser();

    Admin* admin = dynamic_cast<Admin*>(user);
    if (!admin)
        throw PermissionDenied();

    return *admin;
}
