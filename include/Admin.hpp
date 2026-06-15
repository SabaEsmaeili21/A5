#ifndef __ADMIN_HPP__
#define __ADMIN_HPP__
#include <iostream>
#include "User.hpp"

class Admin : public User{
    public:
    Admin(std::string username, std::string password) : User(username, password){}
};
#endif