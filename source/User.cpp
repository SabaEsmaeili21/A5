#include <iostream>
#include "User.hpp"

using namespace std;

bool User::CheckPassword(string password)const{
    return password == password_;
}

string User::Username()const{
    return username_;
}