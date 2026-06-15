#ifndef __USER_HPP__
#define __USER_HPP__

#include <string>

class User{
    public:
    User(std::string username, std::string password_): username_(username), password_(password_){}
    bool CheckPassword(std::string password) const;
    std::string Username() const;
    virtual ~User() = default;
    protected:
    std::string username_;
    std::string password_;

};

#endif