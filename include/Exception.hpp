#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <iostream>

class AppException : public std::exception {
    public:
    AppException(const std::string& error): error_(error){}
    std::string GetError () const {return error_;}
    private:
    std::string error_;
};

class NotFound : public AppException{
    public:
    NotFound() : AppException("Not Found"){}

};

class Empty : public AppException{
    public:
    Empty() : AppException("Empty"){}
};

class BadRequest : public AppException{
    public:
    BadRequest() : AppException("Bad Request"){}
};

class PermissionDenied : public AppException{
    public:
    PermissionDenied() : AppException("Permission Denied"){}
};


class LevelMismatch : public AppException{
    public:
    LevelMismatch() : AppException("Level Mismatch"){}
};


#endif