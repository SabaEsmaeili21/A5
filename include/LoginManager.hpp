#ifndef __LOGINMANAGER_HPP__
#define __LOGINMANAGER_HPP__
#include <iostream>
#include "User.hpp"
#include "Player.hpp"
#include "Admin.hpp"

class LoginManager{
    public:
    void Login(User& User);
    bool IsLoggedIn() const;
    void Logout();
    User* CurrentUser() const;
    bool IsPlayerLoggedIn() const;
    bool IsAdminLoggedIn() const;
    Player& CurrentPlayer() const;
    Admin& CurrentAdmin() const;

    private:
    User* currentUser_ = nullptr;
};
#endif