#ifndef __LOGINMANAGER_HPP__
#define __LOGINMANAGER_HPP__

#include "Player.hpp"
#include "Admin.hpp"

class LoginManager {
public:
    void Login(Player& player);
    void Login(Admin& admin);
    void Logout();

    bool IsLoggedIn() const;
    bool IsPlayerLoggedIn() const;
    bool IsAdminLoggedIn() const;

    User& CurrentUser();
    Player& CurrentPlayer();
    const Player& CurrentPlayer() const;
    Admin& CurrentAdmin();
    const Admin& CurrentAdmin() const;

private:
    Player* currentPlayer_ = nullptr;
    Admin* currentAdmin_ = nullptr;
};

#endif