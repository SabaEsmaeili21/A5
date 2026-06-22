#include "LoginManager.hpp"
#include "Exception.hpp"

void LoginManager::Login(Player& player)
{
    if (IsLoggedIn())
        throw PermissionDenied();

    currentPlayer_ = &player;
}

void LoginManager::Login(Admin& admin)
{
    if (IsLoggedIn())
        throw PermissionDenied();

    currentAdmin_ = &admin;
}

void LoginManager::Logout()
{
    if (!IsLoggedIn())
        throw PermissionDenied();

    currentPlayer_ = nullptr;
    currentAdmin_ = nullptr;
}

bool LoginManager::IsLoggedIn() const
{
    return currentPlayer_ != nullptr || currentAdmin_ != nullptr;
}

bool LoginManager::IsPlayerLoggedIn() const
{
    return currentPlayer_ != nullptr;
}

bool LoginManager::IsAdminLoggedIn() const
{
    return currentAdmin_ != nullptr;
}

Player& LoginManager::CurrentPlayer()
{
    if (currentPlayer_ == nullptr)
        throw PermissionDenied();

    return *currentPlayer_;
}

const Player& LoginManager::CurrentPlayer() const
{
    if (currentPlayer_ == nullptr) {
        throw PermissionDenied();
    }

    return *currentPlayer_;
}

Admin& LoginManager::CurrentAdmin()
{
    if (currentAdmin_ == nullptr)
        throw PermissionDenied();

    return *currentAdmin_;
}

const Admin& LoginManager::CurrentAdmin () const
{
    if (currentAdmin_ == nullptr)
        throw PermissionDenied();

    return *currentAdmin_;
}

User& LoginManager::CurrentUser()
{
    if (currentPlayer_ != nullptr)
        return *currentPlayer_;

    if (currentAdmin_ != nullptr)
        return *currentAdmin_;

    throw PermissionDenied();
}